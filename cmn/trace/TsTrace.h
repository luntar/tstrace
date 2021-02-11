/*!
 * \file TsTrace.h
 * 
 * ┌┬┐┌─┐┌┬┐┬─┐┌─┐┌─┐┌─┐
 *  │ └─┐ │ ├┬┘├─┤│  ├┤ 
 *  ┴ └─┘ ┴ ┴└─┴ ┴└─┘└─┘
 *
 * \brief: This is the main include for the 
 * Time Stamp Trace (TsTrace) system.
 * 
 * HOW TO USE
 * ==============================================
 * 
 * TS_TRACE_ENABLED 
 *      set to 1 to enable
 *      set to 0 to disable
 * 
 * MACRO INTERFACE
 * ---------------------------------------------
 *  TSINIT() must be called once before the system is used.
 * 
 *  TSON(<channel name>) to emit a value of 1 on <channel name>
 * 
 *  TSOFF(<channel name>) to emit a value of 0 on <channel name>
 * 
 * MEMORY SIZE
 * -----------------------------------------------------
 *  
 * Use kTraceMemoryCapacity to set the trace memory size
 */
#ifndef TSTRACE_H
#define TSTRACE_H

#include "trace/MicroCounter.h"
#include "trace/TraceMemory.h"
#include "trace/TraceInserter.h"
#include <thread>
#include <chrono>

#define TS_TRACE_ENABLED 1

#define TSLOGNAME "tstrace.vcd"

namespace tstrace
{
    static const size_t kTraceMemoryCapacity = 1024 * 1024;

#if (TS_TRACE_ENABLED == 1)

    // Global static object that implement the trace memory and
    // the "inserter" logic.
    inline TraceMemory gTsTraceMemory (kTraceMemoryCapacity);
    inline TraceInserter gTracer (gTsTraceMemory);

#define TSMEMORY gTsTraceMemory

#define TSINIT() \
    tstrace::MicroCounter::init();

#define TSON(CH) \
    gTracer.add (CH, 1, MicroCounter::getDelta())

#define TSOFF(CH) \
    gTracer.add (CH, 0, MicroCounter::getDelta())

#define TSSLEEP_US(US) \
    std::this_thread::sleep_for (std::chrono::microseconds (US))

#define TSSLEEP_MS(MS) \
    std::this_thread::sleep_for (std::chrono::milliseconds (MS))

#else
#define TSINIT()
#define TSON(CH)
#define TSOFF(CH)
#define TSSLEEP_US(US)
#define TSSLEEP_MS(MS)
#define TSMEMORY (void)0
#endif

    inline void basicTest()
    {
        TSON ("AAA");
        TSOFF ("AAA");

        TSSLEEP_US (200);

        TSON ("BBB");
        TSSLEEP_US (100);
        TSOFF ("BBB");

        TSSLEEP_US (200);

        TSON ("SSS");
        TSSLEEP_US (150);
        TSOFF ("SSS");
    }

} // namespace tstrace

#endif // TSTRACE_H
