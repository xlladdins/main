// xlldistribution.cpp - random distributions
#include "xllrandom.h"

using namespace xll;

#define HASH_(x) L#x
#define UNPAREN(...) __VA_ARGS__

//#define XLL_ENUM_(a,b,c,d,e,f) XLL_ENUM_DOC(RANDOM_DISTRIBUTION_##a, RANDOM_DISTRIBUTION_##a, CATEGORY, f L". Parameters: " HASH_(UNPAREN(e)), HASH_(f))
//RANDOM_DISTRIBUTION(XLL_ENUM_)

std::default_random_engine dre;

AddIn xai_variate_bool(
    Function(XLL_BOOL, L"?xll_variate_bool", L"VARIATE.BOOL")
    .Arg(XLL_HANDLE, L"h", L"is a handle to a random distribution returning boolean values.")
    .Volatile()
    .Category(CATEGORY)
    .FunctionHelp(L"Generate a random boolean variate.")
    .Documentation(L"x")
);
BOOL WINAPI xll_variate_bool(HANDLEX h)
{
#pragma XLLEXPORT
    BOOL b = FALSE;

    try {
        handle<std::function<bool()>> h_(h);
        //ensure (h_.is_valid());
        b = (*h_)();
    }
    catch (const std::exception& ex) {
        XLL_ERROR(ex.what());
    }

    return b;
}
AddIn xai_variate_int(
    Function(XLL_LONG, L"?xll_variate_int", L"VARIATE.INT")
    .Arg(XLL_HANDLE, L"h", L"is a handle to a random distribution returning integer values.")
    .Volatile()
    .Category(CATEGORY)
    .FunctionHelp(L"Generate a random integer variate.")
    .Documentation(L"x")
);
LONG WINAPI xll_variate_int(HANDLEX h)
{
#pragma XLLEXPORT
    LONG l = 0;

    try {
        handle<std::function<long()>> h_(h);
        //ensure (h_.is_valid());
        l = (*h_)();
    }
    catch (const std::exception& ex) {
        XLL_ERROR(ex.what());
    }

    return l;
}
AddIn xai_variate_num(
    Function(XLL_DOUBLE, L"?xll_variate_num", L"VARIATE.NUM")
    .Arg(XLL_HANDLE, L"h", L"is a handle to a random distribution returning floating point values.")
    .Volatile()
    .Category(CATEGORY)
    .FunctionHelp(L"Generate a random floating point variate.")
    .Documentation(L"x")
);
double WINAPI xll_variate_num(HANDLEX h)
{
#pragma XLLEXPORT
    double d = std::numeric_limits<double>::quiet_NaN();

    try {
        handle<std::function<double()>> h_(h);
        //ensure (h_.is_valid());
        d = (*h_)();
    }
    catch (const std::exception& ex) {
        XLL_ERROR(ex.what());
    }

    return d;
}

//
// Boolean Variates
//

AddIn xai_random_bernoulli(
    Function(XLL_HANDLE, L"?xll_random_bernoulli", L"RANDOM.BERNOULLI")
    .Arg(XLL_WORD, L"engine", L"specifies what engine to use from the RANDOM_ENGINE_* enumeration.")
    .Arg(XLL_DOUBLE, L"p", L"is the probability of returning a TRUE variate.")
    .Uncalced()
    .Category(CATEGORY)
    .FunctionHelp(L"Create a handle to a random number generator called by RANDOM.BOOL")
    .Documentation(L"x")
);
HANDLEX WINAPI xll_random_bernoulli(WORD engine, double p)
{
#pragma XLLEXPORT
    handlex h;

    try {
        ensure (0 <= p && p <= 1);
        std::bernoulli_distribution d(p);

        switch (engine) {
        case RANDOM_ENGINE_DEFAULT:
        default:
            handle<std::function<bool()>> h_(new std::function{[d]() -> bool { return d(dre); }});
            h = h_.get();
        }
    }
    catch (const std::exception& ex) {
        XLL_ERROR(ex.what());
    }

    return h;
}

//
// Integer Variates
//

AddIn xai_random_binomial(
    Function(XLL_HANDLE, L"?xll_random_binomial", L"RANDOM.BINOMIAL")
    .Arg(XLL_WORD, L"engine", L"specifies what engine to use from the RANDOM_ENGINE_* enumeration.")
    .Arg(XLL_LONG, L"t", L"is the number of binomial trials.")
    .Arg(XLL_DOUBLE, L"p", L"is the probability of returning a TRUE variate.")
    .Uncalced()
    .Category(CATEGORY)
    .FunctionHelp(L"Create a handle to a random number generator called by RANDOM.BOOL")
    .Documentation(L"x")
);
HANDLEX WINAPI xll_random_binomial(WORD engine, LONG t, double p)
{
#pragma XLLEXPORT
    handlex h;

    try {
        ensure (t >= 0);
        ensure (0 <= p && p <= 1);
        std::binomial_distribution d(t, p);

        switch (engine) {
        case RANDOM_ENGINE_DEFAULT:
        default:
            handle<std::function<LONG()>> h_(new std::function{[d]() -> LONG { return d(dre); }});
            h = h_.get();
        }
    }
    catch (const std::exception& ex) {
        XLL_ERROR(ex.what());
    }

    return h;
}

//
// Floating Point Variates
//

AddIn xai_random_cauchy(
    Function(XLL_HANDLE, L"?xll_random_cauchy", L"RANDOM.CAUCHY")
    .Arg(XLL_WORD, L"engine", L"specifies what engine to use from the RANDOM_ENGINE_* enumeration.")
    .Arg(XLL_DOUBLE, L"a", L"is the location parameter.")
    .Arg(XLL_DOUBLE, L"b", L"is the scale parameter.")
    .Uncalced()
    .Category(CATEGORY)
    .FunctionHelp(L"Create a handle to a random number generator called by RANDOM.BOOL")
    .Documentation(LR"xyz(
The Cauchy density function is 
f(x;&#x3BC;,&#x3B3;) = 1/&#x3C0;&#x3B3;[1 + ((x - &#x3BC;)/&#x3B3;)<superscript>2</superscript>]
)xyz")
);
HANDLEX WINAPI xll_random_cauchy(WORD engine, double a, double b)
{
#pragma XLLEXPORT
    handlex h;

    try {
        ensure(b >= 0);
        if (b == 0)
            b = 1;
        std::cauchy_distribution d(a, b);

        switch (engine) {
        case RANDOM_ENGINE_DEFAULT:
        default:
            handle<std::function<double()>> h_(new std::function{[d]() -> double { return d(dre); }});
            h = h_.get();
        }
    }
    catch (const std::exception& ex) {
        XLL_ERROR(ex.what());
    }

    return h;
}
