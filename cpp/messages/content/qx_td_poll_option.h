#ifndef QX_TD_POLL_OPTION_H
#define QX_TD_POLL_OPTION_H

#include <QPointer>
#include "common/qx_abstract_int64_id.h"

class QxTdPollOption : public QxTdObject
{
    Q_OBJECT
    Q_PROPERTY(QString text READ text NOTIFY dataChanged)
    Q_PROPERTY(qint32 votes READ votes NOTIFY dataChanged)
    Q_PROPERTY(qint32 percentage READ percentage NOTIFY dataChanged)
    Q_PROPERTY(bool isChosen READ isChosen NOTIFY dataChanged)
    Q_PROPERTY(bool isBeingChosen READ isBeingChosen WRITE setIsBeingChosen NOTIFY dataChanged)
    Q_PROPERTY(int optionIndex READ optionIndex NOTIFY dataChanged)


public:
    explicit QxTdPollOption(QObject *parent = nullptr);

    QString text();
    qint32 votes();
    qint32 percentage();
    bool isChosen();
    bool isBeingChosen();
    void setIsBeingChosen(bool value);
    int optionIndex() const;
    void setOptionIndex(int value);
    void unmarshalJson(const QJsonObject &json);

signals:
    void dataChanged();
    
private:
    Q_DISABLE_COPY(QxTdPollOption)
    QString m_text;
    qint32 m_votes;
    qint32 m_percentage;
    bool m_isChosen;
    bool m_isBeingChosen;
    int m_optionIndex;
};

#endif // QX_TD_POLL_OPTION_H
