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

#include "qxpushbutton.h"

#include <QPainter>
#include <QPixmap>
#include <QTextDocument>
#include <QIcon>
#include <QSize>
#include <QMenu>
#include <QStylePainter>
 

QxPushButton::QxPushButton(QWidget *parent)
    : QPushButton(parent)
{
}

void QxPushButton::setHtml(const QString &text)
{
    htmlText = text;
    isRichText = true;
 
    QPalette palette;
    palette.setBrush(QPalette::ButtonText, Qt::transparent);
    setPalette(palette);
}
 
void QxPushButton::setText(const QString &text)
{
    isRichText = false;
    QPushButton::setText(text);
}
 
 
QString QxPushButton::text() const
{
    if (isRichText) {
        QTextDocument richText;
        richText.setHtml(htmlText);
        return richText.toPlainText();
    } else
        return QPushButton::text();
}

QSize QxPushButton::sizeHint() const
{
    if(!isRichText) {
        return QPushButton::sizeHint();
    } else{
        QTextDocument richTextLabel;
        richTextLabel.setHtml(htmlText);
        return richTextLabel.size().toSize();
    }
}

void QxPushButton::paintEvent(QPaintEvent *event)
{
    if (isRichText) {
        QStylePainter p(this);
 
        QRect buttonRect = rect();
        QPoint point;
 
        QTextDocument richTextLabel;
        richTextLabel.setHtml(htmlText);
 
        QPixmap richTextPixmap(richTextLabel.size().width(), richTextLabel.size().height());
        richTextPixmap.fill(Qt::transparent);
        QPainter richTextPainter(&richTextPixmap);
        richTextLabel.drawContents(&richTextPainter, richTextPixmap.rect());
 
        if (!icon().isNull())
            point = QPoint(buttonRect.x() + buttonRect.width() / 2 + iconSize().width() / 2 + 2, buttonRect.y() + buttonRect.height() / 2);
        else
            point = QPoint(buttonRect.x() + buttonRect.width() / 2 - 1, buttonRect.y() + buttonRect.height() / 2);
 
        buttonRect.translate(point.x() - richTextPixmap.width() / 2, point.y() - richTextPixmap.height() / 2);
 
        p.drawControl(QStyle::CE_PushButton, getStyleOption());
        p.drawPixmap(buttonRect.left(), buttonRect.top(), richTextPixmap.width(), richTextPixmap.height(),richTextPixmap);
    } else
        QPushButton::paintEvent(event);
}
QStyleOptionButton QxPushButton::getStyleOption() const
{
    QStyleOptionButton opt;
    opt.initFrom(this);
    opt.features = QStyleOptionButton::None;
    if (isFlat())
        opt.features |= QStyleOptionButton::Flat;
    if (menu())
        opt.features |= QStyleOptionButton::HasMenu;
    if (autoDefault() || isDefault())
        opt.features |= QStyleOptionButton::AutoDefaultButton;
    if (isDefault())
        opt.features |= QStyleOptionButton::DefaultButton;
    if (isDown() || (menu() && menu()->isVisible()))
        opt.state |= QStyle::State_Sunken;
    if (isChecked())
        opt.state |= QStyle::State_On;
    if (!isFlat() && !isDown())
        opt.state |= QStyle::State_Raised;
    opt.text = text();
    opt.icon = icon();
    opt.iconSize = iconSize();
    return opt;
}