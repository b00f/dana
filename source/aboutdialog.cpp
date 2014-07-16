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

#include "aboutdialog.h"
#include "constants.h"

AboutDialog::AboutDialog(QWidget *parent)
    : QxDialog("about_dialog", parent)
{    
    setupView();
}

void AboutDialog::setupView()
{
    QGridLayout *mainLayout = new QGridLayout(this);

    QLabel *icon = new QLabel(this);
    QLabel *name = new QLabel(this);

    icon->setPixmap(PIXMAP_DANA_96);
    name->setText(tr("<p><h3>Dana</h3><br>version %1<br>A free and open source flash card system based on <a href='http://'>Leitner Box</a><br><br>Written by Mostafa Sedaghat Joo(mostafa.sedaghat@gmail.com)</p>").arg(LAST_VERSION/10, 2, 10, QChar('0')));

    mainLayout->addWidget(icon,     0,0,1,1, Qt::AlignCenter|Qt::AlignTop);
    mainLayout->addWidget(name,     1,0,1,1, Qt::AlignCenter|Qt::AlignTop);

    setSizeIncrement(200, 400);
    setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);

    setWindowTitle(STR_DIALOG_TITLE_ABOUT);
}
