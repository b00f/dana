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

#include "zlibwrappr.h"
#include "constants.h"

#include <QDir>
#include <QDebug>
#include <QProcess>
#include <QDirIterator>

bool zlibWrappr::zipFolder(QString folder, QString zipPath)
{
    QString command = QString("%1/minizip").arg(appPath());
    QStringList parameters;

    parameters << "-o";
    parameters << zipPath;

    QDirIterator iter(folder, QDir::Files | QDir::NoSymLinks, QDirIterator::Subdirectories);
    QDir dir(folder);
    while (iter.hasNext()) {
        iter.next();
        parameters << QString("%1").arg(dir.relativeFilePath(iter.filePath()));
    }

    qDebug() << command;
    qDebug() << parameters;

    QProcess process;

    process.setWorkingDirectory(folder);
    process.start(command, parameters);

    if (!process.waitForFinished()) {
         qDebug() << "failed:" << process.errorString();
         return false;
    }

    qDebug() << "output:" << process.readAll();

    return true;
}

bool zlibWrappr::unzipFolder(QString zipPath, QString folder)
{
    QString command = QString("%1/miniunz").arg(appPath());
    QStringList parameters;

    parameters << "-x";
    parameters << "-o";
    parameters << zipPath;
    parameters << "-d";
    parameters << folder;

    qDebug() << command;
    qDebug() << parameters;

    QProcess process;

    process.start(command, parameters);

    if (!process.waitForFinished(-1)) {
         qDebug() << "failed:" << process.errorString();
         return false;
    }

    qDebug() << "output:" << process.readAll();

    return true;
}
