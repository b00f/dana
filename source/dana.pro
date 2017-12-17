QT += core xml gui network widgets sql charts texttospeech

TARGET = dana
TEMPLATE = app

##macx: CONFIG-=app_bundle

include(dana.pri)
include(./../3rdparty/singleapplication/singleapplication.pri)
DEFINES += QAPPLICATION_CLASS=QApplication


unix {

    isEmpty(PREFIX) {
        PREFIX = /usr
    }

    target.path = $$PREFIX/bin

    shortcutfiles.files = dana.desktop
    shortcutfiles.path = $$PREFIX/share/applications/
    pixmap.files = ./images/dana_96.png
    pixmap.path = $$PREFIX/share/pixmaps/

    INSTALLS += shortcutfiles
    INSTALLS += pixmap
}

INSTALLS += target

DISTFILES += \
    dana.desktop \
    ./images/dana_96.png
