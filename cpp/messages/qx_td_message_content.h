#ifndef QX_TD_MESSAGE_CONTENT_H
#define QX_TD_MESSAGE_CONTENT_H

#include <QUrl>
#include "common/qx_td_object.h"

class QxTdMessageContent : public QxTdObject
{
    Q_OBJECT
    Q_DISABLE_COPY(QxTdMessageContent)
    Q_PROPERTY(QString infoText READ infoText NOTIFY dataChanged)
    Q_PROPERTY(QString typeText READ typeText NOTIFY dataChanged)
    Q_PROPERTY(bool isSecret READ isSecret NOTIFY dataChanged)
    Q_PROPERTY(QUrl infoImageUrl READ infoImageUrl NOTIFY dataChanged)
    QML_ELEMENT
    QML_UNCREATABLE("QxTdMessageContent cannot be created in QML.")
public:
    explicit QxTdMessageContent(QObject *parent = nullptr);
    // infoText and infoImageUrl are helper methods and not part of of TDLib::message_content
    // They are used for displaying limited information about a message when editing or replying.
    QString infoText() const;
    QString typeText() const;
    QUrl infoImageUrl() const;
    bool isSecret() const;
    void setInfoText(const QString &infoText);
    void setTypeText(const QString &typeText);
signals:
    void dataChanged();

protected:
    QString m_infoText;
    QString m_typeText;
    QUrl m_infoImageUrl;
    bool m_isSecret;

};

class QxTdMessageAction : public QxTdMessageContent
{
    Q_OBJECT
public:
    explicit QxTdMessageAction(QObject *parent = nullptr);

private:
    Q_DISABLE_COPY(QxTdMessageAction)
};

class QxTdMessageHidden : public QxTdMessageContent
{
    Q_OBJECT
    QML_ELEMENT
    QML_UNCREATABLE("QxTdMessageHidden cannot be created in QML.")
public:
    explicit QxTdMessageHidden(QObject *parent = nullptr);

private:
    Q_DISABLE_COPY(QxTdMessageHidden)
};
#endif // QX_TD_MESSAGE_CONTENT_H
