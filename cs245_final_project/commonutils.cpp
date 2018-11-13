#include "commonutils.h"

CommonUtils::CommonUtils()
{

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
