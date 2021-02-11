 /*!
 * \file TraceInserter.h
 * 
 * ┌┬┐┌─┐┌┬┐┬─┐┌─┐┌─┐┌─┐
 *  │ └─┐ │ ├┬┘├─┤│  ├┤ 
 *  ┴ └─┘ ┴ ┴└─┴ ┴└─┘└─┘
 * 
 */
#ifndef _TRACEINSERTER_H
#define _TRACEINSERTER_H

#include <cstdint>
#include "trace/TraceMemory.h"
#include <memory>
#include <algorithm>
namespace tstrace
{
    const size_t kFrameSize = sizeof(int64_t)*4;
    const size_t kChNameWidth = sizeof(int64_t)*2;
    const size_t kValueWidth = sizeof(int64_t);
    const size_t kTimeStampWidth = sizeof(int64_t);
    const size_t kOffsetToTs =  sizeof(int64_t)*3;
    const size_t kOffsetToValue =  sizeof(int64_t)*2;

    struct BufIter
    {
        BufIter (TraceMemory& bm)
            : m_bm (bm) {}

        uint8_t* data() {
            return m_bm.data();
        }

        char* cur()
        {
            return (char*) m_bm.data() + m_idx;
        }

        void adv64 ()
        {
            m_idx += sizeof(int64_t);
        }

        void adv()
        {
            m_idx += 1;
        }

        void adv (size_t sz)
        {
            m_idx += sz;
        }
        bool atEnd() const {
            return m_idx >= m_bm.size();
        }

        size_t m_idx { 0 };

        TraceMemory& m_bm;
    };

    class BufOIter : public BufIter
    {
        public: 


    };
    class TraceInserter 
    {
        

    public:
        
        TraceInserter(TraceMemory& bm);
        
        void add(const char* chname, int64_t value, int64_t ts);

    private:
        TraceMemory& m_buffer;
        std::unique_ptr<BufIter> iter;
    };
}
#endif // _TRACEINSERTER_H