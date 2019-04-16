// xllrandom.h - <random>
#pragma once
#include <random>
#include "../xll12/xll/xll.h"

#ifndef CATEGORY
#define CATEGORY L"Random"
#endif
#ifndef PREFIX
#define PREFIX L"RANDOM."
#endif

#define RANDOM_ENGINE(X) \
X(DEFAULT, default_random_engine, "Defaults to mt19937") \
X(KNUTH_B, knuth_b, "Shuffle order engine based on minstd_rand0") \
X(MINSTD_RAND, minstd_rand, "Generates a random sequence by the linear congruential algorithm.") \
X(MINSTD_RAND0, minstd_rand0, "Generates a random sequence by the linear congruential algorithm.") \
X(MT19937, mt19937, "Generates a high quality random sequence of integers based on the Mersenne twister algorithm.") \
X(MT19937_64, mt19937_64, "Generates a high quality random sequence of integers based on the Mersenne twister algorithm.") \

//X(RANLUX24, ranlux24, "Generates a random sequence using discard block and subtract-with-carry (lagged Fibonacci) algorithm.") \
//X(RANLUX3, ranlux3, "Generates a random sequence using discard block and subtract-with-carry (lagged Fibonacci) algorithm.") \
//X(RANLUX4, ranlux4, "Generates a random sequence using discard block and subtract-with-carry (lagged Fibonacci) algorithm.") \
//X(RANLUX48, ranlux48, "Generates a random sequence using discard block and subtract-with-carry (lagged Fibonacci) algorithm.") \

#define ENUM_(a,b,c) RANDOM_ENGINE_ ## a,
enum RandomEngine { RANDOM_ENGINE(ENUM_) };
#undef ENUM_

#define UNPAREN(...) __VA_ARGS__
#define RANDOM_DISTRIBUTION(X) \
X(BERNOULLI, UNPAREN(bernoulli_distribution), bool, UNPAREN(double), UNPAREN(p), "Return true with probability p, false with probability 1 - p") \
X(BINOMIAL, UNPAREN(binomial_distribution<int,double>), int, UNPAREN(int,double), UNPAREN(t,p), "Return i with probability C(t,i) p^i (1 - p)^(t - i)") \
X(CAUCHY, UNPAREN(cauchy_distribution<double>), double, UNPAREN(double,double), UNPAREN(a,b), "Density 1/pi*(1 + x^2)") \
X(CHI_SQUARED, UNPAREN(chi_squared_distribution<double>), double, UNPAREN(double), UNPAREN(n), "Sum of the squares of n standard normal random variables") \
X(DISCRETE, UNPAREN(discrete_distribution<int>), int, UNPAREN(std::initializer_list<double>), UNPAREN(probabilities), "Return i with probability p[i]") \
X(EXPONENTIAL, UNPAREN(exponential_distribution<double>), double, UNPAREN(double), UNPAREN(lambda), "Cumulative distribution 1 - exp(-lambda x), x > 0") \
X(EXTREME_VALUE, UNPAREN(extreme_value_distribution<double>), double, UNPAREN(double,double), UNPAREN(a,b), "Cumulative distribution exp(-exp(-x))") \
X(FISHER_F, UNPAREN(fisher_f_distribution<double>), double, UNPAREN(double,double), UNPAREN(m,n), "Quotient of chi squared distributions") \
X(GAMMA, UNPAREN(gamma_distribution<double>), double, UNPAREN(double,double), UNPAREN(alpha,beta), "Density x^alpha exp(-x/beta)/Gamma(alpha)beta^alpha, x > 0") \
X(GEOMETRIC, UNPAREN(geometric_distribution<int>), int, UNPAREN(double), UNPAREN(p), "Return i with probability p (1 - p)^i") \
X(LOGNORMAL, UNPAREN(lognormal_distribution<double>), double, UNPAREN(double,double), UNPAREN(m,s), "Exponential of normal distribution") \
X(NEGATIVE_BINOMIAL, UNPAREN(negative_binomial_distribution<int>), int, UNPAREN(int,double), UNPAREN(k,p), "") \
X(NORMAL, UNPAREN(normal_distribution<double>), double, UNPAREN(double,double), UNPAREN(mean,stddev), "Density exp(-x^2/2)/sqrt(2 pi)") \
X(PIECEWISE_CONSTANT, UNPAREN(piecewise_constant_distribution<double>), double, UNPAREN(std::vector<double>), UNPAREN(intervals,densities), "") \
X(PIECEWISE_LINEAR, UNPAREN(piecewise_linear_distribution<double>), double, UNPAREN(std::vector<double>), UNPAREN(intervals,densities), "") \
X(POISSON, UNPAREN(poisson_distribution<int>), int, UNPAREN(double), UNPAREN(mean), "Return i with probability m^i exp(-m)/i!") \
X(STUDENT_T, UNPAREN(student_t_distribution<double>), double, UNPAREN(double), UNPAREN(n), "Density proportional to (1 + x^2/n)^(-(n+1)/2)") \
X(UNIFORM_REAL, UNPAREN(uniform_real_distribution<double>), double, UNPAREN(double,double), UNPAREN(a,b), "Uniform reals on [a,b)") \
X(WEIBULL, UNPAREN(weibull_distribution<double>), double, UNPAREN(double,double), UNPAREN(a,b), "Density a/b (x/b)^(a-1) exp(-(x/b)^a), x > 0") \
X(TUKEY, UNPAREN(tukey_lambda_distribution<double>), double, UNPAREN(double), UNPAREN(lambda), "Quantile (q^lambda - (1-q)^lambda)/lambda") \
//X(UNIFORM_INT, UNPAREN(uniform_int_distribution<int>), int, UNPAREN(int,int), UNPAREN(a,b), "Uniform integers on [a,b]") \
// illegal call of non-static member function

#define ENUM_(a,b,c,d,e,f) RANDOM_DISTRIBUTION_ ## a,
enum RandomDistribution { RANDOM_DISTRIBUTION(ENUM_) };
#undef ENUM_

#undef UNPAREN
