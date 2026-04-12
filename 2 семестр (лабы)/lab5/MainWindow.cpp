#include "MainWindow.h"
#include "ui_MainWindow.h"
#include "Magician.h"
#include "Enemy.h"
#include "InfoDialog.h"
#include <QFile>
#include <QTextStream>
#include <QDebug>
#include <QMessageBox>
#include <QFileDialog>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    setupUI();
}

MainWindow::~MainWindow() {
    clearNPCs();
    delete ui;
}

void MainWindow::setupUI() {
    setWindowTitle("НПС - Наследование и полиморфизм");

    ui->tableWidget->setColumnCount(6);
    QStringList headers;
    headers << "Тип" << "Имя" << "Характеристика" << "Значение1" << "Здоровье" << "Броня (Ш/К/С)";
    ui->tableWidget->setHorizontalHeaderLabels(headers);
    ui->tableWidget->horizontalHeader()->setStretchLastSection(true);
    ui->tableWidget->setEditTriggers(QAbstractItemView::NoEditTriggers);
    ui->tableWidget->setSelectionBehavior(QAbstractItemView::SelectRows);

    connect(ui->pushButtonLoad, &QPushButton::clicked,
            this, &MainWindow::onLoadButtonClicked);
    connect(ui->pushButtonPreset, &QPushButton::clicked,
            this, &MainWindow::onLoadPresetClicked);
    connect(ui->tableWidget, &QTableWidget::cellDoubleClicked,
            this, &MainWindow::onTableItemDoubleClicked);
}

void MainWindow::clearTable() {
    ui->tableWidget->setRowCount(0);
}

void MainWindow::clearNPCs() {
    for (NPC* npc : m_npcs) {
        delete npc;
    }
    m_npcs.clear();
}

void MainWindow::addNPCToTable(NPC* npc, int row) {
    QStringList rowData = npc->getTableRow();
    for (int col = 0; col < rowData.size(); ++col) {
        QTableWidgetItem* item = new QTableWidgetItem(rowData[col]);
        ui->tableWidget->setItem(row, col, item);
    }
}

void MainWindow::loadFromFile(const QString& filename, bool useDefaultImages) {
    Magician::setUseDefaultImages(useDefaultImages);
    Enemy::setUseDefaultImages(useDefaultImages);

    QFile file(filename);
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text)) {
        QMessageBox::warning(this, "Ошибка",
                             "Не удалось открыть файл: " + filename);
        return;
    }

    clearTable();
    clearNPCs();

    QTextStream in(&file);
    int lineNum = 0;

    while (!in.atEnd()) {
        QString line = in.readLine();
        line = line.trimmed();
        if (line.isEmpty()) continue;

        QStringList parts = line.split(' ');
        if (parts.size() < 8) {
            qDebug() << "Ошибка в строке" << lineNum + 1
                     << ": недостаточно данных";
            continue;
        }

        int code = parts[0].toInt();
        QString typeOrElement = parts[1];
        QString name = parts[2];
        int value1 = parts[3].toInt();
        int health = parts[4].toInt();
        int armorHelmet = parts[5].toInt();
        int armorChest = parts[6].toInt();
        int armorBoots = parts[7].toInt();

        Armor armor(armorHelmet, armorChest, armorBoots);
        NPC* npc = nullptr;

        if (typeOrElement == "Обычный" || typeOrElement == "Редкий" ||
            typeOrElement == "Легенда" || typeOrElement == "Легендарный") {
            npc = new Enemy(name, typeOrElement, value1, health, armor);
        }
        else {
            npc = new Magician(name, typeOrElement, value1, health, armor);
        }

        if (npc) {
            m_npcs.append(npc);
            int row = ui->tableWidget->rowCount();
            ui->tableWidget->insertRow(row);
            addNPCToTable(npc, row);
        }

        lineNum++;
    }

    file.close();

    QMessageBox::information(this, "Загрузка", QString("Загружено %1 НПС из файла %2")
        .arg(m_npcs.size()).arg(filename));
}

void MainWindow::onLoadButtonClicked()
{
    QString filename = QFileDialog::getOpenFileName(this, "Выберите файл с данными", "", "Текстовые файлы (*.txt)");
    if (!filename.isEmpty()) {
        loadFromFile(filename, false);  // false = использовать случайные картинки из папок
    }
}

void MainWindow::onLoadPresetClicked() {
    loadFromFile("data.txt", true);  // true = использовать стандартные картинки
}

void MainWindow::onTableItemDoubleClicked(int row, int column) {
    Q_UNUSED(column);
    if (row < 0 || row >= m_npcs.size()) return;

    NPC* npc = m_npcs[row];
    InfoDialog dialog(npc, this);
    dialog.exec();

    if (dialog.isPrinted()) {
        delete npc;
        m_npcs.removeAt(row);
        ui->tableWidget->removeRow(row);
    }
}
