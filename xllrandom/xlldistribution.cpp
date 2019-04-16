// xlldistribution.cpp - random distributions
#include "xllrandom.h"

using namespace xll;

#define HASH_(x) L#x
#define UNPAREN(...) __VA_ARGS__

#define XLL_ENUM_(a,b,c,d,e,f) XLL_ENUM_DOC(RANDOM_DISTRIBUTION_##a, RANDOM_DISTRIBUTION_##a, CATEGORY, f L". Parameters: " HASH_(UNPAREN(e)), HASH_(f))
RANDOM_DISTRIBUTION(XLL_ENUM_)

std::default_random_engine dre;

AddIn xai_variate_bool(
    Function(XLL_BOOL, L"?xll_variate_bool", L"VARIATE.BOOL")
    .Arg(XLL_HANDLE, L"h", L"is a handle to a random distribution returning boolean values.")
    .Volatile()
    .Category(CATEGORY)
    .FunctionHelp(L"Generate a random boolean variate.")
    .Documentation(L"")
);
BOOL WINAPI xll_variate_bool(HANDLEX h)
{
#pragma XLLEXPORT
    BOOL b = FALSE;

    try {
        handle<std::function<bool()>> h_(h);
        ensure (h_);
        b = (*h_)();
    }
    catch (const std::exception& ex) {
        XLL_ERROR(ex.what());
    }

    return b;
}

AddIn xai_random_bernoulli(
    Function(XLL_HANDLE, L"?xll_random_bernoulli", L"RANDOM.BERNOULLI")
    .Arg(XLL_WORD, L"engine", L"specifies what engine to use from the RANDOM_ENGINE_* enumeration.")
    .Arg(XLL_DOUBLE, L"p", L"is the probability of returning a TRUE variate.")
    .Uncalced()
    .Category(CATEGORY)
    .FunctionHelp(L"Create a handle to a random number generator called by RANDOM.BOOL")
    .Documentation(L"")
);
HANDLEX WINAPI xll_random_bernoulli(WORD engine, double p)
{
#pragma XLLEXPORT
    handlex h;

    try {
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
