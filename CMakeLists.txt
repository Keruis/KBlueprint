cmake_minimum_required(VERSION 3.31)
project(Blueprint)

set(CMAKE_CXX_STANDARD 26)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)
#set(CMAKE_CXX_MODULE_STD ON)

set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_AUTOUIC ON)

find_package(Qt6 COMPONENTS
        Core
        Gui
        Widgets
        OpenGLWidgets

        REQUIRED)

add_executable(Blueprint
    main.cpp
        MainWindow.cpp
        MainWindow.h
        MainWindow.ui
        CPUFeatures.h
        Title/TitleBar.cpp
        Title/icon.qrc
)

add_subdirectory(utils)
add_subdirectory(Container)
add_subdirectory(BlueprintMain)
add_subdirectory(IP/CPU)
add_subdirectory(Panels)

set(QRC_RESOURCE ${RESOURCE_FILES_BLUEPRINT} Title/icon.qrc)

qt_add_resources(Blueprint
        RESOURCE_FILES ${RESOURCE_FILES_BLUEPRINT}
)

target_link_libraries(Blueprint PRIVATE
        Qt6::Core Qt6::Widgets Qt6::Gui Qt6::OpenGLWidgets

        Utils Container BlueprintModules
)

#target_compile_options(Blueprint PRIVATE -fmodules)