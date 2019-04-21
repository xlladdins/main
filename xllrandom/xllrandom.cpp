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
Enter <codeInline>=RANDOM.DISTRIBUTION.</codeInline><legacyItalic>DIST</legacyItalic>
<codeInline>(RANDOM_ENGINE_</codeInline><legacyItalic>ENG</legacyItalic><codeInline>, params...)</codeInline>"
to get a handle for a <legacyItalic>DIST</legacyItalic> that uses <legacyItalic>ENG</legacyItalic>.
Use <codeInline>=RANDOM.VARIATE.</codeInline><legacyItalic>TYPE</legacyItalic><codeInline>(handle)</codeInline>
with the handle returned by the first function to generate random variates of the <legacyItalic>TYPE</legacyItalic>
for the distribution.
</para> 
)xyz"
));
#endif
