#include <vector>
    #include <QBrush>
    #include <QColor>
    #include <QFont>
    #include "contacttablemodel.h"
    #include "contact.h"
#include <string>

  using std::vector;


ContactTableModel::ContactTableModel(QObject *parent)
    : QAbstractTableModel(parent)
{
    this->createContacts();
}

void ContactTableModel::updateContacts(const vector<Contact>& data){
    this->contacts.clear();
    for(auto& i : data){
        this->contacts.push_back(i);
    }
    this->setData(this->index(0,0), 0);
}

/*
 * rowCount - returns the number of rows in the table model
 */
int ContactTableModel::rowCount(const QModelIndex &parent) const
{
    return contacts.size();
}

void ContactTableModel::createContacts(){
    Contact c1 = Contact();
    this->contacts.push_back(c1);
}

/*
 * columnCount - returns the number of columns in the table model
 */
int ContactTableModel::columnCount(const QModelIndex &parent) const
{
        return 3;
}


/*
* data - defines what data to display, where to display it, and how to display it
*
* this-setData calls this function to help it display the data in the QTableView.
*/
QVariant ContactTableModel::data(const QModelIndex &index, int role) const
{
// Get the row and columns numbers from the given index (QModelIndex)
int row = index.row();
int col = index.column();

// Qt::DisplayRole -> what data do we display and in what columns?
if (role == Qt::DisplayRole)
{
    switch (col)
    {
    case 0: // ID column
        return QString::fromStdString(std::to_string(contacts[row].contactId));
        break;
    case 1: // FNAME column
        return QString::fromStdString(contacts[row].firstName);
        break;
    case 2: // LNAME column
        return QString::fromStdString(contacts[row].lastName);
        break;
    }
}
// Qt::FontRole -> manages the fonts and font styles used in the View
    else if (role == Qt::FontRole)
    {
        // Bold the text in the first column
        if (col == 0) {
            QFont boldFont;
            boldFont.setBold(true);
            return boldFont;
        }
    }

    // Qt::ForegroundRole -> paints the foreground (text) colors
    else if (role == Qt::ForegroundRole)
    {
        // Paint the text red in the Password column
        if (col == 1) {
            QFont boldFont;
            boldFont.setBold(false);
            return boldFont;
        }
    }

    // Qt::TextAlignRole -> controls how data is aligned inside cells
    else if(role == Qt::TextAlignmentRole)
    {
        // All columns after the Username column should be right-aligned
        // horizontally, and centered vertically.
        if (col > 0)
        {
            return Qt::AlignRight + Qt::AlignVCenter;
        }
    }
    return QVariant();
}


/*
* headerData - defines what column/row header data to display
*/
QVariant ContactTableModel::headerData(int section, Qt::Orientation orientation, int role) const
{
if (role == Qt::DisplayRole)
{
    // Set the column (Qt::Horizontal) headers
    if (orientation == Qt::Horizontal) {
        switch (section)
        {
        case 0:
            return QString("ID");
        case 1:
            return QString("First Name");
        case 2:
            return QString("Last Name");
        }
    }
}
return QVariant();
}

/*
 * setData - defines what data to display, where to display it, and how to display it
 *
 * We explicitly call this function to update the data in the View.
 */
bool ContactTableModel::setData(QModelIndex const& idx, QVariant const& value, int role)
{
  // Qt::EditRole: manages changes in the model
  if (Qt::EditRole == role)
  {
    // Get the top left and bottom right indices of the cells in our update range
    QModelIndex topLeft = idx;
    QModelIndex bottomRight = index(this->rowCount() - 1, this->columnCount() - 1);

    // VERY IMPORTANT - emit events telling all listening event handlers
    // that both the data (from cell 0,0 to the end) AND the layout have changed
    emit dataChanged(topLeft, bottomRight);
    emit layoutChanged();


    return true;
  }
  return false;
}


int ContactTableModel::getContactIdByIndex(const QModelIndex & index){
    int col = index.column();
    int row = index.row();
    switch (col)
    {
    case 0: // ID column
        return contacts[row].contactId;
        break;
    case 1: // FNAME column
        return -1;
        break;
    case 2: // LNAME column
        return -1;
        break;
    }
}

bool ContactTableModel::deleteContact(int& id){

    for(std::vector<Contact>::iterator it = this->contacts.begin(); it != this->contacts.end(); ++it) {
        if((*it).getContactId() == id){
            this->contacts.erase(it);
            this->setData(this->index(0,0), 0);
            return true;
        }
    }

    return false;
}

void ContactTableModel::addContact(Contact cntct){
    if((this->contacts.capacity() - this->contacts.size()) < 5){
        this->contacts.reserve(2 * this->contacts.capacity());
    }

    this->contacts.push_back(cntct);

    this->setData(this->index(0,0), 0);
}

void ContactTableModel::updateContact(const Contact& cntct){
    for(std::vector<Contact>::iterator it = this->contacts.begin(); it != this->contacts.end(); ++it) {
        if((*it).getContactId() == cntct.contactId){
            (*it).setFName(cntct.firstName);
            (*it).setLName(cntct.lastName);
            this->setData(this->index(0,0), 0);
        }
    }
}
