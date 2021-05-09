QT       += core gui \
               network \
               core5compat

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++11

# The following define makes your compiler emit warnings if you use
# any Qt feature that has been marked deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    game/gamemodel.cpp \
    game/gameview.cpp \
    game/gamewidget.cpp \
    game/keyboardinput.cpp \
    game/networksystem.cpp \
    mainmenu/loginwindow.cpp \
    mainmenu/mainwindow.cpp \
    mainmenu/changepassword.cpp \
    mainmenu/register.cpp \
    servicelogic.cpp \
    main.cpp

HEADERS += \
    game/gamemodel.h \
    game/gameview.h \
    game/gamewidget.h \
    game/networksystem.h \
    game/keyboardinput.h \
    mainmenu/loginwindow.h \
    mainmenu/mainwindow.h \
    mainmenu/changepassword.h \
    mainmenu/register.h \
    mainmenu/allurl.h \
    servicelogic.h

FORMS += \
    mainmenu/changepassword.ui \
    mainmenu/loginwindow.ui \
    mainmenu/mainwindow.ui \
    mainmenu/register.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

RESOURCES += \
    picture.qrc
