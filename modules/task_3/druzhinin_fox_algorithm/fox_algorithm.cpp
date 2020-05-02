// Copyright 2020 Druzhinin Alexei

#include "../../../modules/task_3/druzhinin_fox_algorithm/fox_algorithm.h"
#include <math.h>
#include <omp.h>
#include <tbb/tbb.h>
#include <algorithm>
#include <limits>
#include <random>


void fillMatrix(double* a, const int size) {  // filling the matrix with random double values
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_real_distribution<> dis(0.0, 100.0);
    for (int i = 0; i < size * size; i++)
        a[i] = dis(gen);
}

bool comparisonMatrixes(const double* a, const double* b, const int size) {  // comparison two matrixes
    for (int i = 0; i < size * size; i++) {
        if (std::fabs(a[i] - b[i]) > std::numeric_limits<double>::epsilon() * max(a[i], b[i]) * 100) {
            return false;
        }
    }
    return true;
}

void defaultMatrixMult(const double* a, const double* b, const int size, double* res) {  // default multiplication
    double tmp;
    for (int i = 0; i < size; i++) {
        for (int j = 0; j < size; j++) {
            tmp = 0;
            for (int k = 0; k < size; k++) {
                tmp += a[i * size + k] * b[k * size + j];
            }
            res[i * size + j] = tmp;
        }
    }
}

void foxAlgorithm_tbb(double* a, double* b, double* res, int size, int count_proc) {  // tbb realisation
    tbb::task_scheduler_init init(count_proc);
    int q = std::sqrt(count_proc);
    int block_size = size / q;
    tbb::parallel_for(tbb::blocked_range<size_t>(0, size / block_size), [&](const tbb::blocked_range<size_t>& r) {
        for (size_t i = r.begin(); i != r.end(); i++)
            for (int j = 0; j < size; j += block_size)
                for (int k = 0; k < size; k += block_size)
                    atomic_mult(a, b, res, size, block_size, i * block_size, j, k);
        });
}

void atomic_mult(double* a, double* b, double* res, int size, int block_size, int ii, int jj, int kk) {
    for (int i = 0; i < block_size; i++)
        for (int j = 0; j < block_size; j++)
            for (int k = 0; k < block_size; k++)
                res[(i + ii) * size + (kk + k)] += a[(ii + i) * size + (jj + j)] * b[(jj + j) * size + (kk + k)];
}
