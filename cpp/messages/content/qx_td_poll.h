#ifndef QX_TD_POLL_H
#define QX_TD_POLL_H

#include "qx_td_poll_option.h"
#include "qx_td_poll_type.h"

class QxTdPoll : public QxTdObject
{
    Q_OBJECT
    Q_PROPERTY(QString question READ question NOTIFY dataChanged)
    Q_PROPERTY(QObject *options READ options NOTIFY dataChanged)
    Q_PROPERTY(bool userHasChosen READ userHasChosen NOTIFY dataChanged)
    Q_PROPERTY(qint32 totalVoters READ totalVoters NOTIFY dataChanged)
    Q_PROPERTY(qint32 openPeriod READ openPeriod NOTIFY dataChanged)     
    Q_PROPERTY(bool isAnonymous READ isAnonymous NOTIFY dataChanged)
    Q_PROPERTY(bool isClosed READ isClosed NOTIFY dataChanged)
    Q_PROPERTY(bool isQuiz READ isQuiz NOTIFY dataChanged)
    Q_PROPERTY(qint32 quizCorrectChoice READ quizCorrectChoice NOTIFY dataChanged)    
    Q_PROPERTY(QxTdFormattedText *quizExplanation READ quizExplanation NOTIFY dataChanged)
    Q_PROPERTY(bool isMultiChoice READ isMultiChoice NOTIFY dataChanged)
    QML_ELEMENT
public:
    explicit QxTdPoll(QObject *parent = nullptr);

    QString question() const;
    QxTdObjectListModel<QxTdPollOption> *options() const;
    qint32 totalVoters() const;
    bool userHasChosen() const;
    qint32 openPeriod() const;
    bool isAnonymous() const;
    bool isClosed() const;
    bool isQuiz() const;
    qint32 quizCorrectChoice() const;
    QxTdFormattedText *quizExplanation() const;
    bool isMultiChoice() const;

    void unmarshalJson(const QJsonObject &json);

signals:
    void dataChanged();

private:
    Q_DISABLE_COPY(QxTdPoll)
    QxTdInt64 m_id;
    QString m_question;
    QScopedPointer<QxTdObjectListModel<QxTdPollOption>> m_options;
    qint32 m_totalVoters;
    //List recent voter Ids
    bool m_isAnonymous;
    QScopedPointer<QxTdPollType> m_pollType;
    qint32 m_openPeriod;
    qint32 m_closeDate;
    bool m_isClosed;
};

#endif // QX_TD_POLL_H
