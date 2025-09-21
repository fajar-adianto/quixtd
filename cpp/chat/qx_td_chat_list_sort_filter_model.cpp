#include "qx_td_chat_list_sort_filter_model.h"
#include <QDebug>
#include "client/qx_td_client.h"
#include "models/qx_td_object_list_model.h"
#include "qx_td_basic_group_chat.h"
#include "qx_td_super_group_chat.h"

QxTdChatListSortFilterModel::QxTdChatListSortFilterModel(QObject *parent)
    : QSortFilterProxyModel(parent)
    , m_chatList(0)
    , m_chatFilters(Everything)
{
    // Intentionally left empty.
}

QxTdChatListModel *QxTdChatListSortFilterModel::model() const
{
    return m_chatList;
}

void QxTdChatListSortFilterModel::setModel(QxTdChatListModel *model)
{
    m_chatList = model;
    setSourceModel(static_cast<QAbstractItemModel *>(m_chatList->model()));
    connect(model, &QxTdChatListModel::chatStatusChanged, [=]() {
        invalidateFilter();
    });
    emit modelChanged();
    setSortRole(static_cast<QxTdObjectListModel<QxTdChat> *>(m_chatList->model())->roleForName("lastMessage"));
    setFilterRole(static_cast<QxTdObjectListModel<QxTdChat> *>(m_chatList->model())->roleForName("chatType"));
    setDynamicSortFilter(true);
    sort(0, Qt::DescendingOrder);
}

int QxTdChatListSortFilterModel::chatFilters() const
{
    return m_chatFilters;
}

void QxTdChatListSortFilterModel::setChatFilters(int chatFilters)
{
    if (m_chatFilters == chatFilters)
        return;

    m_chatFilters = chatFilters;
    emit chatFiltersChanged(m_chatFilters);
    invalidateFilter();
}

void QxTdChatListSortFilterModel::setChatNameFilter(const QString &chatNameFilter)
{
    m_chatNameFilter = chatNameFilter;
    invalidateFilter();
}

bool QxTdChatListSortFilterModel::filterBarVisible() const {
    return m_filterBarVisible;
}

void QxTdChatListSortFilterModel::toggleFilterBar(const bool &value) {
    m_filterBarVisible = value;
    if (!m_filterBarVisible) {
        m_chatFilters |= ChatFilters::Everything;
    } else {
        m_chatFilters &= ~ChatFilters::Everything;
    }
    invalidateFilter();
}

void QxTdChatListSortFilterModel::setChatListFilter(const int &value) {

    switch(value) {
        case 0:
            m_chatFilters = ChatFilters::Everything;
            break;
        case 1:
            m_chatFilters = ChatFilters::Personal;
            break;
        case 2:
            m_chatFilters = ChatFilters::Unread;
            break;
        case 3:
            m_chatFilters = ChatFilters::Archived;
            break;
    }
    invalidateFilter();
}

bool QxTdChatListSortFilterModel::filterAcceptsRow(int source_row, const QModelIndex &source_parent) const
{
    QxTdObjectListModel<QxTdChat> *model = static_cast<QxTdObjectListModel<QxTdChat> *>(sourceModel());
    QxTdChat *chat = model->at(source_row);

    if (!chat || chat->position()->order() == 0) {
        return false;
    }

    bool showRow = true;
    bool archived = chat->position()->list() && chat->position()->list()->typeString() == "chatListArchive";

    //Apply chat title filter, if set
    if (!chat->title().contains(m_chatNameFilter, Qt::CaseInsensitive)) {
        showRow = false;
    }

    if (m_chatFilters & ChatFilters::Everything) {
        return showRow & !archived;
    }

    if (m_chatFilters & ChatFilters::Unread && !(chat->hasUnreadMessages() || chat->hasUnreadMentions())) {
        showRow = false;
    }

    if (m_chatFilters & ChatFilters::Personal && !(chat->isPrivate() || chat->isSecret())) {
        showRow = false;
    }

    if (chat->position()->list()) {
        if (m_chatFilters & ChatFilters::Archived) {
            showRow = showRow & archived;
        } else {
            showRow = showRow & !archived;
        }
    }

    return showRow;
}

bool QxTdChatListSortFilterModel::lessThan(const QModelIndex &source_left, const QModelIndex &source_right) const
{
    /**
     * TDlib suggests to use QxTdChat::order() for ordering of the chat list
     *
     * Note this requires calling getBasicGroupData and getSuperGroupData to get the QxTdChat::order
     * to even update so we have to wait longer for them to arrive compared to a basic chat or channel.
     */
    QxTdObjectListModel<QxTdChat> *model = static_cast<QxTdObjectListModel<QxTdChat> *>(sourceModel());
    QxTdChat *left = model->at(source_left.row());
    QxTdChat *right = model->at(source_right.row());

    /*
    This is how the sorting rule works:
        IF left and right sort orders are <>0 AND left order is smaller than right order, return true
        OR IF both sort orders are equal AND left id is smaller than right id, return true
        OR IF left OR right order is 0 AND left last message date is smaller then right last message date
            AND left is not pinned, return true
        ELSE return false

        The first part is the rule from tdlib, sort by order, but if equal order is given, sort by id
        The second part is a safeguard against sort order being 0, which happens with "Saved Messages" chat a lot
     */
    auto result = left->position()->order() < right->position()->order()
            || left->position()->order() == right->position()->order() && left->id() < right->id();
    return result;
}
