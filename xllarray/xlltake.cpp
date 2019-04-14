// xlltake.cpp - Take elements from the front or back of a range.
#include "xllarray.h"

using namespace xll;

AddIn xai_range_take(
    Function(XLL_LPOPER, L"?xll_range_take", PREFIX L"RANGE.TAKE")
    .Arg(XLL_LONG, L"n", L"is the number of elements to take from the front (n &gt; 0) or back (n &lt; 0) of the range.")
    .Arg(XLL_LPOPER, L"range", L"is a range or a handle to a range.")
    .FunctionHelp(L"Return a new range or modify the range if a handle is given.")
    .Documentation(LR"(Documentation goes here.)")
);
LPOPER WINAPI xll_range_take(LONG n, LPOPER pr)
{
#pragma XLLEXPORT
    static OPER o;

    try {
        LPOPER po = is_handle(*pr);
        if (po != nullptr) {
            take(*po, n);
        }
        else {
            o = take(*pr, n);
        }
    }
    catch (const std::exception& ex) {
        XLL_ERROR(ex.what());

        o = OPER(xlerr::NA);
    }

    return &o;
}

#ifdef _DEBUG

#endif // _DEBUG