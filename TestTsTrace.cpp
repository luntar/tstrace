/*!
 * \file TestTsTrace.cpp
 * 
 * ┌┬┐┌─┐┌┬┐┬─┐┌─┐┌─┐┌─┐
 *  │ └─┐ │ ├┬┘├─┤│  ├┤ 
 *  ┴ └─┘ ┴ ┴└─┴ ┴└─┘└─┘
 */
#include "TestTsTrace.h"

#include "trace/TsTrace.h"
#include "trace/VcdProducer.h"
#include "trace/TestThings.h"
#include <iostream>

using namespace tstrace;

int testTsTrace()
 {
     TSINIT();

     for (int Index = 0; Index < 25; Index++)
     {
         tstrace::basicTest();
     }

#if (TS_TRACE_ENABLED == 1)
     VcdProducer p (TSMEMORY);
     p.toFile (TSLOGNAME);
#else
     std::cout << "TsTrace is not enabled, see the macro TS_TRACE_ENABLED in trace/TsTrace.h\n";
#endif

     return 0;
 }
