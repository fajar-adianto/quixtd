#include "qx_td_secret_chat.h"
#include <QScopedPointer>
#include "chat/requests/qx_td_get_secret_chat_request.h"
#include "client/qx_td_client.h"

QxTdSecretChat::QxTdSecretChat(QObject *parent)
    : QxTdChat(parent)
    , m_secretChatId(0)
    , m_userId(0)
    , m_isOutbound(false)
    , m_ttl(0)
    , m_layer(0)
    , m_state(nullptr)
{
    connect(QxTdClient::instance(), &QxTdClient::secretChat, this, &QxTdSecretChat::updateSecretChat);
    connect(QxTdClient::instance(), &QxTdClient::updateSecretChat, this, &QxTdSecretChat::updateSecretChat);
    m_hashMap = new QxTdObjectListModel<QxTdHashRow>(this);
}

QString QxTdSecretChat::qmlSecretChatId() const
{
    return m_secretChatId.toQmlValue();
}

qint64 QxTdSecretChat::secretChatId() const
{
    return m_secretChatId.value();
}

QString QxTdSecretChat::qmlUserId() const
{
    return m_userId.toQmlValue();
}

qint64 QxTdSecretChat::userId() const
{
    return m_userId.value();
}

bool QxTdSecretChat::isOutbound() const
{
    return m_isOutbound;
}

bool QxTdSecretChat::isWritable() const
{
    auto result = qobject_cast<QxTdSecretChatStateReady *>(m_state);
    return result != nullptr;
}

bool QxTdSecretChat::isPending() const
{
    auto result = qobject_cast<QxTdSecretChatStatePending *>(m_state);
    return result != nullptr;
}

bool QxTdSecretChat::isClosed() const
{
    auto result = qobject_cast<QxTdSecretChatStateClosed *>(m_state);
    return result != nullptr;
}

qint32 QxTdSecretChat::ttl() const
{
    return m_ttl;
}

QString QxTdSecretChat::keyHashString() const
{
    QString hashString = m_keyHash.toUpper();
    hashString = hashString.left(64);
    for (int i = 62; i > 0; i-=2) {
        if (i % 16 == 0) {
            hashString = hashString.insert(i, "\n");
        } else if (i % 8 == 0) {
            hashString = hashString.insert(i, "    ");
        } else
            hashString = hashString.insert(i, " ");
    }
    return hashString;
}
QObject *QxTdSecretChat::keyHashMap() const
{
    if (m_hashMap->isEmpty()) {
        for (int i = 1; i <= 12; i++) {
            std::unique_ptr<QxTdHashRow> hashRow(new QxTdHashRow);
            bool ok;
            QByteArray stringRow = m_keyHash;
            //subdivide the QByteArray in twelve parts of 6 hex char each (3 bytes)
            stringRow.truncate(i * 6);
            stringRow = stringRow.right(6);
            //convert the QByteArray to binary (hex -> int -> binary)
            stringRow = QByteArray::number(stringRow.toInt(&ok, 16), 2);
            // prepend "0" to reach a length of 24 bits
            stringRow.prepend(24 - stringRow.length(), *"0");
            hashRow->setRow(stringRow);
            m_hashMap->append(hashRow.release());
        }
    }
    return m_hashMap;
}

qint32 QxTdSecretChat::layer() const
{
    return m_layer;
}

QxTdSecretChatState *QxTdSecretChat::state() const
{
    return m_state;
}

void QxTdSecretChat::onChatOpened()
{
    getSecretChatData();
    QxTdChat::onChatOpened();
}

void QxTdSecretChat::getSecretChatData()
{
    QxTdChatTypeSecret *secret = qobject_cast<QxTdChatTypeSecret *>(chatType());
    if (secret) {
        QScopedPointer<QxTdGetSecretChatRequest> req(new QxTdGetSecretChatRequest);
        req->setSecretChatId(secret->secretChatId());
        QxTdClient::instance()->send(req.data());
    }
    else
        qWarning() << "Secret chat is null!";
}

void QxTdSecretChat::updateSecretChat(const QJsonObject &data)
{
    QxTdChatTypeSecret *secret = qobject_cast<QxTdChatTypeSecret *>(chatType());
    const qint64 sid = data["id"].toVariant().toLongLong();
    if (sid != secret->secretChatId()) {
        return;
    }

    m_secretChatId = sid;
    m_userId = data["user_id"].toVariant().toLongLong();
    if (m_state) {
        delete m_state;
        m_state = nullptr;
    }
    const QJsonObject state = data["state"].toObject();
    const QString type = state["@type"].toString();
    if (type == "secretChatStateClosed") {
        m_state = new QxTdSecretChatStateClosed(this);
    } else if (type == "secretChatStatePending") {
        m_state = new QxTdSecretChatStatePending(this);
    } else if (type == "secretChatStateReady") {
        m_state = new QxTdSecretChatStateReady(this);
    }
    if (m_state) {
        m_state->unmarshalJson(state);
        emit stateChanged(m_state);
        emit isWritableChanged();
    }
    m_isOutbound = data["is_outbound"].toBool();
    m_ttl = qint32(data["ttl"].toInt());
    m_keyHash = QByteArray::fromBase64(data["key_hash"].toString().toUtf8()).toHex();
    m_layer = qint32(data["layer"].toInt());
    emit secretChatChanged();
}

QxTdHashRow::QxTdHashRow(QObject *parent)
    : QxTdObject(parent)
    , m_hashRow(nullptr)
{
    m_hashRow = new QxTdObjectListModel<QxTdHashPixel>(this);
}
QObject *QxTdHashRow::hashRow() const
{
    return m_hashRow;
}
void QxTdHashRow::setRow(QByteArray stringRow) const
{
    QVector<QColor> colors(4);
    colors[0] = QColor("#ffffffff");
    colors[1] = QColor("#ffd5e6f3");
    colors[2] = QColor("#ff2d5775");
    colors[3] = QColor("#ff2f99c9");
    for (int i = 1; i <= 3; i++) {
        QByteArray byte = stringRow;
        byte.truncate(i * 8);
        byte = byte.right(8);
        for (int j = byte.length() / 2; j > 0; j--) {
            std::unique_ptr<QxTdHashPixel> hashPixel(new QxTdHashPixel);
            bool ok;
            // cut byte to get only 2 bits
            byte.truncate(j * 2);
            QByteArray pixel = byte.right(2);
            //convert binary value into integer
            int pixelInt = pixel.toInt(&ok, 2);
            QColor pixelColor = colors[pixelInt];
            hashPixel->setHashPixelColor(pixelColor);
            m_hashRow->append(hashPixel.release());
        }
    }
}

QxTdHashPixel::QxTdHashPixel(QObject *parent)
    : QxTdObject(parent)
{
    m_hashPixelColor = QColor("darkCyan");
}
QColor QxTdHashPixel::hashPixelColor() const
{
    return m_hashPixelColor;
}
void QxTdHashPixel::setHashPixelColor(QColor hashPixelColor)
{
    if (m_hashPixelColor == hashPixelColor)
        return;

    m_hashPixelColor = hashPixelColor;
}
