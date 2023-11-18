QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets printsupport

CONFIG += c++17 c

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    ../s21_validator.c \
    calcPage.cpp \
    creditPage.cpp \
    depositPage.cpp \
    graphPage.cpp \
    main.cpp \
    mainwindow.cpp \
    ../s21_stack.c \
    ../s21_common_funcs.c \
    ../s21_lexem_parse.c \
    ../s21_calculate.c \
    qcustomplot.cpp

HEADERS += \
    ../s21_validator.h \
    mainwindow.h \
    ../s21_stack.h \
    ../s21_common_funcs.h \
    ../s21_lexem_parse.h \
    ../s21_calculate.h \
    qcustomplot.h

FORMS += \
    mainwindow.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target
