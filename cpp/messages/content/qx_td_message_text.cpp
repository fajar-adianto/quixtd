#include "qx_td_message_text.h"

QxTdMessageText::QxTdMessageText(QObject *parent)
    : QxTdMessageContent(parent)
    , m_text(new QxTdFormattedText)
    , m_webPage(new QxTdWebPage)
    , m_hasWebPage(false)
{
    setType(MESSAGE_TEXT);
}

QxTdFormattedText *QxTdMessageText::text() const
{
    return m_text.data();
}

QxTdWebPage *QxTdMessageText::webPage() const
{
    if (!m_hasWebPage) {
        return nullptr;
    }
    return m_webPage.data();
}

void QxTdMessageText::unmarshalJson(const QJsonObject &json)
{
    QxTdMessageContent::unmarshalJson(json);
    m_hasWebPage = false;
    m_text->unmarshalJson(json["text"].toObject());
    m_infoText = m_text->oneLineText();
    if (json.contains("web_page")) {
        m_webPage->unmarshalJson(json["web_page"].toObject());
        m_hasWebPage = true;
        if (m_webPage->containsPhoto()) {
            m_infoImageUrl = QUrl("image://photo/" + webPage()->photo()->sizes()->at(0)->photo()->local()->path());
        }
    }
    emit dataChanged();
}
