QT       += core gui core5compat

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++17

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    FileLine.cpp \
    batch.cpp \
    ffmpegcontroller.cpp \
    hmstime.cpp \
    infoline.cpp \
    initlizer.cpp \
    main.cpp \
    mainwindow.cpp \
    outputfile.cpp \
    regex.cpp \
    textcommand.cpp \
    videocontrolplayer.cpp \
    videoplayer.cpp

HEADERS += \
    FileLine.h \
    batch.h \
    ffmpegcontroller.h \
    hmstime.h \
    infoline.h \
    initlizer.h \
    mainwindow.h \
    outputfile.h \
    regex.h \
    textcommand.h \
    videocontrolplayer.h \
    videoplayer.h

FORMS +=

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target
