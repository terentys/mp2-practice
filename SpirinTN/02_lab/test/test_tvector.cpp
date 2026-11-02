#include "tmatrix.h"

#include <gtest\gtest.h>

TEST(TDynamicVector, can_create_vector_with_positive_length) {
    ASSERT_NO_THROW(TDynamicVector<int> v(5));
}

TEST(TDynamicVector, cant_create_too_large_vector) {
    ASSERT_ANY_THROW(TDynamicVector<int> v(MAX_VECTOR_SIZE + 1));
}

TEST(TDynamicVector, throws_when_create_vector_with_negative_length) {
    ASSERT_ANY_THROW(TDynamicVector<int> v(-5));
}

TEST(TDynamicVector, can_create_vector_from_raw_array) {
    int arr[4] = { 1, 2, 3, 4 };
    TDynamicVector<int> v(arr, 4);

    EXPECT_EQ(v.size(), 4);
    EXPECT_EQ(v[0], 1);
}

TEST(TDynamicVector, throws_when_create_from_array_with_zero_size) {
    int arr[4] = { 1, 2, 3, 4 };
    EXPECT_THROW(TDynamicVector<int> v(arr, 0), out_of_range);
}

TEST(TDynamicVector, can_create_copied_vector) {
    TDynamicVector<int> v(10);

    ASSERT_NO_THROW(TDynamicVector<int> v1(v));
}

TEST(TDynamicVector, copied_vector_is_equal_to_source_one) {
    TDynamicVector<int> v1(10);
    for (size_t i = 0; i < v1.size(); i++) {
        v1[i] = i * 2;
    }

    TDynamicVector<int> v2(v1);

    EXPECT_TRUE(v1 == v2);
}

TEST(TDynamicVector, copied_vector_has_its_own_memory) {
    TDynamicVector<int> v1(10);
    v1[2] = 5;

    TDynamicVector<int> v2(v1);

    v2[2] = 4;
    EXPECT_TRUE(v1 != v2);
}

TEST(TDynamicVector, move_constructor_transfers_data) {
    TDynamicVector<int> v1(4);
    v1[1] = 123;

    TDynamicVector<int> v2(std::move(v1));

    EXPECT_TRUE(v1 != v2);
}

TEST(TDynamicVector, can_get_size) {
  TDynamicVector<int> v(4);

  EXPECT_EQ(4, v.size());
}

TEST(TDynamicVector, can_set_and_get_element_no_control) {
    TDynamicVector<int> v(4);
    v[0] = 4;

    EXPECT_EQ(4, v[0]);
}

TEST(TDynamicVector, can_set_and_get_element_with_control) {
    TDynamicVector<int> v(4);
    v.at(0) = 4;

    EXPECT_EQ(4, v.at(0));
}

TEST(TDynamicVector, at_throws_when_index_it_out_of_bounds) {
    TDynamicVector<int> v(4);

    ASSERT_THROW(v.at(10), out_of_range);
}

TEST(TDynamicVector, throws_when_set_element_with_negative_index) {
    TDynamicVector<int> v(4);

    ASSERT_THROW(v.at(-1) = 5, out_of_range);
}

TEST(TDynamicVector, throws_when_set_element_with_too_large_index) {
    TDynamicVector<int> v(4);

    ASSERT_THROW(v.at(10) = 5, out_of_range);
}

TEST(TDynamicVector, can_assign_vector_to_itself) {
    TDynamicVector<int> v(4);
    v[1] = 123;

    ASSERT_NO_THROW(v = v);
}

TEST(TDynamicVector, can_assign_vectors_of_equal_size) {
    TDynamicVector<int> v1(4);
    v1[0] = 123;
    v1[1] = 456;
    v1[2] = 789;
    v1[3] = 1000;
    TDynamicVector<int> v2(4);

    v2 = v1;

    EXPECT_TRUE(v1 == v2);
}

TEST(TDynamicVector, assign_operator_change_vector_size) {
    TDynamicVector<int> v1(8);
    TDynamicVector<int> v2(4);

    v2 = v1;

    EXPECT_EQ(v2.size(), 8);
}

TEST(TDynamicVector, can_assign_vectors_of_different_size) {
    TDynamicVector<int> v1(4);
    v1[0] = 123;
    v1[1] = 456;
    v1[2] = 789;
    v1[3] = 1000;
    TDynamicVector<int> v2(3);

    v2 = v1;

    EXPECT_TRUE(v1 == v2);
}

TEST(TDynamicVector, move_assignment_transfers_data) {
    TDynamicVector<int> v1(4);
    v1[0] = 123;
    v1[1] = 456;
    v1[2] = 789;
    v1[3] = 1000;
    TDynamicVector<int> v2(10);

    v2 = std::move(v1);

    EXPECT_TRUE(v1 != v2);
}

TEST(TDynamicVector, compare_equal_vectors_return_true) {
    TDynamicVector<int> v1(4);
    TDynamicVector<int> v2(4);

    for (size_t i = 0; i < v1.size(); i++) {
        v1[i] = i;
        v2[i] = i;
    }

    EXPECT_TRUE(v1 == v2);
}

TEST(TDynamicVector, compare_different_vectors_return_false) {
    TDynamicVector<int> v1(4);
    TDynamicVector<int> v2(4);

    for (size_t i = 0; i < v1.size(); i++) {
        v1[i] = i;
        v2[i] = i;
    }

    v2[2] = 100;

    EXPECT_FALSE(v1 == v2);
}

TEST(TDynamicVector, compare_vector_with_itself_return_true) {
    TDynamicVector<int> v(4);

    EXPECT_TRUE(v == v);
}

TEST(TDynamicVector, vectors_with_different_size_are_not_equal) {
    TDynamicVector<int> v1(4);
    TDynamicVector<int> v2(5);

    for (size_t i = 0; i < v1.size(); i++) {
        v1[i] = i;
        v2[i] = i;
    }

    EXPECT_FALSE(v1 == v2);
}

TEST(TDynamicVector, not_equal_operator_works_correctly) {
    TDynamicVector<int> v1(4);
    TDynamicVector<int> v2(4);

    for (size_t i = 0; i < v1.size(); i++) {
        v1[i] = i;
        v2[i] = i + 1;
    }

    EXPECT_TRUE(v1 != v2);
}

TEST(TDynamicVector, can_add_scalar_to_vector) {
    const int k = 5;
    TDynamicVector<int> v(4), exp(4);
    for (size_t i = 0; i < v.size(); i++) {
        v[i] = i;
        exp[i] = i + k;
    }

    EXPECT_EQ(v + 5, exp);
}

TEST(TDynamicVector, can_subtract_scalar_from_vector) {
    const int k = 5;
    TDynamicVector<int> v(4), exp(4);
    for (size_t i = 0; i < v.size(); i++) {
        v[i] = i;
        exp[i] = static_cast<int>(i) - k;
    }

    EXPECT_EQ(v - 5, exp);
}

TEST(TDynamicVector, can_multiply_scalar_by_vector) {
    const int k = 5;
    TDynamicVector<int> v(4), exp(4);
    for (size_t i = 0; i < v.size(); i++) {
        v[i] = i;
        exp[i] = i * k;
    }

    EXPECT_EQ(v * 5, exp);
}

TEST(TDynamicVector, can_add_vectors_with_equal_size) { //todo
    TDynamicVector<int> v1(4);
    TDynamicVector<int> v2(4);
    TDynamicVector<int> exp(4);
    for (size_t i = 0; i < v1.size(); i++) {
        v1[i] = i;
        v2[i] = i + 1;
        exp[i] = i * 2 + 1;
    }

    EXPECT_EQ(v1 + v2, exp);
}

TEST(TDynamicVector, cant_add_vectors_with_not_equal_size) {
    TDynamicVector<int> v1(4);
    TDynamicVector<int> v2(5);

    ASSERT_THROW(v1 + v2, invalid_argument);
}

TEST(TDynamicVector, can_subtract_vectors_with_equal_size) {  //todo
    TDynamicVector<int> v1(4);
    TDynamicVector<int> v2(4);
    TDynamicVector<int> exp(4);
    for (size_t i = 0; i < v1.size(); i++) {
        v1[i] = i;
        v2[i] = i + 1;
        exp[i] = -1;
    }

    EXPECT_EQ(v1 - v2, exp);
}

TEST(TDynamicVector, cant_subtract_vectors_with_not_equal_size) {
    TDynamicVector<int> v1(4);
    TDynamicVector<int> v2(5);

    ASSERT_THROW(v1 - v2, invalid_argument);
}

TEST(TDynamicVector, can_multiply_vectors_with_equal_size) {
    TDynamicVector<int> v1(4);
    TDynamicVector<int> v2(4);
    for (size_t i = 0; i < v1.size(); i++) {
        v1[i] = i;
        v2[i] = i + 1;
    }

    int scalar = v1 * v2;

    EXPECT_EQ(scalar, 20);
}

TEST(TDynamicVector, cant_multiply_vectors_with_not_equal_size) {
    TDynamicVector<int> v1(4);
    TDynamicVector<int> v2(5);

    ASSERT_THROW(v1 * v2, invalid_argument);
}

