TARGET = qsint

TEMPLATE = lib
CONFIG += staticlib

QT += core gui widgets

DESTDIR = ../lib

include(actions/actions.pri)
include(widgets/widgets.pri)
include(charts/charts.pri)
