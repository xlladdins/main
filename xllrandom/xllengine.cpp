// xllengine.cpp - random engines
#include "xllrandom.h"

using namespace xll;

#define XLL_ENUM_(a,b,c) XLL_ENUM_DOC(RANDOM_ENGINE_##a, RANDOM_ENGINE_##a, CATEGORY, L##c, L##c)
RANDOM_ENGINE(XLL_ENUM_)

AddIn xai_random_engine(
    Function(XLL_WORD, L"?xll_random_default_engine", PREFIX L"ENGINE")
    .Arg(XLL_WORD, L"engine", L"is a value from the RANDOM_ENGINE_* enumeration.")
    .FunctionHelp(L"Set the default random engine.")
    .Category(CATEGORY)
    .Documentation(L"doc")
);
WORD WINAPI xll_random_default_engine(WORD de)
{
#pragma XLLEXPORT
    return de;
}