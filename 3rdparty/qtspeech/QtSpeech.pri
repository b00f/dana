# QtSpeech -- a small cross-platform library to use TTS
# Copyright (C) 2010-2011 LynxLine.
#
# This library is free software; you can redistribute it and/or
# modify it under the terms of the GNU Lesser General Public
# License as published by the Free Software Foundation; either
# version 3 of the License, or (at your option) any later version.
#
# This library is distributed in the hope that it will be useful,
# but WITHOUT ANY WARRANTY; without even the implied warranty of
# MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
# Lesser General Public License for more details.
#
# You should have received a copy of the GNU Lesser General
# Public License along with this library; if not, write to the
# Free Software Foundation, Inc., 51 Franklin Street, Fifth Floor,
# Boston, MA 02110-1301 USA

DEPENDPATH += $$PWD
INCLUDEPATH += $$PWD

DEFINES += QTSPEECH_STATIC

HEADERS += \
    $$PWD/QtSpeech \
    $$PWD/QtSpeech.h \

macx {
    SOURCES += QtSpeech_mac.cpp
    LIBS *= -framework AppKit
}

win32 {


    SOURCES += $$PWD/QtSpeech_win.cpp

    ###LIBS += $$PWD/QtSpeech.vs2005.lib
    ###LIBS += $$PWD/sapi.lib
}

unix:!mac {
    HEADERS += QtSpeech_unx.h
    SOURCES += QtSpeech_unx.cpp

    INCLUDEPATH += $$PWD/festival/speech_tools/include
    INCLUDEPATH += $$PWD/festival/festival/src/include

    #instal fesival-dev before compile:
    # ubuntu:sudo apt-get install festival-dev
    LIBS += -lncurses
    LIBS += -lFestival
    LIBS += -lestools -lestbase -leststring

    # Linux: use asound
    LIBS += -lasound

    # Mac: use system Frameworks
    #LIBS += -framework CoreAudio -framework AudioUnit -framework AudioTooldeck -framework Carbon
}
