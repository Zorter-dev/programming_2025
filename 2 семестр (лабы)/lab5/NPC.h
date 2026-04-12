#ifndef NPC_H
#define NPC_H

#include <QString>
#include "Armor.h"

class NPC
{
public:
    NPC();
    NPC(const QString& name, int health, const Armor& armor);
    virtual ~NPC();

    //Геттеры
    QString getName() const;
    int getHealth() const;
    Armor getArmor() const;

    //Сеттеры
    void setName(const QString& name);
    void setHealth(int health);
    void setArmor(const Armor& armor);

    //Виртуальная функция Craft (для полиморфизма)
    virtual QString craft() const = 0;
    //Виртуальный метод для получения типа
    virtual QString getType() const = 0;
    //получение информации для отображения в таблице
    virtual QStringList getTableRow() const = 0;
    //Получение детальной информации
    virtual QString getDetails() const = 0;
    //Цвет HP
    virtual QString getHealthColor() const;
    virtual QString getImagePath() const = 0;

protected:
    QString m_name;
    int m_health;
    Armor m_armor;
};
#endif // NPC_H
