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

#include "histograph.h"
#include "constants.h"

#include <QPainter>

Histograph::Histograph(QWidget *parent)
    : QWidget(parent)
{
}

void Histograph::setData(QMap<time_t, int> history)
{
    History = history;

    repaint();
}

void Histograph::paintEvent(QPaintEvent*)
{
    QPainter p(this);
    
    int w = width() - 4;
    int h = height() - 4;

    time_t now = QDateTime::currentDateTime().toTime_t();
    time_t start = History.begin().key();
        
    double diff = now - start;    
    double x_unit_width = w / diff;
    double y_unit_width = h / LevelCount;

    double x=0;
    double y=0;
    int i =0;
    int c = History.size();
    QPointF *points = new QPointF[c];
    QMapIterator<time_t, int> itr(History);
    
    p.setRenderHint(QPainter::Antialiasing, true);

    while(itr.hasNext())
    {
        itr.next();

        x = (itr.key() - start) *x_unit_width + 2;
        y = h - (itr.value() *y_unit_width);
        
        points[i].setX(x);
        points[i].setY(y);

        p.setPen(QPen(Qt::black, 3));
        p.drawPoint(x,y);

        i++;
    }
        
    p.setPen(QPen(Qt::black, 1));
    p.drawPolyline(points, c);
}