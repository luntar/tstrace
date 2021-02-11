/*!
 * \file TraceMemory.h
 * 
 * ┌┬┐┌─┐┌┬┐┬─┐┌─┐┌─┐┌─┐
 *  │ └─┐ │ ├┬┘├─┤│  ├┤ 
 *  ┴ └─┘ ┴ ┴└─┴ ┴└─┘└─┘
 *
 * \brief: TraceMemory is a class that manages the memory used
 * by the tstrace system.
 * 
 * The underlining storage of TraceMemory is a 
 * std::vector<uint8_t>.  Given it's capacity,
 * the memory is reserved and initialized with zeros.
 */
#ifndef TRACEMEMORY_H
#define TRACEMEMORY_H

#include <cstdint>
#include <vector>
#include <algorithm>

namespace tstrace
{
    using BufferType_t = std::vector<uint8_t>;

    class TraceMemory
    {
        BufferType_t m_buffer;

    public:
        explicit TraceMemory (size_t capacity)
        {
            setCapacity (capacity);
        }

        BufferType_t& vec()
        {
            return m_buffer;
        }
        operator void*()
        {
            return static_cast<void*> (data());
        }

        operator size_t() const
        {
            return size();
        }

        uint8_t* data()
        {
            return m_buffer.data();
        }
        size_t size() const
        {
            return m_buffer.size();
        }

        void setCapacity (size_t capacity)
        {
            m_buffer.reserve (capacity);
            for (size_t ctr = 0; ctr < capacity; ctr++)
            {
                m_buffer.push_back (0);
            }
        }
    };
} // namespace tstrace
#endif // TRACEMEMORY_H
