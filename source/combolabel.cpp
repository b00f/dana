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

#include "combolabel.h"

#include <QtDebug>
#include <QFocusEvent>
#include <QHBoxLayout>

ComboLabel::ComboLabel(const QIcon &icon, bool labelToRight, QWidget *parent)
    : QWidget(parent)
{
    stacked = new QStackedLayout(this);
    labelLayout = new QHBoxLayout;
    combo = new QComboBox;
    label = new ClickableLabel;


    QWidget *labelWidget = new QWidget;
    
    if(!icon.isNull()) {
        ClickableLabel *image = new ClickableLabel;

        image->setPixmap(icon.pixmap(16));
        labelLayout->addWidget(image);
        labelLayout->addSpacing(5);

        connect(image, SIGNAL(clicked()), this, SLOT(onClick()));
	}
    
	labelLayout->addWidget(label);

    if(labelToRight)
        labelLayout->insertStretch(0);
    else
        labelLayout->addStretch();
    
	labelWidget->setLayout(labelLayout);

    stacked->addWidget(labelWidget);
	stacked->addWidget(combo);
    
    connect(combo, SIGNAL(currentIndexChanged(int)), this, SIGNAL(comboIndexChanged(int)));
    connect(combo, SIGNAL(currentIndexChanged(const QString &)), this, SLOT(onComboChanged(const QString &)));
    connect(label, SIGNAL(clicked()), this, SLOT(onClick()));

    label->setStyleSheet("QLabel{text-decoration:underline; color:blue}");
    /// label->setAlignment(Qt::AlignRight);

    stacked->setSpacing(0);
    stacked->setMargin(0);

    labelLayout->setSpacing(0);
    labelLayout->setMargin(0);

    setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);
    resize(labelWidget->width(), labelWidget->height());

    setLayout(stacked);
    setFocusPolicy(Qt::StrongFocus);
    ///combo->setFocusPolicy(Qt::NoFocus);
    labelWidget->setFocusPolicy(Qt::NoFocus);
    label->setFocusPolicy(Qt::NoFocus);
}

void ComboLabel::addItem(const QString &text, const QVariant &userData)
{
	combo->addItem(text, userData);
}

void ComboLabel::onComboChanged(const QString &text)
{
    stacked->setCurrentIndex(0);
	label->setText(text);
}

void ComboLabel::onClick()
{
    stacked->setCurrentIndex(1);
}

void ComboLabel::focusOutEvent(QFocusEvent *fe)
{
    // mac build
    if(fe->reason()==Qt::PopupFocusReason)
        return;
  ///  if(fe->reason() == Qt::TabFocusReason)
  ///      focusNextChild();

    closeEditor();
}

void ComboLabel::closeEditor()
{
    stacked->setCurrentIndex(0);
}

void ComboLabel::focusInEvent(QFocusEvent *)
{
    stacked->setCurrentIndex(1);
}

void ComboLabel::setCurrentIndex(int index)
{
    combo->setCurrentIndex(index);
}

int ComboLabel::currentIndex()
{
    return combo->currentIndex();
}

QVariant ComboLabel::itemData (int index, int role) const
{
    return combo->itemData(index, role);
}
