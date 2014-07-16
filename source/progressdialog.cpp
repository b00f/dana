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

#include "progressdialog.h"
#include "constants.h"

ProgressDialog::ProgressDialog(QWidget *parent)
    : QxDialog("progress_dialog", parent)
{    
    setWindowTitle(STR_DIALOG_TITLE_PROGRESS);

    setupView();

    setModal(true);

    /// setWindowFlags( Qt::FramelessWindowHint | Qt::WindowSystemMenuHint );

    ///setStyleSheet("QDialog{background-color:#333333}");
}

void ProgressDialog::setupView()
{
    progressBar = new QProgressBar;
    cancelButton = new QPushButton;
    errorLabel = new QLabel;
    captionLabel = new QLabel;

    captionLabel->setStyleSheet("QLabel{font-weight:bold}");
    errorLabel->setStyleSheet("QLabel{color:red}");
    progressBar->setStyleSheet("QProgressBar { text-align:center} QProgressBar::chunk { width: 20px; margin: 0.5px;}");

    cancelButton->setText(STR_CANCEL_PROGRESS);

    connect(cancelButton, SIGNAL(clicked()), this, SLOT(onCancel()));

    QGridLayout *mainLayout = new QGridLayout(this);

    progressBar->setMinimum(0);
    progressBar->setMaximum(100);

    progressBar->setValue(0);

    mainLayout->addWidget(captionLabel,  0,0,1,2);
    mainLayout->addWidget(progressBar,   1,0,1,1);
    mainLayout->addWidget(cancelButton,  1,1,1,1);
    mainLayout->addWidget(errorLabel,    2,0,1,2);

    setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);

    setModal(true);
}

void ProgressDialog::setCaption(QString caption)
{
    captionLabel->setText(caption);
}

void ProgressDialog::setError(QString error)
{
    errorLabel->setText(QString("<font color='red'><b> *%1</b></font>").arg(error));
}

void ProgressDialog::onCancel()
{
    emit canceled();
    close();
}

bool ProgressDialog::isCanceled()
{
    return cancelButton->isEnabled();
}

void ProgressDialog::setProgress(short value)
{
    if(value > 100)
        value = 100;

    progressBar->setValue(value);
    progressBar->setTextVisible(true);
}

void ProgressDialog::showBusy()
{
    progressBar->setMaximum(0);
    progressBar->setMinimum(0);
    progressBar->setValue(0);
}

void ProgressDialog::updateProgress(qint64 finished, qint64 total)
{
    short percentage = GET_PERCENT(finished, total);
    setProgress(percentage);
}