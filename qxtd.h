#ifndef QXTD_H
#define QXTD_H

#include <QtQuick/QQuickPaintedItem>

class QxTd : public QQuickPaintedItem
{
    Q_OBJECT
    QML_ELEMENT
    Q_DISABLE_COPY(QxTd)
public:
    explicit QxTd(QQuickItem *parent = nullptr);
    void paint(QPainter *painter) override;
    ~QxTd() override;
};

#endif // QXTD_H
