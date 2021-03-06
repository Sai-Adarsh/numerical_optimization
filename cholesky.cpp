/*
Find Cholesky factors of a square matrix and check if the 
matrix is positive definite.
*/
#include <iostream>
#include <cmath>
#include <stdio.h> //for printf
#include <valarray>
#include <numeric> //for std::inner_product
#include <string>
#include <iostream>
#include <iterator>
#include <algorithm> //for std::max_element

using std::valarray;

struct CholeskyFactors {
    valarray<double> lower_triangular;
    valarray<double> diagonal;
};

CholeskyFactors cholesky(valarray<double> A, int n) {
  /* The fix parameter is set to 1 to ensure that the diagonal entries D
  are sufficiently positive. Otherwise, D may not be positive definite.
  */
  CholeskyFactors result;
  valarray<double> C (0.0,n*n), D (0.0, n), L (0.0,n*n);
  double sum1, sum2, theta;
  //double delta = pow(10.0, -8);
  //double beta = 2.0;
  double correction = 0.1;

  for (int k = 0; k < n; k++) {
    L[k * n + k] = 1.0;
  }
  //if (fix == 1) {
  //  theta = *std::max_element(std::begin(C) + 1, std::end(C));
  //  double e[3] = {C[0], (theta / beta) * (theta / beta), delta};
  //  D[0] = *std::max_element(std::begin(e), std::end(e));
  D[0] = A[0];
  if (D[0] < correction) {
    D[0] = correction;
  }
  for (int k = 1; k < n; k++) {
    L[k * n] = A[k * n] / D[0];
  }
  for (int j =1 ; j < n; j++) {
    sum1 = 0.0;
    for (int s = 0; s < j; s++) {
      sum1 = sum1 + D[s] * (L[j * n + s] * L[j * n + s]);
    } 
    C[j * n + j] = A[j * n + j] - sum1;
    //if (fix == 1) {
    //  theta =*std::max_element(std::begin(C) + (j + 1), std::end(C));
    //  double e[3] = {C[0], (theta / beta) * (theta / beta), delta};
    //  D[0] =*std::max_element(std::begin(e), std::end(e));
    //} else {
    D[j] = C[j * n + j];
    if (D[j] < correction) {
      D[j] = correction;
    }
    //}
    for (int i = j + 1; i < n; i++) {
      sum2 = 0.0;
      for (int t = 0; t < j; t++) {
        sum2 = sum2 + D[t] * L[i * n + t] * L[j * n + t];
      }
      C[i * n + j] = A[i * n + j] - sum2;
      L[i * n + j] = C[i * n + j] / D[j];
    }
  }

  result.lower_triangular = L;
  result.diagonal = D;
  /*
  std::cout<<"Size of D = "<<D.size()<<std::endl;
  for (int i = 0; i < n * n; i++) {
      printf("lower triangular=%2.8f\n", result.lower_triangular[i]);
  }
  for (int i = 0; i < n; i++) {
      std::cout<<"i = "<<i<<std::endl;
      printf("diagonal=%2.8f\n", result.diagonal[i]);
  }
  */
  return result;
}
