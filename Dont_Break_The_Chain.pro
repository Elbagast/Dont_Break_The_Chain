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

SOURCES += main.cpp \
    chain/main_window.cpp \
    chain/chain_widget.cpp \
    chain/chain_table_model.cpp \
    chain/chain_data.cpp \
    chain/chain_tableview.cpp \
    chain/new_chain_dialog.cpp

HEADERS  += \
    chain/main_window.h \
    chain/quptr.h \
    chain/chain_widget.h \
    chain/chain_table_model.h \
    chain/chain_data.h \
    chain/chain_tableview.h \
    chain/new_chain_dialog.h

FORMS    += \
    chain/main_window.ui \
    chain/new_chain_dialog.ui

DISTFILES += \
    readme.md
