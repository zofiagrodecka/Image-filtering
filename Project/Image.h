#ifndef PROJECT_IMAGE_H
#define PROJECT_IMAGE_H

#include <cstring>
#include "opencv2/core/core.hpp"
#include "opencv2/opencv.hpp"
#include "opencv2/highgui/highgui.hpp"

using namespace std;

class Image {
public:

    Image(string path);
    Image(const Image &other);
    string getPath() const;
    cv::Mat get_image();
    int getWidth() const;
    int getHeight() const;

    void reset();
    void sepia();
    cv::Mat invert();
    cv::Mat grayscale();
    void blur();
    cv::Mat noisy_threshold(int max_val, int threshold);
    cv::Mat only1color(int h_min=0, int h_max=330, int s_min=80, int s_max=255, int v_min=80, int v_max=255);

private:
    string path;
    cv::Mat image;
    cv::Mat original;
    int height;
    int width;
    int n_channels;
    cv::Mat H;
    cv::Mat S;
    cv::Mat V;
    cv::Mat inverted;
    cv::Mat gray;
    cv::Mat noisy;
};


#endif //PROJECT_IMAGE_H
