#ifndef ADDRESLISTVIEW_H
#define ADDRESLISTVIEW_H

#include <QAbstractListModel>
#include "address.h"

class AddresListView : public QAbstractListModel
{
    Q_OBJECT

public:
    explicit AddresListView(std::vector<Address>& addr, QObject *parent = nullptr);



    // Basic functionality:
    int rowCount(const QModelIndex &parent = QModelIndex()) const override;

    QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const override;
    virtual bool setData(const QModelIndex & index, const QVariant & value, int role = Qt::EditRole);

    void loadPhoneNumbers(std::vector<Address>& addr);
    void loadPhoneNumbers();

private:
    std::vector<Address> address;
};

#endif // ADDRESLISTVIEW_H
