add_library(BlueprintModules)

find_package(Qt6 COMPONENTS
        Core
        Gui
        Widgets
        REQUIRED
)

# H
target_sources(Blueprint PRIVATE
        include/BlueprintClass.h
        include/BlueprintPort.h
        include/BlueprintFont.h
        include/BlueprintNode.h
        include/BlueprintConnection.h
        include/RegionItem.h
        Types/PortType.h
        Types/VarType.h
        Draw/PaintNode.h
        Draw/Background.h
)

# CPP
target_sources(Blueprint PRIVATE
        src/BlueprintClass.cpp
        src/BlueprintPort.cpp
        src/BlueprintFont.cpp
        src/BlueprintNode.cpp
        src/BlueprintConnection.cpp
        src/RegionItem.cpp
        Draw/PaintNode-impl.cpp
        Draw/Background.cpp
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
        EventHelpers/EventHelpers.ixx
        Types/DataType.ixx
        Types/NodeType.ixx
)

target_sources(BlueprintModules
        PRIVATE
        EventHelpers/EventHelpers-impl.ixx
        Types/DataType-impl.ixx
        Types/NodeType-impl.ixx
)

set(RESOURCE_FILES_BlUEPRINT
    resources.qrc
)

set(QRC_RESOURCE ${RESOURCE_FILES_BlUEPRINT} PARENT_SCOPE)

target_link_libraries(BlueprintModules PRIVATE
        Qt6::Core Qt6::Widgets Qt6::Gui Utils
)
