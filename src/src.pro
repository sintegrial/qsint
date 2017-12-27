TARGET = qsint

TEMPLATE = lib
CONFIG += staticlib c++11

QT += core gui widgets

DESTDIR = ../lib

include(actions/actions.pri)
include(widgets/widgets.pri)
include(charts/charts.pri)
