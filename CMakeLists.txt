cmake_minimum_required(VERSION 3.31)
project(Blueprint)

set(CMAKE_CXX_STANDARD 26)
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

target_link_libraries(Blueprint
        Qt6::Core Qt6::Widgets Qt6::Gui
)
