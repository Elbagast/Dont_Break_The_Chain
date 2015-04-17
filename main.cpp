#include "chain/main_window.h"
#include <QApplication>
#include <QDebug>

int main(int argc, char *argv[])
{
    QApplication application(argc, argv);
    qDebug() << QCoreApplication::applicationDirPath();
    Chain::Main_Window window(QCoreApplication::applicationDirPath());
    window.show();

    return application.exec();
}
