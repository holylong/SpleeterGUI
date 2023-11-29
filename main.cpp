#include "mainwindow.h"

#include <QApplication>
#include <QLocale>
#include <QTranslator>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    a.setWindowIcon(QIcon(":/res/icon.svg"));

    QTranslator translator;
    const QStringList uiLanguages = QLocale::system().uiLanguages();
    for (const QString &locale : uiLanguages) {
        if(!SpleeterConfig::Instance()->_i18n){
            qDebug() << "use origin lan";
            const QString baseName = "SpleeterGUI_" + QLocale(locale).name();
            if (translator.load(":/res/i18n/" + baseName)) {
                a.installTranslator(&translator);
                break;
            }
        }else{
            qDebug() << "now lan:" << SpleeterConfig::Instance()->_selectLang;
            const QString baseName = "SpleeterGUI_" + SpleeterConfig::Instance()->_selectLang;
            if (translator.load(":/res/i18n/" + baseName)) {
                a.installTranslator(&translator);
                break;
            }
        }
    }
    MainWindow w;
    w.show();
    return a.exec();
}
