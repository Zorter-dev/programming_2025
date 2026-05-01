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

    // подключаем сигналы
    connect(ui->btnLoadTxt, &QPushButton::clicked, this, &ShieldCreator::loadFromTxt);
    connect(ui->btnOk, &QPushButton::clicked, this, &ShieldCreator::saveToJson);
}

ShieldCreator::~ShieldCreator()
{
    delete ui;
}

QString cleanDefenseString(const QString& input)
{
    if (input.isEmpty()) return input;

    QString cleaned = input;

    while (cleaned.length() > 1 && cleaned.startsWith('0') && !cleaned.startsWith("0.")) {
        cleaned.remove(0, 1);
    }

    return cleaned;
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
    QString line = in.readLine();
    file.close();

    if (line.isEmpty()) {
        QMessageBox::warning(this, "Ошибка", "Файл пуст");
        return;
    }

    QStringList parts = line.split('/');

    if (parts.size() < 4) {
        QMessageBox::warning(this, "Ошибка", "Неверный формат файла. Ожидается: название/описание/коэффициент/тип");
        return;
    }

    QString defenseStr = parts[2].trimmed();
    QString cleanedDefense = cleanDefenseString(defenseStr);

    // заполняем поля ввода из файла
    ui->editName->setText(parts[0].trimmed());
    ui->editDescription->setText(parts[1].trimmed());
    ui->editDefenseFactor->setText(cleanedDefense);

    QString type = parts[3].trimmed().toLower();
    int index = ui->comboType->findText(type);
    if (index != -1) {
        ui->comboType->setCurrentIndex(index);
    }
    else {
        ui->comboType->addItem(type);
        ui->comboType->setCurrentText(type);
    }

    QMessageBox::information(this, "Успех", "Данные из файла загружены в поля ввода");
}

void ShieldCreator::saveToJson()
{
    QString name = ui->editName->text().trimmed();
    QString description = ui->editDescription->text().trimmed();
    QString defenseStr = ui->editDefenseFactor->text().trimmed();
    QString type = ui->comboType->currentText().toLower();

    // если все поля пустые, показываем предупреждение
    if (name.isEmpty() && description.isEmpty() && defenseStr.isEmpty()) {
        QMessageBox::warning(this, "Ошибка", "Нет данных для сохранения. Заполните поля или загрузите файл.");
        return;
    }

    QString cleanedDefense = cleanDefenseString(defenseStr);

    // создаем объект щита
    QJsonObject shieldJson;
    shieldJson["name"] = name;
    shieldJson["description"] = description;
    shieldJson["protectionType"] = type;

    bool ok;
    double defenseValue = cleanedDefense.toDouble(&ok);
    if (ok && !cleanedDefense.isEmpty()) {
        shieldJson["defenseFactor"] = defenseValue;
    }
    else {
        shieldJson["defenseFactor"] = cleanedDefense;
    }

    QJsonArray shieldsArray;
    QFile jsonFile("shields.json");

    if (jsonFile.exists() && jsonFile.size() > 0) {
        if (jsonFile.open(QIODevice::ReadOnly)) {
            QByteArray data = jsonFile.readAll();
            jsonFile.close();
            QJsonDocument doc = QJsonDocument::fromJson(data);
            if (doc.isArray()) {
                shieldsArray = doc.array();
            }
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
    }
    else {
        QMessageBox::warning(this, "Ошибка", "Не удалось сохранить файл");
    }
}
