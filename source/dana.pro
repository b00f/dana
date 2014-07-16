QT += core xml gui network widgets sql

TARGET = dana
TEMPLATE = app



include(./../3rdparty/qtsingleapplication/src/qtsingleapplication.pri)
include(./../3rdparty/qtspeech/QtSpeech.pri)
include(dana.pri)

win32 {
   RC_FILE = dana.rc
}
