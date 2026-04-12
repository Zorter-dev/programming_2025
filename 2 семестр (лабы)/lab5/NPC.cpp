#include "NPC.h"

NPC::NPC() : m_name("Unknown"), m_health(0), m_armor() {}

NPC::NPC(const QString& name, int health, const Armor& armor)
    : m_name(name), m_health(health), m_armor(armor) {}

NPC::~NPC() {}

QString NPC::getName() const { return m_name; }
int NPC::getHealth() const { return m_health; }
Armor NPC::getArmor() const { return m_armor; }

void NPC::setName(const QString& name) { m_name = name; }
void NPC::setHealth(int health) { m_health = health; }
void NPC::setArmor(const Armor& armor) { m_armor = armor; }

QString NPC::getHealthColor() const {
    return "black";  // по умолчанию черный
}
