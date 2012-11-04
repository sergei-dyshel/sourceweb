QT += core

TARGET = clang-indexer
TEMPLATE = app

SOURCES += \
    main.cc \
    ASTIndexer.cc \
    IndexerPPCallbacks.cc \
    TUIndexer.cc \
    IndexBuilder.cc \
    IndexerContext.cc \
    NameGenerator.cc \
    Util.cc \
    DaemonPool.cc \
    Process.cc

HEADERS += \
    Switcher.h \
    ASTIndexer.h \
    Location.h \
    IndexerPPCallbacks.h \
    TUIndexer.h \
    IndexBuilder.h \
    IndexerContext.h \
    NameGenerator.h \
    Util.h \
    DaemonPool.h \
    Process.h

DEFINES        += JSON_IS_AMALGAMATION
INCLUDEPATH    += ../third_party/libjsoncpp
PRE_TARGETDEPS += $${OUT_PWD}/../third_party/libjsoncpp/libjsoncpp.a
LIBS           += $${OUT_PWD}/../third_party/libjsoncpp/libjsoncpp.a

PRE_TARGETDEPS += $${OUT_PWD}/../libindexdb/libindexdb.a
LIBS           += $${OUT_PWD}/../libindexdb/libindexdb.a

INCLUDEPATH    += ../third_party/libsnappy
PRE_TARGETDEPS += $${OUT_PWD}/../third_party/libsnappy/libsnappy.a
LIBS           += $${OUT_PWD}/../third_party/libsnappy/libsnappy.a

target.path = /
INSTALLS += target

QMAKE_CXXFLAGS += -std=c++0x
QMAKE_CXXFLAGS_WARN_ON += -Wno-unused-parameter

include(../clang.pri)
