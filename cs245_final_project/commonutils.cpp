#include "commonutils.h"

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

            //Should figure out how to update the QTListView objects with this user's(i) data
            //TODO:

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
    QLineEdit *lineEdit;
    int argCntr = 0;


    for(auto i : fieldNames){
        lineEdit = new QLineEdit(&dialog);
        QString label =  QString(QString::fromStdString(i + ":")).arg(argCntr);
        form.addRow(label, lineEdit);
        fields << lineEdit;

        argCntr++;
    }

    // Add some standard buttons (Cancel/Ok) at the bottom of the dialog
    QDialogButtonBox buttonBox(QDialogButtonBox::Ok | QDialogButtonBox::Cancel,
                               Qt::Horizontal, &dialog);
    form.addRow(&buttonBox);
    QObject::connect(&buttonBox, SIGNAL(accepted()), &dialog, SLOT(accept()));
    QObject::connect(&buttonBox, SIGNAL(rejected()), &dialog, SLOT(reject()));


    // Show the dialog as modal
    if (dialog.exec() == QDialog::Accepted) {
        // If the user didn't dismiss the dialog, do something with the fields
        size_t j = 0;
        for(auto i : fields){
            returnMap[fieldNames[j]] = i->text().toStdString();
            j++;
        }
    }

    return returnMap;
}
