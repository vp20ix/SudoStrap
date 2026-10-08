#include <QApplication>
#include <QCoreApplication>
#include <QFile>
#include <QTextStream>
#include "ui/mainwindow.h"

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);

    QCoreApplication::setApplicationName("SudoStrap");
    QCoreApplication::setApplicationVersion("0.1.0");
    QCoreApplication::setOrganizationName("SudoStrap");

    QString stylePath = QString::fromUtf8(qgetenv("HOME")) + "/.local/share/sudostrap/style.qss";
    QFile styleFile(stylePath);
    if (styleFile.open(QFile::ReadOnly | QFile::Text)) {
        QTextStream stream(&styleFile);
        app.setStyleSheet(stream.readAll());
        styleFile.close();
    }

    MainWindow window;
    window.show();

    return app.exec();
}