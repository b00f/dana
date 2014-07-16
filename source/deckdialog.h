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

#ifndef __DECKDIALOG_H
#define __DECKDIALOG_H


#include "qxdialog.h"
#include "combolabel.h"
#include "iconbutton.h"

class Deck;
class DeckDialog 
    : public QxDialog
{
	Q_OBJECT

public:
    enum Mode{Add=0,Edit,View};

    explicit DeckDialog(Mode mode, QWidget *parent = 0);

    void setDeck(Deck *deck);

private slots:
    void onSave();
    void onChangeFormat();

private:
	void setupView();

private:
    IconButton*iconBtn;
    QLineEdit *nameEdit;
    QPlainTextEdit *descEdit;
    QLineEdit *authorEdit;
    QLineEdit *tagsEdit;
    QLineEdit *createdEdit;
    QLineEdit *updatedEdit;
    QLineEdit *guidEdit;
    ComboLabel *frontPolicyCombo;
    ComboLabel *backPolicyCombo;

	Deck *deck;

    Mode mode;
};

#endif // __DECKDIALOG_H