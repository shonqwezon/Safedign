QT       += core gui \
            network

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++17

SOURCES += \
    main.cpp \
    mainwindow.cpp \
    volumeos.cpp

HEADERS += \
    mainwindow.h \
    volumeos.h

FORMS += \
    mainwindow.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

#win32:CONFIG(release, debug|release): LIBS += -L$$PWD/../SafedignLib/x64/release/ -lSafedignLib
#else:win32:CONFIG(debug, debug|release): LIBS += -L$$PWD/../SafedignLib/x64/debug/ -lSafedignLib

#INCLUDEPATH += $$PWD/../SafedignLib
#DEPENDPATH += $$PWD/../SafedignLib

RESOURCES += \
    res.qrc

LIBS += -lole32

VERSION = 2.0.0.0
QMAKE_TARGET_COMPANY = SifeDign Inc.
QMAKE_TARGET_PRODUCT = Sifedign
QMAKE_TARGET_COPYRIGHT = Copyright © 2021 SifeDign Inc.
RC_ICONS += "icons/app.ico"



