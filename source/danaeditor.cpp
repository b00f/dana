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

#include "danaeditor.h"
#include "latexdialog.h"
#include "qxfiledialog.h"
#include "qxmessagebox.h"
#include "constants.h"


DanaEditor::DanaEditor(QWidget *parent)
    : QTextEdit(parent)
{
    speech = new QTextToSpeech(this);

    rsrcPath = ":/images/danaeditor/";

    setupActions();
    setupView();
    setupToolbar();

    connect(this, SIGNAL(currentCharFormatChanged(const QTextCharFormat &)),
            this, SLOT(currentCharFormatChanged(const QTextCharFormat &)));

    connect(this, SIGNAL(cursorPositionChanged()),
            this, SLOT(cursorPositionChanged()));

    //installEventFilter(this);
    setTabChangesFocus(true);

    setMinimumHeight(60);

    setViewportMargins(0, toolBar->sizeHint().height()+1, 0, 0);
    setContentsMargins(0, toolBar->sizeHint().height(), 0, 0);
}

DanaEditor::~DanaEditor()
{
}

void DanaEditor::setText(QString text)
{
    mergeFormatOnWordOrSelection(charFormat);
    setAlignment(blockFormat.alignment());
    currentCharFormatChanged(textCursor().blockCharFormat());

    if(!acceptRichText()) {
        text = utils::HTML2Plain(text);
    }

    QString align;
    Qt::Alignment a = blockFormat.alignment();

    if (a & Qt::AlignLeft) {
        align="left";
    } else if (a & Qt::AlignHCenter) {
        align="center";
    } else if (a & Qt::AlignRight) {
        align="right";
    } else if (a & Qt::AlignJustify) {
        align="justify";
    }

    QString fontFamily = charFormat.font().family();
    QString fontSize = QString::number(charFormat.font().pointSize());
    QString fontWeight = charFormat.font().bold()?"bold":"normal";
    QString fontStyle = charFormat.font().italic()?"italic":"normal";
    QString textColor = charFormat.foreground().color().name();
    QString textDecoration = charFormat.font().underline()?"underline":"none";

    QString html = QString("<html><bod><div style='text-align:%1 !important; font-family:%2; font-weight:%3; font-style:%4; font-size:%5pt; color:%6; text-decoration:%7; margin:0px; padding:0px'>%8</div></body></html>")
            .arg(align)
            .arg(fontFamily)
            .arg(fontWeight)
            .arg(fontStyle)
            .arg(fontSize)
            .arg(textColor)
            .arg(textDecoration)
            .arg(text);

    QTextEdit::setHtml(html);
}

QString DanaEditor::getText()
{
    QString text;
    if(acceptRichText()) {
        QString rich = QTextEdit::toHtml();

        /// slow
        /// return rich.remove(QRegExp("((?:.(?!<body[^>]*>))+.<body[^>]*>)|(</body*>.+)"));
        ///

        rich = rich.remove(0, rich.indexOf("<body")+1);
        rich = rich.remove(0, rich.indexOf(">")+1);
        rich = rich.left(rich.indexOf("</body"));

        text = rich;
    } else {
        text = QTextEdit::toPlainText();
    }

    return text;
}

void DanaEditor::setupView()
{
    toolBar = new QHBoxLayout(this);

    toolBar->setAlignment(Qt::AlignTop);
}

void DanaEditor::setupActions()
{
    actTextBold      = createAction("format-text-bold.png"     , tr("Bold")          , this, SLOT(textBold())       , Qt::CTRL + Qt::Key_B, true);
    actTextItalic    = createAction("format-text-italic.png"   , tr("Italic")        , this, SLOT(textItalic())     , Qt::CTRL + Qt::Key_I, true);
    actTextUnderline = createAction("format-text-underline.png", tr("Underline")     , this, SLOT(textUnderline())  , Qt::CTRL + Qt::Key_U, true);
    actTextColor     = createAction("format-text-color.png"    , tr("Text Color")    , this, SLOT(textColor())     );
    actTextFont      = createAction("format-font.png"          , tr("Text Font")     , this, SLOT(textFont())      );
    actListNumber    = createAction("format-list-ordered.png"  , tr("Numbered List") , this, SLOT(textListNumber()) , Qt::CTRL + Qt::Key_N, true);
    actListBullet    = createAction("format-list-unordered.png", tr("Bulleted List") , this, SLOT(textListBullet()) , Qt::CTRL + Qt::Key_M, true);
    actTabIndentMore = createAction("format-indent-more.png"   , tr("Indent More")   , this, SLOT(indentMore())    );
    actTabIndentLess = createAction("format-indent-less.png"   , tr("Indent Less")   , this, SLOT(indentLess())    );
    actInsertLatex   = createAction("latex.png"                , tr("Insert Latex")  , this, SLOT(insertLatex())   );
    actInsertImage   = createAction("picture.png"              , tr("Insert Image")  , this, SLOT(insertImage())    , Qt::CTRL + Qt::Key_O);
    actClearFormat   = createAction("format-clear.png"         , tr("Clear Format")  , this, SLOT(clearFormat())    , Qt::CTRL + Qt::Key_Delete);
    actListen        = createAction("listen.png"               , tr("Listen it!")    , this, SLOT(listen())         , Qt::CTRL + Qt::Key_D);
    actShowToolbar   = createAction("show-toolbar.png"         , tr("Show Toolbar")  , this, SLOT(showToolbar())   );

    QActionGroup *grpDir = new QActionGroup(this);
    connect(grpDir, SIGNAL(triggered(QAction*)), this, SLOT(textDirection(QAction*)));

    actDirectionRtl = createAction("format-text-direction-rtl.png", tr("Right To Left"), grpDir, 0, QKeySequence(), true);
    actDirectionLtr = createAction("format-text-direction-ltr.png", tr("Left To Right"), grpDir, 0, QKeySequence(), true);

    QActionGroup *grpAlign = new QActionGroup(this);
    connect(grpAlign, SIGNAL(triggered(QAction*)), this, SLOT(textAlign(QAction*)));

    // Make sure the alignLeft  is always left of the alignRight
    if (QApplication::isLeftToRight()) {
        actAlignLeft   = createAction("format-justify-left.png"  , tr("Left")  , grpAlign, 0, Qt::CTRL + Qt::Key_L, true);
        actAlignCenter = createAction("format-justify-center.png", tr("Center"), grpAlign, 0, Qt::CTRL + Qt::Key_E, true);
        actAlignRight  = createAction("format-justify-right.png" , tr("Right") , grpAlign, 0, Qt::CTRL + Qt::Key_R, true);
    } else {
        actAlignRight  = createAction("format-justify-right.png" , tr("Right") , grpAlign, 0, Qt::CTRL + Qt::Key_R, true);
        actAlignCenter = createAction("format-justify-center.png", tr("Center"), grpAlign, 0, Qt::CTRL + Qt::Key_E, true);
        actAlignLeft   = createAction("format-justify-left.png"  , tr("Left")  , grpAlign, 0, Qt::CTRL + Qt::Key_L, true);
    }
    actAlignJustify = createAction("format-justify-fill.png", tr("Justify"), grpAlign, 0, Qt::CTRL + Qt::Key_J, true);
}

QAction *DanaEditor::createAction(QString icon, QString text, QObject *parent, const char *slot, QKeySequence keySequence, bool checkable)
{
    if(!keySequence.isEmpty())
        text += " (" + keySequence.toString() + ")";

    QAction *a = new QAction(QIcon(rsrcPath + icon), text, parent);
    a->setShortcut(keySequence);
    a->setPriority(QAction::LowPriority);
    a->setShortcutContext(Qt::WidgetWithChildrenShortcut);
    a->setCheckable(checkable);

    if(slot)
        connect(a, SIGNAL(triggered(bool)), this, slot);

    addAction(a);

    return a;
}

void DanaEditor::setupToolbar()
{
    toolBar->setSpacing(1);
    toolBar->setMargin (0);

    addActionToToolbar(actShowToolbar	);
}

void DanaEditor::showToolbar()
{
    QLayoutItem *child;
    while ((child = toolBar->takeAt(0)) != 0) {
        delete child->widget();
        delete child;
    }

    addActionToToolbar(actTextBold		);
    addActionToToolbar(actTextItalic	);
    addActionToToolbar(actTextUnderline);
    toolBar->addSpacing(4);
    addActionToToolbar(actAlignLeft	);
    addActionToToolbar(actAlignCenter	);
    addActionToToolbar(actAlignRight	);
    addActionToToolbar(actAlignJustify );
    toolBar->addSpacing(4);
    addActionToToolbar(actDirectionLtr	);
    addActionToToolbar(actDirectionRtl	);
    toolBar->addSpacing(4);
    addActionToToolbar(actTextColor	);
    addActionToToolbar(actTextFont 	);
    toolBar->addSpacing(4);
    addActionToToolbar(actTabIndentLess);
    addActionToToolbar(actTabIndentMore);
    toolBar->addSpacing(4);
    addActionToToolbar(actListNumber	);
    addActionToToolbar(actListBullet	);
    toolBar->addSpacing(4);
    addActionToToolbar(actInsertImage  );
    ///addActionToToolbar(actInsertLatex  );
    toolBar->addSpacing(4);
    addActionToToolbar(actClearFormat  );
    toolBar->addSpacing(4);
    addActionToToolbar(actListen       );
    toolBar->addStretch();
}

void DanaEditor::addLineToToolbar()
{
    QFrame *line = new QFrame;
    line->setFrameShape(QFrame::VLine);
    line->setFrameShadow(QFrame::Sunken);

    toolBar->addWidget(line);
}

void DanaEditor::addActionToToolbar(QAction *a)
{
    QToolButton *btn = new QToolButton(this);
    btn->setDefaultAction(a);
    btn->setFocusPolicy(Qt::NoFocus);
    btn->setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);
    btn->setIconSize(QSize(16,16));

    toolBar->addWidget(btn);    
}

void DanaEditor::textBold()
{
    QTextCharFormat fmt;
    fmt.setFontWeight(actTextBold->isChecked() ? QFont::Bold : QFont::Normal);
    mergeFormatOnWordOrSelection(fmt);
}

void DanaEditor::textUnderline()
{
    QTextCharFormat fmt;
    fmt.setFontUnderline(actTextUnderline->isChecked());
    mergeFormatOnWordOrSelection(fmt);
}

void DanaEditor::textItalic()
{
    QTextCharFormat fmt;
    fmt.setFontItalic(actTextItalic->isChecked());
    mergeFormatOnWordOrSelection(fmt);
}

void DanaEditor::textListNumber()
{
    textListStyle(QTextListFormat::ListDecimal);
}

void DanaEditor::textListBullet()
{

    textListStyle(QTextListFormat::ListDisc);
}

void DanaEditor::textListStyle(QTextListFormat::Style style)
{
    QTextCursor cursor = textCursor();

    cursor.beginEditBlock();

    QTextBlockFormat blockFmt = cursor.blockFormat();

    QTextListFormat listFmt;

    if (cursor.currentList()) {
        listFmt = cursor.currentList()->format();

        if(listFmt.style()==style) {
            cursor.currentList()->remove(cursor.block());
            cursor.endEditBlock();

            indentLess();
            listFormatChanged();
            return;
        }
    } else {
        listFmt.setIndent(blockFmt.indent() + 1);
        blockFmt.setIndent(0);
        cursor.setBlockFormat(blockFmt);
    }

    listFmt.setStyle(style);

    cursor.createList(listFmt);

    cursor.endEditBlock();

    listFormatChanged();
}

void DanaEditor::textColor()
{
    QColor col = QColorDialog::getColor(QTextEdit::textColor(), this);
    if (!col.isValid())
        return;
    QTextCharFormat fmt;
    fmt.setForeground(col);
    mergeFormatOnWordOrSelection(fmt);
    colorChanged(col);
}

void DanaEditor::textFont()
{
    QTextCursor cursor = textCursor();

    QFontDialog fontDlg(cursor.
                        charFormat().font());

    if(fontDlg.exec()==QFontDialog::Accepted) {

        QTextCharFormat fmt;
        fmt.setFont(fontDlg.selectedFont());
        mergeFormatOnWordOrSelection(fmt);
    }
}

void DanaEditor::textAlign(QAction *a)
{
    if (a == actAlignLeft)
        setAlignment(Qt::AlignLeft | Qt::AlignAbsolute);
    else if (a == actAlignCenter)
        setAlignment(Qt::AlignHCenter);
    else if (a == actAlignRight)
        setAlignment(Qt::AlignRight | Qt::AlignAbsolute);
    else if (a == actAlignJustify)
        setAlignment(Qt::AlignJustify);
}

void DanaEditor::currentCharFormatChanged(const QTextCharFormat &format)
{
    fontChanged(format.font());
    colorChanged(format.foreground().color());
}

void DanaEditor::cursorPositionChanged()
{
    alignmentChanged();
    listFormatChanged();
    directionChanged();
}

void DanaEditor::mergeFormatOnWordOrSelection(const QTextCharFormat &format)
{
    QTextCursor cursor = textCursor();
    if (!cursor.hasSelection())
        cursor.select(QTextCursor::WordUnderCursor);
    cursor.mergeCharFormat(format);
    mergeCurrentCharFormat(format);
}

void DanaEditor::fontChanged(const QFont &f)
{
    actTextBold->setChecked(f.bold());
    actTextItalic->setChecked(f.italic());
    actTextUnderline->setChecked(f.underline());
}

void DanaEditor::listFormatChanged()
{
    QTextCursor cursor = textCursor();
    QTextList *list = cursor.currentList();

    actListNumber->setChecked(false);
    actListBullet->setChecked(false);

    if(list) {
        QTextListFormat::Style f = list->format().style();

        switch(f) {
        case QTextListFormat::ListDecimal:
            actListNumber->setChecked(true);
            break;

        case QTextListFormat::ListDisc:
            actListBullet->setChecked(true);
            break;

        default:
            break;
        }
    }
}

void DanaEditor::colorChanged(const QColor &c)
{
    Q_UNUSED(c);
}

void DanaEditor::alignmentChanged()
{
    Qt::Alignment a = alignment();

    if (a & Qt::AlignLeft) {
        actAlignLeft->setChecked(true);
    } else if (a & Qt::AlignHCenter) {
        actAlignCenter->setChecked(true);
    } else if (a & Qt::AlignRight) {
        actAlignRight->setChecked(true);
    } else if (a & Qt::AlignJustify) {
        actAlignJustify->setChecked(true);
    }
}

void DanaEditor::indentMore()
{
    QTextCursor cursor = textCursor();

    cursor.beginEditBlock();

    QTextBlockFormat blockFmt = cursor.blockFormat();
    int indent = blockFmt.indent();
    indent++;
    blockFmt.setIndent(indent);
    cursor.setBlockFormat(blockFmt);

    cursor.endEditBlock();
}

void DanaEditor::indentLess()
{
    QTextCursor cursor = textCursor();

    cursor.beginEditBlock();

    QTextBlockFormat blockFmt = cursor.blockFormat();
    int indent = blockFmt.indent();
    if(--indent<0)
        indent =0;
    blockFmt.setIndent(indent);
    cursor.setBlockFormat(blockFmt);

    cursor.endEditBlock();
}

void DanaEditor::listen()
{
    speech->say(toPlainText());
}

bool DanaEditor::eventFilter(QObject *watched, QEvent *event)
{
    if(event->type() == QEvent::KeyPress) {

        QKeyEvent *keyEvent = static_cast<QKeyEvent *>(event);
        if (keyEvent->key() == Qt::Key_Tab) {
            focusNextChild();

            return true;
        } else if (keyEvent->key() == Qt::Key_Backtab) {
            focusPreviousChild();
            return false;
        }
    }

    return QTextEdit::eventFilter(watched, event);
}

void DanaEditor::insertLatex()
{
    LatexDialog dlg;

    if(dlg.exec()==QDialog::Accepted) {
        insertHtml(dlg.getHtml());
    }
}

void DanaEditor::insertImage()
{
    QString fileName = QxFileDialog(this).getOpenImageName();

    if (!fileName.isEmpty()) {
        QString mediaPath = utils::combinePaths(deckPath, "files");
        
        utils::createDirectory(mediaPath);

        QFileInfo fi(fileName);
        QString newFileName = utils::getUniqueFileName(mediaPath, fi.fileName());

        QFileInfo fi2(newFileName);
        QString relativeFileName = QString("./files/%1").arg(fi2.fileName());
        QString absoluteFileName = utils::combinePaths(deckPath, relativeFileName);

        utils::copyFile(absoluteFileName, fileName);

        QUrl Uri (relativeFileName);
        QImage image = QImageReader (absoluteFileName).read();

        QTextDocument *textDocument = document();
        textDocument->addResource(QTextDocument::ImageResource, Uri, QVariant (image));
        QTextCursor cursor = textCursor();
        QTextImageFormat imageFormat;
        imageFormat.setWidth(image.width());
        imageFormat.setHeight(image.height());
        imageFormat.setName(Uri.toString());
        cursor.insertImage(imageFormat);
    }
}

void DanaEditor::setDeckPath(QString path)
{
    deckPath = path;
}

QVariant DanaEditor::loadResource(int type, const QUrl &name)
{
    if(type == QTextDocument::ImageResource) {
        if(name.isRelative()) {

            QByteArray data;
            QString fileName = utils::combinePaths(deckPath, name.path());
            QFile f(fileName);
            if (f.open(QFile::ReadOnly)) {
                data = f.readAll();
                f.close();
                return data;
            } else {
                return QVariant();
            }
        }
    }

    return QTextEdit::loadResource(type, name);
}

void DanaEditor::setTextFormat(QTextCharFormat _charFormat, QTextBlockFormat _blockFormat)
{
    charFormat= _charFormat;
    blockFormat= _blockFormat;
}

void DanaEditor::getTextFormat(QTextCharFormat &charFormat, QTextBlockFormat &blockFormat)
{
    QTextCursor cursor = textCursor();
    charFormat = cursor.charFormat();
    blockFormat = cursor.blockFormat();
}

void DanaEditor::setReadOnly(bool ro)
{
    if(ro) {
        actListNumber->setVisible(false);
        actListBullet->setVisible(false);
        actTabIndentMore->setVisible(false);
        actTabIndentLess->setVisible(false);
        actInsertLatex->setVisible(false);
        actInsertImage->setVisible(false);
        actListen->setVisible(false);
    }

    QTextEdit::setReadOnly(ro);
}

void DanaEditor::textDirection(QAction *a)
{
    if(a == actDirectionLtr)
        setDirection(Qt::LeftToRight);
    else if(a == actDirectionRtl)
        setDirection(Qt::RightToLeft);

    directionChanged();
}

void DanaEditor::setDirection(Qt::LayoutDirection direction)
{
    QTextCursor cursor = textCursor();

    cursor.beginEditBlock();

    QTextBlockFormat blockFmt = cursor.blockFormat();
    blockFmt.setLayoutDirection(direction);
    cursor.setBlockFormat(blockFmt);

    cursor.endEditBlock();

    directionChanged();
}

void DanaEditor::directionChanged()
{
    QTextCursor cursor = textCursor();

    QTextBlockFormat blockFmt = cursor.blockFormat();

    actDirectionLtr->setChecked(false);
    actDirectionRtl->setChecked(false);

    if(blockFmt.layoutDirection() == Qt::RightToLeft)
        actDirectionRtl->setChecked(true);
    else if(blockFmt.layoutDirection() == Qt::LeftToRight)
        actDirectionLtr->setChecked(true);
}

void DanaEditor::clearFormat()
{
    QString text = document()->toPlainText();
    text.replace("\n", "<br>");
    setText(text);
}

void DanaEditor::insertFromMimeData (const QMimeData *source)
{
    if(!acceptRichText()) {
        QTextEdit::insertPlainText( source->text() );
    }
    else {
        if(source->hasHtml())
            QTextEdit::insertHtml( source->html() );
        else
            QTextEdit::insertPlainText( source->text() );
    }
}

void DanaEditor::setAcceptRichText(bool accept)
{
    if(!accept) {
        removeAction(actTextBold);
        removeAction(actTextItalic);
        removeAction(actTextUnderline);
        removeAction(actTextBold);
        removeAction(actListNumber);
        removeAction(actListBullet);
        removeAction(actInsertImage);
        removeAction(actClearFormat);
        removeAction(actAlignLeft);   
        removeAction(actAlignCenter); 
        removeAction(actAlignRight);

        QLayoutItem *child;
        while ((child = toolBar->takeAt(0)) != 0) {
            
            delete child->widget();
            delete child;
        }

        setViewportMargins(0, 0, 0, 0);
        setContentsMargins(0, 0, 0, 0);
    }

    QTextEdit::setAcceptRichText(accept);
}
