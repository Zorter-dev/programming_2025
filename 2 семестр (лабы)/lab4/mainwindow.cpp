#include "MainWindow.h"
#include <QMessageBox>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    setWindowTitle("Вариант 2");

    // Создаем валидаторы
    QRegularExpression regex1("^[А-ЯЁ][а-яё]+\\s[А-ЯЁ]{1,2}$");
    m_validatorField1 = new QRegularExpressionValidator(regex1, this);
    ui->lineEdit_field1->setValidator(m_validatorField1);

    QRegularExpression regex2("^\".*\"$");
    m_validatorField2 = new QRegularExpressionValidator(regex2, this);
    ui->lineEdit_field2->setValidator(m_validatorField2);

    QRegularExpression regex3("^\\d{1,3}-\\d{5}$");
    m_validatorField3 = new QRegularExpressionValidator(regex3, this);
    ui->lineEdit_field3->setValidator(m_validatorField3);

    m_validatorField4 = nullptr;

    ui->radioButton_paper->setAutoExclusive(false);
    ui->radioButton_electronic->setAutoExclusive(false);
    ui->radioButton_paper->setChecked(false);
    ui->radioButton_electronic->setChecked(false);
    ui->radioButton_paper->setAutoExclusive(true);
    ui->radioButton_electronic->setAutoExclusive(true);
}

MainWindow::~MainWindow()
{
    delete ui;
    delete m_validatorField1;
    delete m_validatorField2;
    delete m_validatorField3;
    if (m_validatorField4) delete m_validatorField4;
}

bool MainWindow::validateField1(const QString& text) {
    QRegularExpression regex("^[А-ЯЁ][а-яё]+\\s[А-ЯЁ]{1,2}$");
    return regex.match(text).hasMatch();
}

bool MainWindow::validateField2(const QString& text) {
    QRegularExpression regex("^\".*\"$");
    return regex.match(text).hasMatch();
}

bool MainWindow::validateField3(const QString& text) {
    QRegularExpression regex("^\\d{1,3}-\\d{5}$");
    return regex.match(text).hasMatch();
}

bool MainWindow::validateField4(const QString& text) {
    QRegularExpression regex("^(\\d+)/(\\d+)$");
    QRegularExpressionMatch match = regex.match(text);
    if (match.hasMatch()) {
        int first = match.captured(1).toInt();
        int second = match.captured(2).toInt();
        return second < first;
    }
    return false;
}

void MainWindow::showError(const QString& fieldName) {
    QMessageBox::warning(this, "Ошибка ввода", "Поле \"" + fieldName + "\" заполнено неверно\n" "Проверьте формат ввода.");
}

void MainWindow::clearErrorStyles() {
    ui->lineEdit_field1->setStyleSheet("");
    ui->lineEdit_field2->setStyleSheet("");
    ui->lineEdit_field3->setStyleSheet("");
    ui->lineEdit_field4->setStyleSheet("");
}

QString MainWindow::getSelectedGenres() const {
    QStringList genres;
    if (ui->checkBox_detective->isChecked()) genres << "Детектив";
    if (ui->checkBox_fantasy->isChecked()) genres << "Фантастика";
    if (ui->checkBox_roman->isChecked()) genres << "Роман";
    return genres.join(", ");
}

void MainWindow::on_pushButton_save_clicked() {
    clearErrorStyles();

    QString field1 = ui->lineEdit_field1->text();
    QString field2 = ui->lineEdit_field2->text();
    QString field3 = ui->lineEdit_field3->text();
    QString field4 = ui->lineEdit_field4->text();

    QString publicationType = ui->radioButton_paper->isChecked() ? "Бумажное" : "Электронное";

    bool isDetective = ui->checkBox_detective->isChecked();
    bool isFantasy = ui->checkBox_fantasy->isChecked();
    bool isRoman = ui->checkBox_roman->isChecked();

    bool valid = true;

    if (!validateField1(field1)) {
        ui->lineEdit_field1->setStyleSheet("border: 2px solid red;");
        showError("Автор");
        valid = false;
    }

    if (!validateField2(field2)) {
        ui->lineEdit_field2->setStyleSheet("border: 2px solid red;");
        showError("Название");
        valid = false;
    }

    if (!validateField3(field3)) {
        ui->lineEdit_field3->setStyleSheet("border: 2px solid red;");
        showError("Код");
        valid = false;
    }

    if (!validateField4(field4)) {
        ui->lineEdit_field4->setStyleSheet("border: 2px solid red;");
        showError("Наполнение");
        valid = false;
    }

    if (valid) {
        ResultData data(field1, field2, field3, field4,
                        publicationType, isDetective, isFantasy, isRoman);
        data.saveToFile("result.txt");

        QMessageBox::information(this, "Успех", "Данные успешно сохранены в файл result.txt\n" "Тип издания: " + publicationType + "\n" "Жанры: " + getSelectedGenres());

        on_pushButton_reset_clicked();
    }
}

void MainWindow::on_pushButton_reset_clicked() {
    ui->lineEdit_field1->clear();
    ui->lineEdit_field2->clear();
    ui->lineEdit_field3->clear();
    ui->lineEdit_field4->clear();

    ui->radioButton_paper->setAutoExclusive(false);
    ui->radioButton_electronic->setAutoExclusive(false);
    ui->radioButton_paper->setChecked(false);
    ui->radioButton_electronic->setChecked(false);
    ui->radioButton_paper->setAutoExclusive(true);
    ui->radioButton_electronic->setAutoExclusive(true);

    ui->checkBox_detective->setChecked(false);
    ui->checkBox_fantasy->setChecked(false);
    ui->checkBox_roman->setChecked(false);

    clearErrorStyles();
}
