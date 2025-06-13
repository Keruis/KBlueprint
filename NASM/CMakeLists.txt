cmake_minimum_required(VERSION 3.10)

project(Asm_lib C ASM_NASM)

enable_language(ASM_NASM)
set(CMAKE_ASM_NASM_COMPILER nasm)

if(CMAKE_SYSTEM_PROCESSOR MATCHES "x86_64")
    set(NASM_FORMAT elf64)
else()
    set(NASM_FORMAT elf32)
endif()

set(CMAKE_ASM_NASM_OBJECT_FORMAT ${NASM_FORMAT})

file(GLOB_RECURSE ASM_SOURCES CONFIGURE_DEPENDS
        "${CMAKE_CURRENT_SOURCE_DIR}/src/*.asm"
)

add_library(Asm_lib STATIC ${ASM_SOURCES})

target_include_directories(Asm_lib PUBLIC
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
)