#ifndef ENEMY_H
#define ENEMY_H

#include "NPC.h"

class Enemy : public NPC
{
public:
    Enemy();
    Enemy(const QString& name, const QString& rarity, int damage, int health, const Armor& armor);
    ~Enemy();

    QString getRarity() const;
    int getDamage() const;
    void setRarity(const QString& rarity);
    void setDamage(int damage);
    QString craft() const override;
    QString getType() const override;
    QStringList getTableRow() const override;
    QString getDetails() const override;
    QString getHealthColor() const override;
    QString getRarityColor() const;
    QString getImagePath() const override;
    static void setUseDefaultImages(bool useDefault);

private:
    QString m_rarity;
    int m_damage;
    static bool s_useDefaultImages;
};
#endif // ENEMY_H
