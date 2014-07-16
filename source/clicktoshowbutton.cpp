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

#include "clicktoshowbutton.h"

#include <QPainter>

ClickToShowButton::ClickToShowButton(QWidget *parent) :
    QPushButton(parent)
{
    connect(this, SIGNAL(clicked(bool)), this, SLOT(onClick(bool)));

    setFocusPolicy(Qt::NoFocus);
}

void ClickToShowButton::paintEvent(QPaintEvent *pe)
{
	Q_UNUSED(pe);

    QBrush brush(QColor(192,192,192));

    QFont serifFont("", 18, QFont::Normal);
    QRect r = rect();
    QPainter painter(this);

    painter.setFont(serifFont);
    painter.fillRect(r, brush);
    painter.fillRect(r, Qt::BDiagPattern);
    painter.drawText(r, Qt::AlignCenter, "Click to show");

    painter.end();
}

void ClickToShowButton::onClick(bool)
{
    hide();
}
