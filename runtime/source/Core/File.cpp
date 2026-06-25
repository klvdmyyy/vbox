#include "Core/File.h"

namespace ERUNTIME_NAMESPACE
{
    File::File(const std::filesystem::path& filepath)
    {
        m_File.open(filepath, std::ios::in | std::ios::binary);
    }

    File::~File()
    { m_File.close();
    }

    String File::ReadStr()
    {
      if (!m_File)
        return "";

        String result;

        m_File.seekg(0, std::ios::end);
        size_t size = m_File.tellg();
        if(size != -1)
        {
            result.resize(size);
          m_File.seekg(0, std::ios::beg);
            m_File.read(&result[0], size);
        }
        else
        {
            /* TODO: Log the error. Couldn't read from file! */
        }

        return result;
    }
}