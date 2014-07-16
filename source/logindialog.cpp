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

#include "logindialog.h"
#include "networkmanager.h"
#include "constants.h"
#include "preferences.h"

#define SETTING_EMAIL             "email"

LoginDialog::LoginDialog(QWidget *parent)
    : QxDialog("login_dialog", parent)
{
    setupView();
}

void LoginDialog::setupView()
{
    QVBoxLayout *mainLayout = new QVBoxLayout(this);

    emailEdit =  new QLineEdit;
    passwordEdit = new QLineEdit;
    rememberCheck = new QCheckBox;
    createAcountLink = new QLabel;
    forgetPasswordLink = new QLabel;
    errorMessage = new QLabel;
    btnLogin = new QPushButton(STR_LOGIN_LOGIN);

    QGridLayout *loginLayout  = new QGridLayout;
    QHBoxLayout *footerLayout = new QHBoxLayout;
    QGroupBox *loginBox = new QGroupBox(STR_LOGIN_GROUP_ACCOUNT);

    QLabel *lblEmail = new QLabel(STR_LOGIN_EMAIL);
    QLabel *lblPassword = new QLabel(STR_LOGIN_PASSWORD);

    //footerLayout
    {
        QPushButton *btnCancel = new QPushButton(ICON_EXIT, STR_NOPE);

        connect(btnCancel, SIGNAL(clicked()), this, SLOT(reject()));
        connect(btnLogin, SIGNAL(clicked()), this, SLOT(onLogin()));

        btnLogin->setDefault(true);

        footerLayout->addItem(hSpacer());
        footerLayout->addWidget(btnLogin);
        footerLayout->addWidget(btnCancel);
    }

    loginLayout->addWidget(lblEmail         ,0,0,1,1);
    loginLayout->addWidget(emailEdit        ,0,1,1,1);
    loginLayout->addWidget(lblPassword      ,1,0,1,1);
    loginLayout->addWidget(passwordEdit     ,1,1,1,1);
    loginLayout->addWidget(rememberCheck    ,2,0,1,2);

    loginBox->setLayout(loginLayout);

    mainLayout->addWidget(loginBox);
    mainLayout->addWidget(createAcountLink);
    mainLayout->addWidget(forgetPasswordLink);
    mainLayout->addStretch();
    mainLayout->addWidget(errorMessage);
    mainLayout->addWidget(hLine());
    mainLayout->addLayout(footerLayout);

    passwordEdit->setEchoMode(QLineEdit::Password);

    createAcountLink->setText(STR_LOGIN_CREATE_ACCOUNT);
    forgetPasswordLink->setText(STR_LOGIN_CREATE_FORGET_PASSWORD.arg(emailEdit->text()));
    rememberCheck->setText(STR_LOGIN_REMEMBER_ME);

    createAcountLink->setOpenExternalLinks(true);
    forgetPasswordLink->setOpenExternalLinks(true);
    errorMessage->setOpenExternalLinks(true);
    
    rememberCheck->setChecked(true);

    emailEdit->setText( getSetting(SETTING_EMAIL).toString() );

    setWindowTitle(STR_DIALOG_TITLE_LOGIN);
}

void LoginDialog::onLogin()
{
    btnLogin->setEnabled(false);

    NetworkManager *netMan = NetworkManager::GetInstance();
    
    connect(netMan, SIGNAL(succeed(const QString&)), this, SLOT(onLoginAccept(const QString&)));
    connect(netMan, SIGNAL(failed(const QString&)), this, SLOT(onLoginFail(const QString&)));

    netMan->login(emailEdit->text(), passwordEdit->text());
}

void LoginDialog::onLoginAccept(const QString&)
{
    if(rememberCheck->isChecked()) {
        Preferences *preferences = Preferences::GetInstance();

        preferences->setUsername( emailEdit->text() );
        preferences->setPassword( passwordEdit->text() );
    }

    setSetting( SETTING_EMAIL, emailEdit->text() );

    accept();
}

void LoginDialog::onLoginFail(const QString &error)
{
    btnLogin->setEnabled(true);

    errorMessage->setText(QString("<font color='red'><b> *%1</b></font>").arg(error));
}
