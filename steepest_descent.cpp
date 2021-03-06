//Implementation of steepest descent to find best direction in which to perform 
//minimize a function.

#include <iostream>
#include <cmath>
#include <stdio.h> //include printf
#include <valarray>
#include <tuple>
#include "armijo_rule.h"
#include "golden_section_search.h"

using std::valarray;

valarray<double> steepest_descent(double (*f)(valarray<double>), valarray<double> (*g)(valarray<double>), valarray<double> x0, double epsilon, int MAX_ITER) {

  int k = 0;  
  int func_evals = 0;
  double stepsize, gnorm, a, b, fx;
  valarray<double> x, gx, d, newx;
  Armijo steps;
  
  x = x0;
  gx = g(x);
  gnorm = std::sqrt(std::inner_product(std::begin(gx), std::end(gx), std::begin(gx), 0.0));
  
  int gradient_evaluations = 1;

  std::cout << "Enter left endpoint for Golden Section Search: ";
  std::cin >> a;
  std::cout << "Enter right endpoint for Golden Section Search: ";
  std::cin >> b;

  int s1=22,s2=16,s3=14;
  printf("%s %s %*s %*s %*s \n","Iteration (i)", "x_i[0]", s2, "x_i[1]", s2, "f(x_i)", s2, "norm of gradient");

  while (gnorm > epsilon) {
    fx = f(x);
    printf("%d %*.8f %*.8f %*.8f %*.8f \n", k, s1, x[0], s3, x[1], s3, fx, s3, gnorm);
    d = -gx;
    steps = armijo_rule(f, gx, x, d, 2.0, 0.5);
    x += (steps.stepsize * d);
    func_evals += steps.fevals;
    //newx = golden_section_search(x.size(), f, x, a, b, d, pow(10.0, -3));
    //x = newx;
    gx = g(x);
    gradient_evaluations += 1;
    gnorm = std::sqrt(std::inner_product(std::begin(gx), std::end(gx), std::begin(gx), 0.0));
    k++;
    if (k > MAX_ITER) {
      printf("Maximum iterations exceeded \n");
      break;
    }
  }
  std::cout<<func_evals<<" function evaluations"<<std::endl;
  std::cout<<gradient_evaluations<<" gradient evaluations"<<std::endl;
  return x;
}

