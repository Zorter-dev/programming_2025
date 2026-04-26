#include "shield_creator.h"
#include "ui_shield_creator.h"
#include <QFile>
#include <QTextStream>
#include <QJsonDocument>
#include <QJsonArray>
#include <QJsonObject>
#include <QMessageBox>
#include <QFileDialog>

ShieldCreator::ShieldCreator(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::ShieldCreator)
{
    ui->setupUi(this);
    connect(ui->btnLoadTxt, &QPushButton::clicked, this, &ShieldCreator::loadFromTxt);
    connect(ui->btnOk, &QPushButton::clicked, this, &ShieldCreator::saveToJson);
}

ShieldCreator::~ShieldCreator()
{
    delete ui;
}

void ShieldCreator::loadFromTxt()
{
    QString filename = QFileDialog::getOpenFileName(this, "Выберите TXT файл", "", "Текстовые файлы (*.txt)");
    if (filename.isEmpty()) return;

    QFile file(filename);
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text)) {
        QMessageBox::warning(this, "Ошибка", "Не удалось открыть файл");
        return;
    }

    QTextStream in(&file);
    int lineNumber = 0;
    int addedCount = 0;

    // загружаем существующий JSON файл или создаем новый
    QJsonArray shieldsArray;
    QFile jsonFile("shields.json");
    if (jsonFile.exists() && jsonFile.open(QIODevice::ReadOnly)) {
        QByteArray data = jsonFile.readAll();
        jsonFile.close();
        QJsonDocument doc = QJsonDocument::fromJson(data);
        if (doc.isArray()) {
            shieldsArray = doc.array();
        }
    }

    while (!in.atEnd()) {
        QString line = in.readLine();
        line = line.trimmed();
        if (line.isEmpty()) continue;

        lineNumber++;

        // название/описание/коэффициент/тип
        QStringList parts = line.split('/');

        QString name = parts.value(0).trimmed();
        QString description = parts.value(1).trimmed();
        QString defenseStr = parts.value(2).trimmed();
        QString type = parts.value(3).trimmed();

        // создаем объект щита
        QJsonObject shieldJson;
        shieldJson["name"] = name;
        shieldJson["description"] = description;
        shieldJson["protectionType"] = type;

        bool ok;
        defenseStr.toDouble(&ok);
        if (ok) {
            shieldJson["defenseFactor"] = defenseStr.toDouble();
        } else {
            shieldJson["defenseFactor"] = defenseStr;
        }

        shieldsArray.append(shieldJson);
        addedCount++;
    }

    file.close();

    // сохраняем в JSON файл
    if (jsonFile.open(QIODevice::WriteOnly)) {
        QJsonDocument doc(shieldsArray);
        jsonFile.write(doc.toJson());
        jsonFile.close();
        QMessageBox::information(this, "Успех", QString("Добавлено %1 щитов в shields.json").arg(addedCount));
    } else {
        QMessageBox::warning(this, "Ошибка", "Не удалось сохранить файл");
    }
}

void ShieldCreator::saveToJson()
{
    QString name = ui->editName->text().trimmed();
    QString description = ui->editDescription->text().trimmed();
    QString defenseStr = ui->editDefenseFactor->text().trimmed();
    QString type = ui->comboType->currentText();

    QJsonObject shieldJson;
    shieldJson["name"] = name;
    shieldJson["description"] = description;
    shieldJson["protectionType"] = type;

    bool ok;
    defenseStr.toDouble(&ok);
    if (ok) {
        shieldJson["defenseFactor"] = defenseStr.toDouble();
    } else {
        shieldJson["defenseFactor"] = defenseStr;
    }

    QJsonArray shieldsArray;
    QFile jsonFile("shields.json");
    if (jsonFile.exists() && jsonFile.open(QIODevice::ReadOnly)) {
        QByteArray data = jsonFile.readAll();
        jsonFile.close();
        QJsonDocument doc = QJsonDocument::fromJson(data);
        if (doc.isArray()) {
            shieldsArray = doc.array();
        }
    }

    shieldsArray.append(shieldJson);

    if (jsonFile.open(QIODevice::WriteOnly)) {
        QJsonDocument doc(shieldsArray);
        jsonFile.write(doc.toJson());
        jsonFile.close();
        QMessageBox::information(this, "Успех", "Щит успешно добавлен в shields.json");

        ui->editName->clear();
        ui->editDescription->clear();
        ui->editDefenseFactor->clear();
        ui->comboType->setCurrentIndex(0);
    } else {
        QMessageBox::warning(this, "Ошибка", "Не удалось сохранить файл");
    }
}
