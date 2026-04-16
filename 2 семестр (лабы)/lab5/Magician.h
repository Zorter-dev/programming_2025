#ifndef MAGICIAN_H
#define MAGICIAN_H

#include "NPC.h"

class Magician : public NPC
{
public:
    Magician();
    Magician(const QString& name, const QString& element, int mana, int health, const Armor& armor);
    ~Magician();

    QString getElement() const;
    int getMana() const;
    void setElement(const QString& element);
    void setMana(int mana);
    void craft(QWidget* parent) const override;

    QString getType() const override;
    QStringList getTableRow() const override;
    QString getDetails() const override;
    QString getHealthColor() const override;
    QString getManaColor() const;
    QString getElementColor() const;
    QString getImagePath() const override;
    static void setUseDefaultImages(bool useDefault);

private:
    QString m_element;
    int m_mana;
    static bool s_useDefaultImages;
};

#endif // MAGICIAN_H
