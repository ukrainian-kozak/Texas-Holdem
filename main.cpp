#include <QApplication>
#include <QLocale>
#include <QTranslator>

#include "menuwindow.h"
#include "pokertablewidget.h"
#include "cardwidget.h"


int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

#if 0
    QTranslator translator;
    const QStringList uiLanguages = QLocale::system().uiLanguages();
    for (const QString &locale : uiLanguages) {
        const QString baseName = "poker_desktop_" + QLocale(locale).name();
        if (translator.load(":/i18n/" + baseName)) {
            a.installTranslator(&translator);
            break;
        }
    }
#endif

#if 1
    gm::MenuWindow menu;

    menu.show();
#endif

#if 0
    gm::CardWidget wgt(":/4_of_clubs.png");
    wgt.show();
#endif

    return a.exec();

}
