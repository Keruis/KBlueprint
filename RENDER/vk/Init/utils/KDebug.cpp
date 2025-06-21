#include "KDebug.h"

Vulkan::Utils::KDebugStream::KDebugStream(const char *file, int line, const char *func)
    : m_file(file),
      m_line(line),
      m_func(func)
{

}

Vulkan::Utils::KDebugStream::~KDebugStream() {
#if KDEBUG_ENABLED
    std::cerr << "\033[31m[DEBUG] " << m_file << ": " << m_line << " in " << m_func << ":\n\t"
              << m_stream.str() << "\033[0m" << std::endl;
#endif
}

