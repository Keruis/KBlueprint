add_library(UserGuide)

target_sources(UserGuide
        PRIVATE
        UserGuide.h
)

target_sources(UserGuide
        PRIVATE
        UserGuide.cpp
)

include(../cmake/ImportCS.cmake)

import_cs_library(UserGuide "${CMAKE_SOURCE_DIR}/UserGuide" USERGUIDE_LIB)

add_dependencies(UserGuide ${USERGUIDE_LIB})
target_link_libraries(UserGuide
        PRIVATE
        ${USERGUIDE_LIB}
)