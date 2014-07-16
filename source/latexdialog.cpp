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

#include "latexdialog.h"
#include "qxfiledialog.h"
#include "qxmessagebox.h"
#include "clickablelabel.h"
#include "constants.h"

LatexDialog::LatexDialog(QWidget *parent)
    : QxDialog("latex_dialog", parent)
{    
    setWindowTitle(tr("Convert Latex to HTML"));

    setupView();
}

void LatexDialog::setupView()
{
    latex = new QTextEdit();

    latex->setAcceptRichText(false);

    QVBoxLayout *mainLayout =  new QVBoxLayout(this);
    QVBoxLayout *latexLayout = new QVBoxLayout;
    QHBoxLayout *latexTitle = new QHBoxLayout;
    QHBoxLayout *footerLayout = new QHBoxLayout;

    QPushButton *btnCancel = new QPushButton(QIcon(":/images/exit.png"), tr(""));
    QPushButton *btnInsert = new QPushButton(tr("&Insert"));
    QLabel *lblPowered = new QLabel(tr("Powered by <a href='http://hutchinson.belmont.ma.us/tth/'>T<sub><span style='{font-size:small;}'>T</span></sub>H</a>, version 4.03"));

    lblPowered->setOpenExternalLinks(true);

    connect(btnCancel, SIGNAL(clicked()), this, SLOT(reject()));
    connect(btnInsert, SIGNAL(clicked()), this, SLOT(tex2html()));

    btnInsert->setDefault(true);

    QLabel *label1 = new QLabel(tr("Input Latex Here:"));
    ClickableLabel *label2 = new ClickableLabel(tr("<a href='#'>from file</a>"), this);

    connect(label2, SIGNAL(clicked()), this, SLOT(openTexFile()));

    latexTitle->addWidget(label1);
    latexTitle->addWidget(label2);
    latexTitle->addStretch();

    latexLayout->addLayout(latexTitle);
    latexLayout->addWidget(latex);

    footerLayout->addWidget(lblPowered);
    footerLayout->addItem(hSpacer());
    footerLayout->addWidget(btnInsert);
    footerLayout->addWidget(btnCancel);

    mainLayout->addLayout(latexLayout);
    mainLayout->addWidget(hLine());
    mainLayout->addLayout(footerLayout);
}

void LatexDialog::tex2html()
{
    QString latexPath = QString("%1/latex.tex").arg(tempPath());
    QString htmlPath = QString("%1/latex.html").arg(tempPath());

    QByteArray ba;
    ba.append(latex->toPlainText());

    QFile latexFile(latexPath);
    latexFile.open(QIODevice::WriteOnly);
    latexFile.write(ba);
    latexFile.close();

    QString command = QString("%1/tth").arg(appPath());

    QStringList parameters;
    parameters << latexPath;
    parameters << "-r";

    QProcess process;
    process.setProcessChannelMode(QProcess::MergedChannels);
    process.start(command, parameters);

    if (!process.waitForFinished()) {
         QxMessageBox::critical(this, process.errorString());
         return;
    }

    qDebug() << "output:" << process.readAll();

    QString c; /// html file content

    QFile htmlFile(htmlPath);
    htmlFile.open(QIODevice::ReadOnly);
    c.append(htmlFile.readAll());
    htmlFile.close();

    html.clear();
    c.remove("<!---->");/// Because of a bug in Qt
    html.append(QString("<div class='latex'>%1</div>").arg(c));

    accept();
}

void LatexDialog::tex2png()
{
    QString png = QString("%1/latex.png").arg(tempPath());

    QString command = QString("tex2png");

    QStringList parameters;
    parameters << "-lq";
    parameters << latex->toPlainText();
    parameters << png;

    QProcess process;

    process.setProcessChannelMode(QProcess::MergedChannels);
    process.setWorkingDirectory(appPath());
    process.start(command, parameters);

    if (!process.waitForFinished()) {
        qDebug() << "output:" << process.readAll();
         QxMessageBox::critical(this, process.errorString());
         return;
    }

    qDebug() << "output:" << process.readAll();

    html.clear();
    html.append(QString("<img src='%1' >").arg(png));

    accept();
}


QString LatexDialog::getHtml()
{
    return html;
}

void LatexDialog::openTexFile()
{
    QString fileName = QxFileDialog(this).getOpenTexName();

    if (!fileName.isEmpty()) {
        QString c;
        QFile f(fileName);
        f.open(QIODevice::ReadOnly);
        c.append(f.readAll());
        f.close();

        latex->append(c);
    }
}
