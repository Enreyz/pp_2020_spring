// Copyright 2020 Druzhinin Alexei

#ifndef MODULES_TASK_3_DRUZHININ_FOX_ALGORITHM_FOX_ALGORITHM_H_
#define MODULES_TASK_3_DRUZHININ_FOX_ALGORITHM_FOX_ALGORITHM_H_

void fillMatrix(double*, const int);
bool comparisonMatrixes(const double*, const double*, const int);
void defaultMatrixMult(const double*, const double*, const int, double*);
void foxAlgorithm_tbb(double*, double*, double*, int, int);
void atomic_mult(double*, double*, double*, int, int, int, int, int);


#endif  // MODULES_TASK_3_DRUZHININ_FOX_ALGORITHM_FOX_ALGORITHM_H_
