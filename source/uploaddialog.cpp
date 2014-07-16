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

#include "uploaddialog.h"
#include "networkmanager.h"
#include "logindialog.h"
#include "qxmessagebox.h"
#include "deck.h"
#include "constants.h"

UploadDialog::UploadDialog(QWidget *parent)
    : ProgressDialog(parent)
{
    deck = 0;
}

void UploadDialog::uploadDeck(Deck* _deck)
{
    deck = _deck;
    
    NetworkManager *netMan = NetworkManager::GetInstance();

    if(!netMan->isLoggedin())
    {
        LoginDialog dlg(this);
        if(dlg.exec()!=QDialog::Accepted) {
            return;
        }        
    }
    
    connect(netMan, SIGNAL(succeed(const QString&)), this, SLOT(onCheckDeck(const QString&)));
    connect(netMan, SIGNAL(failed(const QString&)), this, SLOT(onError(const QString&)));
    
    netMan->checkDeck(deck);

    setCaption(STR_PROGRESS_DIALOG_UPLOAD_CAPTION);
    exec();
}

void UploadDialog::onCheckDeck(const QString& result)
{
    bool ok = false;
    int resultCode = result.toInt(&ok);

    switch(resultCode) {
    case 0: 
        break; /// 

    case 1:
        if( QxMessageBox::question(this, WNG_ASKING_FOR_UPDATE_REMOTE_DECK, WNG_ASKING_FOR_UPDATE_REMOTE_DECK_TITLE) == 
            QxMessageBox::No) return;
        break;

    default:
    case 2:
        QxMessageBox::critical(this, ERR_UNAUTHORIZED_TO_UPLOAD);
            return;
    }

    QTimer::singleShot(0, this, SLOT(upload()));
}

void UploadDialog::upload()
{
    NetworkManager *netMan = NetworkManager::GetInstance();

    connect(netMan, SIGNAL(uploadProgress(qint64, qint64)), this, SLOT(updateProgress(qint64, qint64))); 
    connect(netMan, SIGNAL(succeed(const QString&)), this, SLOT(onFinish(const QString&)));
    connect(netMan, SIGNAL(failed(const QString&)), this, SLOT(onError(const QString&)));
    connect(this, SIGNAL(canceled()), netMan, SLOT(doAbort())); 

    netMan->uploadDeck(deck);
}

void UploadDialog::onError(const QString& error)
{
    ///QxMessageBox::critical(this, error, STR_NETWORK_ERROR);
    setError(error);
}

void UploadDialog::onFinish(const QString& )
{
    close();
}