# gui tests
add_catch2_executable(
        NAME
                gui-text
        SRCS
                main.cpp
                ../mock/buildTextDocument.cpp
                ../mock/multi-line-string.cpp
                ../mock/InitializedFontManager.cpp
                test-gui-Text.cpp
                test-gui-TextFixedSize.cpp
                test-gui-TextBlock.cpp
                test-gui-TextBlockCursor.cpp
                test-gui-TextDocument.cpp
                test-gui-TextLine.cpp
                test-gui-TextParse.cpp
                test-gui-Font.cpp
                test-gui-TextLineCursor.cpp
        INCLUDE
                ..
                ../mock/
        LIBS
                module-sys
                module-gui
	USE_FS
)
