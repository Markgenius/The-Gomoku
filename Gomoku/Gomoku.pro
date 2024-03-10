######################################################################
# Automatically generated by qmake (3.1) Sat Jun 12 03:10:47 2021
######################################################################

TEMPLATE = app
TARGET = Gomoku
INCLUDEPATH += .

# The following define makes your compiler warn you if you use any
# feature of Qt which has been marked as deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if you use deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

# Input
HEADERS += big_selector.h \
           black_chess.h \
           pass.h \
           select_black.h \
           select_white.h \
           small_selector.h \
           timer.h \
           wasted.h \
           white_chess.h \
           window_Gomoku.h
SOURCES += big_selector.cpp \
           black_chess.cpp \
           mainwindow.cpp \
           pass.cpp \
           select_black.cpp \
           select_white.cpp \
           small_selector.cpp \
           timer.cpp \
           wasted.cpp \
           white_chess.cpp \
           window_Gomoku.cpp
