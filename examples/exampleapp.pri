include(../app.pri)

win32*{
    DESTDIR = $$OUT_PWD/..
}
else{
    DESTDIR = $$OUT_PWD
}

LIBS += -L$$OUT_PWD/../../lib -lqsint

win32-msvc*{
    PRE_TARGETDEPS += $$OUT_PWD/../../lib/qsint.lib
}

