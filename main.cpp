#include <gtest/gtest.h>
#include "list.h"

TEST(ListTest, CopyConstructor) {
    List l0;
    l0.push_back(1);
    l0.push_back(2);
    l0.push_back(3);
    
    List lcopy(l0);
    
    EXPECT_EQ(lcopy.size(), 3);
    
    auto it = lcopy.begin();
    EXPECT_DOUBLE_EQ(*it, 1);
    ++it;
    EXPECT_DOUBLE_EQ(*it, 2);
    ++it;
    EXPECT_DOUBLE_EQ(*it, 3);
}

TEST(ListTest, MoveConstructor) {
    List l0;
    l0.push_back(1);
    l0.push_back(2);
    l0.push_back(3);
    
    List lcopy(l0);
    List l(std::move(lcopy));
    
    EXPECT_EQ(l.size(), 3);
    EXPECT_EQ(lcopy.size(), 0);
    
    auto it = l.begin();
    EXPECT_DOUBLE_EQ(*it, 1);
    ++it;
    EXPECT_DOUBLE_EQ(*it, 2);
    ++it;
    EXPECT_DOUBLE_EQ(*it, 3);
}

TEST(ListTest, IteratorOperations) {
    List l;
    l.push_back(1);
    l.push_back(2);
    l.push_back(3);
    
    auto iter = l.begin();
    EXPECT_DOUBLE_EQ(*iter, 1);
    
    ++iter;
    *iter = 55.5;
    EXPECT_DOUBLE_EQ(*iter, 55.5);
    
    auto last_iter = --l.end();
    EXPECT_DOUBLE_EQ(*last_iter, 3);
    *last_iter = 9.9;
    EXPECT_DOUBLE_EQ(*last_iter, 9.9);
}

TEST(ListTest, PushBefore) {
    List l;
    l.push_back(1);
    l.push_back(55.5);
    l.push_back(9.9);
    
    auto iter_pb = l.begin();
    l.push_before(iter_pb, 5.60);
    EXPECT_DOUBLE_EQ(*l.begin(), 5.60);
    
    iter_pb = l.begin();
    l.push_before(++iter_pb, 8.12);
    
    auto it = l.begin();
    EXPECT_DOUBLE_EQ(*it, 5.60);
    ++it;
    EXPECT_DOUBLE_EQ(*it, 8.12);
    ++it;
    EXPECT_DOUBLE_EQ(*it, 1);
}

TEST(ListTest, PushAfter) {
    List l;
    l.push_back(5.6);
    l.push_back(8.12);
    l.push_back(1);
    l.push_back(55.5);
    l.push_back(9.9);
    
    auto iter_pa = --l.end();
    l.push_after(iter_pa, 2.8);
    EXPECT_DOUBLE_EQ(*(--l.end()), 2.8);
    
    iter_pa = --l.end();
    l.push_after(--iter_pa, 4.);
    
    auto it = l.begin();
    for (int i = 0; i < 5; ++i) ++it;
    EXPECT_DOUBLE_EQ(*it, 4.);
    ++it;
    EXPECT_DOUBLE_EQ(*it, 2.8);
}

TEST(ListTest, PopOperations) {
    List l;
    l.push_back(5.6);
    l.push_back(8.12);
    l.push_back(1);
    l.push_back(55.5);
    l.push_back(9.9);
    l.push_back(4);
    l.push_back(2.8);
    
    auto iter_pop_b = l.begin();
    l.push_before(iter_pop_b, 77.);
    EXPECT_DOUBLE_EQ(*l.begin(), 77.);
    
    iter_pop_b = l.begin();
    l.pop(iter_pop_b);
    EXPECT_DOUBLE_EQ(*l.begin(), 5.6);
    
    auto iter_pop_e = --l.end();
    l.push_after(iter_pop_e, 88.);
    EXPECT_DOUBLE_EQ(*(--l.end()), 88.);
    
    iter_pop_e = --l.end();
    l.pop(iter_pop_e);
    EXPECT_DOUBLE_EQ(*(--l.end()), 2.8);
    
    auto iter_pop_mid = ++(++l.begin());
    l.push_before(iter_pop_mid, 66.);
    
    auto it = l.begin();
    ++it; ++it;
    EXPECT_DOUBLE_EQ(*it, 66.);
    
    l.pop(--iter_pop_mid);
    
    it = l.begin();
    EXPECT_DOUBLE_EQ(*it, 5.6);
    ++it;
    EXPECT_DOUBLE_EQ(*it, 8.12);
    ++it;
    EXPECT_DOUBLE_EQ(*it, 1);
}

TEST(ListTest, PushFrontBack) {
    List l;
    l.push_back(5.6);
    l.push_back(8.12);
    l.push_back(1);
    l.push_back(55.5);
    l.push_back(9.9);
    l.push_back(4);
    
    EXPECT_EQ(l.size(), 6);
    
    l.push_front(5.8);
    EXPECT_DOUBLE_EQ(*l.begin(), 5.8);
    EXPECT_EQ(l.size(), 7);
}

TEST(ListTest, PopFrontBack) {
    List l;
    l.push_back(5.8);
    l.push_back(5.6);
    l.push_back(8.12);
    l.push_back(1);
    l.push_back(55.5);
    l.push_back(9.9);
    l.push_back(4);
    l.push_back(2.8);
    
    EXPECT_EQ(l.size(), 8);
    
    l.pop_back();
    EXPECT_DOUBLE_EQ(*(--l.end()), 4);
    EXPECT_EQ(l.size(), 7);
    
    l.pop_front();
    EXPECT_DOUBLE_EQ(*l.begin(), 5.6);
    EXPECT_EQ(l.size(), 6);
}

TEST(ListTest, ClearList) {
    List l;
    l.push_back(1);
    l.push_back(2);
    l.push_back(3);
    
    EXPECT_EQ(l.size(), 3);
    
    l.clear();
    EXPECT_EQ(l.size(), 0);
    EXPECT_EQ(l.begin(), l.end());
}

TEST(ListTest, EmptyList) {
    List l;
    EXPECT_EQ(l.size(), 0);
    EXPECT_EQ(l.begin(), l.end());
}

TEST(ListTest, EdgeCases) {
    List l;
    
    l.push_back(1);
    EXPECT_EQ(l.size(), 1);
    EXPECT_DOUBLE_EQ(*l.begin(), 1);
    
    l.pop_back();
    EXPECT_EQ(l.size(), 0);
    
    l.push_front(2);
    EXPECT_EQ(l.size(), 1);
    EXPECT_DOUBLE_EQ(*l.begin(), 2);
    
    l.pop_front();
    EXPECT_EQ(l.size(), 0);
}

int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}