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

#include "carditemdelegate.h"
#include "deckdatamodel.h"
#include "decktable.h"
#include "card.h"

#include <QApplication>
#include <QPaintEvent>
#include <QPainter>
#include <QToolTip>
#include <QtDebug>
#include <QColor>

CardItemDelegate::CardItemDelegate(QTableView *parent)
    : QStyledItemDelegate(parent)
{
    QStyleOptionViewItemV4 option;

    int gridHint = parent->style()->styleHint(QStyle::SH_Table_GridLineColor, &option);
    QColor gridColor = static_cast<QRgb>(gridHint);

    gridPen = QPen(gridColor, 0, parent->gridStyle());
}

void CardItemDelegate::paint(QPainter *painter, const QStyleOptionViewItem &option, const QModelIndex &index) const
{
    if(!index.isValid())
        return;

    if (index.column()==DeckDataModel::ColumnStarred) {
        QPixmap pixmap = Card::getStarredPixmap( index.data(DeckDataModel::StarredRole).toBool() );
        QRect rect = option.rect;

        rect.adjust(0, 0, -1, -1);

        int width = pixmap.width();
        int height = pixmap.height();
        int x = rect.x() + (rect.width() / 2) - (width / 2);
        int y = rect.y() + (rect.height() / 2) - (height / 2);

        painter->save();

        if (option.state & QStyle::State_Selected) {
            painter->fillRect(option.rect, option.palette.highlight());
        }

        painter->drawPixmap(x, y, pixmap);

        painter->restore();

    } else if (index.column()==DeckDataModel::ColumnDifficulty) {
        QPixmap pixmap = Card::getDifficultyPixmap( (Card::Difficulty)index.data(DeckDataModel::DifficultyRole).toInt() );
        QRect rect = option.rect;

        rect.adjust(0, 0, -1, -1);

        int width = pixmap.width();
        int height = pixmap.height();
        int x = rect.x() + (rect.width() / 2) - (width / 2);
        int y = rect.y() + (rect.height() / 2) - (height / 2);

        painter->save();

        if (option.state & QStyle::State_Selected) {
            painter->fillRect(option.rect, option.palette.highlight());
        }

        painter->drawPixmap(x, y, pixmap);

        painter->restore();

    } else {
        QStyledItemDelegate::paint(painter, option, index);
    }

    QPen oldPen = painter->pen();
    painter->setPen(gridPen);

    // paint vertical lines
    //painter->drawLine(option.rect.topRight(), option.rect.bottomRight());
    // paint horizontal lines

    //if (index.column()!=1) //<-- check if column need horizontal grid lines
    painter->drawLine(option.rect.bottomLeft(), option.rect.bottomRight());

    painter->setPen(oldPen);
}

QSize CardItemDelegate::sizeHint(const QStyleOptionViewItem &option, const QModelIndex &index) const
{
    return QStyledItemDelegate::sizeHint(option, index);
}

bool CardItemDelegate::editorEvent(QEvent *event, QAbstractItemModel *model, const QStyleOptionViewItem &option, const QModelIndex &index)
{
    if (index.column()==DeckDataModel::ColumnStarred) {
        if (event->type() == QEvent::MouseButtonPress) {

            model->setData(index, QVariant(), DeckDataModel::StarredRole);
            
            return false; //so that the selection can change
        }
    } 

    return QStyledItemDelegate::editorEvent(event, model, option, index);
}

QWidget *CardItemDelegate::createEditor(QWidget *parent, const QStyleOptionViewItem &option, const QModelIndex &index) const
{
    return QStyledItemDelegate::createEditor(parent, option, index);
}

bool CardItemDelegate::eventFilter (QObject *editor, QEvent *event)
{
    return QStyledItemDelegate::eventFilter(editor, event);
}

bool CardItemDelegate::helpEvent(QHelpEvent *e, QAbstractItemView *view, const QStyleOptionViewItem &option, const QModelIndex &index)
{
    if(!index.isValid())
        return false;

    if (e->type() == QEvent::ToolTip) {
        QToolTip::hideText();

        if (index.column()==DeckDataModel::ColumnFront) {
            QString front = index.data(Qt::DisplayRole).toString();
            QToolTip::showText(e->globalPos(), QString("<div>%1</div>").arg(front), view);
            return true;
        } else if (index.column()==DeckDataModel::ColumnDifficulty) {
            QString difficulty = Card::getDifficultyString( (Card::Difficulty)index.data(DeckDataModel::DifficultyRole).toInt() );
            QToolTip::showText(e->globalPos(), QString("<div>%1</div>").arg(difficulty), view);
            return true;
        }else if (index.column()==DeckDataModel::ColumnStarred) {
            QString starred = Card::getStarredString( index.data(DeckDataModel::StarredRole).toBool() );
            if(starred.length()>0)
                QToolTip::showText(e->globalPos(), QString("<div>%1</div>").arg(starred), view);
            return true;
        }
    }

    if (!QStyledItemDelegate::helpEvent(e, view, option, index))
        QToolTip::hideText();

    return true;
}
