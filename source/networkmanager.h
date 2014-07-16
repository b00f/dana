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

#ifndef __NETWORKMANAGER_H
#define __NETWORKMANAGER_H

#include "singleton.h"

#include <QNetworkAccessManager>
#include <QNetworkCookieJar>
#include <QFile>

class Deck;
class NetworkManager
    : public QObject
    , public CSingleton<NetworkManager>
{
    Q_OBJECT

public:
    NetworkManager(QObject *parent = 0);

    void setUrl(QString url);

    void login(QString username, QString password);
    void logout();
    void checkDeck(Deck *deck);
    void uploadDeck(Deck *deck);
    void getDeckList();  
    void downloadDeck(int deckId);
    void vote(int deckId, int rating); 
    void checkUpdate();

    bool isLoggedin();

signals:
    void succeed(const QString & = QString());
    void failed(const QString &); 
    void uploadProgress(qint64, qint64);
    void downloadProgress(qint64, qint64);

public slots:
    void doAbort();

private slots:
    void onReply(QNetworkReply *reply);
    void onProxyAuthentication(const QNetworkProxy &networkProxy, QAuthenticator *authenticator);
    void downloadDone();
    void downloadRead();

protected:
    void autoLogin();

private:
    QNetworkAccessManager *qnam;
    QNetworkCookieJar *cookieJar;
    QNetworkReply *reply;
    QUrl remoteUrl;
    QFile *downFile;

    bool loggedin;
    bool autoProxuAuthentication;
};

#endif // __NETWORKMANAGER_H