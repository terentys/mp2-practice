#include "tmatrix.h"

#include <gtest\gtest.h>

TEST(TDynamicMatrix, can_create_matrix_with_positive_length) {
    ASSERT_NO_THROW(TDynamicMatrix<int> m(5));
}

TEST(TDynamicMatrix, cant_create_too_large_matrix) {
    ASSERT_ANY_THROW(TDynamicMatrix<int> m(MAX_MATRIX_SIZE + 1));
}

TEST(TDynamicMatrix, throws_when_create_matrix_with_negative_length) {
    ASSERT_ANY_THROW(TDynamicMatrix<int> m(-5));
}

TEST(TDynamicMatrix, can_create_copied_matrix) {
    TDynamicMatrix<int> m(5);

    ASSERT_NO_THROW(TDynamicMatrix<int> m1(m));
}

TEST(TDynamicMatrix, copied_matrix_is_equal_to_source_one) {
    TDynamicMatrix<int> m1(4);
    for (size_t i = 0; i < m1.getDimension(); i++) {
        for (size_t j = i; j < m1.getDimension(); j++) {
            m1(i, j) = i + j;
        }
    }

    TDynamicMatrix<int> m2(m1);

    EXPECT_TRUE(m1 == m2);
}

TEST(TDynamicMatrix, copied_matrix_has_its_own_memory) {// todo
    TDynamicMatrix<int> m1(4);
    m1(1, 2) = 123;

    TDynamicMatrix<int> m2(m1);
    m2(1, 2) = 999;

    EXPECT_TRUE(m1 != m2);
}

TEST(TDynamicMatrix, can_get_size) {
    TDynamicMatrix<int> m(4);

    EXPECT_EQ(4, m.getDimension());
}

TEST(TDynamicMatrix, can_set_and_get_element) {
    TDynamicMatrix<int> m(4);
    m(1, 2) = 123;

    EXPECT_EQ(123, m(1, 2));
}

TEST(TDynamicMatrix, throws_when_set_element_with_negative_index) {
    TDynamicMatrix<int> m(4);

    ASSERT_THROW(m(-1, 2) = 123, out_of_range);
}

TEST(TDynamicMatrix, throws_when_set_element_with_too_large_index) {
    TDynamicMatrix<int> m(4);

    ASSERT_THROW(m(1, 5) = 123, out_of_range);
}

TEST(TDynamicMatrix, throws_when_set_element_below_diagonal) {
    TDynamicMatrix<int> m(4);

    ASSERT_THROW(m(3, 1) = 123, out_of_range);
}

TEST(TDynamicMatrix, can_assign_matrix_to_itself) { // todo
    TDynamicMatrix<int> m(4);

    ASSERT_NO_THROW(m = m);
}

TEST(TDynamicMatrix, can_assign_matrices_of_equal_size) { // todo
    TDynamicMatrix<int> m1(4);
    for (size_t i = 0; i < m1.getDimension(); i++) {
        for (size_t j = i; i < m1.getDimension(); i++) {
            m1(i, j) = i * 10 + j * 100;
        }
    }
    TDynamicMatrix<int> m2(4);
    m2 = m1;

    EXPECT_TRUE(m1 == m2);
}

TEST(TDynamicMatrix, assign_operator_change_matrix_size) {
    TDynamicMatrix<int> m1(8);
    TDynamicMatrix<int> m2(4);

    m2 = m1;

    EXPECT_EQ(m2.getDimension(), 8);
}

TEST(TDynamicMatrix, can_assign_matrices_of_different_size) { // todo
    TDynamicMatrix<int> m1(4);
    for (size_t i = 0; i < m1.getDimension(); i++) {
        for (size_t j = i; i < m1.getDimension(); i++) {
            m1(i, j) = i * 10 + j * 100;
        }
    }
    TDynamicMatrix<int> m2(3);

    m2 = m1;

    EXPECT_TRUE(m2 == m1);
}

TEST(TDynamicMatrix, compare_equal_matrices_return_true) {
    TDynamicMatrix<int> m1(4);
    TDynamicMatrix<int> m2(4);
    for (size_t i = 0; i < m1.getDimension(); i++) {
        for (size_t j = i; j < m1.getDimension(); j++) {
            m1(i, j) = i + j;
            m2(i, j) = i + j;
        }
    }

    EXPECT_TRUE(m1 == m2);
}

TEST(TDynamicMatrix, compare_matrix_with_itself_return_true) {
    TDynamicMatrix<int> m(4);

    EXPECT_TRUE(m == m);
}

TEST(TDynamicMatrix, matrices_with_different_size_are_not_equal) {
    TDynamicMatrix<int> m1(4);
    TDynamicMatrix<int> m2(5);

    EXPECT_FALSE(m1 == m2);
}

TEST(TDynamicMatrix, not_equal_operator_works_correctly) { // todo
    TDynamicMatrix<int> m1(4);
    TDynamicMatrix<int> m2(4);
    for (size_t i = 0; i < m1.getDimension(); i++) {
        for (size_t j = i; j < m1.getDimension(); j++) {
            m1(i, j) = i + j;
            m2(i, j) = i + j + 1;
        }
    }

    EXPECT_TRUE(m1 != m2);
}

TEST(TDynamicMatrix, can_multiply_matrix_by_scalar) { // todo
    const int k = 5;
    TDynamicMatrix<int> m(4), exp(4);
    for (size_t i = 0; i < m.getDimension(); i++) {
        for (size_t j = i; j < m.getDimension(); j++) {
            m(i, j) = i + j;
            exp(i, j) = (i + j) * k;
        }
    }

    EXPECT_TRUE((m * k) == exp);
}

TEST(TDynamicMatrix, can_multiply_matrix_by_vector) { // todo
    TDynamicMatrix<int> m(3);
    for (size_t i = 0; i < m.getDimension(); i++) {
        for (size_t j = i; j < m.getDimension(); j++) {
            m(i, j) = 1;
        }
    }
    TDynamicVector<int> v(3), exp(3);
    for (size_t i = 0; i < v.size(); i++) {
        v[i] = i;

        int sum = m(i, i) * v[i];
        for (size_t j = i + 1; j < v.size(); j++) {
            sum += m(i, j) * v[j];
        }
        exp[i] = sum;
    }

    EXPECT_TRUE((m * v) == exp);
}

TEST(TDynamicMatrix, cant_multiply_matrix_by_vector_with_not_equal_size) {
    TDynamicMatrix<int> m(4);
    TDynamicVector<int> v(5);

    ASSERT_THROW(m * v, invalid_argument);
}

TEST(TDynamicMatrix, can_add_matrices_with_equal_size) { // todo //не сделано
    TDynamicMatrix<int> m1(4);
    TDynamicMatrix<int> m2(4);
    for (size_t i = 0; i < m1.getDimension(); i++) {
        for (size_t j = i; j < m1.getDimension(); j++) {
            m1(i, j) = 1;
            m2(i, j) = 2;
        }
    }

    TDynamicMatrix<int> m3 = m1 + m2;

    for (size_t i = 0; i < m3.getDimension(); i++) {
        for (size_t j = i; j < m3.getDimension(); j++) {
            EXPECT_EQ(m3(i, j), 3);
        }
    }
}

TEST(TDynamicMatrix, cant_add_matrices_with_not_equal_size) {
    TDynamicMatrix<int> m1(4);
    TDynamicMatrix<int> m2(5);

    ASSERT_THROW(m1 + m2, invalid_argument);
}

TEST(TDynamicMatrix, can_subtract_matrices_with_equal_size) { // todo //не сделано
    TDynamicMatrix<int> m1(4);
    TDynamicMatrix<int> m2(4);
    for (size_t i = 0; i < m1.getDimension(); i++) {
        for (size_t j = i; j < m1.getDimension(); j++) {
            m1(i, j) = 5;
            m2(i, j) = 2;
        }
    }

    TDynamicMatrix<int> m3 = m1 - m2;

    for (size_t i = 0; i < m3.getDimension(); i++) {
        for (size_t j = i; j < m3.getDimension(); j++) {
            EXPECT_EQ(m3(i, j), 3);
        }
    }
}

TEST(TDynamicMatrix, cant_subtract_matrixes_with_not_equal_size) {
    TDynamicMatrix<int> m1(4);
    TDynamicMatrix<int> m2(5);

    ASSERT_THROW(m1 - m2, invalid_argument);
}

TEST(TDynamicMatrix, can_multiply_matrices_with_equal_size) { // todo //не сделано
    TDynamicMatrix<int> m1(3);
    TDynamicMatrix<int> m2(3);
    for (size_t i = 0; i < m1.getDimension(); i++) {
        for (size_t j = i; j < m1.getDimension(); j++) {
            m1(i, j) = 1;
            m2(i, j) = 1;
        }
    }

    TDynamicMatrix<int> m3 = m1 * m2;

    for (size_t i = 0; i < m3.getDimension(); i++) {
        for (size_t j = i; j < m3.getDimension(); j++) {
            EXPECT_EQ(m3(i, j), static_cast<int>(j - i + 1));
        }
    }
}

TEST(TDynamicMatrix, cant_multiply_matrices_with_not_equal_size) {
    TDynamicMatrix<int> m1(4);
    TDynamicMatrix<int> m2(5);

    ASSERT_THROW(m1 * m2, invalid_argument);
}

