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

#include "modifier.h"


Modifier::Modifier()
{
    resetModification();
}

Modifier::~Modifier()
{
}

void Modifier::setModified(bool _modified)
{
    modified = _modified;
    modifiedTime = QDateTime::currentDateTime();
}

bool Modifier::isModified() const
{
    return modified;
}

QDateTime Modifier::getModifiedTime() const
{
    return modifiedTime;
}

void Modifier::resetModification()
{
    modified = false;
    modifiedTime = QDateTime::currentDateTime();
}