#include <QApplication>
#include "shield_creator.h"

int main(int argc, char *argv[]) {
    QApplication a(argc, argv);
    ShieldCreator w;
    w.show();
    return a.exec();
}
