#include "qx_td_poll.h"

QxTdPoll::QxTdPoll(QObject *parent)
    : QxTdObject(parent)
    , m_id(0)
    , m_question("")
    , m_options(new QxTdObjectListModel<QxTdPollOption>)
    , m_totalVoters(0)
    , m_isAnonymous(false)
    , m_pollType(nullptr)
    , m_openPeriod(0)
    , m_closeDate(0)
    , m_isClosed(false)
{
    setType(POLL);
}

QString QxTdPoll::question() const {
    return m_question;
}

QxTdObjectListModel<QxTdPollOption> *QxTdPoll::options() const {
    return m_options.get();
}

bool QxTdPoll::userHasChosen() const {
    for( auto i = 0; i < m_options.get()->count(); i++ ) {
        auto option = static_cast<QxTdPollOption *>(m_options.get()->get(i));
        if (option->isChosen())
            return true;
    }
    return false;
}

qint32 QxTdPoll::totalVoters() const {
    return m_totalVoters;
}

qint32 QxTdPoll::openPeriod() const {
    return m_openPeriod;
}

bool QxTdPoll::isAnonymous() const {
    return m_isAnonymous;
}

bool QxTdPoll::isClosed() const {
    return m_isClosed;
}

bool QxTdPoll::isQuiz() const {
    return (m_pollType.get() != nullptr) && m_pollType.get()->correctOption() != -1;
}

qint32 QxTdPoll::quizCorrectChoice() const {
    if (m_pollType.get() == nullptr) {
        return -1;
    }
    return m_pollType.get()->correctOption();
}

QxTdFormattedText *QxTdPoll::quizExplanation() const {
    return m_pollType.get()->explanation();
}

bool QxTdPoll::isMultiChoice() const {
    return m_pollType.get() != nullptr && m_pollType.get()->allowMultipleAnswers();
}

void QxTdPoll::unmarshalJson(const QJsonObject &json)
{
    m_id = json["id"].toInt();
    m_question = json["question"].toString();
    const QJsonArray options = json["options"].toArray();
    int i = 0;
    m_options->clear();
    for (const QJsonValue &option : options) {
        auto *s = new QxTdPollOption();
        s->unmarshalJson(option.toObject());
        s->setOptionIndex(i++);
        m_options->append(s);
    }
    m_totalVoters = json["total_voter_count"].toInt();
    m_isAnonymous = json["is_anonymous"].toBool();
    m_pollType.reset(QxTdPollTypeFactory::create(json["type"].toObject(), this));
    m_openPeriod = json["open_period"].toInt();
    m_closeDate = json["close_date"].toInt();
    m_isClosed = json["is_closed"].toBool();

    emit dataChanged();
}
