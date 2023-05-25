#include <opencv2/opencv.hpp>
#include "../image.h"
#include "./opencv_utils.h"

// gaussian for harris corner detector. Typical: 2
float sigma{2.0};
int sigma_bar{20};

// Corner method (0 by default, the others are not implemented yet)
int corner_method{0};

// Threshold for corner/no corner. Typical: 0.1-0.5
float thresh{0.4};
int thresh_bar{4};

// Window size corner detection
int window{7};

// window to perform nms on. Typical: 3
int nms_dist{3};

// Inlier_thresh: threshold for RANSAC inliers. Typical: 2-5
float in_thresh{5.0};
int in_thresh_bar{50};

// Number of RANSAC iterations. Typical: 1,000-50,000
int iters{1000};

// RANSAC inlier cutoff. Typical: 10-100
int cutoff{50};

cv::Mat cv_img;
Image image1;
Image image2;

void panorama_demo(){
    Image pan=panorama_image(image1, image2, sigma, corner_method, thresh, window, nms_dist, in_thresh, iters, cutoff, 0.5);
    cv::Mat mat = imageToMat(pan);
    cv::imshow("Panorama", mat);
}

static void cutoff_trackbar( int, void* )
{
    panorama_demo();
}

static void iters_trackbar( int, void* )
{
    panorama_demo();
}


static void in_thresh_trackbar( int, void* )
{
    in_thresh = (float) in_thresh_bar/10.0;
    panorama_demo();
}

static void nms_dist_trackbar( int, void* )
{
    panorama_demo();
}

static void window_trackbar( int, void* )
{
    panorama_demo();
}

static void sigma_trackbar( int, void* )
{
    sigma = (float) sigma_bar/10.0;
    panorama_demo();
}

static void thresh_trackbar( int, void* )
{
    thresh = (float) thresh_bar/10.0;
    panorama_demo();
}

int main(){
    string file1="pano/rainier/Rainier1.png";
    string file2="pano/rainier/Rainier2.png";
    image1=load_image(file1);
    image2=load_image(file2);
    Image pan=panorama_image(image1, image2, sigma, corner_method, thresh, window, nms_dist, in_thresh, iters, cutoff, 0.5);
    cv::Mat mat = imageToMat(pan);

    // Trackbar for sigma std. deviation Harris Corner detector
    char TrackbarNameSigma[50];
    sprintf(TrackbarNameSigma, "Std. Deviation (Sigma) * 10");
    cv::createTrackbar(TrackbarNameSigma, "Panorama", &sigma_bar, 40, sigma_trackbar);
    sigma_trackbar(sigma, 0);

    // Trackbar for sigma cornerness threshold
    char TrackbarNameThresh[50];
    sprintf( TrackbarNameThresh, "Cornerness threshold * 10");
    cv::createTrackbar(TrackbarNameThresh, "Panorama", &thresh_bar, 10, thresh_trackbar);
    thresh_trackbar(thresh, 0);

    // Trackbar for window size of corner detection
    char TrackbarNamewindow[50];
    sprintf( TrackbarNamewindow, "Window Size");
    cv::createTrackbar(TrackbarNamewindow, "Panorama", &window, 10, window_trackbar);
    window_trackbar(window, 0);

    // Trackbar for distance window for non-maxima-suppression
    char TrackbarNameNms[50];
    sprintf( TrackbarNameNms, "Nms Distance");
    cv::createTrackbar(TrackbarNameNms, "Panorama", &nms_dist, 10, nms_dist_trackbar);
    nms_dist_trackbar(nms_dist, 0);

    // Trackbar for inliers threshold
    char TrackbarNameInThresh[50];
    sprintf( TrackbarNameInThresh, "Inliers threshold * 10");
    cv::createTrackbar(TrackbarNameInThresh, "Panorama", &in_thresh_bar, 100, in_thresh_trackbar);
    in_thresh_trackbar(in_thresh, 0);

    // Trackbar for RANSAC iterations
    char TrackbarNameIters[50];
    sprintf( TrackbarNameIters, "RANSAC iterations");
    cv::createTrackbar(TrackbarNameIters, "Panorama", &iters, 50000, iters_trackbar);
    iters_trackbar(iters, 0);

    // Trackbar for RANSAC inliers threshold
    char TrackbarNameCutoff[50];
    sprintf( TrackbarNameCutoff, "RANSAC threshold");
    cv::createTrackbar(TrackbarNameCutoff, "Panorama", &cutoff, 100, cutoff_trackbar);
    cutoff_trackbar(cutoff, 0);

    cv::namedWindow("Panorama", cv::WINDOW_NORMAL);

    cv::waitKey(0);
    return 0;
}