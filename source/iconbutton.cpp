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

#include "iconbutton.h"
#include "qxfiledialog.h"
#include "constants.h"

#include <QFileDialog>
#include <QToolButton>
#include <QStyle>

IconButton::IconButton(QWidget *parent)
    : QPushButton(parent)
{
    clearButton = new QToolButton(this);
    
    QPixmap pixmapClear(PIXMAP_CLOSE);
    
    clearButton->setIcon(QIcon(pixmapClear));
    clearButton->setIconSize(pixmapClear.size());
    clearButton->setCursor(Qt::ArrowCursor);
    clearButton->setStyleSheet("QToolButton{border: none; padding: 0px;}");

    connect(clearButton, SIGNAL(clicked()), this, SLOT(onResetIcon()));
    connect(this, SIGNAL(clicked()), this, SLOT(onSetIcon()));

    setStyleSheet("QPushButton{outline:none;border:none;padding:0px;margin:0px;}QPushButton:hover{background:#cbdaf1;}");
    setDefaultSize(64); /// default size, for start
}

void IconButton::paintEvent (QPaintEvent *pe)
{
    QSize sz = clearButton->sizeHint();
    int frameWidth = style()->pixelMetric(QStyle::PM_DefaultFrameWidth);

    clearButton->move(rect().right() - frameWidth - sz.width(),
                     (rect().top()   + frameWidth + 2));

    QPushButton::paintEvent(pe);
}

void IconButton::setDefaultPixmap(QPixmap _defaultPixmap)
{
    defaultPixmap = _defaultPixmap;
}

void IconButton::setDefaultSize(int _size)
{
    size.setWidth (_size);
    size.setHeight(_size);

    setFixedSize(size);
    setIconSize (size);
}

void IconButton::setPixmap(QPixmap _pixmap)
{
    pixmap = _pixmap;
    setIcon(QIcon(pixmap));
}

QPixmap IconButton::getPixmap()
{
    return pixmap;
}

void IconButton::onResetIcon()
{
    pixmap = QPixmap();
    setIcon(QIcon(defaultPixmap));
}

void IconButton::onSetIcon()
{
    if(!isEnabled()) 
        return;

    QString fileName = QxFileDialog(this).getOpenImageName();

    if (!fileName.isEmpty()) {
        QImage image(fileName);
        int w = image.width();
        int h = image.height();
        int m =  std::min(w,h)/2;

        QImage cropped;
        cropped = image.copy((w/2)-m, (h/2)-m, m*2, m*2);
        cropped.save(tempPath() + "resized_image.jpg");
        QImage resized = cropped.scaled(size);

        resized.save(tempPath() + "cropped_image.jpg");

        pixmap = QPixmap::fromImage(resized);
        setIcon(QIcon(pixmap));
    }
}

void IconButton::setReadOnly(bool ro)
{
    if(ro) {
        clearButton->hide();
        disconnect(this, SLOT(onSetIcon()));
    } else {
        clearButton->show();
        connect(this, SIGNAL(clicked()), this, SLOT(onSetIcon()));
    }
}