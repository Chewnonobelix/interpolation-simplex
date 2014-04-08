TEMPLATE = app
CONFIG += console
CONFIG -= app_bundle
CONFIG -= qt

SOURCES += main.cpp \
    point.cpp \
    simplexe.cpp \
    tree.cpp \
    abstractpavage.cpp \
    pavagenaif.cpp

HEADERS += \
    point.h \
    simplexe.h \
    tree.h \
    abstractpavage.h \
    pavagenaif.h

INCLUDEPATH += ./boost ./Eigen

DEFINES += STAGE40_FULL_EIGEN3_STRICTNESS
QMAKE_CXXFLAGS += -std=c++11
