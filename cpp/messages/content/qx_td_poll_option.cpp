#include "qx_td_poll_option.h"

QxTdPollOption::QxTdPollOption(QObject *parent)
    : QxTdObject(parent)
    , m_text("")
    , m_votes(0)
    , m_percentage(0)
    , m_isChosen(false)
    , m_isBeingChosen(false)

{
    setType(POLL_OPTION);
}

QString QxTdPollOption::text() {
    return m_text;
}

qint32 QxTdPollOption::votes() {
    return m_votes;
}

qint32 QxTdPollOption::percentage() {
    return m_percentage;
}

bool QxTdPollOption::isChosen() {
    return m_isChosen;
}

bool QxTdPollOption::isBeingChosen() {
    return m_isBeingChosen;
}

void QxTdPollOption::setIsBeingChosen(bool value) {
    m_isBeingChosen = value;
    emit dataChanged();
}

int QxTdPollOption::optionIndex() const {
    return m_optionIndex;
}

void QxTdPollOption::setOptionIndex(int value) {
    m_optionIndex = value;
}

void QxTdPollOption::unmarshalJson(const QJsonObject &json)
{
    m_text = json["text"].toString();
    m_votes = qint32(json["voter_count"].toInt());
    m_percentage = qint32(json["vote_percentage"].toInt());
    m_isChosen = json["is_chosen"].toBool();
    m_isBeingChosen = json["is_being_chosen"].toBool();

    emit dataChanged();
}

