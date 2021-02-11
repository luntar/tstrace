/*!
 * \file MicroCounter.h
 * 
 * ┌┬┐┌─┐┌┬┐┬─┐┌─┐┌─┐┌─┐
 *  │ └─┐ │ ├┬┘├─┤│  ├┤ 
 *  ┴ └─┘ ┴ ┴└─┴ ┴└─┘└─┘
 *
 * \brief: MicroCounter is a static class that manages
 * access to the underlying systems timing facility.
 * 
 * Timing Facility Requirement: The counter must be
 * monotonic and must produced timing with microsecond 
 * glandularly.
 * 
 * NOTE: This file contains OS specific details partitioned
 * using platform defined compiler macros. It's ugly, sigh...
 * 
 */
#ifndef MICROCOUNTER_H
#define MICROCOUNTER_H

#if defined(_WIN32)
#include <windows.h>
#else
#error PLATFORM NOT SUPPORTED
#endif
#include <cstdint>



namespace tstrace
{
     static const int64_t kMicrosecondPerSecond = 1000000;
 
    class MicroCounter
    {
    public:
        /**
        * \brief:initialize the counter, this must be called
        * at least once before other methods are used.
        */
        static void init();

        /**
        * \brief:returns the number of microseconds since \ref init
        * was called.
        */
        static int64_t getDelta() noexcept;

        /**
        * \brief:returns the current clock tick in microseconds
        */
        static int64_t getNow() noexcept;

        /**
        * \brief:returns true if \ref init has been called
        */
        static bool isInit() noexcept;

    private:
#if defined(_WIN32)
        static LARGE_INTEGER gStartingTime;
        static LARGE_INTEGER gTicksPerSecond;
#elif defined(__APPLE__)

#endif
    };

    /**
    * \brief:called from a test program, verify the Micro Counter is working.
    */
    void testMicroCounter();

} // namespace tstrace
#endif // MICROCOUNTER_H
