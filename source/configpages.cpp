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

#include "configpages.h"
#include "preferences.h"
#include "logindialog.h"
#include "networkmanager.h"
#include "constants.h"

#include <QAutostart>

ConfigPage::ConfigPage(QWidget *parent)
    : QWidget(parent)
{
    preferences = Preferences::GetInstance();
    mainLayout = new QVBoxLayout(this);
    captionLabel = new QLabel;
    settingLayout = new QVBoxLayout;    
    
    captionLabel->setStyleSheet(QString("border:1px solid #2d4864; background-color:#5a87b4; color:#fff; font-weight:700;font-size:16px; padding:2px; margin:0px"));

    mainLayout->addWidget(captionLabel);
    mainLayout->addLayout(settingLayout);
    mainLayout->addStretch();
    mainLayout->setMargin(0);

    settingLayout->setMargin(2);

    setLayout(mainLayout);
}

ConfigGeneralPage::ConfigGeneralPage(QWidget *parent)
    : ConfigPage(parent)
{
    captionLabel->setText(STR_CONFIG_CAPTION_GENERAL);
    
    autoStartCheck   = new QCheckBox(STR_CONFIG_AUTO_START_CAPTION);  
    checkUpdateCheck = new QCheckBox(STR_CONFIG_AUTO_UPDATE_CHECK);

    settingLayout->addWidget(autoStartCheck);
    settingLayout->addWidget(checkUpdateCheck);

    autoStartCheck->setChecked ( Autostart().isAutostart() );
    checkUpdateCheck->setChecked( preferences->isCheckUpdate() );
}

void ConfigGeneralPage::save()
{
    Autostart().setAutostart( autoStartCheck->isChecked() );
    preferences->setCheckUpdate( checkUpdateCheck->isChecked() );
}

ConfigDeckPage::ConfigDeckPage(QWidget *parent)
    : ConfigPage(parent)
{
    captionLabel->setText(STR_CONFIG_CAPTION_DECK);

    QHBoxLayout *timerLayout = new QHBoxLayout;
    QLabel *timerLabel = new QLabel(STR_CONFIG_DECK_TIMER_LABEL);
    queryTimer = new SpinLabel(STR_CONFIG_DECK_QUERY_TIMER_FORMAT);
    timerLayout->addWidget(timerLabel);
    timerLayout->addStretch();
    timerLayout->addWidget(queryTimer);

    settingLayout->addLayout(timerLayout);

    /// on close
    /*
    int mainTimerInterval = spinTimer->getSpinValue();
    setSetting(SETTING_TIMER_INTERVAL, mainTimerInterval);
    */

    queryTimer->setSpinValue( preferences->getQueryInterval() );
}

void ConfigDeckPage::save()
{
    preferences->setQueryInterval( queryTimer->getSpinValue() );
}

ConfigNetwordPage::ConfigNetwordPage(QWidget *parent)
    : ConfigPage(parent)
{
    captionLabel->setText(STR_CONFIG_CAPTION_NETWORK);

    QGroupBox *accountBox = new QGroupBox(STR_LOGIN_GROUP_ACCOUNT);
    accountLayout = new QVBoxLayout;

    accountBox->setLayout(accountLayout);
    settingLayout->addWidget(accountBox);

    setupAccountLayout();
}

void ConfigNetwordPage::save()
{
}

void ConfigNetwordPage::onLogin()
{
    LoginDialog dlg(this);

    if(dlg.exec()==QDialog::Accepted) {
        setupAccountLayout();
    }
}

void ConfigNetwordPage::onLogout()
{
    NetworkManager* netMan = NetworkManager::GetInstance();

    netMan->logout();

    setupAccountLayout();
}

void ConfigNetwordPage::setupAccountLayout()
{
    utils::clearLayout(accountLayout);

    NetworkManager* netMan = NetworkManager::GetInstance();

    if(netMan->isLoggedin()) {
        QLabel *label = new QLabel;
        QHBoxLayout *logoutLayout = new QHBoxLayout;
        QPushButton *btnForget = new QPushButton(STR_LOGIN_LOGOUT);

        label->setText(STR_CONFIG_NETWORD_LOGGED_IN_LABEL.arg( preferences->getUsername() ));

        logoutLayout->addStretch();
        logoutLayout->addWidget(btnForget);

        accountLayout->addWidget(label);
        accountLayout->addLayout(logoutLayout);

        connect(btnForget, SIGNAL(clicked()), this, SLOT(onLogout()));
    } else {
        QLabel *label = new QLabel;
        QHBoxLayout *loginLayout = new QHBoxLayout;
        QPushButton *btnLogin = new QPushButton(STR_LOGIN_LOGIN);

        label->setText(STR_CONFIG_NETWORD_LOGGED_OUT_LABEL);

        loginLayout->addStretch();
        loginLayout->addWidget(btnLogin);

        accountLayout->addWidget(label);
        accountLayout->addLayout(loginLayout);

        connect(btnLogin, SIGNAL(clicked()), this, SLOT(onLogin()));
    }
}

