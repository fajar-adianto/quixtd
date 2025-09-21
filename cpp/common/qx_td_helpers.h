#include <QDateTime>
#include <QRegularExpression>

class QxTdHelpers
{
    static QRegularExpression rxEntity;

public:
    static QString formatDate(const QDateTime &dt);
    static QString avatarColor(qint64 userId);
    static QString selfColor();
    static void getEntitiesFromMessage(const QString &messageText,
                                       QString &plainText,
                                       QJsonArray &entities);
    static QJsonArray formatPlainTextMessage(const QString &messageText,
                                             QString &plainText);
    static QString initials(const QString &title);

    private:
        static QStringList colorPalette;
};
