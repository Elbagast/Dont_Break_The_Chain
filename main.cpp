#include "chain/main_window.h"
#include <QApplication>
//#include <QDebug>

int main(int argc, char *argv[])
{
    QApplication application(argc, argv);

    // The file that will store all the chains
    QString chain_filepath{QCoreApplication::applicationDirPath()};
    chain_filepath.append("/chains.xml");

    Chain::Main_Window window(chain_filepath);
    window.show();

    return application.exec();
}
