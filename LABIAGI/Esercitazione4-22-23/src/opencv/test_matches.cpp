#include <opencv2/opencv.hpp>
#include <tuple>
#include "../image.h"
#include "./opencv_utils.h"

// Standard deviation for Harris Corner detector
float sigma{2.0};
int sigma_bar{20};

// Cornerness threshold
float thresh{0.4};
int thresh_bar{4};

// Window size corner detection
int window{7};

// Distance window for non-maxima-suppression
int nms_dist{3};

int corner_method{0};

cv::Mat cv_img1;
cv::Mat cv_img2;
Image image1;
Image image2;
int offset;

std::tuple<vector<Descriptor>, vector<Descriptor>, vector<Match>> matches_demo(Image& img1, Image& img2){
    vector<Descriptor> desc1;
    vector<Descriptor> desc2;
    desc1 = harris_corner_detector(img1, sigma, thresh, window, nms_dist, corner_method);
    desc2 = harris_corner_detector(img2, sigma, thresh, window, nms_dist, corner_method);
    vector<Match> m = match_descriptors(desc1, desc2);
    return {desc1, desc2, m};
}

static void nms_dist_trackbar( int, void* )
{
   std::tuple<vector<Descriptor>, vector<Descriptor>, vector<Match>> descriptors{matches_demo(image1, image2)};
   cv_img1 = imageToMat(image1);
   cv_img2 = imageToMat(image2);
   drawDesc(cv_img1, std::get<0>(descriptors));
   drawDesc(cv_img2, std::get<1>(descriptors));
   cv::hconcat(cv_img1, cv_img2, cv_img1);
   drawMatch(cv_img1, std::get<2>(descriptors), offset, cv::Scalar(0, 0, 255));
   cv::imshow("Draw Matches", cv_img1);
}

static void window_trackbar( int, void* )
{
   std::tuple<vector<Descriptor>, vector<Descriptor>, vector<Match>> descriptors{matches_demo(image1, image2)};
   cv_img1 = imageToMat(image1);
   cv_img2 = imageToMat(image2);
   drawDesc(cv_img1, std::get<0>(descriptors));
   drawDesc(cv_img2, std::get<1>(descriptors));
   cv::hconcat(cv_img1, cv_img2, cv_img1);
   drawMatch(cv_img1, std::get<2>(descriptors), offset, cv::Scalar(0, 0, 255));
   cv::imshow("Draw Matches", cv_img1);
}

static void sigma_trackbar( int, void* )
{
   sigma = (float) sigma_bar/10.0;
   std::tuple<vector<Descriptor>, vector<Descriptor>, vector<Match>> descriptors{matches_demo(image1, image2)};
   cv_img1 = imageToMat(image1);
   cv_img2 = imageToMat(image2);
   drawDesc(cv_img1, std::get<0>(descriptors));
   drawDesc(cv_img2, std::get<1>(descriptors));
   cv::hconcat(cv_img1, cv_img2, cv_img1);
   drawMatch(cv_img1, std::get<2>(descriptors), offset, cv::Scalar(0, 0, 255));
   cv::imshow("Draw Matches", cv_img1);
}

static void thresh_trackbar( int, void* )
{
   thresh = (float) thresh_bar/10.0;
   std::tuple<vector<Descriptor>, vector<Descriptor>, vector<Match>> descriptors{matches_demo(image1, image2)};
   cv_img1 = imageToMat(image1);
   cv_img2 = imageToMat(image2);
   drawDesc(cv_img1, std::get<0>(descriptors));
   drawDesc(cv_img2, std::get<1>(descriptors));
   cv::hconcat(cv_img1, cv_img2, cv_img1);
   drawMatch(cv_img1, std::get<2>(descriptors), offset, cv::Scalar(0, 0, 255));
   cv::imshow("Draw Matches", cv_img1);
}

int main(){
    string file1="pano/rainier/Rainier1.png";
    string file2="pano/rainier/Rainier2.png";
    image1=load_image(file1);
    image2=load_image(file2);
    offset = image1.w;
    std::cout << "DIMENSIONE " << image1.w << std::endl;
    cv_img1 = imageToMat(image1);
    cv_img2 = imageToMat(image2);
    if ( !cv_img1.data || !cv_img2.data )
    {
        printf("No image data \n");
        return -1;
    }

    std::tuple<vector<Descriptor>, vector<Descriptor>, vector<Match>> descriptors{matches_demo(image1, image2)};
    drawDesc(cv_img1, std::get<0>(descriptors));
    drawDesc(cv_img2, std::get<1>(descriptors));
    cv::hconcat(cv_img1, cv_img2, cv_img1);
    drawMatch(cv_img1, std::get<2>(descriptors), offset, cv::Scalar(0, 0, 255));
    cv::namedWindow("Draw Matches", cv::WINDOW_NORMAL);

    // Trackbar for sigma std. deviation Harris Corner detector
    char TrackbarNameSigma[50];
    sprintf(TrackbarNameSigma, "Std. Deviation (Sigma) * 10");
    cv::createTrackbar(TrackbarNameSigma, "Draw Matches", &sigma_bar, 40, sigma_trackbar);
    sigma_trackbar(sigma, 0);

    // Trackbar for sigma cornerness threshold
    char TrackbarNameThresh[50];
    sprintf( TrackbarNameThresh, "Cornerness threshold * 10");
    cv::createTrackbar(TrackbarNameThresh, "Draw Matches", &thresh_bar, 10, thresh_trackbar);
    thresh_trackbar(thresh, 0);

    // Trackbar for window size of corner detection
    char TrackbarNamewindow[50];
    sprintf( TrackbarNamewindow, "Window Size");
    cv::createTrackbar(TrackbarNamewindow, "Draw Matches", &window, 10, window_trackbar);
    window_trackbar(window, 0);

    // Trackbar for distance window for non-maxima-suppression
    char TrackbarNameNms[50];
    sprintf( TrackbarNameNms, "Nms Distance");
    cv::createTrackbar(TrackbarNameNms, "Draw Matches", &nms_dist, 10, nms_dist_trackbar);
    nms_dist_trackbar(nms_dist, 0);
    
    cv::waitKey(0);

    return 0;
}