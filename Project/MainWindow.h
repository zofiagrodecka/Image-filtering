#ifndef PROJECT_MAINWINDOW_H
#define PROJECT_MAINWINDOW_H

#include <QApplication>
#include <utility>
#include "opencv2/core/core.hpp"
#include "opencv2/opencv.hpp"
#include "opencv2/highgui/highgui.hpp"
#include "opencv2/imgproc.hpp"
#include "Image.h"
#include "opencv2/highgui.hpp"
#include "cvui.h"
#include "FileExplorer.h"

class MainWindow{

public:
    MainWindow(string image_path) : image(std::move(image_path))
    {
        has_image = true;
        cvui::init(window_name);
        displayed_image = image.get_image();

        for(int i=0; i<n_colors; i++){
            colors[i] = new bool[1];
            *colors[i] = false;
        }
    };

    cv::Mat show();
    void update_window();
    void index_to_color(int index);

private:
    const char *window_name = "Insta-filter";
    cv::Mat frame;
    Image image;
    bool has_image = false;
    bool window_open = true;
    cv::Mat displayed_image;
    int noise = 0;
    int threshold = 0;
    int h_min = 0;
    int h_max = 0;
    int s_min = 0;
    int s_max = 0;
    int v_min = 0;
    int v_max = 0;
    bool show_noisy = false;
    bool one_color = false;
    int mouse_status;
    int counter = 0;
    static const int n_colors = 10;
    bool **colors = new bool* [n_colors];
};


#endif //PROJECT_MAINWINDOW_H
