// xlldrop.cpp - drop elements from the front or back of a range.
#include "../xll12/xll/shfb/entities.h"
#include "xllarray.h"

using namespace xll;

AddIn xai_range_drop(
    Function(XLL_LPOPER, L"?xll_range_drop", PREFIX L"RANGE.DROP")
    .Arg(XLL_LONG, L"n", L"is the number of elements to drop from the front rows (n positive) or back rows (n negative) of a range.")
    .Arg(XLL_LPOPER, L"range", L"is a range or a handle to a range.")
    .FunctionHelp(L"Return a new range or modify the range if a handle is given.")
    .Category(CATEGORY)
    .Documentation(LR"xyz(
If the absolute value of <codeInline>n</codeInline> is greater than or equal to the number of rows of the
range the operation the result is
<codeInline>xltypNil</codeInline>: the Excel notion of an empty range. 
If <codeInline>n</codeInline> is 0 the the entire range is returned. 
returns the entire range. 
)xyz")
);
LPOPER WINAPI xll_range_drop(LONG n, OPER const* pr)
{
#pragma XLLEXPORT
    static OPER o;

    try {
        LPOPER po = is_handle(*pr);
        if (po != nullptr) {
            drop(*po, n);
        }
        else {
            o = drop(*pr, n);
        }
    }
    catch (const std::exception& ex) {
        XLL_ERROR(ex.what());

        o = OPER(xlerr::NA);
    }

    return &o;
}

#ifdef _DEBUG

test test_range_drop([] {
    {
        OPER o{OPER(1), OPER(true), OPER(L"a")};
        drop(o, 0);
        ensure(o.size() == 3);
        ensure(o[2] == OPER(L"a"));
    }
    {
        const OPER o{OPER(1), OPER(true), OPER(L"a")};
        OPER o1 = drop(o, 0);
        ensure(o1.size() == 3);
        ensure (o1[2] == OPER(L"a"));
    }
    {
        OPER o{OPER(1), OPER(true), OPER(L"a")};
        o.resize(o.size(), 1);
        drop(o, 2);
        ensure(o.size() == 1);
        ensure(o[0] == OPER(L"a"));
    }
    {
        OPER o_{OPER(1), OPER(true), OPER(L"a")};
        o_.resize(o_.size(), 1);
        const OPER o{o_};
        OPER o1 = drop(o, 2);
        ensure(o1.size() == 1);
        ensure(o1[0] == o[2]);
    }
    {
        OPER o{OPER(1), OPER(true), OPER(L"a")};
        o.resize(o.size(), 1);
        drop(o, -2);
        ensure(o.size() == 1);
        ensure(o[0] == OPER(1));
    }
    {
        OPER o_{OPER(1), OPER(true), OPER(L"a")};
        o_.resize(o_.size(), 1);
        const OPER o{o_};
        OPER o1 = drop(o, -2);
        ensure(o1.size() == 1);
        ensure(o1[0] == o[0]);
    }
});

#endif // _DEBUG