// xllarray.h - Array and range functions
#pragma once
#include <algorithm>
#include "../xll12/xll/xll.h"

#ifndef CATEGORY
#define CATEGORY L"XLL"
#endif
#ifndef PREFIX
#define PREFIX CATEGORY L"."
#endif

namespace xll {

    // Return pointer to OPER if o is a handle, otherwise return a nullptr
    inline LPOPER is_handle(const OPER& o)
    {
        if (o.size() == 1 && o[0].xltype == xltypeNum) {
            handle<OPER> ho(o[0].val.num);
            if (ho)
                return ho.ptr();
        }

        return nullptr;
    }

    template<class O>
    inline void take(O& o, int n)
    {
        if (abs(n) <= o.size()) {
            if (n > 0) {
                o.resize(n, o.columns());
            }
            else if (n < 0) {
                std::copy(o.end() + n*o.columns(), o.end(), o.begin());
                o.resize(-n, o.columns());
            }
            else {
                o.resize(0,0);
            }
        }
    }
    template<class O>
    inline O take(const O& co, int n)
    {
        OPER o;

        if (abs(n) <= co.size()) {
            if (n > 0) {
                o.resize(n, o.columns());
                std::copy(co.begin(), co.begin() + n*co.columns(), o.begin());
            }
            else if (n < 0) {
                o.resize(-n, o.columns());
                std::copy(co.begin() + (co.rows() + n)*co.columns(), co.end(), o.begin());
            }
            else {
                o.resize(0, 0);
            }
        }
        else {
            o = co;
        }

        return o;
    }
    template<class O>
    inline O& drop(O& o, int n)
    {
        if (n < 0)
            return take(o, o.size() + n);
        else if (n > 0)
            return take(o, o.size() - n);

        return o;
    }

} // xll