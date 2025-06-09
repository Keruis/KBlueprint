add_library(Http)

target_sources(Http
        PRIVATE
        HttpClient.h
)

target_sources(Http
        PRIVATE
        HttpClient.cpp
)

include(../cmake/ImportRust.cmake)

import_rust_library(http ${CMAKE_SOURCE_DIR}/Rust RUST_TARGET)

add_dependencies(Http ${RUST_TARGET})
target_link_libraries(Http
        PRIVATE
        ${RUST_TARGET}
        ssl
        crypto
)