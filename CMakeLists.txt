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
        REQUIRED)

add_executable(Blueprint
    main.cpp
        MainWindow.cpp
        MainWindow.h
        MainWindow.ui
)

add_subdirectory(BlueprintMain)

qt_add_resources(
        RESOURCE_FILES ${QRC_RESOURCE}
)

target_link_libraries(Blueprint PRIVATE
        Qt6::Core Qt6::Widgets Qt6::Gui
)

#target_compile_options(Blueprint PRIVATE -fmodules)