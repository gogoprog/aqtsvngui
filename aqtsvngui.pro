TEMPLATE = app
TARGET = aqtsvngui
QT += core \
    gui
HEADERS += src/treemodel.h \
    src/svnentry.h \
    src/svnmanager.h \
    src/mainwindow.h \
    src/aqtsvngui.h
SOURCES += src/treemodel.cpp \
    src/svnentry.cpp \
    src/svnmanager.cpp \
    src/mainwindow.cpp \
    src/main.cpp
FORMS += ui/aqtsvngui.ui
RESOURCES += 
