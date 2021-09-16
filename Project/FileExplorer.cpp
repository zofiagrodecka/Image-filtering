#include "FileExplorer.h"
#include <QWidget>
#include <QFileDialog>
#include <iostream>
using namespace std;

string FileExplorer::open_file() {
    QString filename = QFileDialog::getOpenFileName(this, "Open image", "../",
                                                    "All files (*.*) ;; Image files (*.png *.jpg *.jpeg *.bmp");

    if(!filename.isNull()){
        return filename.toStdString();
    }
    return "";
}

string FileExplorer::get_directory() {
    QString dirname = QFileDialog::getExistingDirectory(this, "Open directory", "/home",
                                                   QFileDialog::ShowDirsOnly | QFileDialog::DontResolveSymlinks);

    if(!dirname.isNull()){
        return dirname.toStdString();
    }
    return "";
}
