include(../app.pri)

DESTDIR = $$OUT_PWD/..

LIBS += -L$$OUT_PWD/../../lib -lqsint

PRE_TARGETDEPS += $$OUT_PWD/../../lib/qsint.lib
