add_library(Utils)

# H
target_sources(Blueprint PRIVATE
        xml/xml.h
        UI/ui_helpers.h
)

# CPP
target_sources(Blueprint PRIVATE
        xml/xml-impl.cpp
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

