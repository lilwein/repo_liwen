#ifndef OPENCV_UTILS_H
#define OPENCV_UTILS_H
#include <opencv2/opencv.hpp>
#include "../image.h"

cv::Mat imageToMat(const Image& img);
void drawDesc(cv::Mat& img, vector<Descriptor>& desc);
void drawMatch(cv::Mat& img, vector<Match>& matches, int x_offset, cv::Scalar color);

#endif