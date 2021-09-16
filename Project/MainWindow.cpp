#include <QFileDialog>
#include <QInputDialog>
#include "MainWindow.h"
#include "opencv2/core/core.hpp"
#include "opencv2/opencv.hpp"
#include "opencv2/highgui/highgui.hpp"
#include "cvui.h"

using namespace std;

cv::Mat MainWindow::show() {
    while(window_open){

        frame = cv::Mat(cv::Size(image.getWidth()+500, max(image.getHeight(), 1010)+130), CV_8UC3);
        frame = cv::Scalar(49, 52, 49);

        mouse_status = cvui::iarea(image.getWidth()+20, 250, 450, 425);

        if(cvui::button(frame, 10, 10, "Reset")){
            image.reset();
            displayed_image = image.get_image();
        }

        if(cvui::button(frame, 100, 10, "Sepia")){
            image.sepia();
            displayed_image = image.get_image();
        }

        if(cvui::button(frame, 200, 10, "Invert")){
            displayed_image = image.invert();
        }

        if(cvui::button(frame, 300, 10, "Blur")){
            image.blur();
            displayed_image = image.get_image();
        }

        if(cvui::button(frame, 400, 10, "Grayscale")){
            displayed_image = image.grayscale();
        }

        if(cvui::button(frame, 700, 10, "Save")){
            window_open = false;
            cv::destroyAllWindows();
        }

        cvui::checkbox(frame, image.getWidth()+20, 50, "Apply 60's image filter", &show_noisy);
        cvui::text(frame, image.getWidth()+20, 80, "Noise amount:", 0.5);
        cvui::trackbar(frame, image.getWidth()+20, 110, 450, &noise, 0, 255);
        cvui::text(frame, image.getWidth()+20, 185, "Threshold value:", 0.5);
        cvui::trackbar(frame, image.getWidth()+20, 210, 450, &threshold, 0, 255);

        cvui::checkbox(frame, image.getWidth()+20, 785, "Black", colors[0]);
        cvui::checkbox(frame, image.getWidth()+20, 810, "White", colors[1]);
        cvui::checkbox(frame, image.getWidth()+20, 835, "Dark red", colors[2]);
        cvui::checkbox(frame, image.getWidth()+20, 860, "Light red", colors[3]);
        cvui::checkbox(frame, image.getWidth()+20, 885, "Green", colors[4]);
        cvui::checkbox(frame, image.getWidth()+20, 910, "Blue", colors[5]);
        cvui::checkbox(frame, image.getWidth()+20, 935, "Yellow", colors[6]);
        cvui::checkbox(frame, image.getWidth()+20, 960, "Purple", colors[7]);
        cvui::checkbox(frame, image.getWidth()+20, 985, "Orange", colors[8]);
        cvui::checkbox(frame, image.getWidth()+20, 1010, "Gray", colors[9]);

        update_window();

        cvui::text(frame, image.getWidth()+20, 285, "One color filter:", 0.5);
        cvui::text(frame, image.getWidth()+20, 315, "H lower bound:");
        cvui::trackbar(frame, image.getWidth()+20, 335, 450, &h_min, 0, 255);
        cvui::text(frame, image.getWidth()+20, 390, "H upper bound:");
        cvui::trackbar(frame, image.getWidth()+20, 410, 450, &h_max, 0, 255);
        cvui::text(frame, image.getWidth()+20, 465, "S lower bound:");
        cvui::trackbar(frame, image.getWidth()+20, 485, 450, &s_min, 0, 255);
        cvui::text(frame, image.getWidth()+20, 540, "S upper bound:");
        cvui::trackbar(frame, image.getWidth()+20, 560, 450, &s_max, 0, 255);
        cvui::text(frame, image.getWidth()+20, 615, "V lower bound:");
        cvui::trackbar(frame, image.getWidth()+20, 635, 450, &v_min, 0, 255);
        cvui::text(frame, image.getWidth()+20, 690, "V upper bound:");
        cvui::trackbar(frame, image.getWidth()+20, 710, 450, &v_max, 0, 255);

        if(v_max < v_min){
            v_max = v_min;
        }

        if(h_max < h_min){
            h_max = h_min;
        }

        if(s_max < s_min){
            s_max = s_min;
        }

        if(has_image){
            cv::Mat img = displayed_image;
            cvui::image(frame, 0, 50, img);
        }

        cvui::imshow(window_name, frame);
        if (cv::waitKey(20) == 27) {
            break;
        }

        try {

            if (cv::getWindowProperty(window_name, 0) < 0) {
                cv::destroyAllWindows();
                window_open = false;
            }

        } catch(cv::Exception &exception){ // nie zamyka okien settingsow
            cout << "App closed" << endl;
            window_open = false;
            cv::destroyAllWindows();
        }
    }
    return displayed_image;
}

void MainWindow::update_window() {

    if(mouse_status == cvui::CLICK || mouse_status == cvui::DOWN){
        one_color = true;
    }
    else{
        if(counter == 0){
            one_color = false;
        }
    }

    if(show_noisy){
        displayed_image = image.noisy_threshold(noise, threshold);
    }

    for(int i=0; i<n_colors; i++){
        counter = 0;
        if(*colors[i]){
            counter ++;
            one_color = true;
            index_to_color(i);
        }
    }

    if(one_color){
        displayed_image = image.only1color(h_min, h_max, s_min, s_max, v_min, v_max);
    }
}

void MainWindow::index_to_color(int index) {
    switch(index){
        case 0:
            h_max = 180;
            s_max = 255;
            v_max = 30;
            h_min = 0;
            s_min = 0;
            v_min = 0;
            break;
        case 1:
            h_max = 180;
            s_max = 28;
            v_max = 255;
            h_min = 0;
            s_min = 0;
            v_min = 231;
            break;
        case 2:
            h_max = 180;
            s_max = 255;
            v_max = 255;
            h_min = 159;
            s_min = 50;
            v_min = 70;
            break;
        case 3:
            h_max = 9;
            s_max = 255;
            v_max = 255;
            h_min = 0;
            s_min = 50;
            v_min = 70;
            break;
        case 4:
            h_max = 89;
            s_max = 255;
            v_max = 255;
            h_min = 36;
            s_min = 50;
            v_min = 70;
            break;
        case 5:
            h_max = 128;
            s_max = 255;
            v_max = 255;
            h_min = 90;
            s_min = 50;
            v_min = 70;
            break;
        case 6:
            h_max = 35;
            s_max = 255;
            v_max = 255;
            h_min = 25;
            s_min = 50;
            v_min = 70;
            break;
        case 7:
            h_max = 158;
            s_max = 255;
            v_max = 255;
            h_min = 129;
            s_min = 50;
            v_min = 70;
            break;
        case 8:
            h_max = 24;
            s_max = 255;
            v_max = 255;
            h_min = 10;
            s_min = 50;
            v_min = 70;
            break;
        case 9:
            h_max = 180;
            s_max = 18;
            v_max = 230;
            h_min = 0;
            s_min = 0;
            v_min = 40;
            break;
    }
}


