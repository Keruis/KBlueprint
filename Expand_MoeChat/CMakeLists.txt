add_library(MoeChat)

find_package(Qt6 COMPONENTS
        Core
        Gui
        Widgets
        Network
        Multimedia
        REQUIRED)

# H
target_sources(MoeChat PRIVATE
        ChatWidget.h
        ContentContainer.h
        ChatInterface.h
        AvatarWidget.h
        ChatMessageItem.h
        ChatMessageBubble.h
        Markdown.h
        FloatingSidebar.h
        AudioPlayer.h
        TipButton.h
)

# CPP
target_sources(MoeChat PRIVATE
        ChatWidget.cpp
        ContentContainer.cpp
        ChatInterface.cpp
        AvatarWidget.cpp
        ChatMessageItem.cpp
        ChatMessageBubble.cpp
        FloatingSidebar.cpp
        TipButton.cpp
        AudioPlayer.cpp
        resource.qrc
)

qt_add_resources(MoeChat
        RESOURCE_FILES resource.qrc
)

target_link_libraries(MoeChat PRIVATE
        Qt6::Core
        Qt6::Widgets
        Qt6::Gui
        Qt6::Network
        Qt6::Multimedia
        Http
)