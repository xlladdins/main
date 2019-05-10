// xllproduct.cpp - product ranges
#include "xllarray.h"

using namespace xll;

#if 0
AddIn xai_range_product(
    Function(XLL_LPOPER, L"?xll_range_product", PREFIX L"RANGE.PRODUCT")
    .Arg(XLL_LPOPER, L"range1", L"is a range.")
    .Arg(XLL_LPOPER, L"range2", L"is a range.")
    .FunctionHelp(L"Return the Cartesian product of range1 and range2.")
    .Category(CATEGORY)
    .Documentation(LR"xyz(
The result is a range have rows equal to the product of the rows and
columns equal to the sum of the columns of the range arguments.
)xyz")
);
LPOPER WINAPI xll_range_product(OPER const* pa, OPER const* pb)
{
#pragma XLLEXPORT
    static OPER o;

    try {
        o = product(*pa, *pb);
    }
    catch (const std::exception& ex) {
        XLL_ERROR(ex.what());

        o = OPER(xlerr::NA);
    }

    return &o;
}

#ifdef _DEBUG

test test_range_product([] {
    {
        OPER o{OPER(1), OPER(true), OPER(L"a")};
        product(o, o);
        ensure (o.rows() == 1);
        ensure (o.columns() == 6);
        ensure (o(0,5) == OPER(L"a"));
    }
    {
        OPER o{OPER(1), OPER(true), OPER(L"a")};
        product(o, o);
        ensure(o.rows() == 1);
        ensure(o.columns() == 6);
        ensure(o(0, 5) == OPER(L"a"));
        o.resize(2,3);
            product(o,o);
            /*
            ensure(o.rows() == 4);
        ensure(o.columns() == 6);
        ensure(o(3,5) == OPER(L"a"));
    */
    }
});

#endif // _DEBUG
#endif // 0