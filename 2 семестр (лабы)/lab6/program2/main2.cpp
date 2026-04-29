#include <QApplication>
#include "shield_viewer.h"

int main(int argc, char *argv[]) {
    QApplication a(argc, argv);
    ShieldViewer w;
    w.show();
    return a.exec();
}
