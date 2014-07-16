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

#ifndef __CARDITEMDELEGATE_H
#define __CARDITEMDELEGATE_H

#include <QStyledItemDelegate>
#include <QPen>
#include <QTableView>


class CardItemDelegate 
    : public QStyledItemDelegate
{
    Q_OBJECT
public:
    CardItemDelegate(QTableView *parent = 0);
 
    void paint(QPainter *painter, const QStyleOptionViewItem &option, const QModelIndex &index) const;
	QSize sizeHint(const QStyleOptionViewItem &option, const QModelIndex &index) const;
	bool editorEvent(QEvent *event, QAbstractItemModel *model, const QStyleOptionViewItem &option, const QModelIndex &index);
	QWidget *createEditor(QWidget *parent, const QStyleOptionViewItem &option, const QModelIndex &index) const;
	bool eventFilter (QObject *editor, QEvent *event);
    bool helpEvent(QHelpEvent *e, QAbstractItemView *view, const QStyleOptionViewItem &option, const QModelIndex &index);

private:
    QPen gridPen;
};

#endif // __CARDITEMDELEGATE_H
