add_library(Container Module/Detail.ixx
        )

# H
target_sources(Blueprint PRIVATE
        Vec/Vector.h
        Module/Detail.h
)

# CPP
target_sources(Blueprint PRIVATE
        Vec/Vector.tpp
)

target_sources(Container PUBLIC
        FILE_SET CXX_MODULES
        FILES
        Module/Detail.ixx
)

