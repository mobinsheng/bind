TEMPLATE = app
CONFIG += console c++11
CONFIG -= app_bundle
CONFIG -= qt

SOURCES += \
    test.cpp

HEADERS += \
    bind/bind.h \
    bind/closure.h \
    bind/scoped_ref_ptr.h \
    bind/template_util.h \
    lazy_closure.h
