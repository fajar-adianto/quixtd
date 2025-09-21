#ifndef QX_TD_CONNECTION_STATE_H
#define QX_TD_CONNECTION_STATE_H

#include "common/qx_td_object.h"

/**
 * @brief The QxTdConnectionState class
 *
 * https://core.telegram.org/tdlib/docs/classtd_1_1td__api_1_1_connection_state.html
 */
class QxTdConnectionState : public QxTdObject
{
    Q_OBJECT
    QML_ELEMENT
    QML_UNCREATABLE("QxTdConnectionState and its derived classes cannot be created in QML.")
    Q_DISABLE_COPY(QxTdConnectionState)
public:
    explicit QxTdConnectionState(QObject *parent = nullptr);
};

/**
 * @brief The QxTdConnectionStateWaitingForNetwork class
 *
 * https://core.telegram.org/tdlib/docs/classtd_1_1td__api_1_1connection_state_waiting_for_network.html
 */
class QxTdConnectionStateWaitingForNetwork : public QxTdConnectionState
{
    Q_OBJECT
    QML_ELEMENT
    QML_UNCREATABLE("QxTdConnectionState and its derived classes cannot be created in QML.")
    Q_DISABLE_COPY(QxTdConnectionStateWaitingForNetwork)
public:
    explicit QxTdConnectionStateWaitingForNetwork(QObject *parent = nullptr);
};

/**
 * @brief The QxTdConnectionStateConnectingToProxy class
 *
 * https://core.telegram.org/tdlib/docs/classtd_1_1td__api_1_1connection_state_connecting_to_proxy.html
 */
class QxTdConnectionStateConnectingToProxy : public QxTdConnectionState
{
    Q_OBJECT
    QML_ELEMENT
    QML_UNCREATABLE("QxTdConnectionState and its derived classes cannot be created in QML.")
    Q_DISABLE_COPY(QxTdConnectionStateConnectingToProxy)
public:
    explicit QxTdConnectionStateConnectingToProxy(QObject *parent = nullptr);
};

/**
 * @brief The QxTdConnectionStateConnecting class
 *
 * https://core.telegram.org/tdlib/docs/classtd_1_1td__api_1_1connection_state_connecting.html
 */
class QxTdConnectionStateConnecting : public QxTdConnectionState
{
    Q_OBJECT
    QML_ELEMENT
    QML_UNCREATABLE("QxTdConnectionState and its derived classes cannot be created in QML.")
    Q_DISABLE_COPY(QxTdConnectionStateConnecting)
public:
    explicit QxTdConnectionStateConnecting(QObject *parent = nullptr);
};

/**
 * @brief The QxTdConnectionStateUpdating class
 *
 * https://core.telegram.org/tdlib/docs/classtd_1_1td__api_1_1connection_state_updating.html
 */
class QxTdConnectionStateUpdating : public QxTdConnectionState
{
    Q_OBJECT
    QML_ELEMENT
    QML_UNCREATABLE("QxTdConnectionState and its derived classes cannot be created in QML.")
    Q_DISABLE_COPY(QxTdConnectionStateUpdating)
public:
    explicit QxTdConnectionStateUpdating(QObject *parent = nullptr);
};

/**
 * @brief The QxTdConnectionStateReady class
 *
 * https://core.telegram.org/tdlib/docs/classtd_1_1td__api_1_1connection_state_ready.html
 */
class QxTdConnectionStateReady : public QxTdConnectionState
{
    Q_OBJECT
    QML_ELEMENT
    QML_UNCREATABLE("QxTdConnectionState and its derived classes cannot be created in QML.")
    Q_DISABLE_COPY(QxTdConnectionStateReady)
public:
    explicit QxTdConnectionStateReady(QObject *parent = nullptr);
};

#endif // QX_TD_CONNECTION_STATE_H
