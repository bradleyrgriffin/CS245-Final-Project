#ifndef EMAILLISTVIEW_H
#define EMAILLISTVIEW_H

#include <QAbstractListModel>
#include "email.h"

class EmailListView : public QAbstractListModel
{
    Q_OBJECT

public:
    explicit EmailListView(std::vector<Email>& email, QObject *parent = nullptr);

    virtual bool setData(const QModelIndex & index, const QVariant & value, int role = Qt::EditRole);
    // Basic functionality:
    int rowCount(const QModelIndex &parent = QModelIndex()) const override;

    QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const override;

    void loadPhoneNumbers(std::vector<Email>& email);
    void loadPhoneNumbers();

private:
    std::vector<Email> emails;
};

#endif // EMAILLISTVIEW_H
