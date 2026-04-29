#ifndef SHIELD_VIEWER_H
#define SHIELD_VIEWER_H

#include <QMainWindow>
#include <QVector>
#include <QJsonValue>

struct ShieldData {
    QString name;
    QString description;
    QJsonValue defenseFactor;
    QString protectionType;
    bool isValid;
    bool hasLeadingZero;
    bool hasComma;
};

QT_BEGIN_NAMESPACE
namespace Ui {class ShieldViewer;}
QT_END_NAMESPACE

class ShieldViewer : public QMainWindow {
    Q_OBJECT

public:
    explicit ShieldViewer(QWidget *parent = nullptr);
    ~ShieldViewer();

private slots:
    void loadJson();

private:
    void updateTables();
    void saveSeparateFiles();
    int validCount() const;
    int invalidCount() const;

    bool isDefenseFactorValid(const QString& str, bool& hasLeadingZero, bool& hasComma);

    Ui::ShieldViewer *ui;
    QVector<ShieldData> m_shields;
};

#endif // SHIELD_VIEWER_H
