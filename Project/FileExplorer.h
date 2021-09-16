#ifndef PROJECT_FILEEXPLORER_H
#define PROJECT_FILEEXPLORER_H

#include <QWidget>

using namespace std;

class FileExplorer : public QWidget {
public:
    string open_file();
    string get_directory();
};


#endif //PROJECT_FILEEXPLORER_H
