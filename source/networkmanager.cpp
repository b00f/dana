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

#include "networkmanager.h"
#include "proxydialog.h"
#include "preferences.h"
#include "deck.h"
#include "constants.h"

#include <QNetworkRequest>
#include <QNetworkCookie>
#include <QAuthenticator>
#include <QNetworkProxy>
#include <QNetworkReply>
#include <QUrlQuery>
#include <QDebug>

#define ADD_QUERY_ITEM(b,n,v) QString("%1Content-Disposition: form-data; name=\"%2\"\r\n\r\n%3").arg(b).arg(n).arg(v);


enum DanaRequestType {
    LoginRequest        = 0,
    LogoutRequest          ,
    UploadRequest          ,
    CheckDeckRequest       ,
    DeckListRequest        ,
    DownloadRequest        ,
    VoteRequest            ,
    CheckUpdateRequest     ,
};

NetworkManager::NetworkManager(QObject *parent)
{
    qnam = new QNetworkAccessManager(parent);
    cookieJar = new QNetworkCookieJar(parent);
    loggedin = false;
    reply = 0;
    downFile = 0;
    remoteUrl = QUrl("http://dana-box.com/dana/dana.php");
    autoProxuAuthentication = true;

    qnam->setCookieJar(cookieJar);
    qnam->proxyFactory()->setUseSystemConfiguration(true);

    connect(qnam, SIGNAL(finished(QNetworkReply*)),
        this, SLOT(onReply(QNetworkReply*)), Qt::QueuedConnection);

    connect(qnam, SIGNAL(proxyAuthenticationRequired(const QNetworkProxy&,QAuthenticator*)),
        this, SLOT(onProxyAuthentication(QNetworkProxy,QAuthenticator*)));

    autoLogin();
}

bool NetworkManager::isLoggedin()
{
    return loggedin;
}

void NetworkManager::autoLogin()
{
    Preferences *preferences = Preferences::GetInstance();

    if(!preferences->getUsername().isEmpty()) {
        login(
            preferences->getUsername(),
            preferences->getPassword() );
    }
}

void NetworkManager::onProxyAuthentication(const QNetworkProxy &networkProxy, QAuthenticator *authenticator)
{
    if( autoProxuAuthentication ) {
        Preferences *preferences = Preferences::GetInstance();

        authenticator->setUser    ( preferences->getProxyUsername() );
        authenticator->setPassword( preferences->getProxyPassword() );

        autoProxuAuthentication = false;
        return;
    }

    ProxyDialog dlg;

    dlg.setHost    ( networkProxy.hostName() );
    dlg.setPort    ( networkProxy.port()     );
    dlg.setUsername( networkProxy.user()     );
    dlg.setPassword( networkProxy.password() );

    if(dlg.exec()==QDialog::Accepted) {
        authenticator->setUser(dlg.getUsername());
        authenticator->setPassword(dlg.getPassword());

        Preferences *preferences = Preferences::GetInstance();

        preferences->setProxyUsername( dlg.getUsername() );
        preferences->setProxyPassword( dlg.getPassword() );
    }
}

void NetworkManager::onReply(QNetworkReply *reply)
{
    QString error;

    if(reply->error() != QNetworkReply::NoError) {
        error = reply->errorString();

        qDebug() << error;
    }

    /// if an error occurred
    if(!error.isEmpty()) {
        emit failed(error);
        return;
    }

    QByteArray replyData = reply->readAll();
    QString result = replyData;
    int requestType= reply->request().attribute(QNetworkRequest::User).toInt();

    result = result.trimmed();
    switch(requestType) {
    case LoginRequest:
        if(result.isEmpty()) {
            loggedin = true;
            emit succeed();
        } else {
            emit failed(result);
        }
        break;

    case LogoutRequest:
        loggedin = false;
        emit succeed(result);
        break;

    case CheckDeckRequest:
    case CheckUpdateRequest:
    case DeckListRequest:
        emit succeed(result);
        break;

    case DownloadRequest:
        if(result.isEmpty()) {
            emit succeed(downFile->fileName());
        } else {
            emit failed(result);
        }
        break;

    case UploadRequest:
    case VoteRequest:
    default:
        if(result.isEmpty()) {
            emit succeed();
        } else {
            emit failed(result);
        }
        break;
    }

    disconnect(SIGNAL(succeed(const QString &)));
    disconnect(SIGNAL(failed(const QString &)));
    reply = 0;
}

void NetworkManager::uploadDeck(Deck *deck)
{
    QString filePath =
        utils::combinePaths(tempPath(), "deck.dana");

    utils::removeFile(filePath);

    deck->exportDeck(filePath);

    QFileInfo finfo(filePath);

    QString boundaryRegular(QString("--==--98759032542878--==--"));/// this is a boundary
    QString boundary("\r\n--"+boundaryRegular+"\r\n");
    QString boundaryLast("\r\n--"+boundaryRegular+"--\r\n");
    QByteArray postData;

    postData += ADD_QUERY_ITEM(boundary, "action",  "share");
    postData += ADD_QUERY_ITEM(boundary, "version",  appVersionString());
    postData += ADD_QUERY_ITEM(boundary, "name",     deck->getName());
    postData += ADD_QUERY_ITEM(boundary, "desc",     deck->getDesc());
    postData += ADD_QUERY_ITEM(boundary, "author",   deck->getAuthor());
    postData += ADD_QUERY_ITEM(boundary, "tags",     deck->getTags());
    postData += ADD_QUERY_ITEM(boundary, "cards_no", deck->getTotalCardsNo());
    postData += ADD_QUERY_ITEM(boundary, "created",  deck->getCreatedTime().toString("yyyy-MM-dd hh:mm:ss"));
    postData += ADD_QUERY_ITEM(boundary, "guid",     deck->getGuid().toString());

    postData += boundary;
    postData += "Content-Disposition: form-data; name=\"deck\"; filename=\""+finfo.fileName()+"\"\r\n";
    postData += "Content-Type: application/octet-stream\r\n\r\n";
    QFile file(finfo.absoluteFilePath());
    file.open(QIODevice::ReadOnly);
    postData += file.readAll();
    postData += boundaryLast;

    postData += boundary;
    postData += "Content-Disposition: form-data; name=\"icon\"; filename=\"icon.png\"\r\n";
    postData += "Content-Type: image/png\r\n\r\n";
    QPixmap pixmap = deck->getPixmap();
    QByteArray bArray;
    QBuffer buffer( &bArray );
    buffer.open( QIODevice::WriteOnly );
    pixmap.save( &buffer, "PNG" );
    buffer.close();
    postData += bArray;
    postData += boundaryLast;

    QNetworkRequest request;

    request.setAttribute(QNetworkRequest::User, UploadRequest);
    request.setHeader(QNetworkRequest::ContentTypeHeader, QString("multipart/form-data; boundary=" + boundaryRegular).toUtf8());
    request.setHeader(QNetworkRequest::ContentLengthHeader, postData.size());
    request.setUrl(remoteUrl);

    reply = qnam->post(request, postData);

    connect(reply, SIGNAL(uploadProgress(qint64, qint64)), this, SIGNAL(uploadProgress(qint64, qint64)));
}

void NetworkManager::login(QString username, QString password)
{
    //login on www
    QByteArray postData;
    QUrlQuery urlQuery;
    QNetworkRequest request;

    urlQuery.addQueryItem("action", "login");
    urlQuery.addQueryItem("version", appVersionString());
    urlQuery.addQueryItem("email", username);
    urlQuery.addQueryItem("password", password);
    postData = urlQuery.query(QUrl::FullyEncoded).toUtf8();

    request.setAttribute(QNetworkRequest::User, LoginRequest);
    request.setHeader(QNetworkRequest::ContentTypeHeader, QVariant("application/x-www-form-urlencoded"));
    request.setUrl(remoteUrl);

    reply = qnam->post(request, postData);
}

void NetworkManager::logout()
{
    loggedin = false; /// need to set here, because of preferences dialog

    QByteArray postData;
    QUrlQuery urlQuery;
    QNetworkRequest request;

    urlQuery.addQueryItem("action", "logout");

    postData = urlQuery.query(QUrl::FullyEncoded).toUtf8();

    request.setAttribute(QNetworkRequest::User, LogoutRequest);
    request.setHeader(QNetworkRequest::ContentTypeHeader, QVariant("application/x-www-form-urlencoded"));
    request.setUrl(remoteUrl);

    reply = qnam->post(request, postData);
}

void NetworkManager::getDeckList()
{
    QByteArray postData;
    QUrlQuery urlQuery;
    QNetworkRequest request;

    urlQuery.addQueryItem("action", "deck_list");
    urlQuery.addQueryItem("version", appVersionString());
    postData = urlQuery.query(QUrl::FullyEncoded).toUtf8();

    request.setAttribute(QNetworkRequest::User, DeckListRequest);
    request.setHeader(QNetworkRequest::ContentTypeHeader, QVariant("application/x-www-form-urlencoded"));
    request.setUrl(remoteUrl);

    reply = qnam->post(request, postData);
}

void NetworkManager::checkDeck(Deck *deck)
{
    QByteArray postData;
    QUrlQuery urlQuery;
    QNetworkRequest request;

    urlQuery.addQueryItem("action", "check_deck");
    urlQuery.addQueryItem("version", appVersionString());
    urlQuery.addQueryItem("name", deck->getName());
    urlQuery.addQueryItem("guid", deck->getGuid().toString());
    postData = urlQuery.query(QUrl::FullyEncoded).toUtf8();

    request.setAttribute(QNetworkRequest::User, CheckDeckRequest);
    request.setHeader(QNetworkRequest::ContentTypeHeader, QVariant("application/x-www-form-urlencoded"));
    request.setUrl(remoteUrl);

    reply = qnam->post(request, postData);
}

void NetworkManager::vote(int deckId, int rating)
{
    QByteArray postData;
    QUrlQuery urlQuery;
    QNetworkRequest request;

    urlQuery.addQueryItem("action", "vote");
    urlQuery.addQueryItem("version", appVersionString());
    urlQuery.addQueryItem("deck_id", QString::number(deckId));
    urlQuery.addQueryItem("rating", QString::number(rating));
    postData = urlQuery.query(QUrl::FullyEncoded).toUtf8();

    request.setAttribute(QNetworkRequest::User, VoteRequest);
    request.setHeader(QNetworkRequest::ContentTypeHeader, QVariant("application/x-www-form-urlencoded"));
    request.setUrl(remoteUrl);

    reply = qnam->post(request, postData);
}

void NetworkManager::downloadDeck(int deckId)
{
    QByteArray postData;
    QUrlQuery urlQuery;
    QNetworkRequest request;

    urlQuery.addQueryItem("action", "download");
    urlQuery.addQueryItem("version", appVersionString());
    urlQuery.addQueryItem("deck_id", QString::number(deckId));
    postData = urlQuery.query(QUrl::FullyEncoded).toUtf8();

    request.setAttribute(QNetworkRequest::User, DownloadRequest);
    request.setHeader(QNetworkRequest::ContentTypeHeader, QVariant("application/x-www-form-urlencoded"));
    request.setUrl(remoteUrl);

    QString filePath =
        utils::combinePaths(tempPath(), "download.dana");

    utils::removeFile(filePath);

    downFile = new QFile(filePath);
    downFile->open(QIODevice::ReadWrite);

    reply = qnam->post(request, postData);

    connect(reply, SIGNAL(finished()), this, SLOT(downloadDone()));
    connect(reply, SIGNAL(readyRead()), this, SLOT(downloadRead()));
    connect(reply, SIGNAL(downloadProgress(qint64, qint64)), this, SIGNAL(downloadProgress(qint64, qint64)));
}

void NetworkManager::checkUpdate()
{
    QByteArray postData;
    QUrlQuery urlQuery;
    QNetworkRequest request;

    urlQuery.addQueryItem("action", "check_update");
    urlQuery.addQueryItem("version", appVersionString());
    postData = urlQuery.query(QUrl::FullyEncoded).toUtf8();

    request.setAttribute(QNetworkRequest::User, CheckUpdateRequest);
    request.setHeader(QNetworkRequest::ContentTypeHeader, QVariant("application/x-www-form-urlencoded"));
    request.setUrl(remoteUrl);

    reply = qnam->post(request, postData);
}

void NetworkManager::doAbort()
{
    if(reply)
        reply->abort();
}

void NetworkManager::downloadDone()
{
    if (downFile) {
        downFile->write(reply->readAll());
        downFile->flush();
        downFile->close();
    }
}

void NetworkManager::downloadRead()
{
    if (downFile)
        downFile->write(reply->readAll());
}
