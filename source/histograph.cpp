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
    , History(0)
{
}

void Histograph::setHistory(CardHistory* history)
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
    time_t start = History->history[0]->time.toTime_t();
        
    double diff = now - start;    
    double x_unit_width = w / diff;
    double y_unit_width = h / LevelCount;

    double x=0;
    double y=0;
    int i =0;
    int c = History->history.size();
    QPointF *points = new QPointF[c];
    
    p.setRenderHint(QPainter::Antialiasing, true);

    for (auto it=History->history.constBegin();
        it!=History->history.constEnd(); ++it) {

        x = ((*it)->time.toTime_t() - start) *x_unit_width + 2;
        y = h - ((*it)->level *y_unit_width);
        
        points[i].setX(x);
        points[i].setY(y);

        p.setPen(QPen(Qt::black, 3));
        p.drawPoint(x,y);

        i++;
    }
        
    p.setPen(QPen(Qt::black, 1));
    p.drawPolyline(points, c);
}
