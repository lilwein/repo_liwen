#include <opencv2/opencv.hpp>
#include "../image.h"
#include "./opencv_utils.h"

// Standard deviation for Harris Corner detector
float sigma{2.0};
int sigma_bar{20};

// Cornerness threshold
float thresh{0.4};
int thresh_bar{4};

// Window size corner detection
int window{5};

// Distance window for non-maxima-suppression
int nms_dist{3};

int corner_method{0};

cv::Mat cv_img;
Image image;

vector<Descriptor> harris_demo(Image& img){
    Image structure;
    Image response;
    Image nms;
    vector<Descriptor> desc;
    structure = structure_matrix(img, sigma);
    response = cornerness_response(structure, corner_method);
    nms = nms_image(response, nms_dist);
    desc = detect_corners(img,nms,thresh,window);
    return desc;
}

static void nms_dist_trackbar( int, void* )
{
   vector<Descriptor> desc{harris_demo(image)};
   cv_img = imageToMat(image);
   drawDesc(cv_img, desc);
   cv::imshow("Harris Corner Detector", cv_img);
}

static void window_trackbar( int, void* )
{
   vector<Descriptor> desc{harris_demo(image)};
   cv_img = imageToMat(image);
   drawDesc(cv_img, desc);
   cv::imshow("Harris Corner Detector", cv_img);
}

static void sigma_trackbar( int, void* )
{
   sigma = (float) sigma_bar/10.0;
   vector<Descriptor> desc{harris_demo(image)};
   cv_img = imageToMat(image);
   drawDesc(cv_img, desc);
   cv::imshow("Harris Corner Detector", cv_img);
}

static void thresh_trackbar( int, void* )
{
   thresh = (float) thresh_bar/10.0;
   vector<Descriptor> desc{harris_demo(image)};
   cv_img = imageToMat(image);
   drawDesc(cv_img, desc);
   cv::imshow("Harris Corner Detector", cv_img);
}

int main(){
    string file="pano/rainier/Rainier1.png";
    image=load_image(file);

    cv_img = imageToMat(image);
    if ( !cv_img.data )
    {
        printf("No image data \n");
        return -1;
    }

    vector<Descriptor> desc{harris_demo(image)};
    drawDesc(cv_img, desc);
    cv::namedWindow("Harris Corner Detector", cv::WINDOW_NORMAL );

    // Trackbar for sigma std. deviation Harris Corner detector
    char TrackbarNameSigma[50];
    sprintf(TrackbarNameSigma, "Std. Deviation (Sigma) * 10");
    cv::createTrackbar(TrackbarNameSigma, "Harris Corner Detector", &sigma_bar, 40, sigma_trackbar);
    sigma_trackbar(sigma, 0);

    // Trackbar for sigma cornerness threshold
    char TrackbarNameThresh[50];
    sprintf( TrackbarNameThresh, "Cornerness threshold * 10");
    cv::createTrackbar(TrackbarNameThresh, "Harris Corner Detector", &thresh_bar, 10, thresh_trackbar);
    thresh_trackbar(thresh, 0);

    // Trackbar for window size of corner detection
    char TrackbarNamewindow[50];
    sprintf( TrackbarNamewindow, "Window Size");
    cv::createTrackbar(TrackbarNamewindow, "Harris Corner Detector", &window, 10, window_trackbar);
    window_trackbar(window, 0);

    // Trackbar for distance window for non-maxima-suppression
    char TrackbarNameNms[50];
    sprintf( TrackbarNameNms, "Nms Distance");
    cv::createTrackbar(TrackbarNameNms, "Harris Corner Detector", &nms_dist, 10, nms_dist_trackbar);
    nms_dist_trackbar(nms_dist, 0);
    
    cv::waitKey(0);

    return 0;
}