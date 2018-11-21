#ifndef CONTACTTABLEMODEL_H
#define CONTACTTABLEMODEL_H

#include <QAbstractTableModel>
#include <vector>
#include <string>
#include <contact.h>

using std::string;
using std::vector;

class ContactTableModel : public QAbstractTableModel
{
    Q_OBJECT

public:
    explicit ContactTableModel(QObject *parent = 0);

    // Overrides methods inherited from QAbstractTableModel
    virtual int rowCount(const QModelIndex &parent = QModelIndex()) const ;
    virtual int columnCount(const QModelIndex &parent = QModelIndex()) const;
    virtual QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const;
    virtual QVariant headerData(int section, Qt::Orientation orientation, int role) const;
    virtual bool setData(const QModelIndex & index, const QVariant & value, int role = Qt::EditRole);

    void createContacts();

    void updateContacts(const vector<Contact>& ctnct);

    int getContactIdByIndex(const QModelIndex& index);

public slots:

signals:



private:
    vector<Contact> contacts;
};

#endif // CONTACTTABLEMODEL_H