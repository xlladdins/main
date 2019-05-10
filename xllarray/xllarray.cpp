#include "xllarray.h"

using namespace xll;

#ifdef _DEBUG
AddIn doc_xllarray(
    Documentation(LR"xyz(
A <newTerm>range</newTerm> is a 2-dimensional array of cells.
This add-in provides functions that operate on ranges. It
is also possible to create in-memory ranges.

)xyz")
);
#endif

AddIn xai_range(
    Function(XLL_HANDLE, L"?xll_range", PREFIX L"RANGE")
    .Arg(XLL_WORD, L"rows", L"is the number of rows in the range.")
    .Arg(XLL_WORD, L"columns", L"is the number of columns in the range. Default is 1.")
    .Uncalced()
    .FunctionHelp(L"Return a handle to a range having the given rows and columns.")
    .Category(CATEGORY)
    .Documentation(L"Create a handle to a range.")
);
HANDLEX WINAPI xll_range(WORD r, WORD c)
{
#pragma XLLEXPORT
    handlex h;

    try {
        // 0x0 range is special
        if (c == 0 && r != 0)
            c = 1;

        handle<OPER> ho(new OPER(r, c));
        h = ho.get();
    }
    catch (const std::exception& ex) {
        XLL_ERROR(ex.what());
    }

    return h;
}

AddIn xai_range_set(
    Function(XLL_HANDLE, L"?xll_range_set", PREFIX L"RANGE.SET")
    .Arg(XLL_LPOPER, L"range", L"is a range.")
    .Uncalced()
    .FunctionHelp(L"Return a handle to a copy of range.")
    .Category(CATEGORY)
    .Documentation(L"Create a handle to range.")
);
HANDLEX WINAPI xll_range_set(LPOPER po)
{
#pragma XLLEXPORT
    handlex h;

    try {
        handle<OPER> ho(new OPER(*po));
        h = ho.get();
    }
    catch (const std::exception& ex) {
        XLL_ERROR(ex.what());
    }

    return h;
}

AddIn xai_range_get(
    Function(XLL_LPOPER, L"?xll_range_get", PREFIX L"RANGE.GET")
    .Arg(XLL_HANDLE, L"handle", L"is a handle created by " PREFIX "RANGE.")
    .FunctionHelp(L"Return a range given its handle.")
    .Category(CATEGORY)
    .Documentation(L"Convert a handle to a range to the underlying range.")
);
LPOPER WINAPI xll_range_get(HANDLEX h)
{
#pragma XLLEXPORT
    LPOPER po = nullptr;

    try {
        handle<OPER> ho(h);
        ensure (ho);
        po = ho.ptr();
    }
    catch (const std::exception& ex) {
        XLL_ERROR(ex.what());
    }

    return po;
}

