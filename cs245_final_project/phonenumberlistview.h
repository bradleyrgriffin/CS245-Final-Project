#ifndef PHONENUMBERLISTVIEW_H
#define PHONENUMBERLISTVIEW_H

#include <QAbstractListModel>
#include <vector>
#include "phone.h"
#include <string>

class PhoneNumberListView : public QAbstractListModel
{
    Q_OBJECT

public:
    explicit PhoneNumberListView(std::vector<Phone>& phones, QObject *parent = nullptr);

    // Basic functionality:
    int rowCount(const QModelIndex &parent = QModelIndex()) const override;

    virtual bool setData(const QModelIndex & index, const QVariant & value, int role = Qt::EditRole);

    QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const override;

    void loadPhoneNumbers(std::vector<Phone> phns);

private:
    std::vector<Phone> phones;

public slots:

signals:

};

#endif // PHONENUMBERLISTVIEW_H
