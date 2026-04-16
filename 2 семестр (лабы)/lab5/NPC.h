#ifndef NPC_H
#define NPC_H

#include <QString>
#include <QStringList>
#include <QWidget>
#include "Armor.h"

class NPC
{
public:
    NPC();
    NPC(const QString& name, int health, const Armor& armor);
    virtual ~NPC();

    QString getName() const;
    int getHealth() const;
    Armor getArmor() const;

    void setName(const QString& name);
    void setHealth(int health);
    void setArmor(const Armor& armor);

    virtual void craft(QWidget* parent) const = 0;
    virtual QString getType() const = 0;
    virtual QStringList getTableRow() const = 0;
    virtual QString getDetails() const = 0;
    virtual QString getHealthColor() const;
    virtual QString getImagePath() const = 0;

protected:
    QString m_name;
    int m_health;
    Armor m_armor;
};

#endif // NPC_H
