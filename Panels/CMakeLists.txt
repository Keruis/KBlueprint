# H
target_sources(Blueprint PRIVATE
        Explorer/explorer.h
        Explorer/FileViewer.h
        Terminal/terminal.h
        Terminal/CPUUsage.h
        RenderPreviewWidget/RenderPreviewWidget.h
)

# CPP
target_sources(Blueprint PRIVATE
        Explorer/explorer.cpp
        Explorer/FileViewer.cpp
        Terminal/terminal.cpp
        Terminal/CPUUsage.cpp
        RenderPreviewWidget/RenderPreviewWidget.cpp
        icons.qrc
)

set(PANELS_ICON_QRC
        icons.qrc
)

set(QRC_RESOURCE ${PANELS_ICON_QRC} PARENT_SCOPE)