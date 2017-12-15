QT += core xml gui network widgets sql charts

TARGET = dana
TEMPLATE = app

##macx: CONFIG-=app_bundle

include(./../3rdparty/qtsingleapplication/src/qtsingleapplication.pri)
include(./../3rdparty/qtspeech/QtSpeech.pri)
include(dana.pri)



win32 {
   RC_FILE = dana.rc
}

unix {

    isEmpty(PREFIX) {
        PREFIX = /usr
    }

    target.path = $$PREFIX/bin

    shortcutfiles.files = dana.desktop
    shortcutfiles.path = $$PREFIX/share/applications/
    data.files += ./images/dana_96.png
    data.path = $$PREFIX/share/pixmaps/

    INSTALLS += shortcutfiles
}

INSTALLS += target

DISTFILES += \
    dana.desktop \
    dana.png
