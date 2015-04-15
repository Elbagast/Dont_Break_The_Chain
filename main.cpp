#include "chain/main_window.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication application(argc, argv);
    Chain::Main_Window window;
    window.show();

    return application.exec();
}
