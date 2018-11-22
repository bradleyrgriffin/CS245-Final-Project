#include "emaillistview.h"

EmailListView::EmailListView(std::vector<Email>& email, QObject *parent)
    : QAbstractListModel(parent), emails(email)
{
}

int EmailListView::rowCount(const QModelIndex &parent) const
{
    // For list models only the root node (an invalid parent) should return the list's size. For all
    // other (valid) parents, rowCount() should return 0 so that it does not become a tree model.
    if (parent.isValid()){
        return 0;}
    else{
        return emails.size();}
}

QVariant EmailListView::data(const QModelIndex &index, int role) const
{
    if (!index.isValid())
        return QVariant();

    if (role==Qt::DisplayRole)
    {
        std::string displayName = emails.at(index.row()).displayName;
        return QVariant(QString::fromStdString(displayName));
    }

    return QVariant();
}

/*
 * setData - defines what data to display, where to display it, and how to display it
 *
 * We explicitly call this function to update the data in the View.
 */
bool EmailListView::setData(QModelIndex const& idx, QVariant const& value, int role)
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

void EmailListView::loadPhoneNumbers(std::vector<Email>& phns){
    this->emails.clear();
    this->emails = phns;
    this->setData(this->index(0,0), 0);
}
void EmailListView::loadPhoneNumbers(){
    this->emails.clear();
    this->setData(this->index(0,0), 0);
}
