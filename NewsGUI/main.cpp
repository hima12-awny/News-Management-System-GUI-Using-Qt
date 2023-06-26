
#include "loadandstore.h"

#include "loginpage.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);

    app.setWindowIcon(QIcon("K:\\C++\\GUI Qt\\NewsGUI\\newspaper-folded.png"));
    app.setApplicationDisplayName("ABC News");

    loadAndStoreFiles* tool = new loadAndStoreFiles();
    LoginPage log(tool);
    log.show();

    return app.exec();
}
