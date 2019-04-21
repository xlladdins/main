// xlltake.cpp - Take elements from the front or back of a range.
#include "../xll12/xll/shfb/entities.h"
#include "xllarray.h"

using namespace xll;

AddIn xai_range_take(
    Function(XLL_LPOPER, L"?xll_range_take", PREFIX L"RANGE.TAKE")
    .Arg(XLL_LONG, L"n", L"is the number of elements to take from the front rows (n positive) or back rows (n negative) of a range.")
    .Arg(XLL_LPOPER, L"range", L"is a range or a handle to a range.")
    .FunctionHelp(L"Return a new range or modify the range if a handle is given.")
    .Category(CATEGORY)
    .Documentation(LR"xyz(
If the absolute value of <codeInline>n</codeInline> is greater than or equal to the number of rows of the
range the operation returns the entire range. If <codeInline>n</codeInline> is 0 the result is
<codeInline>xltypNil</codeInline>: the Excel notion of an empty range.
)xyz")
);
LPOPER WINAPI xll_range_take(LONG n, OPER const* pr)
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

test test_range_take([] {
    {
        OPER o{OPER(1), OPER(true), OPER(L"a")};
        ensure(o.size() == 3);
        take(o, 0);
        ensure(o.size() == 0);
        ensure(o.xltype == xltypeNil);
    }
    {
        const OPER o{OPER(1), OPER(true), OPER(L"a")};
        ensure (o.size() == 3);
        OPER o1 = take(o, 0);
        ensure(o.size() == 3);
        ensure (o1.xltype == xltypeNil);
    }
    {
        OPER o{OPER(1), OPER(true), OPER(L"a")};
        o.resize(o.size(), 1);
        ensure(o.size() == 3);
        take(o, 2);
        ensure(o.size() == 2);
    }
    {
        OPER o_{OPER(1), OPER(true), OPER(L"a")};
        o_.resize(o_.size(), 1);
        const OPER o{o_};
        ensure(o.size() == 3);
        OPER o1 = take(o, 2);
        ensure(o.size() == 3);
        ensure(o1[0] == o[0] && o1[1] == o[1]);
    }
    {
        OPER o{OPER(1), OPER(true), OPER(L"a")};
        o.resize(o.size(), 1);
        ensure(o.size() == 3);
        take(o, -2);
        ensure(o.size() == 2);
        ensure(o[0] == true);
        ensure(o[1] == OPER(L"a"));
    }
    {
        OPER o_{OPER(1), OPER(true), OPER(L"a")};
        o_.resize(o_.size(), 1);
        const OPER o{o_};
        ensure(o.size() == 3);
        OPER o1 = take(o, -2);
        ensure(o.size() == 3);
        ensure(o1[0] == o[1] && o1[1] == o[2]);
    }
});

#endif // _DEBUG