#-------------------------------------------------
#
# Project created by QtCreator 2015-04-11T15:02:04
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = Dont_Break_The_Chain
TEMPLATE = app

# Compiler Flags
#==============================
# Getting MinGW to use C++14 features like std::make_unique
mingw {
    QMAKE_CXXFLAGS += -std=gnu++14
}



# Boost
#==============================
# Define custom variables to stitch together, these probably need to be edited for other systems
BOOST_INCLUDE_DIR = D:/Programming/C++/Boost/boost_1_57_0
BOOST_LIBRARY_DIR = $${BOOST_INCLUDE_DIR}/stage/lib
BOOST_LIBRARIES += boost_date_time

BOOST_COMPILER = -mgw49
BOOST_VERSION = -1_57
BOOST_THREADS = -mt
BOOST_DEBUG = -d

# Must specify the library for MinGW, if the filename is libfoobar-a-b-blah.a then this is -lfoobar-a-b-blah
#LIBS += -LD:/Programming/C++/Boost/boost_1_57_0/stage/lib
LIBS += -L$${BOOST_LIBRARY_DIR}
# debug versions
mingw:debug {

    # Simple way, do per library:
    #LIBS += -lboost_filesystem-mgw49-mt-d-1_57
    # Automated way:
    for(library, BOOST_LIBRARIES) {
        LIBS += -l$${library}$${BOOST_COMPILER}$${BOOST_THREADS}$${BOOST_DEBUG}$${BOOST_VERSION}
    }
}
# release versions
mingw:!debug {
    # Simple way, do per library:
    #LIBS += -lboost_filesystem-mgw49-mt-1_57
    # Automated way:
    for(library, BOOST_LIBRARIES) {
        LIBS += -l$${library}$${BOOST_COMPILER}$${BOOST_THREADS}$${BOOST_VERSION}
    }
}
# msvc doesn't need this, it can find the right .lib files on its own

INCLUDEPATH += $${BOOST_INCLUDE_DIR}
DEPENDPATH += $${BOOST_LIBRARY_DIR}


SOURCES += main.cpp \
    chain/main_window.cpp \
    chain/chain_widget.cpp \
    chain/chain_table_model.cpp \
    chain/chain_data.cpp \
    chain/link_data.cpp \
    chain/chain_tableview.cpp \
    chain/new_chain_dialog.cpp

HEADERS  += \
    chain/main_window.h \
    chain/quptr.h \
    chain/chain_widget.h \
    chain/chain_table_model.h \
    chain/chain_data.h \
    chain/link_data.h \
    chain/chain_tableview.h \
    chain/new_chain_dialog.h

FORMS    += \
    chain/main_window.ui \
    chain/new_chain_dialog.ui

DISTFILES += \
    readme.md
