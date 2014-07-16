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

#ifndef BUSYINDICATOR_H
#define BUSYINDICATOR_H

#include <QTimer>
#include <QtWidgets/QWidget>

class BusyIndicator : public QWidget
{
    Q_OBJECT
public:
    enum IndicatorStyle{StyleRect, StyleEllipse, StyleArc};

    explicit BusyIndicator(QWidget *parent = 0);

    void paintEvent(QPaintEvent *);
    QSize minimumSizeHint() const;
    QSize sizeHint() const;

    void setIndicatorStyle(IndicatorStyle);
    void setColor(QColor color);
    const IndicatorStyle indicatorStyle() const;

signals:

private slots:
    void rotate();

private:
    QPixmap generatePixmap(int sideLength);
    void drawRectStyle(QPainter *painter);
    void drawEllipseStyle(QPainter *painter);
    void drawArcStyle(QPainter *painter);

    QTimer timer;
    int startAngle;

    IndicatorStyle m_style;

    QColor fillColor;
};

#endif // BUSYINDICATOR_H
