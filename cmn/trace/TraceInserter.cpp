/*!
 * \file TraceInserter.h
 * 
 * ┌┬┐┌─┐┌┬┐┬─┐┌─┐┌─┐┌─┐
 *  │ └─┐ │ ├┬┘├─┤│  ├┤ 
 *  ┴ └─┘ ┴ ┴└─┴ ┴└─┘└─┘
 * 
 */
#include "TraceInserter.h"

namespace tstrace
{
    TraceInserter::TraceInserter (TraceMemory& bm)
        : m_buffer (bm)
    {
        iter = std::make_unique<BufIter> (m_buffer);
    }

    void TraceInserter::add (const char* chname, int64_t value, int64_t ts)
    {
        size_t chNameSz = strlen (chname);
        strcpy_s (iter->cur(), chNameSz+1, chname);
        iter->adv (kChNameWidth);

        *((int64_t*) iter->cur()) = value;
        iter->adv64();

        *((int64_t*) iter->cur()) = ts;
        iter->adv64();
    }
} // namespace tstrace