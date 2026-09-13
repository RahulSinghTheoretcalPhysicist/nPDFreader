#include <QApplication>
#include <QCoreApplication>
#include <QGuiApplication>

#include "ui/MainWindow.h"

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);

    QCoreApplication::setOrganizationName("RahulPDF");
    QCoreApplication::setApplicationName("PDFReader");
    QCoreApplication::setApplicationVersion(PDFREADER_VERSION);

    QGuiApplication::setDesktopFileName("PDFReader");

    MainWindow window;
    window.show();

    return app.exec();
}
