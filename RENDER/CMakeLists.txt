add_library(Render)

# H
target_sources(Render PRIVATE
        vk/System.h
)

# CPP
target_sources(Render PRIVATE
        vk/System.cpp
)

target_link_libraries(Render
        PRIVATE Utils
)

