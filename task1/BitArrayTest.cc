#include <gtest/gtest.h>
#include "BitArray.h"
#include "BitArray.cpp"

TEST(BitArray, CopyConstructor) {
    auto bits1 = BitArray<size_t>();
    for (int i = 0; i < 50; i++) {
        bits1.pushBack(true);
    }
    auto bits2 = BitArray<size_t>(bits1);
    EXPECT_TRUE(bits2 == bits1);
}

TEST(BitArray, Swap) {
    BitArray<long> bits1;
    for (int i = 0; i < 10; i++) {
        bits1.pushBack(true);
    }
    auto bits2 = ~bits1;
    BitArray<long> old_bits1;
    old_bits1 = bits1;
    bits2.swap(bits1);
    EXPECT_TRUE(~bits1 == old_bits1);
}

TEST(BitArray, None) {
    auto bits = BitArray<long>();
    for (int i = 0; i < 5; i++) {
        bits.pushBack(false);
    }
    EXPECT_TRUE(bits.none());

}

TEST(BitArray, Any) {
    auto bits = BitArray<long>();
    for (int i = 0; i < 5; i++) {
        bits.pushBack(false);
    }
    bits.set(4, true);
    EXPECT_TRUE(bits.any());
}

TEST(BitArray, Resize) {
    auto bits = BitArray<double>(100);
    bits.resize(20);
    EXPECT_EQ(bits.size(), 20);
}

TEST(BitArray, Clear) {
    auto bits = BitArray<double>(100);
    bits.clear();
    EXPECT_EQ(bits.size(), 0);
}



TEST(BitArray, BitWiseToString) {
    auto bits1 = BitArray<char>(8);
    for (int i = 0; i < bits1.size(); i += 2) {
        bits1.set(i, true);
    }
    auto bits2 = ~bits1;
    auto resAnd = bits2 & bits1;
    EXPECT_TRUE(resAnd.none());
    auto resOr = bits2 | bits1;
    EXPECT_TRUE(resOr.toString()[0] == char(255));
    auto resXor = bits2 ^ bits1;
    EXPECT_TRUE(resOr == resXor);
    auto resNot = ~bits1;
    EXPECT_TRUE(bits2 == resNot);
    bits2.reset();
    bits2.set(0, true);
    EXPECT_TRUE((bits2 >> 2).toString()[0] == char(32));
    bits2 >>= 2;
    EXPECT_TRUE((bits2 << 2).toString()[0] == char(128));
    bits2 <<= 2;
    bits2 >>= 0;
    EXPECT_TRUE(bits2.toString()[0] == char(128));
}

TEST(BitArray, Count) {
    auto bits = BitArray<long long>(100);
    bits.reset();
    for (int i = 0; i < bits.size(); i++) {
        if (i % 10 == 0) {
            bits.set(i, true);
        }
    }
    EXPECT_EQ(bits.count(), 10);
}

TEST(BitArray, Empty) {
    BitArray<int> bits;
    EXPECT_TRUE(bits.empty());
    bits.resize(40);
    bits.set();
    EXPECT_EQ(bits.count(), 40);
}


TEST(BitArray, Reset) {
    BitArray<int> bits;
    EXPECT_TRUE(bits.empty());
    bits.resize(40);
    bits.reset();
    EXPECT_EQ(bits.count(), 0);
}


TEST(BitArray, Push) {
    BitArray<long long> bits;
    for (int i = 0; i < 1000; i++) {
        bits.pushBack(true);
    }
    EXPECT_EQ(bits.count(), 1000);
    bits.resize(0);
    for (int i = 0; i < 100; i++) {
        bits.pushBack(true);
    }
    EXPECT_EQ(bits.count(), 100);
    bits.clear();
    for (int i = 0; i < 10; i++) {
        bits.pushBack(false);
    }
    EXPECT_EQ(bits.count(), 0);
}