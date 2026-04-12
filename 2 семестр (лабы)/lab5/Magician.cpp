#include "Magician.h"
#include <QRandomGenerator>
#include <QDir>
#include <QCoreApplication>
#include <QDebug>

// Инициализация флага
bool Magician::s_useDefaultImages = false;

void Magician::setUseDefaultImages(bool useDefault) {
    s_useDefaultImages = useDefault;
}

Magician::Magician() : NPC(), m_element("Unknown"), m_mana(0) {}

Magician::Magician(const QString& name, const QString& element, int mana, int health, const Armor& armor):
    NPC(name, health, armor), m_element(element), m_mana(mana) {}

Magician::~Magician() {}

QString Magician::getElement() const {return m_element;}
int Magician::getMana() const {return m_mana;}

void Magician::setElement(const QString& element) {m_element = element;}
void Magician::setMana(int mana) {m_mana = mana;}

QString Magician::craft() const {
    return QString("Маг %1 колдует заклинание стихии %2! (Мана: %3)")
        .arg(m_name, m_element, QString::number(m_mana));
}

QString Magician::getType() const {
    return "Маг";
}

QStringList Magician::getTableRow() const {
    return QStringList() << getType() << m_name << m_element
                         << QString::number(m_mana)
                         << QString::number(m_health)
                         << m_armor.toString();
}

QString Magician::getDetails() const {
    return QString("Тип: Маг\n"
                   "Имя: %1\n"
                   "Стихия: %2\n"
                   "Мана: %3\n"
                   "Здоровье: %4\n"
                   "Броня (Шлем/Кираса/Сапоги): %5")
        .arg(m_name, m_element, QString::number(m_mana),
             QString::number(m_health), m_armor.toString());
}

QString Magician::getHealthColor() const {
    return "green";
}

QString Magician::getManaColor() const {
    return "blue";
}

QString Magician::getElementColor() const {
    QString elem = m_element.toLower();
    if (elem == "огонь") return "red";
    if (elem == "вода") return "blue";
    if (elem == "земля") return "brown";
    return "black";
}

QString Magician::getImagePath() const {
    if (s_useDefaultImages) {
        return QCoreApplication::applicationDirPath() + "/images/magician_default.png";
    }
    QDir dir(QCoreApplication::applicationDirPath() + "/images/mag_res");

    if (!dir.exists()) {
        return QCoreApplication::applicationDirPath() + "/images/magician_default.png";
    }

    QStringList filters;
    filters << "*.png" << "*.jpg" << "*.jpeg";
    QStringList files = dir.entryList(filters);

    if (files.isEmpty()) {
        return QCoreApplication::applicationDirPath() + "/images/magician_default.png";
    }

    int randomIndex = QRandomGenerator::global()->bounded(files.size());
    return QCoreApplication::applicationDirPath() + "/images/mag_res/" + files[randomIndex];
}
