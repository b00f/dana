/* * Dana - Dana, Symbol of Wisdom
 * Copyright (C) 2014 Mostafa Sedaghat Joo (mostafa.sedaghat@gmail.com)
 *
 * This file is part of Dana.
 *
 * Dana is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * Dana is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with Dana.  If not, see <http://www.gnu.org/licenses/>.
 */

#ifndef __CONTANTS_H
#define __CONTANTS_H

//#include "qxsettings.h"
#include "strings.h"
#include "utils.h"

#include <QCoreApplication>
#include <QSettings>
#include <QString>
#include <QObject>
#include <QColor>
#include <QDir>

#define GET_PERCENT(no,total)  (total==0) ? 100 : ((no*100)/(total));

#define SEC_2_MSEC(s)   (s*1000)
#define MIN_2_MSEC(m)   (m*60*1000)

#define zap(x)    if(x){delete x; x=0;}
#define zaparr(x) if(x){delete []x; x=0;}

#define SET_FLAG(f,v)     (f=(f|v))
#define UNSET_FLAG(f,v)   (f=(f&~v))
#define TURN_FLAG(f,v)    (f=(f^v))
#define IS_FLAG_SET(f,v)  ((f&v)==v)


static const QString APP_NAME     = QString("Dana");
static const QString APP_TITLE    = QString("Dana");
static const QString xml_suffix   = QString("xml");
static const QString cards_suffix = QString("cards");  /// Mnemosyne files
static const QString txt_suffix   = QString("txt");
static const QString dana_suffix  = QString("dana");


enum Versions {
    FIRST_VERSION           = 100,
    ENABLE_NETWORK_MANAGER  = 101,
    ADD_CARD_INFO           = 102,
    LAST_VERSION                 ,
};


enum Levels {
    Level_ALL       = -1, /// All cards on progress decks
    Level_1         = 0 ,
    Level_2             ,
    Level_3             ,
    Level_4             ,
    Level_5             ,

    LevelCount          ,
    Level_Retired = LevelCount,
    Level_Starred       ,
};

static const QString LevelsName[LevelCount+1] = {
    STR_LEVEL_1      ,
    STR_LEVEL_2      ,
    STR_LEVEL_3      ,
    STR_LEVEL_4      ,
    STR_LEVEL_5      ,
    STR_LEVEL_RETIRED,
};

static const QColor LevelsColor[LevelCount+1] = {
    QColor(220,20,60),
    QColor(139,0,139),
    QColor(70,130,180),
    QColor(60,179,113),
    QColor(34,139,34),
    QColor(0,0,0),
};


static inline int appVersion() {
    return LAST_VERSION-1;
}

static inline QString appVersionString() {
    return QString::number(appVersion());
}

static inline QString appPath() {
    QDir appDir = QDir(qApp->applicationDirPath());
#ifdef Q_OS_MAC
    /*
     * if (appDir.dirName() == "MacOS") {
        appDir.cdUp();
        appDir.cdUp();
        appDir.cdUp();
    }*/
#endif
    return appDir.absolutePath();
}

static inline QString danaPath() {
    QString path = QSettings().value("dana_folder").toString();

    if(path.isEmpty())
        path = QDir::homePath() + "/.dana";

    utils::createDirectory(path);

    return path;
}

static inline QString dBPath() {

    QString dbPath =
        utils::combinePaths(danaPath(), "dana.sqlite");

    return dbPath;
}

static inline QString tempPath() {
    QString tempPath =
        utils::combinePaths(QDir::tempPath(), "Dana");

    utils::createDirectory(tempPath);

    return tempPath;
}

static inline QString cardNumberToString(int count) {
    if(count == 0)
        return STR_CARD_NUMBER_EMPTY;

    if(count == 1)
        return STR_CARD_NUMBER_ONE;

    return STR_CARD_NUMBER_MORE.arg(count);
}

#define XML_TAG_ROOT                QString("dana")
#define XML_TAG_VERSION             QString("version")
#define XML_TAG_DECKS               QString("decks")
#define XML_TAG_DECK                QString("deck")
#define XML_TAG_ID                  QString("id")
#define XML_TAG_NAME                QString("name")
#define XML_TAG_DESC                QString("desc")
#define XML_TAG_ICON                QString("icon")
#define XML_TAG_GUID                QString("guid")
#define XML_TAG_CREATED             QString("created")
#define XML_TAG_UPDATED             QString("updated")
#define XML_TAG_AUTHOR              QString("author")
#define XML_TAG_TAGS                QString("tags")
#define XML_TAG_FLAGS               QString("flags")
#define XML_TAG_INHAND              QString("inhand")
#define XML_TAG_DOWNLOADS           QString("downloads")
#define XML_TAG_CARDS               QString("cards")
#define XML_TAG_CARD                QString("card")
#define XML_TAG_FRONT               QString("front")
#define XML_TAG_BACK                QString("back")
#define XML_TAG_RATING              QString("rating")
#define XML_TAG_FORMAT              QString("format")
#define XML_TAG_FORMAT_FONT         QString("font")
#define XML_TAG_FORMAT_FOREGROUND   QString("foreground")
#define XML_TAG_FORMAT_ALIGNMENT    QString("alignment")
#define XML_TAG_FORMAT_POLICY       QString("policy")

#endif // __CONTANTS_H
