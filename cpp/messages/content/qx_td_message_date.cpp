#include "qx_td_message_date.h"
#include "utils/qx_td_translate_tools.h"

QxTdMessageDate::QxTdMessageDate(QObject *parent)
    : QxTdMessageContent(parent)
    , m_date(0)
{
    setType(MESSAGE_DATE);
}

QDateTime QxTdMessageDate::date() const
{
    return QDateTime::fromSecsSinceEpoch(m_date);
}

QString QxTdMessageDate::dateString() const
{
    if (date().date() == QDate::currentDate()) {
        return qxTranslate("Today");
    } else if (date().date() == QDate::currentDate().addDays(-1)) {
        return qxTranslate("Yesterday");
    } else if (date().date() > QDate::currentDate().addDays(-7)) {
        //TRANSLATORS: String in date separator label. For messages within a week: full weekday name
        return date().toString(qxTranslate("dddd"));
    } else if (date().date().year() < QDate::currentDate().year()) {
        //TRANSLATORS: String in date separator label. For messages of pas years: date number, month name and year
        return date().toString(qxTranslate("dd MMMM yyyy"));
    } else {
        //TRANSLATORS: String in date separator label. For messages older that a week but within the current year: date number and month name
        return date().toString(qxTranslate("dd MMMM"));
    }
}

void QxTdMessageDate::setDate(const qint32 &date)
{
    if (date == m_date) {
        return;
    }
    m_date = date;
    emit dataChanged();
}
