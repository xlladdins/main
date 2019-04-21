// xllrandom.cpp
#include "../xll12/xll/shfb/entities.h"
#include "xllrandom.h"

using namespace xll;

#ifdef _DEBUG
AddIn doc_xllrandom(
    Documentation(LR"xyz(
Implementation of the C++ &lt;random&gt; library.
This library allows you to specify a distribution and an engine that returns a handle to the appropriate
random variate generator for boolean, integer, or floating point values.
<para>
Enter <codeInline>=RANDOM.DISTRIBUTION.</codeInline>name<codeInline>(RANDOM_ENGINE_name, params...)</codeInline>
</para>
)xyz")
);
#endif
