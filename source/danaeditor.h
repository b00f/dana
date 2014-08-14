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

#ifndef __DANAEDITOR_H
#define __DANAEDITOR_H

#include <QtGui>
#include <QtDebug>
#include <QtWidgets>

#include <QtSpeech>

class DanaEditor 
    : public QTextEdit
{
	Q_OBJECT

public:
    DanaEditor(QWidget *parent = 0);
    ~DanaEditor();

    void setDeckPath(QString path);

    void setTextFormat(QTextCharFormat charFormat, QTextBlockFormat blockFormat);
    void getTextFormat(QTextCharFormat &charFormat, QTextBlockFormat &blockFormat);

    void setText(QString text);
    QString getText();

    void setReadOnly(bool ro);

    void setAcceptRichText(bool accept);

private:
	void setupView();
	void setupActions();
	void setupToolbar();

    void textListStyle(QTextListFormat::Style style);
	void mergeFormatOnWordOrSelection(const QTextCharFormat &format);
	void fontChanged(const QFont &f);
	void colorChanged(const QColor &c);
    void alignmentChanged();
    void listFormatChanged();
    void directionChanged();
    void setDirection(Qt::LayoutDirection direction);

    void addActionToToolbar(QAction *a);
    void addLineToToolbar();

    bool eventFilter(QObject *watched, QEvent *event);
    QVariant loadResource(int type, const QUrl &name);

    QAction *createAction(QString icon,
                          QString text,
                          QObject *parent,
                          const char *slot,
                          QKeySequence keySequence = QKeySequence(),
                          bool checkable = false);

    void insertFromMimeData(const QMimeData *source);

public slots:
    void showToolbar();

private slots:
	void textBold();
	void textUnderline();
	void textItalic();
    void textDirection(QAction *a);
    void textFont();
	void textListNumber();
	void textListBullet();
	void textColor();
    void textAlign(QAction *a);
    void indentLess();
    void indentMore();
    void insertLatex();
    void insertImage();
    void clearFormat();
    void listen();

	void currentCharFormatChanged(const QTextCharFormat &format);
    void cursorPositionChanged();

    void onFinishSpeech();

private:
    QAction *actShowToolbar,
            *actTextBold,
			*actTextItalic,
			*actTextUnderline,
			*actAlignLeft,
			*actAlignRight,
			*actAlignCenter,
			*actAlignJustify,
            *actDirectionRtl,
            *actDirectionLtr,
			*actTextColor,
            *actTextFont,
			*actListNumber,
            *actListBullet,
            *actTabIndentMore,
            *actTabIndentLess,
            *actInsertLatex,
            *actInsertImage,
            *actClearFormat,
            *actListen;

    QHBoxLayout *toolBar;

    QString rsrcPath;

    QtSpeech *speech;

    QString deckPath;

    QTextCharFormat charFormat;
    QTextBlockFormat blockFormat;
};

#endif // __DANAEDITOR_H
