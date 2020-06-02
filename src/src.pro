TARGET = qsint

TEMPLATE = lib
CONFIG += staticlib c++11

win32-msvc*{
    QMAKE_CXXFLAGS += /MP
    QMAKE_CXXFLAGS += /Zi
    QMAKE_CXXFLAGS += /Gy
    QMAKE_CXXFLAGS += /FS
}

QT += core gui widgets

DESTDIR = ../lib

include(actions/actions.pri)
include(widgets/widgets.pri)
include(charts/charts.pri)
