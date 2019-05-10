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
    inline void drop(O& o, int n)
    {
        if (abs(n) >= o.size()) {
            o.resize(0,0);
        }
        else if (n > 0) {
            std::copy(o.begin() + n*o.columns(), o.end(), o.begin());
            o.resize(o.rows() - n, o.columns());
        }
        else if (n < 0) {
            o.resize(o.rows() + n, o.columns());
        }
    }
    template<class O>
    inline O drop(const O& co, int n)
    {
        OPER o;

        if (abs(n) >= co.rows()) {
            o.resize(0,0);
        }
        else if (n > 0) {
            o.resize(co.rows() - n, co.columns());
            std::copy(co.begin() + n*o.columns(), co.end(), o.begin());
        }
        else if (n < 0) {
            o.resize(co.rows() + n, co.columns());
            std::copy(co.begin(), co.end() + n*o.columns(), o.begin());
        }
        else {
            o = co;
        }

        return o;
    }

    // pad empty rows, columns to right, bottom of array

    // Cartesian product of arrays
    template<class O>
    inline void product(O& a, const O& b)
    {
        auto ar = a.rows();
        auto ac = a.columns();
        auto br = b.rows();
        auto bc = b.columns();

        a.resize(ar*br, ac + bc);

        for (int i = 0; i < a.rows(); ++i) {
            for (int j = 0; j < br; ++j) {
                // copy a row i
                std::copy(&a(i%ar,0), &a(i%ar,ac), &a(i+j,0));
                // copy b row j
                std::copy(&b(j, 0), &b(j, bc), &a(i+j, ac));
            }
        }
    }
    template<class O>
    inline O product(const O& a, const O& b)
    {
        O o = a;

        product(o, b);

        return o;
    }

    template<class O>
    inline O product(size_t n, const O* const os)
    {
        O o;

        if (n > 0)
            o = os[0];

        for (size_t i = 0; i < n; ++i) {
            product(o, os[i]);
        }

        return o;
    }

} // xll