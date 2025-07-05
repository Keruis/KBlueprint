/*
 * File:    KDebug.cpp
 * Author:  Keruis
 * Date:    2025-07-05
 * Project: Blueprint Vulkan Renderer
 * Brief:   KDebugStream 类的具体实现，提供调试模式下的日志输出。
 *
 * Description:
 *   This file implements the KDebugStream class defined in KDebug.h.
 *   It formats and prints debug information (file, line, function, message)
 *   to the standard output, but only when compiled in debug mode.
 *
 *   本实现文件定义了调试输出类 KDebugStream 的构造与析构行为，
 *   在 Debug 模式下将日志信息（包括文件、行号、函数名）输出到控制台。
 *   在 Release 模式下，这些输出不会产生实际代码。
 *
 * License: MIT License
 */

#include "KDebug.h"

Vulkan::Utils::KDebugStream::KDebugStream
(const char *file, int line, const char *func)
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

