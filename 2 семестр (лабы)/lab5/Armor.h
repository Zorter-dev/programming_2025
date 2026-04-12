#ifndef ARMOR_H
#define ARMOR_H

#include <QString>

struct Armor {
    int helmet;
    int chest;
    int boots;

    Armor() : helmet(0), chest(0), boots(0) {}
    Armor(int h, int c, int b) : helmet(h), chest(c), boots(b) {}

    QString toString() const {
        return QString("%1/%2/%3").arg(helmet).arg(chest).arg(boots);
    }
};
#endif // ARMOR_H
