#include "SaveDialogWindow.h"
#include <QWidget>
#include <QInputDialog>
#include <QDir>
#include <iostream>

using namespace std;

string SaveDialogWindow::display() {
    bool ok;
    QString filename = QInputDialog::getText(this, "Save file", "Type file name to be saved:",
                                             QLineEdit::Normal, QDir::home().dirName(), &ok);
    if(ok && !filename.isEmpty()){
        QByteArray ba = filename.toLocal8Bit();
        char *str = ba.data();
        cout << str << endl;
        return filename.toStdString();
    }
    return "";
}
