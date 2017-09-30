/*
Implementation of Inexact Search using Armijo's rule (refer to Chapter 8 in
Bazaraa, M.S., Sherali, H.D., & Shetty, C.M. "Nonlinear Programming (3rd ed)" 
to minimize a function.
*/
#include <iostream>
#include <cmath>
#include <stdio.h> //for printf
#include <valarray>
#include <numeric> //for std::inner_product
#include <string>
#include <iostream>
#include <iterator>

using std::valarray;

int comparison (int iter,double (*f)(valarray<double>),valarray<double> (*g)(valarray<double>),valarray<double>& xk,valarray<double> p, double multiplier, double th)
{
  double fxc,lc,prod,fxk;
  valarray<double> xc,gxc;
  xc=xk;
  fxc=f(xc);
  gxc=g(xc);
  prod=std::inner_product(std::begin(gxc),std::end(gxc),std::begin(p),0.0);
  lc=fxc+multiplier*th*prod;
  xk=xc+(multiplier*p);
  fxk=f(xk);


  int s1=22,s2=16;
  //printf("%d & %*.8f & %*.8f & %*.8f & %*.8f & %*.8f & %*.8f \\\\ \n",i,s1,xs[0],s2,xu[0],s2,xl[0],s2,xr[0],s2,fxl,s2,fxr);
  printf("%d %*.8f %*.8f %*.8f %*.8f %*.8f\n",iter,s1,multiplier,s2,xc[0],s2,xc[1],s2,fxc,s2,lc);
  
  if (fxk<=lc) {
    return 1;
  } else {
    return 0;
  }
}

valarray<double> armijo_rule(int n,double (*f)(valarray<double>),valarray<double> (*g)(valarray<double>),valarray<double> x0,valarray<double> d, double a, double eta, double theta)
{
  //User must supply the function f: R^n -> R and the gradient of the function g:R^n.
  double alpha;
  int t=1;
  alpha=a;
  valarray<double> xc=x0;
  
  /*
  std::cout<<std::endl;
  printf("NOTE 1: multiplier = (eta^j)^i*alpha where j is either 1 or -1 depending on whether\n");
  printf("alpha is doubled or halved in that iteration i.\n");
  printf("NOTE 2: r(multiplier) = f(x_0)+(multiplier*theta*grad*d) where grad is the gradient\n");
  printf("of f at the initial point x_0 and d is the user-supplied direction.\n");
  */
  
  std::cout<<std::endl;
  int s1=22,s2=16;
  printf("%s %s %*s %*s %*s %*s\n","Iteration (i)","multiplier",s2,"x_i",s2,"y_i",s2,"f(x_i,y_i)",s2,"r(multiplier)");
  
  if (comparison(t,f,g,xc,d,alpha,theta)==1) {
    //std::cout<<"f(x_i) <= r(multiplier)"<<std::endl;
    alpha=pow(eta,t)*alpha;
    while (comparison(t,f,g,xc,d,alpha,theta)==0) {
      t+=1;
      alpha=pow(eta,t)*alpha;
    }
  } else {
    //std::cout<<"f(x_i) > r(multiplier)"<<std::endl;
    alpha=pow(1/eta,t)*alpha;
    while (comparison(t,f,g,xc,d,alpha,theta)==0) {
      t+=1;
      alpha=pow(1/eta,t)*alpha;
    }
  }
  std::cout<<std::endl;
  
  return xc;
}
