#ifndef BLUEPRINT_KDEBUG_H
#define BLUEPRINT_KDEBUG_H

#include <iostream>
#include <sstream>
#include <string>
#include <utility>

namespace Vulkan::Utils {

#ifndef NDEBUG
    #define KDEBUG_ENABLED 1
#else
    #define KDEBUG_ENABLED 0
#endif

    class KDebugStream {
    public:
        KDebugStream(const char *file, int line, const char *func);

        ~KDebugStream();

        template<typename Ty_>
        KDebugStream &operator<<(Ty_ &&val) {
#if KDEBUG_ENABLED
            m_stream << std::forward<Ty_>(val) << ' ';
#endif
            return *this;
        }

    private:
        std::ostringstream  m_stream;
        const char *        m_file;
        int                 m_line;
        const char *        m_func;
    };
}
#if KDEBUG_ENABLED
    #define kDebug() ::Vulkan::Utils::KDebugStream(__FILE__, __LINE__, __func__)
#else
    class KDebugNoOp {
    public:
        template<typename T> constexpr KDebugNoOp& operator<<(T&&) { return *this; }
    };
    #define kDebug() KDebugNoOp()
#endif

#endif //BLUEPRINT_KDEBUG_H
