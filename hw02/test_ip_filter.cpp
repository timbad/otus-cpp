#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include "ip_filter.h"


TEST(IPFilterTest, DescendingAscendingOrder) {
    ip4_vec_t ip4_vec = {
        {32, 209, 238, 246},
        {46, 70, 29, 76},
        {5, 101, 217, 197},
        {5, 102, 217, 197},
        {46, 70, 100, 76},
        {32, 209, 238, 247},
    };
    ip4_vec_t ip4_vec_descending_ref = {
        {46, 70, 100, 76},
        {46, 70, 29, 76},
        {32, 209, 238, 247},
        {32, 209, 238, 246},
        {5, 102, 217, 197},
        {5, 101, 217, 197},
    };
    sort(ip4_vec);
    EXPECT_EQ(ip4_vec.size(), ip4_vec_descending_ref.size()) << "Missing some ip addresses after descending sort";
    for (size_t i = 0; i < ip4_vec.size(); i++) {
        const auto& cur = ip4_vec[i];
        const auto& ref = ip4_vec_descending_ref[i];
        EXPECT_THAT(cur, testing::ContainerEq(ref));
    }

    ip4_vec_t ip4_vec_ascending_ref = {
        {5, 101, 217, 197},
        {5, 102, 217, 197},
        {32, 209, 238, 246},
        {32, 209, 238, 247},
        {46, 70, 29, 76},
        {46, 70, 100, 76},
    };
    sort(ip4_vec, false);
    EXPECT_EQ(ip4_vec.size(), ip4_vec_ascending_ref.size()) << "Missing some ip addresses after ascending sort";
    for (size_t i = 0; i < ip4_vec.size(); i++) {
        const auto& cur = ip4_vec[i];
        const auto& ref = ip4_vec_ascending_ref[i];
        EXPECT_THAT(cur, testing::ContainerEq(ref));
    }
}

TEST(IPFilterTest, FilterFirst) {
    ip4_vec_t ip4_vec = {
            {32, 209, 238, 246},
            {46, 70, 29, 76},
            {5, 101, 217, 197},
            {5, 102, 217, 197},
            {46, 70, 100, 76},
            {32, 209, 238, 247},
    };
    ip4_vec_t ip4_vec_ref = {
            {5, 101, 217, 197},
            {5, 102, 217, 197},
    };
    auto ip4_vec2 = filter(ip4_vec, 5);
    EXPECT_EQ(ip4_vec2.size(), ip4_vec_ref.size()) << "Wrong number of ip addresses after filtering";
    for (size_t i = 0; i < ip4_vec2.size(); i++) {
        const auto& cur = ip4_vec2[i];
        const auto& ref = ip4_vec_ref[i];
        EXPECT_THAT(cur, testing::ContainerEq(ref));
    }
}

TEST(IPFilterTest, FilterSecond) {
    ip4_vec_t ip4_vec = {
            {32, 209, 238, 246},
            {46, 70, 29, 76},
            {5, 101, 217, 197},
            {5, 102, 217, 197},
            {46, 70, 100, 76},
            {32, 209, 238, 247},
    };
    ip4_vec_t ip4_vec_ref = {
            {46, 70, 29, 76},
            {46, 70, 100, 76},
    };
    auto ip4_vec2 = filter(ip4_vec, -1, 70);
    EXPECT_EQ(ip4_vec2.size(), ip4_vec_ref.size()) << "Wrong number of ip addresses after filtering";
    for (size_t i = 0; i < ip4_vec2.size(); i++) {
        const auto& cur = ip4_vec2[i];
        const auto& ref = ip4_vec_ref[i];
        EXPECT_THAT(cur, testing::ContainerEq(ref));
    }
}

TEST(IPFilterTest, FilterThird) {
    ip4_vec_t ip4_vec = {
            {32, 209, 238, 246},
            {46, 70, 29, 76},
            {5, 101, 217, 197},
            {5, 102, 217, 197},
            {46, 70, 100, 76},
            {32, 209, 238, 247},
    };
    ip4_vec_t ip4_vec_ref = {
            {32, 209, 238, 246},
            {32, 209, 238, 247},
    };
    auto ip4_vec2 = filter(ip4_vec, -1, -1, 238);
    EXPECT_EQ(ip4_vec2.size(), ip4_vec_ref.size()) << "Wrong number of ip addresses after filtering";
    for (size_t i = 0; i < ip4_vec2.size(); i++) {
        const auto& cur = ip4_vec2[i];
        const auto& ref = ip4_vec_ref[i];
        EXPECT_THAT(cur, testing::ContainerEq(ref));
    }
}

TEST(IPFilterTest, FilterFourth) {
    ip4_vec_t ip4_vec = {
            {32, 209, 238, 246},
            {46, 70, 29, 76},
            {5, 101, 217, 197},
            {5, 102, 217, 197},
            {46, 70, 100, 76},
            {32, 209, 238, 247},
    };
    ip4_vec_t ip4_vec_ref = {
            {46, 70, 29, 76},
            {46, 70, 100, 76},
    };
    auto ip4_vec2 = filter(ip4_vec, -1, -1, -1, 76);
    EXPECT_EQ(ip4_vec2.size(), ip4_vec_ref.size()) << "Wrong number of ip addresses after filtering";
    for (size_t i = 0; i < ip4_vec2.size(); i++) {
        const auto& cur = ip4_vec2[i];
        const auto& ref = ip4_vec_ref[i];
        EXPECT_THAT(cur, testing::ContainerEq(ref));
    }
}

TEST(IPFilterTest, FilterAll) {
    ip4_vec_t ip4_vec = {
            {5, 101, 217, 197},
            {32, 209, 238, 246},
            {46, 70, 29, 76},
            {5, 101, 217, 197},
            {5, 102, 217, 197},
            {46, 70, 100, 76},
            {32, 209, 238, 247},
            {5, 101, 217, 197},
    };
    ip4_vec_t ip4_vec_ref = {
            {5, 101, 217, 197},
            {5, 101, 217, 197},
            {5, 101, 217, 197},
    };
    auto ip4_vec2 = filter(ip4_vec, 5, 101, 217, 197);
    EXPECT_EQ(ip4_vec2.size(), ip4_vec_ref.size()) << "Wrong number of ip addresses after filtering";
    for (size_t i = 0; i < ip4_vec2.size(); i++) {
        const auto& cur = ip4_vec2[i];
        const auto& ref = ip4_vec_ref[i];
        EXPECT_THAT(cur, testing::ContainerEq(ref));
    }
}

TEST(IPFilterTest, FilterAny) {
    ip4_vec_t ip4_vec = {
            {100, 5, 255, 255},
            {32, 209, 238, 246},
            {46, 70, 29, 76},
            {5, 100, 217, 197},
            {5, 102, 217, 197},
            {46, 70, 100, 76},
            {32, 209, 238, 247},
            {5, 101, 217, 100},
    };
    ip4_vec_t ip4_vec_ref = {
            {100, 5, 255, 255},
            {5, 100, 217, 197},
            {46, 70, 100, 76},
            {5, 101, 217, 100},
    };
    auto ip4_vec2 = filter_any(ip4_vec, 100);
    EXPECT_EQ(ip4_vec2.size(), ip4_vec_ref.size()) << "Wrong number of ip addresses after filtering";
    for (size_t i = 0; i < ip4_vec2.size(); i++) {
        const auto& cur = ip4_vec2[i];
        const auto& ref = ip4_vec_ref[i];
        EXPECT_THAT(cur, testing::ContainerEq(ref));
    }
}