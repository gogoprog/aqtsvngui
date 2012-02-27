#include "treemodel.h"

#include <QSize>
#include "svnmanager.h"
#include "svnentry.h"

TreeModel::TreeModel(QObject *parent)
: QAbstractItemModel(parent)
{
}

TreeModel::~TreeModel()
{
}

QVariant TreeModel::data(const QModelIndex &index, int role) const
{
    if (!index.isValid())
        return QVariant();

    if (role == Qt::CheckStateRole && index.column() == 0) {
        SVNEntry *entry = static_cast<SVNEntry *>(index.internalPointer());
        if (entry->isSelected())
            return QVariant(Qt::Checked);
        else
            return QVariant(Qt::Unchecked);
    }

    if (role != Qt::DisplayRole && role != Qt::EditRole)
        return QVariant();

    if(index.column() == 0)
        return QVariant();

    if(index.column() == 1)
        return QVariant(SVNManager::getInstance().getEntryList()[index.row()]->getRelativePath());

    if(index.column() == 2) {
        switch(SVNManager::getInstance().getEntryList()[index.row()]->getStatus()) {
            case SVNEntry::Modified:
                return QVariant("Modified");
                break;
            case SVNEntry::Unversioned:
                return QVariant("Unversioned");
                break;
        }
    }

    return QVariant("Impossible");
}

bool TreeModel::setData(const QModelIndex & index, const QVariant & value, int role)
{
    if (index.column() == 0) {
        SVNEntry *entry = static_cast<SVNEntry *>(index.internalPointer());

        entry->setIsSelected(!entry->isSelected());

        emit dataChanged(index, index);
    }

    return true;
}

Qt::ItemFlags TreeModel::flags(const QModelIndex &index) const
{
    if (!index.isValid())
        return 0;

    if (index.column() == 0) {
        return Qt::ItemIsEnabled | Qt::ItemIsSelectable | Qt::ItemIsUserCheckable | Qt::ItemIsEditable;
    }

    return Qt::ItemIsEnabled | Qt::ItemIsSelectable;
}

QVariant TreeModel::headerData(int section, Qt::Orientation orientation, int role) const
{
    if (orientation == Qt::Horizontal) {
        if (role == Qt::DisplayRole) {
            if (section == 0)
                return QVariant("");

            if (section == 1)
                return QVariant("File");

            if (section == 2)
                return QVariant("Status");
        }
    }
    return QVariant();
}

QModelIndex TreeModel::index(int row, int column, const QModelIndex &parent) const
{
    if (!hasIndex(row, column, parent) || row >= SVNManager::getInstance().getEntryList().size())
        return QModelIndex();

    return createIndex(row, column, SVNManager::getInstance().getEntryList()[row]);
}

QModelIndex TreeModel::parent(const QModelIndex &index) const
{
    return QModelIndex();
}

int TreeModel::rowCount(const QModelIndex &parent) const
{
    if (parent.column() > 0 || parent.isValid())
        return 0;

    return SVNManager::getInstance().getEntryList().size();
}

int TreeModel::columnCount(const QModelIndex &/*parent*/) const
{
    return 3;
}


