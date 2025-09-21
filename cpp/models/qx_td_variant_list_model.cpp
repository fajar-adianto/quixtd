#include "qx_td_variant_list_model.h"

QxTdVariantListModel::QxTdVariantListModel(QObject *parent)
    : QAbstractListModel(parent)
    , m_count(0)
{
    // Intentionally left empty.
}

QHash<int, QByteArray> QxTdVariantListModel::rolenames() const
{
    QHash<int, QByteArray> roles;
    roles.insert(Qt::UserRole, QByteArrayLiteral("qtVariant"));
    return roles;
}

QVariant QxTdVariantListModel::data(const QModelIndex &index, int role) const
{
    QVariant value;
    const int row = index.row();
    if (row >= 0 && row < count() && role == Qt::UserRole) {
        value = m_values.value(row);
    }
    return value;
}

bool QxTdVariantListModel::setData(const QModelIndex &index, const QVariant &value, int role)
{
    bool dataSet = false;
    const int row = index.row();
    if (row >= 0 && row < count()) {
        m_values.replace(row, value);
        QModelIndex item = QAbstractListModel::index(row, 0, QModelIndex());
        emit dataChanged(item, item, QVector<int>(1, role));
        dataSet = true;
    }
    return dataSet;
}

int QxTdVariantListModel::rowCount(const QModelIndex &parent) const
{
    Q_UNUSED(parent);
    return m_values.count();
}

void QxTdVariantListModel::append(const QVariant &value)
{
    const int rows = count();
    beginInsertRows(QModelIndex(), rows, rows);
    m_values.append(value);
    endInsertRows();
    countPossiblyChanged();
}

void QxTdVariantListModel::appendList(const QVariantList &values)
{
    if (values.isEmpty()) {
        return;
    }
    const int rows = count();
    beginInsertRows(QModelIndex(), rows, rows + values.count() - 1);
    m_values.append(values);
    endInsertRows();
    countPossiblyChanged();
}

int QxTdVariantListModel::count() const
{
    return rowCount();
}

void QxTdVariantListModel::clear()
{
    if (m_values.isEmpty()) {
        return;
    }
    beginRemoveRows(QModelIndex(), 0, rowCount() - 1);
    m_values.clear();
    endRemoveRows();
    countPossiblyChanged();
}

QVariant QxTdVariantListModel::get(int index)
{
    QVariant value;
    if (index >= 0 && index < m_values.size()) {
        value = m_values.value(index);
    }
    return value;
}

bool QxTdVariantListModel::isEmpty() const
{
    return m_values.isEmpty();
}

void QxTdVariantListModel::insert(int index, const QVariant &value)
{
    beginInsertRows(QModelIndex(), index, index);
    m_values.insert(index, value);
    endInsertRows();
    countPossiblyChanged();
}

void QxTdVariantListModel::insertList(int index, const QVariantList &values)
{
    if (values.isEmpty()) {
        return;
    }
    beginInsertRows(QModelIndex(), index, (index + values.count()) - 1);
    int offset = 0;
    for (auto value : values) {
        m_values.insert(index + offset, value);
        ++offset;
    }
    endInsertRows();
    countPossiblyChanged();
}

QVariantList QxTdVariantListModel::list() const
{
    return m_values;
}

void QxTdVariantListModel::move(int index, int to)
{
    if (index == to) {
        // well that's not clever
        return;
    }
    beginMoveRows(QModelIndex(), index, index, QModelIndex(), (index < to ? to + 1 : to));
    m_values.move(index, to);
    endMoveRows();
    countPossiblyChanged();
}

void QxTdVariantListModel::prepend(const QVariant &value)
{
    beginInsertColumns(QModelIndex(), 0, 0);
    m_values.prepend(value);
    endInsertRows();
    countPossiblyChanged();
}

void QxTdVariantListModel::prependList(const QVariantList &values)
{
    if (values.isEmpty()) {
        return;
    }
    beginInsertRows(QModelIndex(), 0, values.count() - 1);
    int offset = 0;
    for (auto value : values) {
        m_values.insert(offset, value);
    }
    endInsertRows();
    countPossiblyChanged();
}

void QxTdVariantListModel::replace(int index, const QVariant &value)
{
    if (index >= 0 && index < count()) {
        m_values.replace(index, value);
        QModelIndex item = QAbstractListModel::index(index, 0, QModelIndex());
        emit dataChanged(item, item, QVector<int>(1, Qt::UserRole));
    }
}

void QxTdVariantListModel::remove(int index)
{
    if (index >= 0 && index < count()) {
        beginRemoveColumns(QModelIndex(), index, index);
        m_values.removeAt(index);
        endRemoveRows();
        countPossiblyChanged();
    }
}

void QxTdVariantListModel::countPossiblyChanged()
{
    if (m_count != count()) {
        m_count = count();
        emit countChanged();
    }
}
