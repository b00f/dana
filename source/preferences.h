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

#ifndef __PREFERENCES_H
#define __PREFERENCES_H


#include "singleton.h"

#include <QString>


class Preferences
    : public CSingleton<Preferences>
{
public:
    Preferences(void);
    ~Preferences(void);

    void load();
    void save();

    int getQueryInterval();
    void setQueryInterval(int interval);

    QString getUsername();
    void setUsername(QString username);

    QString getPassword();
    void setPassword(QString password);

    QString getProxyUsername();
    void setProxyUsername(QString username);

    QString getProxyPassword();
    void setProxyPassword(QString password);

    bool isCheckUpdate();
    void setCheckUpdate(bool enabled);

private:
    int         queryInterval;
    int         frontPolicy;
    int         backPolicy;
    QString     username;
    QString     password;
    QString     proxyUsername;
    QString     proxyPassword;
    bool        checkUpdate;
};

#endif // __PREFERENCES_H
