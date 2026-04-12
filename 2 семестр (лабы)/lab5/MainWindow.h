#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QTableWidget>
#include <QPushButton>
#include <QVector>
#include <QComboBox>
#include <QFileDialog>
#include "NPC.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
private slots:
    void onLoadButtonClicked();
    void onLoadPresetClicked();
    void onTableItemDoubleClicked(int row, int column);

private:
    Ui::MainWindow *ui;
    QVector<NPC*> m_npcs;
    void setupUI();
    void loadFromFile(const QString& filename, bool useDefaultImages);
    void addNPCToTable(NPC* npc, int row);
    void clearTable();
    void clearNPCs();
};
#endif // MAINWINDOW_H
