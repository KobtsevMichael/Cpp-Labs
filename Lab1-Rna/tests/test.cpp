#include "gtest/gtest.h"
#include "gmock/gmock.h"

#include "../src/rna.h"

using testing::Eq;

class OperatorsTests: public testing::Test {};
class MemoryTest: public testing::Test {};
class TimeTests: public testing::Test {};


TEST_F(OperatorsTests, index_operator) {
    RNA a("TGTCGG");
    a[4] = a[3] = A;

    char* chain = a.getString();
    ASSERT_STREQ(chain, "TGTAAG") << "INDEX error";
    delete[] chain;
}

TEST_F(OperatorsTests, const_index_operator) {
    const RNA a(C, 5);
    Nucl k = a[2];

    ASSERT_EQ(k, a[2]) << "CONST INDEX error";
}

TEST_F(OperatorsTests, not_sum_operators) {
    RNA a("TAGTCC");
    RNA b("TTTTTT");
    RNA c;
    c = !a + !b;

    char* chain = c.getString();
    ASSERT_STREQ(chain, "ATCAGGAAAAAA") << "NOT & SUM error";
    delete[] chain;
}

TEST_F(OperatorsTests, is_complementary_method) {
    RNA a("GACCTAGGGG");
    RNA b("CTGGATCCCC");
    RNA c("TCAT");

    EXPECT_TRUE(a.isComplementary(b)) << "IS COMPLEMETARY 1 error";
    EXPECT_FALSE(a.isComplementary(c)) << "IS COMPLEMETARY 2 error";
}

TEST_F(OperatorsTests, split_method) {
    RNA a(C, 12);
    a.add(G);
    a.add(T);
    a.add(A);
    a.add(G);

    RNA b = a.split(4);
    RNA c = a.split(0);

    char* chain_b = b.getString();
    ASSERT_STREQ(chain_b, "CCCCCCCCGTAG") << "SPLIT 1 error";
    delete[] chain_b;

    char* chain_c = c.getString();
    ASSERT_STREQ(chain_c, "CCCCCCCCCCCCGTAG") << "SPLIT 2 error";
    delete[] chain_c;
}

TEST_F(MemoryTest, million_nuls) {
    RNA a;
    for (int_t i=0; i < 1000000; ++i) {
        a.addPlus(G);
        ASSERT_LE(a.getCapacity(), 1000000/4/sizeof(byte));
    }
}

TEST_F(TimeTests, million_nuls_sum) {
    RNA a;
    for (int_t i=0; i < 1000000; ++i) {
        a.addPlus(G);
    }
}

TEST_F(TimeTests, million_nuls_mul) {
    RNA a;
    for (int_t i=0; i < 1000000; ++i) {
        a.add(G);
    }
}