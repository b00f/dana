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

#include "proxydialog.h"
#include "constants.h"

ProxyDialog::ProxyDialog(QWidget *parent)
    : QxDialog("proxy_dialog", parent)
{
    setupView();
}

void ProxyDialog::setupView()
{
    QVBoxLayout *mainLayout = new QVBoxLayout(this);

    QGridLayout *proxyLayout  = new QGridLayout;
    QHBoxLayout *footerLayout = new QHBoxLayout;
    QGroupBox *proxyBox = new QGroupBox(STR_PROXY_GROUP_PROXY);

    QLabel *proxyLabel = new QLabel(STR_PROXY_REQUEST);

    usernameEdit = new QLineEdit;
    passwordEdit = new QLineEdit;
    hostEdit     = new QLineEdit;
    portEdit     = new QLineEdit;

    QLabel *usernameLabel = new QLabel(STR_PROXY_USERNAME);
    QLabel *passwordLabel = new QLabel(STR_PROXY_PASSWORD);
    QLabel *hostLabel     = new QLabel(STR_PROXY_HOST    );
    QLabel *portLabel     = new QLabel(STR_PROXY_PORT    );

    passwordEdit->setEchoMode(QLineEdit::Password);

    //footerLayout
    {
        QPushButton *btnConnect = new QPushButton(STR_CONNECT);
        QPushButton *btnCancel = new QPushButton(ICON_EXIT, STR_NOPE);

        connect(btnConnect, SIGNAL(clicked()), this, SLOT(onClose()));
        connect(btnCancel, SIGNAL(clicked()), this, SLOT(reject()));

        btnConnect->setDefault(true);

        footerLayout->addItem(hSpacer());
        footerLayout->addWidget(btnConnect);
        footerLayout->addWidget(btnCancel);
    }

    proxyLayout->addWidget(hostLabel       ,0,0,1,1);
    proxyLayout->addWidget(hostEdit        ,0,1,1,1);
    proxyLayout->addWidget(portLabel       ,1,0,1,1);
    proxyLayout->addWidget(portEdit        ,1,1,1,1);
    proxyLayout->addWidget(usernameLabel   ,2,0,1,1);
    proxyLayout->addWidget(usernameEdit    ,2,1,1,1);
    proxyLayout->addWidget(passwordLabel   ,3,0,1,1);
    proxyLayout->addWidget(passwordEdit    ,3,1,1,1);

    proxyBox->setLayout(proxyLayout);

    mainLayout->addWidget(proxyLabel);
    mainLayout->addWidget(proxyBox);
    mainLayout->addStretch();
    mainLayout->addWidget(hLine());
    mainLayout->addLayout(footerLayout);

    hostEdit->setReadOnly(true);
    portEdit->setReadOnly(true);
    hostEdit->setDisabled(true);
    portEdit->setDisabled(true);

    setWindowTitle(STR_DIALOG_TITLE_PROXY);
}

void ProxyDialog::onClose()
{
    accept();
}

void ProxyDialog::setUsername(QString username)
{
    usernameEdit->setText(username);
}

void ProxyDialog::setPassword(QString password)
{
    passwordEdit->setText(password);
}

void ProxyDialog::setHost(QString host)
{
    hostEdit->setText(host);
}

void ProxyDialog::setPort(int port)
{
    portEdit->setText(QString::number(port));
}

QString ProxyDialog::getUsername()
{
    return usernameEdit->text();
}

QString ProxyDialog::getPassword()
{
    return passwordEdit->text();
}

QString ProxyDialog::getHost()
{
    return hostEdit->text();
}

int ProxyDialog::getPort()
{
    return portEdit->text().toInt();
}
