CONFIG += c++1z
QMAKE_CXXFLAGS += -stdlib=libc++ -Wall
# QMAKE_CXXFLAGS += -stdlib=libc++ -fsanitize=address -Wall
QMAKE_LFLAGS += -lc++ -lc++abi

unix:!macx: LIBS += -L$$PWD/benchmark/build/src/ -lbenchmark

INCLUDEPATH += $$PWD/benchmark/include
DEPENDPATH += $$PWD/benchmark/build/src

unix:!macx: PRE_TARGETDEPS += $$PWD/benchmark/build/src/libbenchmark.a

SOURCES += \
    main.cpp
