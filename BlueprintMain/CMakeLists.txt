# H
target_sources(Blueprint PRIVATE
        include/BlueprintClass.h
        include/BlueprintPort.h
        include/BlueprintFont.h
)

# CPP
target_sources(Blueprint PRIVATE
        src/BlueprintClass.cpp
        src/BlueprintPort.cpp
        src/BlueprintFont.cpp
)

# UI
target_sources(Blueprint PRIVATE
        ui/BlueprintClass.ui
)

# IXX
target_sources(Blueprint PRIVATE
        FILE_SET CXX_MODULES
        FILES
        Module/BlueprintPortType.ixx
)