# H
target_sources(Blueprint PRIVATE
        Explorer/explorer.h
        Terminal/terminal.h
        Terminal/CPUUsage.h
        RenderPreviewWidget/RenderPreviewWidget.h
)

# CPP
target_sources(Blueprint PRIVATE
        Explorer/explorer.cpp
        Terminal/terminal.cpp
        Terminal/CPUUsage.cpp
        RenderPreviewWidget/RenderPreviewWidget.cpp
        icons.qrc
)

set(PANELS_ICON_QRC
        icons.qrc
)

set(QRC_RESOURCE ${PANELS_ICON_QRC} PARENT_SCOPE)