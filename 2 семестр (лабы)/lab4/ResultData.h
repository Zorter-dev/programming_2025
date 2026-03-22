#ifndef RESULTDATA_H
#define RESULTDATA_H

#include <QString>
#include <QTextStream>

class ResultData
{
public:
    ResultData();
    ResultData(const QString& field1, const QString& field2, const QString& field3, const QString& field4, const QString& publicationType, bool isDetective, bool isFantasy, bool isRoman);

    void saveToFile(const QString& filename) const;

    // Геттеры
    QString getField1() const { return m_field1; }
    QString getField2() const { return m_field2; }
    QString getField3() const { return m_field3; }
    QString getField4() const { return m_field4; }
    QString getPublicationType() const { return m_publicationType; }
    bool isDetective() const { return m_isDetective; }
    bool isFantasy() const { return m_isFantasy; }
    bool isRoman() const { return m_isRoman; }

private:
    QString m_field1;
    QString m_field2;
    QString m_field3;
    QString m_field4;
    QString m_publicationType;
    bool m_isDetective;
    bool m_isFantasy;
    bool m_isRoman;
};

#endif // RESULTDATA_H
