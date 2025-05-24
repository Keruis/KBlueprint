add_library(Utils)

# H
target_sources(Blueprint PRIVATE

)

# CPP
target_sources(Blueprint PRIVATE

)

# IXX
target_sources(Utils
        PUBLIC
        FILE_SET CXX_MODULES FILES
        xml/xml.ixx
        json/json.ixx
)

target_sources(Utils
        PRIVATE
        xml/xml-impl.ixx
        json/json-impl.ixx
)

