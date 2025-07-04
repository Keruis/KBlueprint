cmake_minimum_required(VERSION 3.31)
project(Blueprint)

set(CMAKE_CXX_STANDARD 26)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)
#set(CMAKE_CXX_MODULE_STD ON)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -O3")

set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_AUTOUIC ON)

find_package(Qt6 COMPONENTS
        Core
        Gui
        Widgets
        OpenGLWidgets
        Svg
        Multimedia
        REQUIRED)

add_executable(Blueprint
    main.cpp
        MainWindow.cpp
        MainWindow.h
        MainWindow.ui
        CPUFeatures.h
        Attribute.h
        Title/TitleBar.cpp
        RadialMenu/RadialMenu.cpp
        SplashWindow/SplashWindow.cpp
        Title/icon.qrc
        resources.qrc
        Expand_MoeChat/resource.qrc
)

add_compile_options(-Wno-ignored-attributes)

add_subdirectory(utils)
add_subdirectory(Container)
add_subdirectory(BlueprintMain)
add_subdirectory(IP/CPU)
add_subdirectory(Panels)
add_subdirectory(widgets)
add_subdirectory(HTTP)
add_subdirectory(UserGuide)
add_subdirectory(NASM)
add_subdirectory(Expand_MoeChat)
add_subdirectory(RENDER)

set(QRC_RESOURCE ${RESOURCE_FILES_BLUEPRINT} ${PANELS_ICON_QRC} Title/icon.qrc resources.qrc Expand_MoeChat/resource.qrc)

qt_add_resources(Blueprint
        RESOURCE_FILES ${RESOURCE_FILES_BLUEPRINT}
)

target_link_libraries(Blueprint PRIVATE
        Qt6::Core
        Qt6::Widgets
        Qt6::Gui
        Qt6::OpenGLWidgets
        Qt6::Svg
        Qt6::Multimedia

        Utils Container BlueprintModules Http UserGuide Asm_lib MoeChat Render
)

#target_compile_options(Blueprint PRIVATE -fmodules)