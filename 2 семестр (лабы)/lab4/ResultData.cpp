#include "ResultData.h"
#include <QFile>
#include <QTextStream>
#include <QDebug>

ResultData::ResultData()
    : m_field1(""), m_field2(""), m_field3(""), m_field4(""),
    m_publicationType(""), m_isDetective(false), m_isFantasy(false), m_isRoman(false)
{
}

ResultData::ResultData(const QString& field1, const QString& field2,
                       const QString& field3, const QString& field4,
                       const QString& publicationType,
                       bool isDetective, bool isFantasy, bool isRoman)
    : m_field1(field1), m_field2(field2), m_field3(field3), m_field4(field4),
    m_publicationType(publicationType),
    m_isDetective(isDetective), m_isFantasy(isFantasy), m_isRoman(isRoman)
    m_field1(field1), m_field2(field2), m_field3(field3), m_field4(field4), m_publicationType(publicationType), m_isDetective(isDetective), m_isFantasy(isFantasy), m_isRoman(isRoman)
{
}

void ResultData::saveToFile(const QString& filename) const
{
void ResultData::saveToFile(const QString& filename) const {
    QFile file(filename);
    if (!file.open(QIODevice::Append | QIODevice::Text)) {
        qDebug() << "Не удалось открыть файл для записи";
        return;
    }

    QTextStream out(&file);
    out << "=== НОВАЯ ЗАПИСЬ ===\n";
    out << "Поле 1 (рус, первая буква капсом + пробел + буква капсом): " << m_field1 << "\n";
    out << "Поле 2 (в кавычках \"...\"): " << m_field2 << "\n";
    out << "Поле 3 (формат 123-12345): " << m_field3 << "\n";
    out << "Поле 4 (формат 2/1, второе меньше первого): " << m_field4 << "\n";
    out << "Тип издания: " << m_publicationType << "\n";

    QString genres;
    if (m_isDetective) genres += "Детектив ";
    if (m_isFantasy) genres += "Фантастика ";
    if (m_isRoman) genres += "Роман ";
    if (genres.isEmpty()) genres = "Не выбрано";

    out << "Жанры: " << genres.trimmed() << "\n";
    out << "------------------------\n\n";

    file.close();
}
