#include "qx_td_helpers.h"
#include "client/qx_td_client.h"

QString QxTdHelpers::formatDate(const QDateTime &dt)
{
    const QDateTime now = QDateTime::currentDateTimeUtc().toLocalTime();
    const QDateTime localdt = dt.toLocalTime();
    auto daysDiff = now.daysTo(localdt);
    if (daysDiff == 0) {
        return localdt.toString("hh:mm");
    } else if (daysDiff > -7) {
        return localdt.toString("ddd hh:mm");
    } else
        return localdt.toString("dd.MM.yy hh:mm");
}

QStringList QxTdHelpers::colorPalette = {
    "#a93226",
    "#cb4335",
    "#884ea0",
    "#7d3c98",
    "#2471a3",
    "#2e86c1",
    "#17a589",
    "#138d75",
    "#229954",
    "#28b463",
    "#d4ac0d",
    "#d68910",
    "#ca6f1e",
    "#ba4a00",
    "#839192",
    "#707b7c"
};

QString QxTdHelpers::avatarColor(qint64 userId)
{
    return colorPalette.at(abs((int)(userId % colorPalette.size())));
}

QString QxTdHelpers::selfColor()
{
    return "#65aadd";
}
QRegularExpression QxTdHelpers::rxEntity;

void QxTdHelpers::getEntitiesFromMessage(const QString &messageText, QString &plainText, QJsonArray &entities)
{
    if (!rxEntity.isValid()) {
        // Use non-greedy quantifiers (.+?) instead of setMinimal(true)
        rxEntity = QRegularExpression(R"(\*\*.+?\*\*|__.+?__|```[^`].+?```|`[^`\n\r]+?`)");
    }

    plainText = messageText;
    int offsetCorrection = 0;

    QRegularExpressionMatchIterator it = rxEntity.globalMatch(messageText);
    while (it.hasNext()) {
        QRegularExpressionMatch matchObj = it.next();
        if (!matchObj.hasMatch())
            continue;

        QString match = matchObj.captured(0);
        int pos = matchObj.capturedStart();
        int actualPos = pos - offsetCorrection;

        QJsonObject entity;
        entity["@type"] = "textEntity";
        entity["offset"] = actualPos;

        QJsonObject entityType;

        if (match.startsWith("**")) {
            int contentLength = matchObj.capturedLength() - 4;
            entityType["@type"] = "textEntityTypeBold";
            entity["length"] = contentLength;
            plainText = plainText.replace(actualPos, 2, "");
            plainText = plainText.replace(actualPos + contentLength, 2, "");
            offsetCorrection += 4;

        } else if (match.startsWith("__")) {
            int contentLength = matchObj.capturedLength() - 4;
            entityType["@type"] = "textEntityTypeItalic";
            entity["length"] = contentLength;
            plainText = plainText.replace(actualPos, 2, "");
            plainText = plainText.replace(actualPos + contentLength, 2, "");
            offsetCorrection += 4;

        } else if (match.startsWith("```")) {
            if (pos > 0 && messageText.at(pos - 1) == '`')
                continue;

            int contentLength = matchObj.capturedLength() - 6;
            entityType["@type"] = "textEntityTypePre";
            entity["length"] = contentLength;

            plainText = plainText.replace(actualPos, 3, "");
            if (actualPos > 0 && plainText.at(actualPos - 1) != "\n") {
                plainText = plainText.insert(actualPos, "\n");
                entity["offset"] = actualPos + 1;
                offsetCorrection--;
            }
            plainText = plainText.replace(actualPos + contentLength, 3, "");
            if (plainText.at(actualPos + contentLength) != "\n") {
                plainText = plainText.insert(actualPos + contentLength, "\n");
                offsetCorrection--;
            }
            offsetCorrection += 6;

        } else if (match.startsWith("`")) {
            if (pos > 0 && messageText.at(pos - 1) == '`')
                continue;

            int contentLength = matchObj.capturedLength() - 2;
            entityType["@type"] = "textEntityTypeCode";
            entity["length"] = contentLength;
            plainText = plainText.replace(actualPos, 1, "");
            plainText = plainText.replace(actualPos + contentLength, 1, "");
            offsetCorrection += 2;
        }

        entity["type"] = entityType;
        entities << entity;
    }
}

QJsonArray QxTdHelpers::formatPlainTextMessage(const QString &message, QString &plainText)
{
    //First call tdlib to markup all complex entities
    auto parseRequest = QJsonObject{
        { "@type", "getTextEntities" },
        { "text", message }
    };
    auto result = QxTdClient::instance()->exec(parseRequest);
    result.waitForFinished();

    QJsonArray entities = result.result()["entities"].toArray();

    //Then do the text formatting
    QxTdHelpers::getEntitiesFromMessage(message, plainText, entities);

    return entities;
}

QString QxTdHelpers::initials(const QString &title)
{
    if (title != "") {
        QString initials = "";
        QStringList parts = title.trimmed().split(" ", Qt::SkipEmptyParts);
        for (int i = 0; i < parts.size(); i++) {
            initials += parts[i][0].toUpper();
            if (initials.length() >= 2) {
                break;
            }
        }
        if (initials.length() < 2) {
            initials = title.trimmed().left(2).toUpper();
        }
        return initials;
    }
    return "";
}
