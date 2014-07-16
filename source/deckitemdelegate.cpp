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

#include "deckitemdelegate.h"
#include "decklistdatamodel.h"
#include "deck.h"
#include "constants.h"

#include <QtGui>
#include <QToolTip>
#include <QAbstractItemModel>


struct RectsInfo {
    QRect iconRect;
    QRect nameRect;
    QRect descRect;
    QRect cardNoRect;
    QRect downloadRect;
    QRect ratingRect;
};

DeckItemDelegate::DeckItemDelegate(QObject *parent)
    : QAbstractItemDelegate(parent)
    , nameFont("Lucida Grande", 14, QFont::Bold  , false)
    , descFont("Lucida Grande", 10, QFont::Normal, false)
    , statFont("Lucida Grande",  8, QFont::Normal, true)
    , starred(PIXMAP_STARRED)
    , unstarred(PIXMAP_UNSTARRED)
{
    viewOption = DetailView;
}

void DeckItemDelegate::paint (QPainter *painter, const QStyleOptionViewItem &option, 
                              const QModelIndex &index) const
{
    QRect r = option.rect;

    //Color: #C4C4C4
    QPen linePen(QColor::fromRgb(211,211,211), 1, Qt::SolidLine);

    //Color: #005A83
    QPen lineMarkedPen(QColor::fromRgb(0,90,131), 1, Qt::SolidLine);

    //Color: #333
    QPen fontPen(QColor::fromRgb(51,51,51), 1, Qt::SolidLine);

    //Color: #fff
    QPen fontMarkedPen(Qt::white, 1, Qt::SolidLine);
    
    if(option.state & QStyle::State_Selected) {
        QLinearGradient gradientSelected(r.left(),r.top(),r.left(),r.height()+r.top());
        gradientSelected.setColorAt(0.0, QColor::fromRgb(119,213,247));
        gradientSelected.setColorAt(0.9, QColor::fromRgb(27,134,183));
        gradientSelected.setColorAt(1.0, QColor::fromRgb(0,120,174));
        painter->setBrush(gradientSelected);
        painter->drawRect(r);

        //BORDER
        painter->setPen(lineMarkedPen);
        painter->drawLine(r.topLeft(),r.topRight());
        painter->drawLine(r.topRight(),r.bottomRight());
        painter->drawLine(r.topLeft(),r.bottomLeft());
        painter->drawLine(r.bottomLeft()+QPoint(0,1),r.bottomRight()+QPoint(0,1));

        painter->setPen(fontMarkedPen);

    } else {
        //BACKGROUND
        //ALTERNATING COLORS
        if(option.state & QStyle::State_Enabled)
            painter->setBrush((index.row() % 2) ? Qt::white : QColor(252,252,252));
        else
            painter->setBrush(Qt::lightGray);
        painter->drawRect(r);

        //BORDER
        painter->setPen(linePen);
        painter->drawLine(r.topLeft(),r.topRight());
        painter->drawLine(r.topRight(),r.bottomRight());
        painter->drawLine(r.topLeft(),r.bottomLeft());
        painter->drawLine(r.bottomLeft()+QPoint(0,1),r.bottomRight()+QPoint(0,1));

        painter->setPen(fontPen);
    }

    // Get rects
    RectsInfo rects;
    getRects(option, index, rects);

    //GET NAME, DESCRIPTION AND ICON
    int type = index.data( DeckListDataModel::TypeRole ).toInt();
    QPixmap pixmap = index.data( DeckListDataModel::PixmapRole ).value<QPixmap>();
    QString name = index.data( DeckListDataModel::NameRole ).toString();
    QString description  = index.data( DeckListDataModel::DescRole ).toString();
    QString cardNo = cardNumberToString(  index.data( DeckListDataModel::CardNumberRole ).toInt() );
    
    /////==========================
    ///// statistic box
    ///// 
    ///// draw right section
    painter->setFont(QFont("Lucida Grande", 8, QFont::Normal, true));

    // CARD NO
    painter->drawText(rects.cardNoRect, Qt::AlignRight|Qt::AlignVCenter, cardNo);

    if(type == Deck::Type_iDeck) {
        int rating = index.data( DeckListDataModel::RatingRole ).toInt();
        QString downloads = QString(STR_DECK_DOWNLOADS).arg( index.data( DeckListDataModel::DownloadsRole ).toInt() );

        // DOWNLOADS
        painter->drawText(rects.downloadRect, Qt::AlignRight|Qt::AlignVCenter, downloads);

        // RATING
        int width = starred.width();
        int x = rects.ratingRect.x();
        int y = rects.ratingRect.y();
        for (int i = 0; i < 5; ++i) {
            if(i<rating)
                painter->drawPixmap(x, y, starred);
            else
                painter->drawPixmap(x, y, unstarred);
            x += width;
        }
    }
    /////==========================

    // ICON
    if (!pixmap.isNull()) {
        //ICON
        painter->drawPixmap(rects.iconRect, pixmap);
    }

    //NAME
    painter->setFont(nameFont);
    painter->drawText(rects.nameRect, Qt::AlignBottom|Qt::AlignLeft, name);

    //DESCRIPTION
    painter->setFont(QFont("Lucida Grande", 10, QFont::Normal));
    painter->drawText(rects.descRect, Qt::AlignLeft|Qt::TextWordWrap, description);
}

QSize DeckItemDelegate::sizeHint (const QStyleOptionViewItem &option, const QModelIndex &index) const
{
    Q_UNUSED(index);
    Q_UNUSED(option);

    if(viewOption == ListView) {
        QFontMetrics metric(nameFont);
        int height = metric.height() + 10; /// 5+5 for top and bottom padding
        return QSize(400, height); // very dumb value
    }

    return QSize(400, 80); // very dumb value
}

bool DeckItemDelegate::editorEvent(QEvent *event, QAbstractItemModel *model,
                               const QStyleOptionViewItem &option,
                               const QModelIndex &index)
{
    if (event->type() == QEvent::MouseButtonPress) {
        // RATING
        QMouseEvent *mouseEvent = static_cast<QMouseEvent*>(event);
        
        int type = index.data( DeckListDataModel::TypeRole ).toInt();

        if(type == Deck::Type_iDeck) {  
            /// Get rects
            RectsInfo rects;
            getRects(option, index, rects);

            if(rects.ratingRect.contains(mouseEvent->pos())){
                int stars = qBound(0, int(0.7 + qreal(mouseEvent->pos().x()
                    - rects.ratingRect.x()) / (rects.ratingRect.width()/5)), 5);

                emit voted(index, stars);
               
                return false; //so that the selection can change
            }
        }
    }

    return QAbstractItemDelegate::editorEvent(event, model, option, index);
}

QWidget *DeckItemDelegate::createEditor(QWidget *parent, const QStyleOptionViewItem &option, 
                                        const QModelIndex &index) const
{
    return QAbstractItemDelegate::createEditor(parent, option, index);
}

bool DeckItemDelegate::helpEvent(QHelpEvent *event, QAbstractItemView *view, const QStyleOptionViewItem &option, 
                                 const QModelIndex &index)
{
    if(event->type()==QEvent::ToolTip) {
        QString nameTip     = index.data( DeckListDataModel::NameRole ).toString();
        QString descTip     = index.data( DeckListDataModel::DescRole ).toString();
        QString cardNoTip   = index.data( DeckListDataModel::CardNumberRole ).toString();
        QString DownloadTip = index.data( DeckListDataModel::DownloadsRole ).toString();
        QString RatingTip   = index.data( DeckListDataModel::RatingStateRole ).toString();

        /// Get rects
        RectsInfo rects;
        QString tooltip;
        getRects(option, index, rects);

        if(viewOption == ListView) {
            tooltip = QString("<table> \
                <tr><td><b>%1</b> </td><td> %2</td></tr> \
                <tr><td><b>%3</b> </td><td> %4</td></tr> \
                <tr><td><b>%5</b> </td><td> %6</td></tr> \
                <tr><td><b>%7</b> </td><td> %8</td></tr></table>")
                .arg(STR_DECK_NAME)
                .arg(nameTip)
                .arg(STR_DECK_DESC)
                .arg(descTip)
                .arg(STR_DECK_CARD_NO)
                .arg(cardNoTip)
                .arg(STR_DECK_DOWNLOADS_1)
                .arg(DownloadTip); 
        } else {
            if(rects.nameRect.contains(event->pos())) {
                tooltip = QString("<div align=justify><b>%1</b></div>").arg(nameTip);
            } else if(rects.descRect.contains(event->pos())) {
                tooltip = QString("<div align=justify>%1</div>").arg(descTip);
            } else if(rects.cardNoRect.contains(event->pos())) {
                tooltip = QString("<div align=justify>%1</div>").arg(cardNoTip);
            } else if(rects.downloadRect.contains(event->pos())) {
                tooltip = QString("<div align=justify>%1</div>").arg(DownloadTip);
            } else if(rects.ratingRect.contains(event->pos())) {
                tooltip = QString("<div align=justify>%1</div>").arg(RatingTip);
            } else {
                QToolTip::hideText();
                event->ignore();
                return true;
            }
        }
        QToolTip::showText(event->globalPos(), tooltip);

        return true;
    }

    return QAbstractItemDelegate::helpEvent(event, view, option, index);
}

void DeckItemDelegate::getRects(const QStyleOptionViewItem &option, const QModelIndex &index, RectsInfo &rects) const
{
    int type = index.data( DeckListDataModel::TypeRole ).toInt();
    QString name = index.data( DeckListDataModel::NameRole ).toString();
    QPixmap pixmap = index.data( DeckListDataModel::PixmapRole ).value<QPixmap>();
    QString cardNo = cardNumberToString(  index.data( DeckListDataModel::CardNumberRole ).toInt() );
    QString downloads = QString(STR_DECK_DOWNLOADS).arg( index.data( DeckListDataModel::DownloadsRole ).toInt() );

    if(viewOption == ListView) {
        QRect itemRect = option.rect;
        
        int x = 0;
        int y = 0;
        int w = 0;
        int h =  0;
        int width = 0;
        int height = 0;
        int statWidth = 0;

        if(type == Deck::Type_iDeck) {
            // RATING
            width = starred.width()*5;
            height = starred.height();
            x = itemRect.right() - width - 5;
            y = itemRect.top() + (itemRect.height()/2) - (height/2);
            w = width;
            h = height;
            statWidth = width;

            rects.ratingRect.setRect(x,y,w,h);
        } else {
            /***/
        }

        statWidth += 10;    

        QFontMetrics metric2(nameFont);
        height = metric2.height();
        x = itemRect.x() + 5;
        y = itemRect.top() + (itemRect.height()/2) - (height/2);
        w = itemRect.width() - statWidth;
        h = height;

        rects.nameRect.setRect(x,y,w,h);
    }
    else
    {
        QRect itemRect = option.rect;
        
        int x = 0;
        int y = 0;
        int w = 0;
        int h =  0;
        int width = 0;
        int height = 0;
        int temp = 0;
        int statWidth = 0;
        int iconWidth = 0;

        /////==========================
        ///// statistic box
        ///// 
        ///// draw right section
        QFontMetrics metric1(statFont);

        // Card No
        width = metric1.width(cardNo)+2;
        height = metric1.height();
        x = itemRect.right() - width - 5;
        y = itemRect.bottom() - height - 5;
        w = width;
        h = height;
        statWidth = std::max<int>(statWidth, width);

        rects.cardNoRect.setRect(x,y,w,h);

        if(type == Deck::Type_iDeck) {
            // DOWNLOADS
            width = metric1.width(downloads)+2;
            x = itemRect.right() - width - 5;
            y -= (height);
            w = width;
            h = height;
            temp += height;
            statWidth = std::max<int>(statWidth, width);

            rects.downloadRect.setRect(x,y,w,h);

            // RATING
            width = starred.width()*5;
            x = itemRect.right() - width - 5;
            y -= (height + 12);
            w = width;
            h = height;
            statWidth = std::max<int>(statWidth, width);

            rects.ratingRect.setRect(x,y,w,h);
        } else {
            /***/
        }

        statWidth += 10;    
        /////==========================

        // ICON
        if (!pixmap.isNull()) {
            //ICON
            w = 64;///pixmap.width();
            h = 64;///pixmap.height();
            x = itemRect.x() + 5;
            y = itemRect.y() + 10;
            iconWidth = w+10;

            rects.iconRect.setRect(x, y, w, h);
        }

        //NAME
        QFontMetrics metric2(nameFont);
        height = metric2.height();
        x = itemRect.x() + iconWidth;
        y = itemRect.y() + 10;
        w = itemRect.width() - statWidth - iconWidth;
        h = height;
        temp = height;

        rects.nameRect.setRect(x,y,w,h);

        //DESCRIPTION
        QFontMetrics metric3(descFont);
        height = metric3.height();
        x = itemRect.x() + iconWidth;
        y = itemRect.y() + temp + 10;
        w = itemRect.width() - statWidth - iconWidth;
        h = itemRect.height() - temp - 15;
        h = (h/height)*height;

        rects.descRect.setRect(x,y,w,h);
    }
}

void DeckItemDelegate::setViewOption(int option)
{
    viewOption = option;
}