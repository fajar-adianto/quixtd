#ifndef QX_TD_TEXT_ENTITY_TYPE_H
#define QX_TD_TEXT_ENTITY_TYPE_H

#include "common/qx_td_object.h"

class QxTdTextEntityType : public QxTdObject
{
    Q_OBJECT
    Q_PROPERTY(QString additionalInfo READ additionalInfo NOTIFY additionalInfoChanged)
    QML_ELEMENT
public:
    explicit QxTdTextEntityType(QObject *parent = nullptr);
    QString additionalInfo() const;

signals:
    void additionalInfoChanged();

protected:
    QString m_additionalInfo;
};

#define TEXT_ENTITY_CLASS(name, type)                         \
    class QxTdTextEntityType##name : public QxTdTextEntityType  \
    {                                                         \
        Q_OBJECT                                              \
        Q_DISABLE_COPY(QxTdTextEntityType##name)               \
    public:                                                   \
        explicit QxTdTextEntityType##name(QObject *parent = 0) \
            : QxTdTextEntityType(parent)                       \
        {                                                     \
            setType(type);                                    \
        };                                                    \
    };

TEXT_ENTITY_CLASS(Bold, QxTdObject::TEXT_ENTITY_TYPE_BOLD)
TEXT_ENTITY_CLASS(BotCommand, QxTdObject::TEXT_ENTITY_TYPE_BOT_COMMAND)
TEXT_ENTITY_CLASS(Code, QxTdObject::TEXT_ENTITY_TYPE_CODE)
TEXT_ENTITY_CLASS(EmailAddress, QxTdObject::TEXT_ENTITY_TYPE_EMAIL_ADDRESS)
TEXT_ENTITY_CLASS(Hashtag, QxTdObject::TEXT_ENTITY_TYPE_HASHTAG)
TEXT_ENTITY_CLASS(Italic, QxTdObject::TEXT_ENTITY_TYPE_ITALIC)
TEXT_ENTITY_CLASS(Mention, QxTdObject::TEXT_ENTITY_TYPE_MENTION)
TEXT_ENTITY_CLASS(MentionName, QxTdObject::TEXT_ENTITY_TYPE_MENTION_NAME)
TEXT_ENTITY_CLASS(PhoneNumber, QxTdObject::TEXT_ENTITY_TYPE_PHONE_NUMBER)
TEXT_ENTITY_CLASS(Cashtag, QxTdObject::TEXT_ENTITY_TYPE_CASHTAG)
TEXT_ENTITY_CLASS(Pre, QxTdObject::TEXT_ENTITY_TYPE_PRE)
TEXT_ENTITY_CLASS(PreCode, QxTdObject::TEXT_ENTITY_TYPE_PRE_CODE)
TEXT_ENTITY_CLASS(Strikethrough, QxTdObject::TEXT_ENTITY_TYPE_STRIKETHROUGH)
TEXT_ENTITY_CLASS(Underline, QxTdObject::TEXT_ENTITY_TYPE_UNDERLINE)
TEXT_ENTITY_CLASS(Url, QxTdObject::TEXT_ENTITY_TYPE_URL)
TEXT_ENTITY_CLASS(Spoiler, QxTdObject::TEXT_ENTITY_TYPE_SPOILER)
TEXT_ENTITY_CLASS(CustomEmoji, QxTdObject::TEXT_ENTITY_TYPE_CUSTOM_EMOJI)

//TODO
//TEXT_ENTITY_CLASS(BankCardNumber, QxTdObject::TEXT_ENTITY_TYPE_BANKCARDNUMBER)

struct QxTdTextEntityFactory
{
    static QxTdTextEntityType *create(const QJsonObject &json, QObject *parent = nullptr);
};

class QxTdTextEntityTypeTextUrl : public QxTdTextEntityType
{
    Q_OBJECT
public:
    explicit QxTdTextEntityTypeTextUrl(QObject *parent = 0)
        : QxTdTextEntityType(parent)
    {
        setType(QxTdObject::TEXT_ENTITY_TYPE_TEXT_URL);
    }

    void unmarshalJson(const QJsonObject &json)
    {
        m_additionalInfo = json["url"].toString();
        emit additionalInfoChanged();
    }
};

#endif // QX_TD_TEXT_ENTITY_TYPE_H
