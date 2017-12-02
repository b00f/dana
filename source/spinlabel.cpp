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

#include "spinlabel.h"

#include <QtDebug>
#include <QFocusEvent>
#include <QHBoxLayout>

SpinLabel::SpinLabel(QString format, QWidget *parent)
    : QWidget(parent)
    , format(format)
{
    stacked = new QStackedLayout(this);
    spin = new QSpinBox;
    label = new ClickableLabel;

    stacked->addWidget(label);
    stacked->addWidget(spin);

    connect(spin, SIGNAL(valueChanged(int)), this, SIGNAL(spinValueChanged(int)));
    connect(spin, SIGNAL(valueChanged(int)), this, SLOT(onSpinValueChanged(int)));
    connect(label, SIGNAL(clicked()), this, SLOT(onClick()));

    label->setStyleSheet("QLabel{text-decoration:underline;}");

    stacked->setSpacing(0);
    stacked->setMargin(0);

    label->setMargin(0);
    
    setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);
    resize(spin->width(), spin->height());
    
    setLayout(stacked);
    setFocusPolicy(Qt::StrongFocus);
    spin->setFocusPolicy(Qt::NoFocus);
    label->setFocusPolicy(Qt::NoFocus);
}

void SpinLabel::onClick()
{
    stacked->setCurrentWidget(spin);
}

void SpinLabel::focusOutEvent(QFocusEvent *fe)
{
    Q_UNUSED(fe);
    ///qDebug("focusOutEvent");

    closeEditor();
}

void SpinLabel::focusInEvent(QFocusEvent *)
{
    ///qDebug("focusInEvent");

    stacked->setCurrentWidget(spin);
}

void SpinLabel::closeEditor()
{
    stacked->setCurrentWidget(label);
}

void SpinLabel::setSpinValue(int value)
{
    spin->setValue(value);
}

int SpinLabel::getSpinValue()
{
    return spin->value();
}

void SpinLabel::onSpinValueChanged(int value)
{
    ///stacked->setCurrentWidget(label);

    label->setText(QString(format).arg(value));
}
