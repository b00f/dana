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

#ifndef __UTILS_H
#define __UTILS_H

#include <QDir>
#include <QWidget>
#include <QLayout>
#include <QFileInfo>
#include <QLayoutItem>
#include <QTextDocument>

class utils
{
public:
    static QString combinePaths(const QString &path1, const QString &path2)
    {
        return QDir::toNativeSeparators( 
            QDir::cleanPath(path1 + QDir::separator() + path2) );
    }

    static void createDirectory(const QString &path)
    {
        QDir dir(path);

        if (!dir.exists()) {
            dir.mkpath(".");
        }
    }

    ///http://john.nachtimwald.com/2010/06/08/qt-remove-directory-and-its-contents/
    static bool removeDirectory(const QString &dirName)
    {
        bool result = true;
        QDir dir(dirName);

        if (dir.exists(dirName)) {
            Q_FOREACH(QFileInfo info, dir.entryInfoList(QDir::NoDotAndDotDot | QDir::System | QDir::Hidden  | QDir::AllDirs | QDir::Files, QDir::DirsFirst)) {
                if (info.isDir()) {
                    result = removeDirectory(info.absoluteFilePath());
                }
                else {
                    result = QFile::remove(info.absoluteFilePath());
                }

                if (!result) {
                    return result;
                }
            }
            result = dir.rmdir(dirName);
        }

        return result;
    }

    static void copyFile(const QString &to, const QString &from)
    {
        QFile sourceFile(from);

        if(sourceFile.exists())
            sourceFile.copy(to);
    }

    //// http://www.qtcentre.org/archive/index.php/t-23469.html
    static void copyDirectory(const QString &to, const QString &from)
    {
        QDir sourceDir(from);
        if(!sourceDir.exists())
            return;

        QDir destDir(to);
        if(!destDir.exists()) {
            destDir.mkdir(to);
        }

        QStringList files = sourceDir.entryList(QDir::Files);
        for(int i = 0; i< files.count(); i++)
        {
            QString srcName = from + QDir::separator() + files[i];
            QString destName = to + QDir::separator() + files[i];

            copyFile(destName, srcName);
        }

        QStringList dirs = sourceDir.entryList(QDir::AllDirs | QDir::NoDotAndDotDot);
        for(int i = 0; i< dirs.count(); i++)
        {
            QString srcName = from + QDir::separator() + dirs[i];
            QString destName = to + QDir::separator() + dirs[i];

            copyDirectory(destName, srcName);
        }
    }

    static void moveDirectory(const QString &source, const QString &dest)
    {
        copyDirectory(source, dest);
        removeDirectory(source);
    }

    static bool removeFile(QString path)
    {
        return QFile::remove(path);
    }

    static QString HTML2Plain(QString richText)
    {
        /// convert front to plain text
        /*richText.remove(QRegExp("<style[^*]*</style>"));
        richText.remove(QRegExp("<[^>]*>"));
        richText.remove(QRegExp("\n"));
        */

        QTextDocument doc;
        doc.setHtml(richText);
        return doc.toPlainText();
    }

    static QString getUniqueFileName(QString path, QString fileName)
    {
        QFileInfo fi(fileName);
        QString uniqueFileName = QString("%1/%2")
                .arg(path)
                .arg(fileName);

        int nameSuffix = 1;
        while(QFile::exists(uniqueFileName)) {
            uniqueFileName = QString("%1/%2_%3.%4")
                    .arg(path)
                    .arg(fi.completeBaseName())
                    .arg(nameSuffix++)
                    .arg(fi.suffix());
        }

        return uniqueFileName;
    }

    static void clearLayout(QLayout *layout)
    {
        QLayoutItem *child;
        while ((child = layout->takeAt(0)) != 0) {
            if(child->layout() != 0)
                clearLayout( child->layout() );
            else if(child->widget() != 0)
                delete child->widget();

            delete child;
        }
    }


};

#endif // __UTILS_H
