// Copyright 2020 Druzhinin Alexei

#include <gtest/gtest.h>
#include <tbb/tbb.h>
#include "../../../modules/task_3/druzhinin_fox_algorithm/fox_algorithm.h"

#define SIZE_SMALL 3
#define SIZE_MEDIUM 4
#define SIZE_LARGE 50
#define NTHREADS 4

TEST(Fox_Algorithm, Comparison_Equal_Matrixes_Correct) {
    // Arrange
    double a[SIZE_SMALL * SIZE_SMALL];  // matrix size = 3x3
    bool res;

    // Act
    fillMatrix(a, SIZE_SMALL);
    res = comparisonMatrixes(a, a, SIZE_SMALL);

    // Assert
    ASSERT_EQ(res, true);
}


TEST(Fox_Algorithm, Comparison_Unequal_Matrixes_Correct) {
    // Arrange
    double a[SIZE_SMALL * SIZE_SMALL];
    double b[SIZE_SMALL * SIZE_SMALL] = { 1.1, 1.1, 1.1,
                                        1.1, 1.1, 1.1,
                                        1.1, 1.1, 1.1 };
    bool res;

    // Act
    fillMatrix(a, SIZE_SMALL);
    res = comparisonMatrixes(a, b, SIZE_SMALL);

    // Assert
    ASSERT_EQ(res, false);
}

TEST(Fox_Algorithm, Default_Matrix_Multiplication_Correct) {
    // Arrange
    double a[SIZE_SMALL * SIZE_SMALL] = { 1.1, 1.1, 1.1,
                                        1.1, 1.1, 1.1,
                                        1.1, 1.1, 1.1 };
    double b[SIZE_SMALL * SIZE_SMALL] = { 1.2, 1.2, 1.2,
                                        1.2, 1.2, 1.2,
                                        1.2, 1.2, 1.2 };
    double res[SIZE_SMALL * SIZE_SMALL]{};
    double true_res[SIZE_SMALL * SIZE_SMALL] = { 3.96, 3.96, 3.96,
                                                3.96, 3.96, 3.96,
                                                3.96, 3.96, 3.96 };
    bool result;

    // Act
    defaultMatrixMult(a, b, SIZE_SMALL, res);
    result = comparisonMatrixes(res, true_res, SIZE_SMALL);

    // Assert
    ASSERT_EQ(result, true);
}

TEST(Fox_Algorithm, TBB_Fox_Matrix_Multiplication_Correct_Medium_Size) {
    // Arrange
    double a[SIZE_MEDIUM * SIZE_MEDIUM] = { 1., 2., 3., 4.,
                                        5., 6., 7., 8.,
                                        9., 10., 11., 12.,
                                        13., 14., 15., 16.};
    double b[SIZE_MEDIUM * SIZE_MEDIUM] = { 1., 2., 3., 4.,
                                        5., 6., 7., 8.,
                                        9., 10., 11., 12.,
                                        13., 14., 15., 16. };
    double res[SIZE_MEDIUM * SIZE_MEDIUM]{};
    double true_res[SIZE_MEDIUM * SIZE_MEDIUM] = { 90.0, 100.0, 110.0, 120.0,
                                                202.0, 228.0, 254.0, 280.0,
                                                314.0, 356.0, 398.0, 440.0,
                                                426.0, 484.0, 542.0, 600.0 };
    bool result;

    // Act
    foxAlgorithm_tbb(a, b, res, SIZE_MEDIUM, NTHREADS);
    result = comparisonMatrixes(res, true_res, SIZE_MEDIUM);
    // Assert
    ASSERT_EQ(result, true);
}

TEST(Fox_Algorithm, TBB_Fox_and_Default_Matrix_Multiplication_Give_Identical_Result_Large_Size) {
    // Arrange
    double* a = new double[SIZE_LARGE * SIZE_LARGE];
    double* b = new double[SIZE_LARGE * SIZE_LARGE];
    double* def_res = new double[SIZE_LARGE * SIZE_LARGE]{};
    double* fox_res = new double[SIZE_LARGE * SIZE_LARGE]{};
    bool result;

    // Act
    fillMatrix(a, SIZE_LARGE);
    fillMatrix(b, SIZE_LARGE);

    // tbb::tick_count start_time = tbb::tick_count::now();
    defaultMatrixMult(a, b, SIZE_LARGE, def_res);
    // tbb::tick_count finish_time = tbb::tick_count::now();
    // double def_time = (finish_time - start_time).seconds();
    // std::cout << "Default multiplication = " << def_time << std::endl;

    // start_time = tbb::tick_count::now();
    foxAlgorithm_tbb(a, b, fox_res, SIZE_LARGE, NTHREADS);
    // finish_time = tbb::tick_count::now();
    // double fox_time = (finish_time - start_time).seconds();
    // std::cout << "Fox multiplication = " << fox_time << std::endl;
    // std::cout << "Speedup = " << def_time / fox_time << std::endl;

    result = comparisonMatrixes(def_res, fox_res, SIZE_LARGE);
    // Assert
    ASSERT_EQ(result, true);
    delete[] a;
    delete[] b;
    delete[] def_res;
    delete[] fox_res;
}

int main(int argc, char** argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
