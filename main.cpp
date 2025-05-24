#include <QApplication>
#include "MainWindow.h"

int main(int argc, char *argv[]) {
    QApplication a(argc, argv);
    MainWindow window;

    window.Initialization();
    window.show();
    window.Shutdown();

    return a.exec();
}
