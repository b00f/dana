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

#ifndef __QXMESSAGEBOX_H
#define __QXMESSAGEBOX_H

#include <QMessageBox>

#include "constants.h"

class QxMessageBox 
    : public QMessageBox
{
    Q_OBJECT

public:
    explicit QxMessageBox(QWidget *parent = 0);

    static StandardButton critical   (QWidget *parent, const QString &text, const QString &title = STR_ERROR);
    static StandardButton question   (QWidget *parent, const QString &text, const QString &title = STR_QUESTION);
    static StandardButton warning    (QWidget *parent, const QString &text, const QString &title = STR_WARNING);
    static StandardButton information(QWidget *parent, const QString &text, const QString &title = STR_INFORMATION);
    
};

#endif // __QXMESSAGEBOX_H