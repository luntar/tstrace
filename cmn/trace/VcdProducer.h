/*!
 * \file VcdProducer.h
 * 
 * ┌┬┐┌─┐┌┬┐┬─┐┌─┐┌─┐┌─┐
 *  │ └─┐ │ ├┬┘├─┤│  ├┤ 
 *  ┴ └─┘ ┴ ┴└─┴ ┴└─┘└─┘
 * 
 * \brief: This class is given a BufferMemory object
 * that contains the raw trace data and produces a
 * VCD file. For more information about the VCD 
 * file format, please see: 
 * https://en.wikipedia.org/wiki/Value_change_dump
 */
#ifndef _VCDPRODUCER_H
#define _VCDPRODUCER_H
#include <string>
#include <fstream>

#include "trace/TraceMemory.h"
#include "trace/TraceInserter.h"
#include "trace/TsTrace.h"

namespace tstrace
{
    /**
     * \class: The VcdProducer class transforms a raw trace buffer
     * into a VCD file.
     */
    class VcdProducer
    {
    public:

        /**
        * \brief: instantiate this class with the trace buffer object.
        */
        VcdProducer (TraceMemory& bmem)
            : m_iter (bmem) { }

        /**
        * \brief:For the given full filepath, create a VCD file
        * from the raw trace data.
        */
        void toFile (std::string path);

        /**
        * \brief: return a pointer to the underlying trace data buffer
        */
        uint8_t* data()
        {
            return m_iter.data();
        }

    private:
        BufIter m_iter;
    };
} // namespace tstrace
#endif // _VCDPRODUCER_H