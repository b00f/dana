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

#include "qxdialog.h"
#include "qxsettings.h"
#include "constants.h"

QxDialog::QxDialog(QString name, QWidget *parent)
    : QDialog(parent)
    , name(name)
{
    Qt::WindowFlags flags = windowFlags();
    flags &= ~Qt::WindowContextHelpButtonHint;
    setWindowFlags(flags);

    connect(this, SIGNAL(finished(int)), this, SLOT(onFinish(int)));

    restoreGeometry(getSetting("geometry").toByteArray());
}

void QxDialog::setWindowTitle(const QString &caption)
{
    QString title = QString("%1 - %2").arg(APP_TITLE).arg(caption);

    QDialog::setWindowTitle(title);
}

void QxDialog::onFinish(int result)
{
    Q_UNUSED(result)

    setSetting("geometry", saveGeometry());
}

QVariant QxDialog::getSetting(const QString &key)
{
    QString group = name;
    return QxSettings::getSetting(key, group);
}

void QxDialog::setSetting(const QString &key, const QVariant &value)
{
    QString group = name;
    QxSettings::setSetting(key, group, value);
}

QWidget *QxDialog::hLine()
{
    QFrame *hLine = new QFrame;

    hLine->setFrameShape(QFrame::HLine);
    hLine->setFrameShadow(QFrame::Sunken);
    hLine->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Minimum);

    return hLine;
}

QWidget *QxDialog::vLine()
{
    QFrame *vLine = new QFrame;

    vLine->setFrameShape(QFrame::VLine);
    vLine->setFrameShadow(QFrame::Sunken);
    vLine->setSizePolicy(QSizePolicy::Minimum, QSizePolicy::Minimum);

    return vLine;
}

QWidget *QxDialog::vLine2()
{
    QFrame *vLine = new QFrame;

    vLine->setFrameShape(QFrame::VLine);
    vLine->setFrameShadow(QFrame::Sunken);
    vLine->setSizePolicy(QSizePolicy::Minimum, QSizePolicy::Expanding);

    return vLine;
}

QLayoutItem *QxDialog::hSpacer()
{
    QSpacerItem *hSpacer = new QSpacerItem(0, 8, QSizePolicy::Expanding, QSizePolicy::Fixed);
    return hSpacer;
}

QLayoutItem *QxDialog::vSpacer()
{
    QSpacerItem *vSpacer = new QSpacerItem(8, 0, QSizePolicy::Fixed, QSizePolicy::Expanding);
    return vSpacer;
}
