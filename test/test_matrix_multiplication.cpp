#include "matrix_multiplication.h"
#include <iostream>
#include <gtest/gtest.h>

using IntMx = std::vector<std::vector<int>>;

class ValueBasedMultiplicationTestFixture :
        public testing::TestWithParam<int> {
};
INSTANTIATE_TEST_SUITE_P(
        IntegerScalarRange,
        ValueBasedMultiplicationTestFixture,
        testing::Range(-150, 150)
);

/*
 * #####################################################################################################################
 * WHAT
 * - Zero-element property for scalar multiplication.
 * HOW
 * - Parameterized test for ranges of values [-150, 150].
 * - Exploiting commutative property.
 * EXPECTED
 * - Result should be 0.
 * #####################################################################################################################
 */
TEST_P(ValueBasedMultiplicationTestFixture, WhenScalarX0ShouldBeZero) {
int value = GetParam();

IntMx A = {
        {0}
};
IntMx B = {
        {value}
};

IntMx C(1, std::vector<int>(1, 0));

multiplyMatrices(A, B, C, 1, 1, 1);

IntMx expected = {
        {0}
};

ASSERT_EQ(C, expected) << "Zero-element property (left 0) for scalar multiplication failed! :(((((";

multiplyMatrices(B, A, C, 1, 1, 1);
ASSERT_EQ(C, expected) << "Zero-element property (right 0) for scalar multiplication failed! :(((((";
}

/*
 * #####################################################################################################################
 * WHAT
 * - Neutral-element property for scalar multiplication.
 * HOW
 * - Parameterized test for ranges of values [-150, 150].
 * - Exploiting commutative property.
 * EXPECTED
 * - Result should be equal to the factor <> neutral element.
 * #####################################################################################################################
 */
TEST_P(ValueBasedMultiplicationTestFixture, WhenScalarX1ShouldBeScalar) {
int value = GetParam();

IntMx A = {
        {1}
};
IntMx B = {
        {value}
};

IntMx C(1, std::vector<int>(1, 0));

multiplyMatrices(A, B, C, 1, 1, 1);

IntMx expected = {
        {value}
};

ASSERT_EQ(C, expected) << "Neutral element property (left 1) for scalar multiplication failed! :(((((";

multiplyMatrices(B, A, C, 1, 1, 1);
ASSERT_EQ(C, expected) << "Neutral element property (right 1) for scalar multiplication failed! :(((((";
}

/*
 *
 * #####################################################################################################################
 * WHAT
 * - Scalar power of 2.
 * HOW
 * - Parameterized test for ranges of values [-150, 150].
 * EXPECTED
 * - Result should be equal to the actual value raised to the power of 2.
 * #####################################################################################################################
 */
TEST_P(ValueBasedMultiplicationTestFixture, WhenScalarXScalarShouldBePow2) {
int value = GetParam();

IntMx A = {
        {value}
};
IntMx B = {
        {value}
};

IntMx C(1, std::vector<int>(1, 0));

multiplyMatrices(A, B, C, 1, 1, 1);

IntMx expected = {
        {value * value}
};

ASSERT_EQ(C, expected) << "Scalar multiplication between equal numbers failed! :(((((";
}

/*
 *
 * #####################################################################################################################
 * WHAT
 * - Scalar product (row-column).
 * - ( Indirectly, test even number of A rows / B columns. )
 * HOW
 * - Parameterized test for ranges of values [-150, 150].
 * EXPECTED
 * - Result should be equal to {num.elements} times the value squared.
 * #####################################################################################################################
 */
TEST_P(ValueBasedMultiplicationTestFixture, WhenScalarProductShouldBeSumOfSquaredValues) {
int value = GetParam();

IntMx A = {
        {value, value}
};
IntMx B = {
        {value},
        {value}
};

IntMx C(1, std::vector<int>(1, 0));

multiplyMatrices(A, B, C, 1, 2, 1);

IntMx expected = {
        {2 * value * value}
};

ASSERT_EQ(C, expected) << "Scalar product (row-column) between equal vectors failed! :(((((";
}

/*
 * #####################################################################################################################
 * WHAT
 * - Associative property on scalar multiplication.
 * EXPECTED
 * - Actual product.
 * #####################################################################################################################
 */
TEST(AssociativePropertyTest, WhenAssociativePropertyShouldWork) {
IntMx A = {
        {2}
};
IntMx B = {
        {3}
};
IntMx C = {
        {4}
};

IntMx D_temp(1, std::vector<int>(1, 0));
IntMx D1(1, std::vector<int>(1, 0));
IntMx D2(1, std::vector<int>(1, 0));
IntMx D3(1, std::vector<int>(1, 0));

// D1 = (A x B) x C
multiplyMatrices(A, B, D_temp, 1, 1, 1);
multiplyMatrices(D_temp, C, D1, 1, 1, 1);

// D2 = A x (B x C)
multiplyMatrices(B, C, D_temp, 1, 1, 1);
multiplyMatrices(A, D_temp, D2, 1, 1, 1);

// D3 = (A x C) x B
multiplyMatrices(A, C, D_temp, 1, 1, 1);
multiplyMatrices(D_temp, B, D3, 1, 1, 1);

IntMx expected = {
        {24}
};

ASSERT_EQ(D1, expected) << "Associative property ((A x B) x C) for scalar product failed! :(((((";
ASSERT_EQ(D2, expected) << "Associative property (A x (B x C)) for scalar product failed! :(((((";
ASSERT_EQ(D3, expected) << "Associative property ((A x C) x B) for scalar product failed! :(((((";
}

/*
 * #####################################################################################################################
 * WHAT
 * - Associative property on scalar multiplication.
 * - ( By reverse engineering to avoid already known errors, some test cases may allow to spot new errors. )
 * EXPECTED
 * - The input value for both the elements in the result first row.
 * #####################################################################################################################
 */
TEST_P(ValueBasedMultiplicationTestFixture, WhenAIsVectorWithFirstElementInputValueAndBIsRectangularWith11OnFirstRowThenResultValuesShouldBeInputValue) {
int value = GetParam();

IntMx A = {
        {value, 0, 0, 0}
};
IntMx B = {
        {1, 1},
        {0, 0},
        {0, 0},
        {0, 0}
};

IntMx C(1, std::vector<int>(2, 0));

multiplyMatrices(A, B, C, 1, 4, 2);

IntMx expected = {
        {value, value}
};

ASSERT_EQ(C, expected) << "[x,0...0] [{1,1}, {0,0}, ...] = [x,x] for scalar product failed! :(((((";
}

/*
 * #####################################################################################################################
 * This test is the given example.
 * WHAT
 * - Testing matrix product.
 * EXPECTED
 * - Actual product.
 * #####################################################################################################################
 */
TEST(MatrixMultiplicationTest, TestMultiplyMatrices) {
IntMx A = {
        {1, 2, 3},
        {4, 5, 6}
};
IntMx B = {
        {7, 8},
        {9, 10},
        {11, 12}
};
IntMx C(2, std::vector<int>(2, 0));

multiplyMatrices(A, B, C, 2, 3, 2);

IntMx expected = {
        {58, 64},
        {139, 154}
};

ASSERT_EQ(C, expected) << "Matrix multiplication test failed! :(((()";
}

int main(int argc, char **argv) {
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
