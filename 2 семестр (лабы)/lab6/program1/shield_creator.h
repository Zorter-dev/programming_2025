#ifndef SHIELD_CREATOR_H
#define SHIELD_CREATOR_H

#include <QWidget>

QT_BEGIN_NAMESPACE
namespace Ui {class ShieldCreator;}
QT_END_NAMESPACE

class ShieldCreator : public QWidget {
    Q_OBJECT

public:
    explicit ShieldCreator(QWidget *parent = nullptr);
    ~ShieldCreator();

private slots:
    void loadFromTxt();
    void saveToJson();

private:
    Ui::ShieldCreator *ui;
};

#endif // SHIELD_CREATOR_H
