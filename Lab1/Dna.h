#ifndef LAB1_DNA_H
#define LAB1_DNA_H

class DNA {
public:
    RNA right;
    RNA left;

    DNA(RNA &right, RNA &left) : right(right), left(left) {}
};

#endif //LAB1_DNA_H
