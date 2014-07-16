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

#ifndef __IDECK_H
#define __IDECK_H

#include "filedownloader.h"
#include "deck.h"

class iDeck 
    : public Deck
{
    Q_OBJECT

public:
    iDeck(QObject *parent = 0);

    void    setRating(int rating);

    int     getRating();
    int     getDownloads();
    QString getDeckPath() const;

    void  saveDeck();
    void  removeDeck();

    bool  openDeck(QVariant param = QVariant());
    bool  openDeck(const QDomNode &nodeDeck);
    void  closeDeck(QVariant param = QVariant());    

protected:
    void  loadPixmap(QString path);

private slots:
    void loadImage();
	
private:
    int rating;
    int downloads;

    FileDownloader *downloader;
};

#endif // __IDECK_H
