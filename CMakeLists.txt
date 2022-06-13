cmake_minimum_required(VERSION 3.5)

project(VCut VERSION 0.1 LANGUAGES CXX)

set(CMAKE_INCLUDE_CURRENT_DIR ON)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
 if (WIN32)
     INCLUDE_DIRECTORIES("win/ffmpeg/include")
     LINK_DIRECTORIES("win/ffmpeg/lib")
     INCLUDE_DIRECTORIES("win/include")
     LINK_DIRECTORIES("win/lib")
 endif (WIN32)

 if (${CMAKE_SYSTEM_NAME} MATCHES "Darwin")
     INCLUDE_DIRECTORIES("macos/ffmpeg/include")
     LINK_DIRECTORIES("macos/ffmpeg/lib")
     INCLUDE_DIRECTORIES("macos/include")
     LINK_DIRECTORIES("macos/lib")
 endif()

find_package(QT NAMES Qt6 REQUIRED COMPONENTS Widgets)
find_package(Qt${QT_VERSION_MAJOR} REQUIRED COMPONENTS Widgets Core OpenGLWidgets OpenGL Gui MultimediaWidgets Multimedia)

set(PROJECT_SOURCES
        main.cpp
        mainwindow.cpp mainwindow.h
        processhandler.h processhandler.cpp
        filelist.h filelist.cpp
        getfile.h getfile.cpp
        FileLine.h FileLine.cpp
        videoplayer.h videoplayer.cpp
        choosefile.h choosefile.cpp
        selectwidget.h selectwidget.cpp
        matchwidget.h matchwidget.cpp
        filestruct.h filestruct.cpp
        ffmpegwidget.h ffmpegwidget.cpp
        videoinfo.h videoinfo.cpp
        AbstructOption.h
        ffoptions.h ffoptions.cpp
)

if(${QT_VERSION_MAJOR} GREATER_EQUAL 6)
    qt_add_executable(VCut
        MANUAL_FINALIZATION
        ${PROJECT_SOURCES}
    )
# Define target properties for Android with Qt 6 as:
#    set_property(TARGET VCut APPEND PROPERTY QT_ANDROID_PACKAGE_SOURCE_DIR
#                 ${CMAKE_CURRENT_SOURCE_DIR}/android)
# For more information, see https://doc.qt.io/qt-6/qt-add-executable.html#target-creation
else()
    if(ANDROID)
        add_library(VCut SHARED
            ${PROJECT_SOURCES}
        )
# Define properties for Android with Qt 5 after find_package() calls as:
#    set(ANDROID_PACKAGE_SOURCE_DIR "${CMAKE_CURRENT_SOURCE_DIR}/android")
    else()
        add_executable(VCut
            ${PROJECT_SOURCES}
        )
    endif()
endif()

#target_link_libraries(VCut PRIVATE Qt${QT_VERSION_MAJOR}::Widgets Qt6::Core swscale avutil avformat avcodec avdevice avfilter postproc swresample swscale)
target_link_libraries(VCut PRIVATE Qt${QT_VERSION_MAJOR}::Widgets
                                    Qt${QT_VERSION_MAJOR}::Core
                                    Qt${QT_VERSION_MAJOR}::OpenGLWidgets
                                    Qt${QT_VERSION_MAJOR}::OpenGL
                                    Qt${QT_VERSION_MAJOR}::Gui
                                    Qt${QT_VERSION_MAJOR}::MultimediaWidgets
                                    Qt${QT_VERSION_MAJOR}::Multimedia
                                    QtAVPlayer
                                   )

set_target_properties(VCut PROPERTIES
    MACOSX_BUNDLE_GUI_IDENTIFIER my.example.com
    MACOSX_BUNDLE_BUNDLE_VERSION ${PROJECT_VERSION}
    MACOSX_BUNDLE_SHORT_VERSION_STRING ${PROJECT_VERSION_MAJOR}.${PROJECT_VERSION_MINOR}
    MACOSX_BUNDLE TRUE
    WIN32_EXECUTABLE TRUE
)

if(QT_VERSION_MAJOR EQUAL 6)
    qt_finalize_executable(VCut)
endif()
