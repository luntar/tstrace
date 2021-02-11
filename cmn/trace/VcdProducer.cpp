 /*!
 * \file VcdProducer.cpp
 * 
 * ┌┬┐┌─┐┌┬┐┬─┐┌─┐┌─┐┌─┐
 *  │ └─┐ │ ├┬┘├─┤│  ├┤ 
 *  ┴ └─┘ ┴ ┴└─┴ ┴└─┘└─┘
 */
#include "VcdProducer.h"

namespace tstrace
{
    
    void VcdProducer::toFile (std::string path)
    {
        std::ofstream of;
        of.open(path,std::ofstream::out | std::ofstream::trunc);
        
        if (of.is_open())
        {
            // #TODO: This is where the VCD file format logic goes
            // A proper VCD header and other sections need to be created.
            while(!m_iter.atEnd())
            {
                std::string chname;
                chname.append(m_iter.cur());
                if (chname.empty())
                {
                    break;
                }

                of << chname << " ";
                m_iter.adv (kChNameWidth);

                // This is a hack, this should be easy and fast, but I have only
                // used C++ for 25 years, so I don't yet know what to do.
                int64_t val64;
                memcpy(&val64,m_iter.cur(),sizeof(int64_t));
                m_iter.adv (kValueWidth);
                of << val64;
                of << " ";

                // This is a hack, this should be easy and fast, but I have only
                // used C++ for 25 years, so I don't yet know what to do.
                memcpy (&val64, m_iter.cur(), sizeof (int64_t));
                m_iter.adv (kTimeStampWidth);
                of << val64;
                of << "\n";
            }
            of.flush();
            of.close();
        }
    }

} // namespace tstrace