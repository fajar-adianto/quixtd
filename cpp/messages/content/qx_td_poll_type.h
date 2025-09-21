#ifndef QX_TD_POLL_TYPE_H
#define QX_TD_POLL_TYPE_H

#include "qx_td_formatted_text.h"

class QxTdPollType : public QxTdObject
{
    Q_OBJECT
    Q_PROPERTY(qint32 correctOption READ correctOption NOTIFY dataChanged)
    Q_PROPERTY(QxTdFormattedText *explanation READ explanation NOTIFY dataChanged)
    Q_PROPERTY(bool allowMultipleAnswers READ allowMultipleAnswers NOTIFY dataChanged)
    QML_ELEMENT
public:
    explicit QxTdPollType(QObject *parent = nullptr);

    virtual qint32 correctOption() const;
    virtual QxTdFormattedText *explanation() const;
    virtual bool allowMultipleAnswers() const;

signals:
    void dataChanged();

private:
    Q_DISABLE_COPY(QxTdPollType)
};

class QxTdPollTypeQuiz : public QxTdPollType
{
    Q_OBJECT

public:
    explicit QxTdPollTypeQuiz(QObject *parent = nullptr);

    qint32 correctOption() const;
    QxTdFormattedText *explanation() const;

    void unmarshalJson(const QJsonObject &json);

private:
    Q_DISABLE_COPY(QxTdPollTypeQuiz)

    qint32 m_correctOption;
    QScopedPointer<QxTdFormattedText> m_explanation;
};

class QxTdPollTypeRegular : public QxTdPollType
{
    Q_OBJECT

public:
    explicit QxTdPollTypeRegular(QObject *parent = nullptr);

    bool allowMultipleAnswers() const;

    void unmarshalJson(const QJsonObject &json);

private:
    Q_DISABLE_COPY(QxTdPollTypeRegular)

    bool m_allowMultipleAnswers;
};

struct QxTdPollTypeFactory
{
    static QxTdPollType *create(const QJsonObject &json, QObject *parent = nullptr);
};

#endif // QX_TD_POLL_TYPE_H
