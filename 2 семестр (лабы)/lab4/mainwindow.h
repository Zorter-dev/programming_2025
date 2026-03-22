#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QRegularExpressionValidator>
#include "ResultData.h"
#include "ui_MainWindow.h"

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void on_pushButton_save_clicked();
    void on_pushButton_reset_clicked();

private:
    Ui::MainWindow *ui;

    QRegularExpressionValidator* m_validatorField1;
    QRegularExpressionValidator* m_validatorField2;
    QRegularExpressionValidator* m_validatorField3;
    QRegularExpressionValidator* m_validatorField4;

    bool validateField1(const QString& text);
    bool validateField2(const QString& text);
    bool validateField3(const QString& text);
    bool validateField4(const QString& text);

    void showError(const QString& fieldName);
    void clearErrorStyles();

    QString getSelectedGenres() const;
};

#endif // MAINWINDOW_H
