#include "Image.h"
#include "opencv2/core/core.hpp"
#include "opencv2/opencv.hpp"
#include "opencv2/highgui/highgui.hpp"

using namespace std;

Image::Image(string path) {
    this->path = path;
    this->image = cv::imread(path);
    if(image.empty()){
        perror("Cannot read image");
        exit(1);
    }
    this->original = image.clone();
    this->width = image.size().width;
    this->height = image.size().height;
    this->n_channels = image.channels();
    cv::Mat channels[3];
    this->H = channels[0];
    this->S = channels[1];
    this->V = channels[2];
    cv::cvtColor(image, inverted, cv::COLOR_RGB2BGR);
    cv::cvtColor(image, gray, cv::COLOR_BGR2GRAY);
    cv::cvtColor(gray, gray, cv::COLOR_GRAY2BGR);
    cout << "W: " << width << " h: " << height << endl;
}

Image::Image(const Image &other) {
    this->path = other.path;
    this->image = cv::imread(path);
    this->width = image.size().width;
    this->height = image.size().height;
    this->n_channels = image.channels();
    cv::Mat channels[3];
    this->H = channels[0];
    this->S = channels[1];
    this->V = channels[2];
    cv::cvtColor(image, inverted, cv::COLOR_BGR2GRAY);
    cv::cvtColor(image, gray, cv::COLOR_BGR2GRAY);
    cv::cvtColor(gray, gray, cv::COLOR_GRAY2BGR);
}

string Image::getPath() const{
    return path;
}

cv::Mat Image::get_image() {
    return image;
}

int Image::getWidth() const {
    return width;
}

int Image::getHeight() const {
    return height;
}

void Image::reset() {
    image = original;
}

cv::Mat Image::invert() {
    return inverted;
}

cv::Mat Image::grayscale() {
    return gray;
}

void Image::sepia() {
    image = original;
    cv::Mat result = image.clone();
    cv::cvtColor(result, result, cv::COLOR_BGR2RGB);
    cv::transform(result, result, cv::Matx33f(0.393, 0.769, 0.189, 0.349, 0.686, 0.168, 0.272, 0.534, 0.131));
    cv::cvtColor(result, result, cv::COLOR_RGB2BGR);
    image = result;
}

cv::Mat Image::noisy_threshold(int max_val, int threshold) { // val thresh
    image = original;
    cv::Mat copy = image.clone();
    cv::cvtColor(image, copy, cv::COLOR_BGR2GRAY);

    for (int i=0; i < height; i++){
        for (int j=0; j < width; j++){
            if (rand()%100 <= threshold){
                if (rand()%2 == 0) {
                    copy.at<uchar>(i, j) = std::min(copy.at<uchar>(i, j) + rand() % ((int) max_val + 1), 255);
                }
                else {
                    copy.at<uchar>(i, j) = std::max(copy.at<uchar>(i, j) - rand() % ((int) max_val + 1), 0);
                }
            }
        }
    }

    cv::cvtColor(copy, noisy, cv::COLOR_GRAY2BGR);
    return noisy;
}

void Image::blur() {
    image = original;
    cv::Mat blurred;
    cv::GaussianBlur(image, blurred, cv::Size(31,31), 0);
    image = blurred;
}

cv::Mat Image::only1color(int h_min, int h_max, int s_min, int s_max, int v_min, int v_max) {
    image = original;
    cv::Mat result;

    cv::Mat color_result;
    cv::Mat color_mask;
    cv::Mat hsv;
    cv::cvtColor(image, hsv, cv::COLOR_BGR2HSV);

    //extracting red colors, rest is black
    cv::inRange(hsv, cv::Scalar(h_min, s_min, v_min), cv::Scalar(h_max, s_max, v_max), color_mask);
    cv::bitwise_and(image, image, color_result, color_mask);

    // extracting grey
    cv::Mat gray_mask;
    cv::Mat inv_gray_mask;
    cv::Mat gray_hsv;
    cv::Mat gray_result;
    cv::cvtColor(image, gray_hsv, cv::COLOR_BGR2GRAY);
    cv::bitwise_not(color_mask, gray_mask);
    cv::bitwise_and(gray_hsv, gray_hsv, gray_result, gray_mask);

    cv::cvtColor(gray_result, gray_result, cv::COLOR_GRAY2BGR);
    cv::add(color_result, gray_result, result);
    return result;
}

