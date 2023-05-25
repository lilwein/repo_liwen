#include <opencv2/opencv.hpp>
#include "../image.h"
#include "opencv_utils.h"

// Convert the Image struct to a cv::Mat
cv::Mat imageToMat(const Image& img) {
    // Create a CV_8UC3 Mat object with the same size as the Image struct
    cv::Mat mat(img.h, img.w, CV_8UC3);

    
    // Convert from RGB to BGR (OpenCV format)
    for(int i=0; i<img.w; i++)for(int j=0; j<img.h; j++){
        mat.at<cv::Vec3b>(j, i)[0] = img(i, j, 2)*255;
        mat.at<cv::Vec3b>(j, i)[1] = img(i, j, 1)*255;
        mat.at<cv::Vec3b>(j, i)[2] = img(i, j, 0)*255;
    }

    return mat;
}

void drawDesc(cv::Mat& img, vector<Descriptor>& desc){
    for(int i=0; i<desc.size(); i++){
        cv::Point pt{desc[i].p.x, desc[i].p.y};
        cv::circle(img, pt, 1, cv::Scalar(255, 0, 255), 4, 8, 0);
    }
    
}

void drawMatch(cv::Mat& img, vector<Match>& matches, int x_offset, cv::Scalar color){
    for(int i=0; i<matches.size(); i++){
        cv::Point pt_a{matches[i].a->p.x, matches[i].a->p.y};
        cv::Point pt_b{matches[i].b->p.x+x_offset, matches[i].b->p.y};
        cv::line(img, pt_a, pt_b, color);
    }
    
}