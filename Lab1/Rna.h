#ifndef LAB1_RNA_H
#define LAB1_RNA_H
#include <stdint.h>

typedef uint8_t byte;
typedef int8_t short_t;
typedef int32_t int_t;

enum Nucl {A, G, C, T};

class RNA {
private:

    byte *chain;
    int_t capacity;
    int_t size;

    int_t arr_len(double) const;
    short_t get(int_t);
    void fill(Nucl, int_t);

    class NuclReference {
    private:
        int_t index;
        RNA *rna;
    public:
        NuclReference(int_t index, RNA &rna) : index(index), rna(&rna) {}

        NuclReference& operator = (Nucl);
        NuclReference& operator = (NuclReference&);
        operator Nucl();
    };
public:

    RNA() : chain(nullptr), capacity(0), size (0) {}
    RNA(Nucl, int_t);
    RNA(const RNA&);

    ~RNA();

    void add(Nucl);
    bool isComplementary(const RNA&);
    RNA  split(int_t);

    void print();

    RNA& operator =  (const RNA&);
    bool operator == (const RNA&) const;
    bool operator != (const RNA&) const;
    RNA  operator +  (const RNA&) const;
    RNA  operator !  ()           const;

    NuclReference operator [] (int_t);
};

#endif //LAB1_RNA_H