#include "commonutils.h"
#include "group.h"

CommonUtils::CommonUtils()
{

}

void CommonUtils::displayProfilePicture(MainWindow* thing, const string& photo){


    string path = "..\\cs245_final_project\\photos\\" + photo;
    QPixmap pix(QString::fromStdString(path));
    thing->ui->profilePicture->setPixmap(pix);

}

void CommonUtils::displayData(MainWindow* thing){
    int id = stoi(thing->ui->contactId->text().toStdString());
    for(auto& i : thing->data.getContacts()){
        if(i.getContactId() == id){
            thing->ui->firstName->setText(QString::fromStdString(i.getFirstName()));
            thing->ui->lastName->setText(QString::fromStdString(i.getLastName()));
            displayProfilePicture(thing, thing->data.getPhotoById(i.getPhotoId()).getPhotoPath());
            for(auto& j : i.getPhoneNumbers()){
                int catId = j.getCategoryID();
                j.displayName = j.getPhoneNumber() + "/ " + thing->data.getCategoryById(catId).getCategoryName();
            }
            for(auto& j : i.getAddresses()){
                int catId = j.getCategoryId();
                j.displayName = j.getAddress() + "/ " + j.getCity() + "/ " +thing->data.getCategoryById(catId).getCategoryName();
            }
            for(auto& j : i.getEmails()){
                int catId = j.getCategoryId();
                j.displayName = j.getEmailName() + "/ " + thing->data.getCategoryById(catId).getCategoryName();
            }

            vector<Group> fakeGroups;
            for(auto& j : i.getGroupIds()){
                Group g = thing->data.getGroupById(j);
                g.displayName = g.getGroupName();
                fakeGroups.push_back(g);
            }

            thing->phoneListModel->loadPhoneNumbers(i.getPhoneNumbers());
            thing->addressListModel->loadPhoneNumbers(i.getAddresses());
            thing->emailListModel->loadPhoneNumbers(i.getEmails());
            thing->groupListModel->loadPhoneNumbers(fakeGroups);

        }
    }
}

void CommonUtils::toggleContactIdButtons(MainWindow* thing){
    bool toggle = false;

    try {
        int id = stoi(thing->ui->contactId->text().toStdString());
        for(auto& i : thing->data.getContacts()){
            if(i.getContactId() == id){
                toggle = true;
                break;
            }
        }
    } catch (exception& e) {
        toggle = false;
    }

    if(toggle){
        cout << "Enabling Contact Buttons" << endl;
        enableBtn(thing->ui->updateContactButton);
        enableBtn(thing->ui->addGroupButton_2);
        enableBtn(thing->ui->addAddressButton);
        enableBtn(thing->ui->addEmailButton);
        enableBtn(thing->ui->addPhoneButton);
        enableBtn(thing->ui->deleteContactButton);
        enableBtn(thing->ui->deleteAddressButton);
        enableBtn(thing->ui->deleteEmailButton);
        enableBtn(thing->ui->deleteGroupButton);
        enableBtn(thing->ui->deletePhoneButton);
        displayData(thing);
    }else{
        thing->ui->contactId->setText("");
        thing->ui->firstName->setText("");
        thing->ui->lastName->setText("");
        thing->phoneListModel->loadPhoneNumbers();
        thing->addressListModel->loadPhoneNumbers();
        thing->emailListModel->loadPhoneNumbers();
        thing->groupListModel->loadPhoneNumbers();
        QPixmap pix(QString::fromStdString("clear"));
        thing->ui->profilePicture->setPixmap(pix);

        cout << "Disabling Contact Buttons" << endl;
        disableBtn(thing->ui->updateContactButton);
        disableBtn(thing->ui->addGroupButton_2);
        disableBtn(thing->ui->addAddressButton);
        disableBtn(thing->ui->addEmailButton);
        disableBtn(thing->ui->addPhoneButton);
        disableBtn(thing->ui->deleteContactButton);
        disableBtn(thing->ui->deleteAddressButton);
        disableBtn(thing->ui->deleteEmailButton);
        disableBtn(thing->ui->deleteGroupButton);
        disableBtn(thing->ui->deletePhoneButton);
    }
}
void CommonUtils::disableBtn(QPushButton* btn){
    btn->setEnabled(false);
}


void CommonUtils::enableBtn(QPushButton* btn){
    btn->setEnabled(true);
}

bool CommonUtils::validateFields(map<string, string>& data, MainWindow* thing){
    for(auto& i : data){
        if(i.second == ""){
            cout << "Invalid Data in Fields" << endl;
            return false;
        }else if(i.first == "Group"){
            try {
                int id = stoi(i.second);

            } catch (exception& e) {
                cout << "Invalid Data in Fields" << endl;
                return false;
            }
        }else if(i.first == "Category"){
            try {
                int id = stoi(i.second);
            } catch (exception& e) {
                cout << "Invalid Data in Fields" << endl;
                return false;
            }
        }else if (i.first == "Photo"){
            try {
                int id = stoi(i.second);
            } catch (exception& e) {
                cout << "Invalid Data in Fields" << endl;
                return false;
            }
        }
    }

    return true;
}

//This function should take in "this" window, and a vector of labels. This will generate a dialog box, with line-edits,
//and the attached labels, and will return a map of the labels passed in, and the values retrieved.
map<string, string> CommonUtils::dialogPrompt(MainWindow * thisPtr, vector<string> fieldNames){
    //ReturnMap
    map<string, string> returnMap;

    QDialog dialog(thisPtr);

    // Use a layout allowing to have a label next to each field
    QFormLayout form(&dialog);

    // Add some text above the fields
    form.addRow(new QLabel("Enter Information:"));

    // Add the lineEdits with their respective labels
    QList<QLineEdit *> fields;
    QList<QComboBox *> dd;
    QLineEdit *lineEdit;
    int argCntr = 0;


    for(auto i : fieldNames){
        if(i == "Category" || i == "Group" || i == "Photo"){
            //To Maintain Index positions... Removed adding it to the box though

            fields << new QLineEdit();

            QString label =  QString(QString::fromStdString(i + ":")).arg(argCntr);


            if(i == "Group"){
                QComboBox* groupCombo = new QComboBox(thisPtr);
                QListView* groupView = new QListView(groupCombo);
                for(auto& i : thisPtr->data.getGroups()){
                    groupCombo->addItem(QString::fromStdString(to_string(i.getGroupId()) + "/" + i.getGroupName()));
                }
                groupView->setStyleSheet("QListView::item {                              \
                                             border-bottom: 5px solid white; margin:3px; }  \
                                             QListView::item:selected {                     \
                                             border-bottom: 5px solid black; margin:3px;    \
                                             color: black;                                  \
                                            }                                               \
                                            ");
                groupCombo->setView(groupView);

                form.addRow(label, groupCombo);
                dd << groupCombo;
            }else if(i == "Category"){
                QComboBox* categoryCombo = new QComboBox(thisPtr);
                QListView* groupView = new QListView(categoryCombo);
                for(auto& i : thisPtr->data.getCategories()){
                    categoryCombo->addItem(QString::fromStdString(to_string(i.getCategoryId()) + "/" + i.getCategoryName()));
                }
                groupView->setStyleSheet("QListView::item {                              \
                                             border-bottom: 5px solid white; margin:3px; }  \
                                             QListView::item:selected {                     \
                                             border-bottom: 5px solid black; margin:3px;    \
                                             color: black;                                  \
                                            }                                               \
                                            ");
                categoryCombo->setView(groupView);

                form.addRow(label, categoryCombo);
                dd << categoryCombo;
            }else if(i == "Photo"){
                    QComboBox* photoCombo = new QComboBox(thisPtr);
                    QListView* groupView = new QListView(photoCombo);
                    for(auto& i : thisPtr->data.getPhotos()){
                        photoCombo->addItem(QString::fromStdString(to_string(i.getPhotoId()) + "/" + i.getPhotoPath()));
                    }
                    groupView->setStyleSheet("QListView::item {                              \
                                                 border-bottom: 5px solid white; margin:3px; }  \
                                                 QListView::item:selected {                     \
                                                 border-bottom: 5px solid black; margin:3px;    \
                                                 color: black;                                  \
                                                }                                               \
                                                ");
                    photoCombo->setView(groupView);

                    form.addRow(label, photoCombo);
                    dd << photoCombo;
            }
        }else{
            lineEdit = new QLineEdit(&dialog);
            QString label =  QString(QString::fromStdString(i + ":")).arg(argCntr);
            form.addRow(label, lineEdit);
            fields << lineEdit;
        }


        argCntr++;
    }

    // Add some standard buttons (Cancel/Ok) at the bottom of the dialog
    QDialogButtonBox buttonBox(QDialogButtonBox::Ok | QDialogButtonBox::Cancel,
                               Qt::Horizontal, &dialog);
    form.addRow(&buttonBox);
    QObject::connect(&buttonBox, SIGNAL(accepted()), &dialog, SLOT(accept()));
    QObject::connect(&buttonBox, SIGNAL(rejected()), &dialog, SLOT(reject()));


    int cmbnum = 0;
    int lndt = 0;
    // Show the dialog as modal
    if (dialog.exec() == QDialog::Accepted) {
        // If the user didn't dismiss the dialog, do something with the fields
        for(int j = 0; j < argCntr; j++){
            if(fieldNames[j] == "Group" || fieldNames[j] == "Category" || fieldNames[j] == "Photo"){
                returnMap[fieldNames[j]] = dd[cmbnum]->currentText().toStdString();
                cmbnum++;
            }else{
                returnMap[fieldNames[j]] = fields[lndt]->text().toStdString();
                lndt++;
            }
    }

    }

    return returnMap;
}

string CommonUtils::substringStr(const string& s){
    std::string::size_type pos = s.find('/');
        if (pos != std::string::npos)
        {
            return s.substr(0, pos);
        }
        else
        {
            return s;
        }
}
