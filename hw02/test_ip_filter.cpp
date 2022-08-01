#include <gtest/gtest.h>
#include "gmock/gmock.h"
#include "ip_filter.h"


TEST(IPFilterTest, DescendingOrder) {
    ip4_vec_t ip4_vec = {
        {32, 209, 238, 246},
        {46, 70, 29, 76},
        {5, 101, 217, 197},
        {5, 102, 217, 197},
        {46, 70, 100, 76},
        {32, 209, 238, 247},
    };
    ip4_vec_t ip4_vec_ref = {
        {46, 70, 100, 76},
        {46, 70, 29, 76},
        {32, 209, 238, 247},
        {32, 209, 238, 246},
        {5, 102, 217, 197},
        {5, 101, 217, 197},
    };
    sort(ip4_vec);
    EXPECT_EQ(ip4_vec.size(), ip4_vec_ref.size()) << "Missing some ip addresses after sort";
    for (size_t i = 0; i < ip4_vec.size(); i++) {
        const auto& cur = ip4_vec[i];
        const auto& ref = ip4_vec_ref[i];
        EXPECT_THAT(cur, ContainerEq(ref));
    }
}