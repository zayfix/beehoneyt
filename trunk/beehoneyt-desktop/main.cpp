#include "ihm.h"
#include <QApplication>
#include <QTranslator>
#include <QLocale>
#include <QLibraryInfo>

/**
 * @file    main.cpp
 * @brief   Programme principal de l'application desktop qui crée et affiche l'ihm principale
 * @author  ACKERMANN Théo
 * @version 0.2
 */

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    QString locale = QLocale::system().name().section('_', 0, 0);
    QTranslator translator;
    translator.load(QString("qt_") + locale, QLibraryInfo::location(QLibraryInfo::TranslationsPath));
    a.installTranslator(&translator);

    Ihm w;
    w.show();

    return a.exec();
}
