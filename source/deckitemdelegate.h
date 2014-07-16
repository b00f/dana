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

#ifndef __DECKITEMDELEGATE_H
#define __DECKITEMDELEGATE_H

#include <QAbstractItemDelegate>

struct RectsInfo;
class DeckItemDelegate 
    : public QAbstractItemDelegate
{
    Q_OBJECT

public:
    enum DeckViewOption {
        DetailView = 0,
        ListView      ,
    };

    explicit DeckItemDelegate(QObject *parent = 0);

    void paint(QPainter *painter, const QStyleOptionViewItem &option, const QModelIndex &index) const;
    QSize sizeHint(const QStyleOptionViewItem &option, const QModelIndex &index) const;
    bool editorEvent(QEvent *event, QAbstractItemModel *model, const QStyleOptionViewItem &option, const QModelIndex &index);
    QWidget *createEditor(QWidget *parent, const QStyleOptionViewItem &option, const QModelIndex &index) const;
    bool helpEvent(QHelpEvent *event, QAbstractItemView *view, const QStyleOptionViewItem &option, const QModelIndex &index);

    void setViewOption(int option);

signals:
    void voted(const QModelIndex &index, int rating);

private:
    void getRects(const QStyleOptionViewItem &option, const QModelIndex &index, RectsInfo &rects) const;

private:
    QFont nameFont;
    QFont descFont;
    QFont statFont;

    QPixmap starred;
    QPixmap unstarred;

    int viewOption;
};

#endif // __DECKITEMDELEGATE_H