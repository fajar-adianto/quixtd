#ifndef QX_TD_TEXT_FORMATTER_H
#define QX_TD_TEXT_FORMATTER_H

#include <QQuickTextDocument>

#include "messages/content/qx_td_formatted_text.h"
#include <QtQmlIntegration/qqmlintegration.h>

class QxTdTextFormatter : public QObject
{
    Q_OBJECT
    Q_PROPERTY(QQuickTextDocument *textDocument READ textDocument WRITE setTextDocument NOTIFY textDocumentChanged)
    Q_PROPERTY(QxTdFormattedText *content READ content WRITE setContent NOTIFY contentChanged)
    Q_PROPERTY(QColor linkColor READ linkColor WRITE setLinkColor NOTIFY textColorsChanged)
    Q_PROPERTY(QColor codeColor READ codeColor WRITE setCodeColor NOTIFY textColorsChanged)
    Q_PROPERTY(QColor spoilerForeground READ spoilerForeground WRITE setSpoilerForeground NOTIFY textColorsChanged)
    Q_PROPERTY(QColor spoilerBackground READ spoilerBackground WRITE setSpoilerBackground NOTIFY textColorsChanged)
    QML_ELEMENT
public:
    explicit QxTdTextFormatter(QObject *parent = nullptr);

    QQuickTextDocument *textDocument() const;

    QxTdFormattedText *content() const;

    QColor linkColor() const;
    QColor codeColor() const;
    QColor spoilerForeground() const;
    QColor spoilerBackground() const;

signals:
    void textDocumentChanged(QQuickTextDocument *textDocument);
    void contentChanged(QxTdFormattedText *content);
    void textColorsChanged();

public slots:

    void setTextDocument(QQuickTextDocument *textDocument);
    void setContent(QxTdFormattedText *content);
    void setLinkColor(QColor linkColor);
    void setCodeColor(QColor codeColor);
    void setSpoilerForeground(QColor codeColor);
    void setSpoilerBackground(QColor codeColor);

private slots:
    void doFormat();

private:
    QQuickTextDocument *m_textDocument;
    QxTdFormattedText *m_content;
    QColor m_linkColor;
    QColor m_codeColor;
    QColor m_spoilerForeground;
    QColor m_spoilerBackground;
};

#endif // QX_TD_TEXT_FORMATTER_H
