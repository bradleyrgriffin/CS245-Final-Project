#ifndef GROUPLISTVIEW_H
#define GROUPLISTVIEW_H

#include <QAbstractListModel>
#include "group.h"

class GroupListView : public QAbstractListModel
{
    Q_OBJECT

public:
    explicit GroupListView(std::vector<Group>& group, QObject *parent = nullptr);

     virtual bool setData(const QModelIndex & index, const QVariant & value, int role = Qt::EditRole);
    // Basic functionality:
    int rowCount(const QModelIndex &parent = QModelIndex()) const override;

    QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const override;

    void loadPhoneNumbers(std::vector<Group>& phns);
    void loadPhoneNumbers();

private:
    std::vector<Group> groups;
};

#endif // GROUPLISTVIEW_H
