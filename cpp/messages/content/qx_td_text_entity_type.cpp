#include "qx_td_text_entity_type.h"

QxTdTextEntityType::QxTdTextEntityType(QObject *parent)
    : QxTdObject(parent)
{
    // Intentionally left empty.
}

QString QxTdTextEntityType::additionalInfo() const
{
    return m_additionalInfo;
}

QxTdTextEntityType *QxTdTextEntityFactory::create(const QJsonObject &json, QObject *parent)
{
    const QString type = json["@type"].toString();
    if (type == "textEntityTypeBold") {
        return new QxTdTextEntityTypeBold(parent);
    } else if (type == "textEntityTypeBotCommand") {
        return new QxTdTextEntityTypeBotCommand(parent);
    } else if (type == "textEntityTypeCashtag") {
        return new QxTdTextEntityTypeCashtag(parent);
    } else if (type == "textEntityTypeCode") {
        return new QxTdTextEntityTypeCode(parent);
    } else if (type == "textEntityTypeEmailAddress") {
        return new QxTdTextEntityTypeEmailAddress(parent);
    } else if (type == "textEntityTypeHashtag") {
        return new QxTdTextEntityTypeHashtag(parent);
    } else if (type == "textEntityTypeItalic") {
        return new QxTdTextEntityTypeItalic(parent);
    } else if (type == "textEntityTypeMention") {
        return new QxTdTextEntityTypeMention(parent);
    } else if (type == "textEntityTypeMentionName") {
        return new QxTdTextEntityTypeMentionName(parent);
    } else if (type == "textEntityTypePhoneNumber") {
        return new QxTdTextEntityTypePhoneNumber(parent);
    } else if (type == "textEntityTypePre") {
        return new QxTdTextEntityTypePre(parent);
    } else if (type == "textEntityTypePreCode") {
        return new QxTdTextEntityTypePreCode(parent);
    } else if (type == "textEntityTypeStrikethrough") {
        return new QxTdTextEntityTypeStrikethrough(parent);
    } else if (type == "textEntityTypeUnderline") {
        return new QxTdTextEntityTypeUnderline(parent);
    } else if (type == "textEntityTypeTextUrl") {
        auto entityTypeTextUrl = new QxTdTextEntityTypeTextUrl(parent);
        entityTypeTextUrl->unmarshalJson(json);
        return entityTypeTextUrl;
    } else if (type == "textEntityTypeUrl") {
        return new QxTdTextEntityTypeUrl(parent);
    } else if (type == "textEntityTypeSpoiler") {
        return new QxTdTextEntityTypeSpoiler(parent);
    }
    return new QxTdTextEntityType(parent);
}
