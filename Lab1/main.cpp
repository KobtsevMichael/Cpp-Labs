#include <iostream>
using namespace std;

enum Nucl {A, G, C, T, Empty};


class RNA {

private:
    char *chain = nullptr;
    int capacity = 0;
    int size = 0;

    short getNucl(int index) {
        if (0 <= index && index < size) {
            char block = chain[index/4];
            block >>= 2*(3 - (index%4));
            return block & 0x03;
        }
        return Empty;
    }

public:
    RNA() {}

    RNA(Nucl nucl, int quantity) {
        addNucles(nucl, quantity);
    }
    RNA(const RNA &other) {

    }
    ~RNA() {
        if (chain != nullptr) {
            delete[] chain;
        }
    }

    void addNucles(Nucl nucl, int quantity) {

        if (quantity <= 0) {
            return;
        }

        if (chain == nullptr) {
            capacity = quantity;
            chain = new char[capacity/4 + 1];
            chain[capacity/4 + 1] = 0;
        }

        int iter = size/4;
        unsigned char cur_byte = 0;

        for (int i=size, j=0; i < size + quantity; i++, j+=2) {

            if (i > capacity) {
                capacity *= 2;
                realloc(chain, sizeof(char)*(capacity/4 + 1));
            }

            if (!(i % 4) && i != 0) {
                chain[iter++] = cur_byte;
                cur_byte = 0;
                j = 0;
            }
            if (nucl % 2) {
                cur_byte |= (1 << j);
            }
            if (nucl / 2) {
                cur_byte |= (1 << (j+1));
            }
        }
        cur_byte <<= 2*(4 - (size+quantity)%4);
        chain[iter] = cur_byte;
        size += quantity;
    }
    void printChain() {
        for (int i=0; i < size; ++i) {
            switch (getNucl(i)) {
                case 0: cout << "A"; break;
                case 1: cout << "G"; break;
                case 2: cout << "C"; break;
                case 3: cout << "T";
            }
        }
        cout << endl;
    }

    RNA& operator =(const RNA &other) {
        return *this;
    }
    RNA operator +(const RNA &other){
        RNA tmp;
        return tmp;
    }
    Nucl operator [](int index) {
        return (Nucl)getNucl(index);
    }
};

int main() {

    RNA a;

    a.addNucles(T, 13);
    a.printChain();

    // char *chain = new char[3] {0x0E, 0x6F, 0x02};

    // delete [] chain;

    return 0;
}
