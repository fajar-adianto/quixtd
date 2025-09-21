#ifndef QX_TD_CHAT_LIST_SORT_FILTER_MODEL_H
#define QX_TD_CHAT_LIST_SORT_FILTER_MODEL_H

#include <QObject>
#include <QPointer>
#include <QFlags>
#include <QString>
#include <QSortFilterProxyModel>
#include "qx_td_chat_list_model.h"

/**
 * @brief The QxTdChatListSortFilterModel class
 *
 * Sorts chat list in descending order based on QxTdChat::order()
 *
 * Filters can be applied to show certain QxTdChatType's
 */
class QxTdChatListSortFilterModel : public QSortFilterProxyModel
{
    Q_OBJECT
    Q_PROPERTY(QxTdChatListModel *model READ model WRITE setModel NOTIFY modelChanged)
    Q_PROPERTY(int chatFilters READ chatFilters WRITE setChatFilters NOTIFY chatFiltersChanged)
    Q_PROPERTY(bool filterBarVisible READ filterBarVisible NOTIFY filterBarVisibleChanged)
    QML_ELEMENT
public:
    explicit QxTdChatListSortFilterModel(QObject *parent = nullptr);

    enum ChatFilters {
        Everything = 1, // this includes banned or left chats
        Personal =2,
        Unread = 4,
        Archived = 8
    };
    Q_ENUM(ChatFilters)

    QxTdChatListModel *model() const;
    void setModel(QxTdChatListModel *model);
    int chatFilters() const;
    bool filterBarVisible() const;

public slots:
    void setChatFilters(int chatFilters);
    void setChatNameFilter(const QString &nameFilter);
    void toggleFilterBar(const bool &value);
    void setChatListFilter(const int &value);

signals:
    void modelChanged();
    void countChanged();
    void chatFiltersChanged(int chatFilters);
    void filterBarVisibleChanged();

protected:
    bool filterAcceptsRow(int source_row, const QModelIndex &source_parent) const override;
    bool lessThan(const QModelIndex &source_left, const QModelIndex &source_right) const override;

private:
    Q_DISABLE_COPY(QxTdChatListSortFilterModel)
    QPointer<QxTdChatListModel> m_chatList;
    int m_chatFilters;
    bool m_filterBarVisible;
    QString m_chatNameFilter;
};

#endif // QX_TD_CHAT_LIST_SORT_FILTER_MODEL_H
