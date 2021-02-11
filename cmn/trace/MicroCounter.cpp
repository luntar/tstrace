/*!
 * \file MicroCounter.h
 * 
 * ┌┬┐┌─┐┌┬┐┬─┐┌─┐┌─┐┌─┐
 *  │ └─┐ │ ├┬┘├─┤│  ├┤ 
 *  ┴ └─┘ ┴ ┴└─┴ ┴└─┘└─┘
 * 
 */
#include "MicroCounter.h"
#include <assert.h>
#include <iostream>
#include "trace/TestThings.h"
#include "trace/TsTrace.h"


namespace tstrace
{

#if defined(_WIN32)
    LARGE_INTEGER MicroCounter::gStartingTime { 0 };
    LARGE_INTEGER MicroCounter::gTicksPerSecond { 0 };
#endif
    void MicroCounter::init()
    {
#if defined(_WIN32)
         /* Retrieves the frequency of the performance counter.
	        The frequency of the performance counter is fixed at system boot
	        and is consistent across all processors. Therefore, the frequency
	        need only be queried upon application initialization,
	        and the result can be cached.
	    */
        QueryPerformanceFrequency (&gTicksPerSecond);
        QueryPerformanceCounter (&gStartingTime);
#endif // defined(_WIN32)
    }

    int64_t MicroCounter::getDelta() noexcept
    {
        assert(isInit());
#if defined(_WIN32)
        LARGE_INTEGER endingTime;
        QueryPerformanceCounter (&endingTime);

        int64_t elapsedTime = endingTime.QuadPart - gStartingTime.QuadPart;

        // Convert ticks to desired time units
        elapsedTime = kMicrosecondPerSecond * elapsedTime;
        // To guard against loss-of- precision, convert *before*
        // dividing by ticks-per-second.
        elapsedTime /= gTicksPerSecond.QuadPart;
        return elapsedTime;
#else
        return static_cast<int64> (0);
#endif
    }

    int64_t MicroCounter::getNow() noexcept
    {
      assert(isInit());

#if defined(_WIN32)
        LARGE_INTEGER currentCounter;
        QueryPerformanceCounter (&currentCounter);
        currentCounter.QuadPart = kMicrosecondPerSecond * currentCounter.QuadPart;
        currentCounter.QuadPart /= gTicksPerSecond.QuadPart;
        return static_cast<int64_t> (currentCounter.QuadPart);
#else
        return static_cast<int64> (0);
#endif
    }

    bool MicroCounter::isInit() noexcept
    {
#if defined(_WIN32)
        return gTicksPerSecond.QuadPart != 0;
#else
        return false;
#endif
    }
    
    bool testMicroCounterInit()
    {
        bool rtval = false;
        if (MicroCounter::isInit())
        {
            std::cout << "Initialized\n";
            rtval = true;
        }
        else
        {
            std::cout << "Not Initialized\n";
        }
        return rtval;
    }

    void testMicroCounter()
    {
        CHECK_FALSE (testMicroCounterInit());
        TSINIT();
        CHECK_TRUE (testMicroCounterInit());

        auto ts = MicroCounter::getDelta();
        std::cout << "delta time: " << ts << "\n";
        std::vector<std::tuple<int64_t, int64_t, int64_t>> resultVector;
        for (int64_t usecs = 1000; usecs < 10000; usecs += 500)
        {
            for (int fff = 0; fff < 100; fff++)
            {
                auto st = MicroCounter::getNow();
                std::this_thread::sleep_for (std::chrono::microseconds (usecs));
                auto et = MicroCounter::getNow();
                auto delta = et - st;
                auto result = std::make_tuple (usecs, delta, delta - usecs);
                resultVector.push_back (result);
            }
        }
        int cnt = 0;
        for (auto [t, d, e] : resultVector)
        {
            std::cout << cnt++ << "," << t << "," << d << "," << e << "\n";
        }
    }

} // namespace tstrace
