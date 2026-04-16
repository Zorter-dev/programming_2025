#include "InfoDialog.h"
#include "ui_InfoDialog.h"
#include "Magician.h"
#include "Enemy.h"
#include <QPixmap>
#include <QFile>

InfoDialog::InfoDialog(const NPC* npc, QWidget *parent)
    : QDialog(parent), ui(new Ui::InfoDialog), m_npc(npc), m_printed(false)
{
    ui->setupUi(this);
    displayInfo();
    displayImage();

    connect(ui->printButton, &QPushButton::clicked, this, &InfoDialog::onPrintClicked);
    connect(ui->cancelButton, &QPushButton::clicked, this, &InfoDialog::onCancelClicked);
}

InfoDialog::~InfoDialog() {
    delete ui;
}

void InfoDialog::displayInfo() {
    if (!m_npc) return;

    QString details;
    if (const Magician* mag = dynamic_cast<const Magician*>(m_npc)) {
        details = QString("Тип: <b>Маг</b><br>"
                          "Имя: %1<br>"
                          "Стихия: <span style='color:%2;'>%3</span><br>"
                          "Мана: <span style='color:%4;'>%5</span><br>"
                          "Здоровье: <span style='color:%6;'>%7</span><br>"
                          "Броня (Шлем/Кираса/Сапоги): %8")
                      .arg(mag->getName())
                      .arg(mag->getElementColor())
                      .arg(mag->getElement())
                      .arg(mag->getManaColor())
                      .arg(mag->getMana())
                      .arg(mag->getHealthColor())
                      .arg(mag->getHealth())
                      .arg(mag->getArmor().toString());
    }
    else if (const Enemy* enemy = dynamic_cast<const Enemy*>(m_npc)) {
        details = QString("Тип: <b>Враг</b><br>"
                          "Имя: %1<br>"
                          "Редкость: <span style='color:%2;'>%3</span><br>"
                          "Урон: %4<br>"
                          "Здоровье: <span style='color:%5;'>%6</span><br>"
                          "Броня (Шлем/Кираса/Сапоги): %7")
                      .arg(enemy->getName())
                      .arg(enemy->getRarityColor())
                      .arg(enemy->getRarity())
                      .arg(enemy->getDamage())
                      .arg(enemy->getHealthColor())
                      .arg(enemy->getHealth())
                      .arg(enemy->getArmor().toString());
    }

    ui->infoLabel->setText(details);
}

void InfoDialog::displayImage() {
    QString imagePath = m_npc->getImagePath();
    QPixmap pixmap(imagePath);
    if (!pixmap.isNull()) {
        ui->imageLabel->setPixmap(pixmap.scaled(150, 150, Qt::KeepAspectRatio));
    } else {
        ui->imageLabel->setText("Нет изображения");
        ui->imageLabel->setAlignment(Qt::AlignCenter);
    }
}

void InfoDialog::onPrintClicked() {
    m_printed = true;
    accept();
}

void InfoDialog::onCancelClicked() {
    m_printed = false;
    accept();
}
