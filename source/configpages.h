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

#ifndef __CONFIGPAGE_H
#define __CONFIGPAGE_H

#include "spinlabel.h"
#include "combolabel.h"

#include <QtWidgets>

class Preferences;
class ConfigPage
    : public QWidget
{
    Q_OBJECT

public:
    explicit ConfigPage(QWidget *parent = 0);

    virtual void save() = 0;

protected:
    QLabel *captionLabel;
    QVBoxLayout *mainLayout;
    QVBoxLayout *settingLayout;
    Preferences *preferences;
};


class ConfigGeneralPage
    : public ConfigPage
{
    Q_OBJECT

public:
    explicit ConfigGeneralPage(QWidget *parent = 0);
    void save();

private:
    bool isAutoStart();
    void setAutoStart(bool enabled);

protected:
    QCheckBox *autoStartCheck;
    QCheckBox *checkUpdateCheck;

};

class ConfigDeckPage
    : public ConfigPage
{
    Q_OBJECT

public:
    explicit ConfigDeckPage(QWidget *parent = 0);
    void save();

protected:
    SpinLabel *queryTimer;
    ComboLabel *shufflingCombo;
};

class ConfigNetwordPage 
    : public ConfigPage
{
    Q_OBJECT

public:
    explicit ConfigNetwordPage(QWidget *parent = 0);
    void save();

private slots:
    void onLogin();
    void onLogout();
    void setupAccountLayout();

private:
    QVBoxLayout *accountLayout;
};

#endif // __CONFIGPAGE_H