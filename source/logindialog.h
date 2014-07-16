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

#ifndef __LOGINDIALOG_H
#define __LOGINDIALOG_H

#include "qxdialog.h"


class LoginDialog 
    : public QxDialog
{
    Q_OBJECT

public:
    explicit LoginDialog(QWidget *parent = 0);

private slots:
    void onLogin();
    void onLoginAccept(const QString&);
    void onLoginFail(const QString &error);

private:
    void setupView();

private:
    QLineEdit *emailEdit;
    QLineEdit *passwordEdit;
    QCheckBox *rememberCheck;
    QLabel    *errorMessage;
    QLabel    *createAcountLink;
    QLabel    *forgetPasswordLink;
    QPushButton *btnLogin;
};

#endif // __LOGINDIALOG_H