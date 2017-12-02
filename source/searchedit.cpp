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

#include "searchedit.h"
#include "constants.h"

#include <QFocusEvent>
#include <QToolButton>
#include <QPainter>
#include <QStyle>
#include <QPen>

SearchEdit::SearchEdit(QWidget *parent)
: QLineEdit(parent)
{
	drawSearchLabel = true;
	
	clearButton = new QToolButton(this);
	searchButton = new QToolButton(this);

	QPixmap pixmapClear(PIXMAP_CLOSE);
	QPixmap pixmapSearch(PIXMAP_SEARCH);

	searchButton->setIcon(QIcon(pixmapSearch));
	searchButton->setIconSize(pixmapSearch.size());
	searchButton->setCursor(Qt::PointingHandCursor);
	searchButton->setStyleSheet("QToolButton { border: none; padding: 0px; }");

	clearButton->setIcon(QIcon(pixmapClear));
	clearButton->setIconSize(pixmapClear.size());
	clearButton->setCursor(Qt::ArrowCursor);
	clearButton->setStyleSheet("QToolButton { border: none; padding: 0px; }");
    clearButton->hide();

	connect(clearButton, SIGNAL(clicked()), this, SLOT(clear()));
	connect(searchButton, SIGNAL(clicked()), this, SLOT(selectAll()));

    connect(this, SIGNAL(textChanged(const QString&)), this, SLOT(updateCloseButton(const QString&)));
	int frameWidth = style()->pixelMetric(QStyle::PM_DefaultFrameWidth);

	setStyleSheet(QString("QLineEdit { padding-left: %1px; padding-right: %2px; } ")
		.arg(searchButton->sizeHint().width() + frameWidth)
		.arg(clearButton->sizeHint().width() + frameWidth + 1));

	QSize msz = minimumSizeHint();
	setMinimumSize(qMax(msz.width(),  clearButton->sizeHint().height() + frameWidth *2 + 2),
		qMax(msz.height(), clearButton->sizeHint().height() + frameWidth *2 + 2));
}

void SearchEdit::resizeEvent(QResizeEvent *)
{
    int frameWidth = style()->pixelMetric(QStyle::PM_DefaultFrameWidth);
    QSize sz ;

    sz = searchButton->sizeHint();
    searchButton->move(rect().left() + (3*frameWidth),
		(rect().bottom() + 1 - sz.height())/2);

    sz = clearButton->sizeHint();
	clearButton->move(rect().right() - frameWidth - sz.width(),
		(rect().bottom() + 1 - sz.height())/2);
}

void SearchEdit::paintEvent(QPaintEvent *pe)
{
	QLineEdit::paintEvent(pe);

	if(drawSearchLabel) {
		QPainter painter(this);

		painter.setPen(QPen(Qt::gray));
		QRect r = rect();
		r.moveLeft (searchButton->width()+2);
		painter.drawText(r, Qt::AlignLeft|Qt::AlignVCenter, "Search");

	}

}
void SearchEdit::updateCloseButton(const QString &text)
{
    clearButton->setVisible(!text.isEmpty());
}

void SearchEdit::focusInEvent(QFocusEvent *e)
{
	QLineEdit::focusOutEvent(e);

	drawSearchLabel = false;
}

void SearchEdit::focusOutEvent(QFocusEvent *e)
{
	QLineEdit::focusOutEvent(e);

	bool hasText = text().isEmpty();
	if(e->lostFocus()) {
		if(hasText){
			drawSearchLabel = true;
		}
	}
}
