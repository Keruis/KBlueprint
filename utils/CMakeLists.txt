add_library(Utils)

find_package(X11 REQUIRED)

# H
target_sources(Blueprint PRIVATE
        xml/xml.h
        UI/ui_helpers.h
        window/X11.h
)

# CPP
target_sources(Blueprint PRIVATE
        xml/xml-impl.cpp
        window/X11.cpp
)

# IXX
target_sources(Utils
        PUBLIC
        FILE_SET CXX_MODULES FILES

        json/json.ixx
)

target_sources(Utils
        PRIVATE

        json/json-impl.ixx
)

target_link_libraries(Utils
        PRIVATE ${X11_LIBRARIES}
)

