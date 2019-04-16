// xllengine.cpp - random engines
#include "xllrandom.h"

using namespace xll;

#define XLL_ENUM_(a,b,c) XLL_ENUM_DOC(RANDOM_ENGINE_##a, RANDOM_ENGINE_##a, CATEGORY, L##c, L##c)
RANDOM_ENGINE(XLL_ENUM_)

