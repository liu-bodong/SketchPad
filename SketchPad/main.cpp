#include "MainWindow.h"
#include <qapplication.h>

int main(int argc, char* argv[])
{
    QApplication a(argc, argv);
    MainWindow* pMainWindow = MainWindow::GetInstance();
    pMainWindow->show();
    return QApplication::exec();
}
