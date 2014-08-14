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

#include "tempdeck.h"
#include "constants.h"

TempDeck::TempDeck(QObject *parent)
    : Deck(Type_TempDeck, parent)
{

}

void TempDeck::saveDeck()
{
}

void TempDeck::removeDeck()
{
}

bool TempDeck::openDeck(QVariant param)
{
    Q_UNUSED(param);

    return false;
}

void TempDeck::closeDeck(QVariant param)
{
    Q_UNUSED(param);
}

QString TempDeck::getDeckPath() const
{
    QString deckPath = utils::combinePaths(
        tempPath(), QString("tempDeck_%1").arg((quint64)this));

    utils::createDirectory(deckPath);

    return deckPath;
}
