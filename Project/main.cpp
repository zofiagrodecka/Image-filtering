#include <iostream>
#define CVUI_IMPLEMENTATION
#define MAX_FILENAME 500
#include "MainWindow.h"
#include "SaveDialogWindow.h"

using namespace std;

class Main{
public:
    static int load_file(int argc, char **argv) {

        QApplication app(argc, argv);
        string filename;
        FileExplorer fileExplorer;


        filename = fileExplorer.open_file();


        if(!filename.empty()){
            MainWindow window = MainWindow(filename);
            cv::Mat image = window.show();

            string directory = fileExplorer.get_directory();
            cout << "dir: " << directory << endl;
            if(!directory.empty()){
                SaveDialogWindow save_window;
                string name = save_window.display();
                if(!name.empty()){
                    cout << directory + "/" + name << endl;
                    cv::imwrite(directory + "/" + name, image);
                }
                else{
                    perror("Cannot save image");
                    return 1;
                }
            }
            else{
                perror("Cannot save image");
                return 1;
            }

        }
        else{
            perror("You have to choose an image to proceed");
            return 1;
        }

        return 0;

    }
};

int main(int argc, char *argv[])
{
    Main mainApp;
    return mainApp.load_file(argc, argv);
}


