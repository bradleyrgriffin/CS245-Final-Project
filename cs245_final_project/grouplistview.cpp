#include "grouplistview.h"

GroupListView::GroupListView(std::vector<Group>& group, QObject *parent)
    : QAbstractListModel(parent), groups(group)
{
}

int GroupListView::rowCount(const QModelIndex &parent) const
{
    if (parent.isValid()){
        return 0;}
    else{
        return groups.size();}
}

QVariant GroupListView::data(const QModelIndex &index, int role) const
{
    if (!index.isValid())
        return QVariant();

    if (role==Qt::DisplayRole)
    {
        std::string displayName = groups.at(index.row()).displayName;
        return QVariant(QString::fromStdString(displayName));
    }

    return QVariant();
}


/*
 * setData - defines what data to display, where to display it, and how to display it
 *
 * We explicitly call this function to update the data in the View.
 */
bool GroupListView::setData(QModelIndex const& idx, QVariant const& value, int role)
{
  // Qt::EditRole: manages changes in the model
  if (Qt::EditRole == role)
  {
    // Get the top left and bottom right indices of the cells in our update range
    QModelIndex topLeft = idx;
    QModelIndex bottomRight = index(this->rowCount() - 1, 0);

    // VERY IMPORTANT - emit events telling all listening event handlers
    // that both the data (from cell 0,0 to the end) AND the layout have changed
    emit dataChanged(topLeft, bottomRight);
    emit layoutChanged();


    return true;
  }
  return false;
}

void GroupListView::loadPhoneNumbers(std::vector<Group>& phns){
    this->groups.clear();
    this->groups = phns;
    this->setData(this->index(0,0), 0);
}
void GroupListView::loadPhoneNumbers(){
    this->groups.clear();
    this->setData(this->index(0,0), 0);
}
