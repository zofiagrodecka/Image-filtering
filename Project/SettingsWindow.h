#ifndef PROJECT_SETTINGSWINDOW_H
#define PROJECT_SETTINGSWINDOW_H

#include "Image.h"
#include "cvui.h"

class SettingsWindow {

public:
    SettingsWindow(const char *window_name, const char *image_path) : name(window_name), image(image_path)
    {
        cvui::init(window_name);
        frame = cv::Mat(cv::Size(image.getWidth()+200, image.getHeight()+200), CV_8UC3);
        frame = cv::Scalar(49, 52, 49);
    };

    void show();

private:
    const char * name;
    Image image;
    cv::Mat frame;

};


#endif //PROJECT_SETTINGSWINDOW_H
