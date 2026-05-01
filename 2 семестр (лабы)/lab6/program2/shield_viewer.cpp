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

    QStringList headers = {"Название", "Описание", "Коэф. защиты", "Тип защиты"};
    ui->tableValid->setColumnCount(4);
    ui->tableValid->setHorizontalHeaderLabels(headers);
    ui->tableValid->horizontalHeader()->setStretchLastSection(true);
    ui->tableValid->setEditTriggers(QAbstractItemView::NoEditTriggers);

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

// Функция проверки корректности коэффициента защиты
bool ShieldViewer::isDefenseFactorValid(const QString& str, bool& hasLeadingZero, bool& hasComma)
{
    hasLeadingZero = false;
    hasComma = false;

    if (str.isEmpty()) return false;

    // проверка на запятую вместо точки
    if (str.contains(',')) {
        hasComma = true;
        return false;
    }

    // проверка на ноль в начале
    if (str.length() > 1 && str.startsWith('0') && !str.startsWith("0.")) {
        hasLeadingZero = true;
        return false;
    }

    bool ok;
    double value = str.toDouble(&ok);
    if (!ok) return false;

    if (value < 0 || value > 100) return false;

    return true;
}

void sortShieldsByDescendingName(QVector<ShieldData>& shields)
{
    std::sort(shields.begin(), shields.end(),
              [](const ShieldData& a, const ShieldData& b) {
                  return a.name.toLower() > b.name.toLower();  // > для убывания
              });
}

void ShieldViewer::updateTables()
{
    QVector<ShieldData> validShields;
    for (const ShieldData& shield : m_shields) {
        if (shield.isValid) {
            validShields.append(shield);
        }
    }
    sortShieldsByDescendingName(validShields);

    ui->tableValid->setRowCount(0);
    for (int i = 0; i < validShields.size(); ++i) {
        const ShieldData& shield = validShields[i];
        ui->tableValid->insertRow(i);
        ui->tableValid->setItem(i, 0, new QTableWidgetItem(shield.name));
        ui->tableValid->setItem(i, 1, new QTableWidgetItem(shield.description));

        if (shield.defenseFactor.isDouble()) {
            ui->tableValid->setItem(i, 2, new QTableWidgetItem(QString::number(shield.defenseFactor.toDouble())));
        } else {
            ui->tableValid->setItem(i, 2, new QTableWidgetItem(shield.defenseFactor.toString()));
        }

        ui->tableValid->setItem(i, 3, new QTableWidgetItem(shield.protectionType));
    }

    QVector<ShieldData> invalidShields;
    for (const ShieldData& shield : m_shields) {
        if (!shield.isValid) {
            invalidShields.append(shield);
        }
    }
    sortShieldsByDescendingName(invalidShields);

    ui->tableInvalid->setRowCount(0);
    for (int i = 0; i < invalidShields.size(); ++i) {
        const ShieldData& shield = invalidShields[i];
        ui->tableInvalid->insertRow(i);

        QTableWidgetItem* nameItem = new QTableWidgetItem(shield.name);
        QTableWidgetItem* descItem = new QTableWidgetItem(shield.description);
        QTableWidgetItem* defenseItem = new QTableWidgetItem();
        QTableWidgetItem* typeItem = new QTableWidgetItem(shield.protectionType);

        if (shield.defenseFactor.isDouble()) {
            defenseItem->setText(QString::number(shield.defenseFactor.toDouble()));
        } else {
            defenseItem->setText(shield.defenseFactor.toString());
        }

        if (shield.name.trimmed().isEmpty()) {
            nameItem->setBackground(Qt::red);
            nameItem->setForeground(Qt::white);
        }

        if (shield.description.trimmed().isEmpty()) {
            descItem->setBackground(Qt::red);
            descItem->setForeground(Qt::white);
        }

        bool isNumber = shield.defenseFactor.isDouble();
        QString defenseStr;
        if (isNumber) {
            defenseStr = QString::number(shield.defenseFactor.toDouble());
        } else {
            defenseStr = shield.defenseFactor.toString();
        }

        bool hasLeadingZero = false;
        bool hasComma = false;
        bool defenseValid = isDefenseFactorValid(defenseStr, hasLeadingZero, hasComma);

        if (!defenseValid || !isNumber) {
            defenseItem->setBackground(Qt::red);
            defenseItem->setForeground(Qt::white);
        }

        if (hasLeadingZero) {
            defenseItem->setToolTip("Ведущий ноль (например, 099)");
        }
        if (hasComma) {
            defenseItem->setToolTip("Использована запятая вместо точки (например, 2,4)");
        }

        QString type = shield.protectionType.trimmed().toLower();
        if (type != "physical" && type != "magic" && type != "general") {
            typeItem->setBackground(Qt::red);
            typeItem->setForeground(Qt::white);
        }

        ui->tableInvalid->setItem(i, 0, nameItem);
        ui->tableInvalid->setItem(i, 1, descItem);
        ui->tableInvalid->setItem(i, 2, defenseItem);
        ui->tableInvalid->setItem(i, 3, typeItem);
    }
}

void ShieldViewer::saveSeparateFiles()
{
    // сохраняем корректные щиты
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

    // сохраняем битые щиты
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

        bool hasLeadingZero = false;
        bool hasComma = false;

        QString defenseStr;
        if (shield.defenseFactor.isDouble()) {
            defenseStr = QString::number(shield.defenseFactor.toDouble());
        }
        else {
            defenseStr = shield.defenseFactor.toString();
        }

        bool defenseValid = isDefenseFactorValid(defenseStr, hasLeadingZero, hasComma);

        if (!defenseValid) {
            shield.isValid = false;
        }

        QString type = shield.protectionType.trimmed().toLower();
        if (type != "physical" && type != "magic" && type != "general") {
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
