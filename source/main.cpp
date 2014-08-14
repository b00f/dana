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

#include "mainwindow.h"
#include "constants.h"

#include <QApplication>
#include <QtSingleApplication>

int main(int argc, char *argv[])
{
    QtSingleApplication a(argc, argv);

    QString plugins = appPath();
#ifdef Q_OS_MAC
    plugins += "/../Resources/";
#else
    QString plugins = appPath();
    plugins += "/plugins";
#endif
    a.addLibraryPath(plugins);

	if (a.isRunning()) {
		a.sendMessage("SHOW");
        return 0;
	}

    MainWindow w;
    w.show();

    a.setActivationWindow(&w);
    a.setQuitOnLastWindowClosed(false);

	a.connect(&a, SIGNAL(messageReceived(const QString &)),
			   &w, SLOT  (onMessageReceiveFromOtherInst(const QString &)));

///    QApplication a(argc, argv);
///    MainWindow w;
///    w.show();

    return a.exec();
}
