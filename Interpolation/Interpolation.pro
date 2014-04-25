TEMPLATE = app
CONFIG += console
CONFIG -= app_bundle
CONFIG -= qt

SOURCES += main.cpp \
    point.cpp \
    simplexe.cpp \
    tree.cpp \
    abstractpavage.cpp \
    pavagenaif.cpp \
#    parser.cpp

HEADERS += \
    point.h \
    simplexe.h \
    tree.h \
    abstractpavage.h \
    pavagenaif.h \
#    parser.h

INCLUDEPATH += ./boost

QMAKE_CXXFLAGS += -std=c++11

OTHER_FILES += \
    fichier.txt
