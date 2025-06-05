# H
target_sources(Blueprint PRIVATE
        Explorer/explorer.h
        Explorer/FileViewer.h
        Terminal/terminal.h
        SystemMonitor/CPUUsage.h
        RenderPreviewWidget/RenderPreviewWidget.h

        Auxiliary/BottomBar.h
        Auxiliary/LeftToolBar.h
)

# CPP
target_sources(Blueprint PRIVATE
        Explorer/explorer.cpp
        Explorer/FileViewer.cpp
        Terminal/terminal.cpp
        SystemMonitor/CPUUsage.cpp
        RenderPreviewWidget/RenderPreviewWidget.cpp
        icons.qrc

        Auxiliary/BottomBar.cpp
        Auxiliary/LeftToolBar.cpp
)

set(PANELS_ICON_QRC
        icons.qrc
)

set(QRC_RESOURCE ${PANELS_ICON_QRC} PARENT_SCOPE)