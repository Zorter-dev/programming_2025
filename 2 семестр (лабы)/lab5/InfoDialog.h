#ifndef INFODIALOG_H
#define INFODIALOG_H

#include <QDialog>
#include "NPC.h"

QT_BEGIN_NAMESPACE
namespace Ui { class InfoDialog; }
QT_END_NAMESPACE

class InfoDialog : public QDialog
{
    Q_OBJECT

public:
    explicit InfoDialog(NPC* npc, QWidget *parent = nullptr);
    ~InfoDialog();
    bool isPrinted() const { return m_printed; }
private slots:
    void onPrintClicked();
    void onCancelClicked();
private:
    Ui::InfoDialog *ui;
    NPC* m_npc;
    bool m_printed;
    void displayInfo();
    void displayImage();
};
#endif // INFODIALOG_H
