#include "shield_viewer.h"
#include "ui_shield_viewer.h"
#include <QFile>
#include <QJsonDocument>
#include <QJsonArray>
#include <QJsonObject>
#include <QMessageBox>
#include <QFileDialog>
#include <QHeaderView>

ShieldViewer::ShieldViewer(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::ShieldViewer)
{
    ui->setupUi(this);

    // Настройка таблицы корректных щитов (4 колонки)
    QStringList headers = {"Название", "Описание", "Коэф. защиты", "Тип защиты"};
    ui->tableValid->setColumnCount(4);
    ui->tableValid->setHorizontalHeaderLabels(headers);
    ui->tableValid->horizontalHeader()->setStretchLastSection(true);
    ui->tableValid->setEditTriggers(QAbstractItemView::NoEditTriggers);

    // Настройка таблицы битых щитов (4 колонки)
    ui->tableInvalid->setColumnCount(4);
    ui->tableInvalid->setHorizontalHeaderLabels(headers);
    ui->tableInvalid->horizontalHeader()->setStretchLastSection(true);
    ui->tableInvalid->setEditTriggers(QAbstractItemView::NoEditTriggers);

    connect(ui->btnLoad, &QPushButton::clicked, this, &ShieldViewer::loadJson);
}

ShieldViewer::~ShieldViewer()
{
    delete ui;
}

void ShieldViewer::updateTables()
{
    // Корректные щиты
    ui->tableValid->setRowCount(0);
    int validRow = 0;
    for (const ShieldData& shield : m_shields) {
        if (shield.isValid) {
            ui->tableValid->insertRow(validRow);
            ui->tableValid->setItem(validRow, 0, new QTableWidgetItem(shield.name));
            ui->tableValid->setItem(validRow, 1, new QTableWidgetItem(shield.description));

            // Отображаем коэффициент защиты (для корректных всегда число)
            if (shield.defenseFactor.isDouble()) {
                ui->tableValid->setItem(validRow, 2, new QTableWidgetItem(QString::number(shield.defenseFactor.toDouble())));
            } else {
                ui->tableValid->setItem(validRow, 2, new QTableWidgetItem(shield.defenseFactor.toString()));
            }

            ui->tableValid->setItem(validRow, 3, new QTableWidgetItem(shield.protectionType));
            validRow++;
        }
    }

    // Битые щиты - подсвечиваем красным неверные поля (без указания ошибки)
    ui->tableInvalid->setRowCount(0);
    int invalidRow = 0;
    for (const ShieldData& shield : m_shields) {
        if (!shield.isValid) {
            ui->tableInvalid->insertRow(invalidRow);

            QTableWidgetItem* nameItem = new QTableWidgetItem(shield.name);
            QTableWidgetItem* descItem = new QTableWidgetItem(shield.description);
            QTableWidgetItem* defenseItem = new QTableWidgetItem();
            QTableWidgetItem* typeItem = new QTableWidgetItem(shield.protectionType);

            // Отображаем коэффициент защиты (как есть)
            if (shield.defenseFactor.isDouble()) {
                defenseItem->setText(QString::number(shield.defenseFactor.toDouble()));
            } else {
                defenseItem->setText(shield.defenseFactor.toString());
            }

            // ★★★ ТОЛЬКО ПОДСВЕТКА КРАСНЫМ, БЕЗ ТЕКСТА ОШИБКИ ★★★
            if (shield.name.trimmed().isEmpty()) {
                nameItem->setBackground(Qt::red);
                nameItem->setForeground(Qt::white);
            }

            if (shield.description.trimmed().isEmpty()) {
                descItem->setBackground(Qt::red);
                descItem->setForeground(Qt::white);
            }

            // Коэффициент защиты: если не число или вне диапазона
            bool isNumber = shield.defenseFactor.isDouble();
            double defenseVal = isNumber ? shield.defenseFactor.toDouble() : -1;

            if (!isNumber || defenseVal < 0 || defenseVal > 100) {
                defenseItem->setBackground(Qt::red);
                defenseItem->setForeground(Qt::white);
            }

            QString type = shield.protectionType.trimmed().toLower();
            if (type != "физический" && type != "магический" && type != "общий") {
                typeItem->setBackground(Qt::red);
                typeItem->setForeground(Qt::white);
            }

            ui->tableInvalid->setItem(invalidRow, 0, nameItem);
            ui->tableInvalid->setItem(invalidRow, 1, descItem);
            ui->tableInvalid->setItem(invalidRow, 2, defenseItem);
            ui->tableInvalid->setItem(invalidRow, 3, typeItem);
            invalidRow++;
        }
    }
}

void ShieldViewer::saveSeparateFiles()
{
    // Сохраняем корректные щиты
    QJsonArray validArray;
    for (const ShieldData& shield : m_shields) {
        if (shield.isValid) {
            QJsonObject obj;
            obj["name"] = shield.name;
            obj["description"] = shield.description;
            obj["defenseFactor"] = shield.defenseFactor;
            obj["protectionType"] = shield.protectionType;
            validArray.append(obj);
        }
    }

    QFile validFile("valid_shields.json");
    if (validFile.open(QIODevice::WriteOnly)) {
        QJsonDocument validDoc(validArray);
        validFile.write(validDoc.toJson());
        validFile.close();
    }

    // Сохраняем битые щиты
    QJsonArray invalidArray;
    for (const ShieldData& shield : m_shields) {
        if (!shield.isValid) {
            QJsonObject obj;
            obj["name"] = shield.name;
            obj["description"] = shield.description;
            obj["defenseFactor"] = shield.defenseFactor;
            obj["protectionType"] = shield.protectionType;
            invalidArray.append(obj);
        }
    }

    QFile invalidFile("invalid_shields.json");
    if (invalidFile.open(QIODevice::WriteOnly)) {
        QJsonDocument invalidDoc(invalidArray);
        invalidFile.write(invalidDoc.toJson());
        invalidFile.close();
    }
}

int ShieldViewer::validCount() const
{
    int count = 0;
    for (const ShieldData& shield : m_shields) {
        if (shield.isValid) count++;
    }
    return count;
}

int ShieldViewer::invalidCount() const
{
    return m_shields.size() - validCount();
}

void ShieldViewer::loadJson()
{
    QString filename = QFileDialog::getOpenFileName(this, "Выберите JSON файл", "", "JSON файлы (*.json)");
    if (filename.isEmpty()) return;

    QFile file(filename);
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text)) {
        QMessageBox::warning(this, "Ошибка", "Не удалось открыть файл");
        return;
    }

    QByteArray data = file.readAll();
    file.close();

    QJsonDocument doc = QJsonDocument::fromJson(data);
    if (doc.isNull() || !doc.isArray()) {
        QMessageBox::warning(this, "Ошибка", "Неверный формат JSON файла");
        return;
    }

    m_shields.clear();
    QJsonArray array = doc.array();

    for (int i = 0; i < array.size(); ++i) {
        QJsonObject obj = array[i].toObject();
        ShieldData shield;
        shield.name = obj["name"].toString();
        shield.description = obj["description"].toString();
        shield.defenseFactor = obj["defenseFactor"];
        shield.protectionType = obj["protectionType"].toString();

        shield.isValid = true;

        if (shield.name.trimmed().isEmpty()) {
            shield.isValid = false;
        }

        if (shield.description.trimmed().isEmpty()) {
            shield.isValid = false;
        }

        if (!shield.defenseFactor.isDouble()) {
            shield.isValid = false;
        }

        QString type = shield.protectionType.trimmed().toLower();
        if (type != "физический" && type != "магический" && type != "общий") {
            shield.isValid = false;
        }

        m_shields.append(shield);
    }

    updateTables();
    saveSeparateFiles();

    QMessageBox::information(this, "Успех", QString("Загружено %1 щитов. Корректных: %2, Битых: %3")
        .arg(m_shields.size())
        .arg(validCount())
        .arg(invalidCount()));
}
