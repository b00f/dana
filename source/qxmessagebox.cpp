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

#include "qxmessagebox.h"
#include "qxsettings.h"


QxMessageBox::QxMessageBox(QWidget *parent) :
    QMessageBox(parent)
{
}

QMessageBox::StandardButton QxMessageBox::critical(QWidget *parent, const QString &text , const QString &title)
{
    QMessageBox msgBox(parent);


    msgBox.setIcon(QMessageBox::Question);
    msgBox.setWindowTitle(APP_TITLE);
    msgBox.setText(QString("<b>%1</b>").arg(title));
    msgBox.setInformativeText(text);
    msgBox.setStandardButtons(QMessageBox::Ok);
    msgBox.setDefaultButton(QMessageBox::Ok);

    return (QMessageBox::StandardButton)msgBox.exec();
}

QMessageBox::StandardButton QxMessageBox::question(QWidget *parent, const QString &text , const QString &title)
{
    QMessageBox msgBox(parent);

    msgBox.setIcon(QMessageBox::Question);
    msgBox.setWindowTitle(APP_TITLE);
    msgBox.setText(QString("<b>%1</b>").arg(title));
    msgBox.setInformativeText(text);
    msgBox.setStandardButtons(QMessageBox::Yes | QMessageBox::No);
    msgBox.setDefaultButton(QMessageBox::No);

    return (QMessageBox::StandardButton)msgBox.exec();
}

QMessageBox::StandardButton QxMessageBox::warning(QWidget *parent, const QString &text , const QString &title)
{
    QMessageBox msgBox(parent);

    msgBox.setIcon(QMessageBox::Warning);
    msgBox.setWindowTitle(APP_TITLE);
    msgBox.setText(QString("<b>%1</b>").arg(title));
    msgBox.setInformativeText(text);
    msgBox.setStandardButtons(QMessageBox::Ok);
    msgBox.setDefaultButton(QMessageBox::Ok);

    return (QMessageBox::StandardButton)msgBox.exec();
}


QMessageBox::StandardButton QxMessageBox::information(QWidget *parent, const QString &text , const QString &title)
{
    QMessageBox msgBox(parent);

    msgBox.setIcon(QMessageBox::Information);
    msgBox.setWindowTitle(APP_TITLE);
    msgBox.setText(QString("<b>%1</b>").arg(title));
    msgBox.setInformativeText(text);
    msgBox.setStandardButtons(QMessageBox::Ok);
    msgBox.setDefaultButton(QMessageBox::Ok);

    return (QMessageBox::StandardButton)msgBox.exec();
}