
#include "loadandstore.h"

#include "loginpage.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    loadAndStoreFiles* tool = new loadAndStoreFiles();

    LoginPage log(tool, true);

    log.show();

    return a.exec();
}
