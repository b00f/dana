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

#ifndef __COMPRESSOR_H
#define __COMPRESSOR_H

#include <QFile>
#include <QDataStream>
#include <QDir>

class Compressor
{
public:
    explicit Compressor();

    //A recursive function that scans all files inside the source folder
    //and serializes all files in a row of file names and compressed
    //binary data in a single file
    bool compressFolder(QString sourceFolder, QString destinationFile);

    //A function that deserializes data from the compressed file and
    //creates any needed subfolders before saving the file
    bool decompressFolder(QString sourceFile, QString destinationFolder);

private:
    QFile file;
    QDataStream dataStream;

    bool compress(QString sourceFolder, QString prefex);
};

#endif // __COMPRESSOR_H
