#include "qx_td_poll_type.h"

QxTdPollType::QxTdPollType(QObject *parent)
    : QxTdObject(parent)
{
    // Intentionally left empty.
}

qint32 QxTdPollType::correctOption() const {
    return -1;
}

QxTdFormattedText *QxTdPollType::explanation() const {
    return nullptr;
}

bool QxTdPollType::allowMultipleAnswers() const {
    return false;
}


QxTdPollTypeQuiz::QxTdPollTypeQuiz(QObject *parent)
    : QxTdPollType(parent)
    , m_correctOption(-1)
    , m_explanation(new QxTdFormattedText)
{
    setType(POLL_TYPE_QUIZ);
}

qint32 QxTdPollTypeQuiz::correctOption() const {
    return m_correctOption;
}


QxTdFormattedText *QxTdPollTypeQuiz::explanation() const {
    return m_explanation.get();
}

void QxTdPollTypeQuiz::unmarshalJson(const QJsonObject &json)
{
    m_correctOption = qint32(json["correct_option_id"].toInt());
    m_explanation->unmarshalJson((json["explanation"].toObject()));
}

QxTdPollTypeRegular::QxTdPollTypeRegular(QObject *parent)
    : QxTdPollType(parent)
    , m_allowMultipleAnswers(false)
{
    setType(POLL_TYPE_REGULAR);
}

bool QxTdPollTypeRegular::allowMultipleAnswers() const {
    return m_allowMultipleAnswers;
}

void QxTdPollTypeRegular::unmarshalJson(const QJsonObject &json)
{
    m_allowMultipleAnswers = json["allow_multiple_answers"].toBool();
}

QxTdPollType *QxTdPollTypeFactory::create(const QJsonObject &json, QObject *parent)
{
    const QString type = json["@type"].toString();
    // TODO: create a map of QMap<@type, QxTdObject::Type> so we can do fast lookups and
    // switch on the type. Otherwise this is/elseif is going to get huge supporting all content
    // types
    QxTdPollType *result;

    if (type == "pollTypeQuiz") {
        result = new QxTdPollTypeQuiz(parent);
    
    } else if (type == "pollTypeRegular") {
        result = new QxTdPollTypeRegular(parent);
    } else {
        qWarning() << "Received unknown poll type" << type << json;
        return new QxTdPollType(parent);
    }
    result->unmarshalJson(json);
    return result;
}
