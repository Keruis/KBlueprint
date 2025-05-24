add_library(BlueprintModules)

find_package(Qt6 COMPONENTS
        Core
        Gui
        Widgets
        REQUIRED)

# H
target_sources(Blueprint PRIVATE
        include/BlueprintClass.h
        include/BlueprintPort.h
        include/BlueprintFont.h
        include/BlueprintNode.h
)

# CPP
target_sources(Blueprint PRIVATE
        src/BlueprintClass.cpp
        src/BlueprintPort.cpp
        src/BlueprintFont.cpp
        src/BlueprintNode.cpp
)

# UI
target_sources(Blueprint PRIVATE
        ui/BlueprintClass.ui
)

# QRC
target_sources(Blueprint PRIVATE
        resources.qrc
)

# IXX
target_sources(BlueprintModules
        PUBLIC
        FILE_SET CXX_MODULES FILES
        Module/BlueprintPortType.ixx
        EventHelpers/EventHelpers.ixx
)

target_sources(BlueprintModules
        PRIVATE
        EventHelpers/EventHelpers-impl.ixx
)

set(RESOURCE_FILES
    resources.qrc
)

set(QRC_RESOURCE ${RESOURCE_FILES} PARENT_SCOPE)

target_link_libraries(BlueprintModules PRIVATE
        Qt6::Core Qt6::Widgets Qt6::Gui
)