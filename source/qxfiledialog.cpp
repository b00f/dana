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

#include "qxfiledialog.h"
#include "qxsettings.h"

QxFileDialog::QxFileDialog(QWidget *parent) :
    QFileDialog(parent)
{
}

QString QxFileDialog::getOpenDeckName()
{
    return getOpenFileName(tr("Open File"),
                           tr("All Supported Files (*.dana *.xml *.txt *.cards);; Dana Files (*.dana);;XML Files (*.xml);; Anki Tab Separated text files (*.txt);; Mnemosyne files (*.cards)"));
}

QString QxFileDialog::getSaveDeckName()
{
    return getSaveFileName(tr("Save File"),
                           tr("Dana Files (*.dana);;XML Files (*.xml);; Tab Separated text files (*.txt)"));
}

QString QxFileDialog::getOpenImageName()
{
    return getOpenFileName(tr("Open Image File"),
                           tr("Image Files (*.gif *.jpg *.jpeg *.bmp *.png);;All Files (*.*)"));

}

QString QxFileDialog::getOpenTexName()
{
    return getOpenFileName(tr("Open Tex File"),
                           tr("Latex Files (*.tex);;All Files (*.*)"));

}

QString QxFileDialog::getOpenFileName(const QString &caption, const QString &filter, QString *selectedFilter, Options options)
{
    QString settingName = caption;
    QString settingGroup = "open_file_dialog";
    QString fileName = QFileDialog::getOpenFileName(parentWidget(),
                                                    caption,
                                                    QxSettings::getSetting(settingName, settingGroup).toString(),
                                                    filter,
                                                    selectedFilter,
                                                    options);
    if (!fileName.isEmpty()) {
        QxSettings::setSetting(settingName, settingGroup, QFileInfo(fileName).absoluteDir().absolutePath());
    }

    return fileName;
}

QString QxFileDialog::getSaveFileName(const QString &caption, const QString &filter, QString *selectedFilter, Options options)
{
    QString settingName = caption;
    QString settingGroup = "save_file_dialog";
    QString fileName = QFileDialog::getSaveFileName(parentWidget(),
                                                    caption,
                                                    QxSettings::getSetting(settingName, settingGroup).toString(),
                                                    filter,
                                                    selectedFilter,
                                                    options);
    if (!fileName.isEmpty()) {
        QxSettings::setSetting(settingName, settingGroup, QFileInfo(fileName).absoluteDir().absolutePath());
    }

    return fileName;
}
