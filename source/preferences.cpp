//
// Dana - Dana, Symbol of Wisdom
// Copyright (C) 2014 Mostafa Sedaghat Joo (mostafa.sedaghat@gmail.com)
//
// This file is part of Dana.
//
// Dana is free software: you can redistribute it and/or modify
// it under the terms of the GNU General Public License as published by
// the Free Software Foundation, either version 3 of the License, or
// (at your option) any later version.
//
// Dana is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU General Public License for more details.
//
// You should have received a copy of the GNU General Public License
// along with Dana.  If not, see <http://www.gnu.org/licenses/>.
//

#include "preferences.h"
#include "qxsettings.h"
#include "simplecrypt.h"


#define SETTING_GROUP_NAME             "preference"
#define SETTING_KEY_AUTOSTART          "auto_start"
#define SETTING_KEY_CHECK_UPDATE       "update_check"
#define SETTING_KEY_QUERY_INTERVAL     "query_interval"
#define SETTING_KEY_USERNAME           "username"
#define SETTING_KEY_PASSWORD           "password"
#define SETTING_KEY_PROXY_ENABLED      "proxy_enabled"
#define SETTING_KEY_PROXY_HOSTNAME     "proxy_hostname"
#define SETTING_KEY_PROXY_PORT         "proxy_port"
#define SETTING_KEY_PROXY_USERNAME     "proxy_username"
#define SETTING_KEY_PROXY_PASSWORD     "proxy_password"

#define ENCRYPT_RANDOM_KEY  Q_UINT64_C(0x0011223344556677)

Preferences::Preferences(void)
{
    load();
}

Preferences::~Preferences(void)
{
    save();
}

void Preferences::load()
{
    queryInterval   = QxSettings::getSetting(SETTING_KEY_QUERY_INTERVAL,    SETTING_GROUP_NAME, 30).toInt();
    username        = QxSettings::getSetting(SETTING_KEY_USERNAME,          SETTING_GROUP_NAME, "").toString();
    password        = QxSettings::getSetting(SETTING_KEY_PASSWORD,          SETTING_GROUP_NAME, "").toString();
    proxyUsername   = QxSettings::getSetting(SETTING_KEY_PROXY_USERNAME,    SETTING_GROUP_NAME, "").toString();
    proxyPassword   = QxSettings::getSetting(SETTING_KEY_PROXY_PASSWORD,    SETTING_GROUP_NAME, "").toString();
    checkUpdate     = QxSettings::getSetting(SETTING_KEY_CHECK_UPDATE,      SETTING_GROUP_NAME, false).toBool();
}

void Preferences::save()
{
    QxSettings::setSetting(SETTING_KEY_QUERY_INTERVAL,  SETTING_GROUP_NAME, queryInterval);
    QxSettings::setSetting(SETTING_KEY_USERNAME,        SETTING_GROUP_NAME, username);
    QxSettings::setSetting(SETTING_KEY_PASSWORD,        SETTING_GROUP_NAME, password);
    QxSettings::setSetting(SETTING_KEY_PROXY_USERNAME,  SETTING_GROUP_NAME, proxyUsername);
    QxSettings::setSetting(SETTING_KEY_PROXY_PASSWORD,  SETTING_GROUP_NAME, proxyPassword);
    QxSettings::setSetting(SETTING_KEY_CHECK_UPDATE,    SETTING_GROUP_NAME, checkUpdate);
}

int Preferences::getQueryInterval()
{
    return queryInterval;
}

void Preferences::setQueryInterval(int interval)
{
    queryInterval = interval;
}

QString Preferences::getUsername()
{
    return username;
}

void Preferences::setUsername(QString _username)
{
    username = _username;
}

QString Preferences::getPassword()
{
    SimpleCrypt crypto(ENCRYPT_RANDOM_KEY);
    return crypto.decryptToString(password);
}

void Preferences::setPassword(QString _password)
{
    SimpleCrypt crypto(ENCRYPT_RANDOM_KEY);
    password =  crypto.encryptToString(_password);
}

QString Preferences::getProxyUsername()
{
    return proxyUsername;
}

void Preferences::setProxyUsername(QString username)
{
    proxyUsername = username;
}

QString Preferences::getProxyPassword()
{
    SimpleCrypt crypto(ENCRYPT_RANDOM_KEY);
    return crypto.decryptToString(proxyPassword);
}

void Preferences::setProxyPassword(QString password)
{
    SimpleCrypt crypto(ENCRYPT_RANDOM_KEY);
    proxyPassword =  crypto.encryptToString(password);
}

bool Preferences::isCheckUpdate()
{
    return checkUpdate;
}

void Preferences::setCheckUpdate(bool enabled)
{
    checkUpdate = enabled;
}
