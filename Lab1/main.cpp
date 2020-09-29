#include <iostream>
#include <string.h>
#include <math.h>

using namespace std;
typedef unsigned char byte;

enum Nucl {A, G, C, T, EMPTY};


class RNA {
private:

    byte *chain;
    int capacity;
    int size;

    short get(int index) {
        if (0 <= index && index < size) {
            byte block = chain[index/4];
            block >>= 2*(3 - index%4);
            return block & 0x03;
        }
        return EMPTY;
    }
    void fill(Nucl nucl, int quantity) {

        byte block = 0;

        for (int i=0, j=0; i < quantity; ++i) {

            block |= nucl << 2*(3 - i%4);

            if (i % 4 == 3 || i == quantity-1) {
                chain[j++] = block;
                block = 0;
            }
        }

        size = quantity;
        capacity = quantity;
    }
    int arr_len(double quantity) const {
        return ceil(quantity/4);
    }
public:
    RNA() {
        chain = NULL;
        capacity = 0;
        size = 0;
    }

    RNA(Nucl nucl, int quantity) {
        if (quantity > 0) {
            chain = new byte[arr_len(quantity)];
            fill(nucl, quantity);
        }
        else {
            RNA();
        }
    }
    RNA(const RNA &other) {
        this->capacity = other.capacity;
        this->size = other.size;
        this->chain = new byte[arr_len(other.capacity)];
        memcpy(this->chain, other.chain, sizeof(byte)*arr_len(other.capacity));
    }
    ~RNA() {
        delete[] chain;
    }

    void add(Nucl nucl) {

        // Довыделение памяти
        if (size == capacity) {
            capacity = (capacity) ? capacity*2 : 32;
            realloc(chain, sizeof(byte)*arr_len(capacity));
            memset(&chain[arr_len(capacity/2)], 0, sizeof(byte)*arr_len(capacity/2));
        }

        chain[size/4] |= nucl << 2*(3 - size%4);
        size++;
    }
    void print() {
        for (int i=0; i < size; ++i) {
            switch (get(i)) {
                case 0: cout << "A"; break;
                case 1: cout << "G"; break;
                case 2: cout << "C"; break;
                case 3: cout << "T"; break;
                case 4: cout << "_";
            }
        }
        cout << endl;
    }
    bool isComplementary(const RNA &other) {
        return *this == !other;
    }

    RNA& operator =  (const RNA &);
    Nucl operator [] (int);

    bool operator == (const RNA &) const;
    bool operator != (const RNA &) const;
    RNA  operator +  (const RNA &) const;
    RNA  operator !  ()            const;
};


RNA& RNA::operator = (const RNA &other) {
    this->capacity = other.capacity;
    this->size = other.size;

    delete[] this->chain;
    this->chain = new byte[arr_len(other.capacity)];
    memcpy(this->chain, other.chain, sizeof(byte)*arr_len(other.capacity));

    return *this;
}

Nucl RNA::operator [] (int index) {
    return (Nucl)get(index);
};

bool RNA::operator == (const RNA &other) const {
    if (this->size != other.size) {
        return false;
    }
    for (int i=0; i < arr_len(this->size); ++i) {
        if (this->chain[i] != other.chain[i]) {
            return false;
        }
    }
    return true;
}

bool RNA::operator != (const RNA &other) const {
    return !(*this == other);
}

RNA RNA::operator + (const RNA &other) const {

    if (this->size + other.size == 0) {
        return RNA();
    }

    RNA tmp;
    tmp.capacity = this->capacity + other.capacity;
    tmp.size = this->size + other.size;
    tmp.chain = new byte[arr_len(tmp.capacity)];

    memcpy(tmp.chain, this->chain, sizeof(byte)*arr_len(other.size));
    memcpy(&tmp.chain[arr_len(this->size)], other.chain, sizeof(byte)*arr_len(other.size));

    short shift = this->size % 4;
    if (shift) {
        for (int i=this->size/4; i < arr_len(tmp.size); ++i) {
            tmp.chain[i] |= tmp.chain[i+1] >> 2*shift;
        }
    }
    return tmp;
}

RNA RNA::operator ! () const {

    RNA tmp = *this;

    for (int i=0; i < arr_len(tmp.size); ++i) {
        tmp.chain[i] = ~tmp.chain[i];
    }

    // Обнуление хвоста последнего байта
    tmp.chain[tmp.size/4] >>= 2*(3 - tmp.size%4);
    tmp.chain[tmp.size/4] <<= 2*(3 - tmp.size%4);

    return tmp;
}


class DNA {
public:
    RNA right;
    RNA left;

    DNA(RNA &right, RNA &left) {
        this->right = right;
        this->left = left;
    }
};


int main() {

    RNA a(A, 4);
    RNA c(A, 5);

    a.add(A);
    a.add(T);
    a.add(G);
    a.add(C);

    c.add(T);
    c.add(G);
    c.add(C);

    c.print();

    cout << (a == c);

    DNA d(a, c);

    return 0;
}
