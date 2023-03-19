#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <math.h>
#include <assert.h>
#include "image.h"

#define M_PI 3.14159265358979323846


/*
Smooths a grayscale image by convolving it with a Gaussian kernel of standard deviation sigma.
Input:
    Image im: the input image
    float sigma: the standard deviation of the Gaussian kernel
Output:
    Image: the smoothed image (im.w, im.h, 1)
*/
Image smooth_image(const Image& im, float sigma)
{
    // TODO: Your code here
    NOT_IMPLEMENTED();
    return im;
}


/*
Computes the magnitude and direction of the gradient of an image.
Input:
    Image im: the input image
Output:
    pair<Image,Image>: the magnitude and direction of the gradient of the image
                       with magnitude in [0,1] and direction in [-pi,pi]
*/
pair<Image,Image> compute_gradient(const Image& im)
{
    // TODO: Your code here
    NOT_IMPLEMENTED();
    return{im, im};
}


/*
Performs non-maximum suppression on an image.
Input:
    Image mag: the magnitude of the gradient of the image [0,1]
    Image dir: the direction of the gradient of the image [-pi,pi]
Output:
    Image: the image after non-maximum suppression
*/
Image non_maximum_suppression(const Image& mag, const Image& dir)
{
    Image nms(mag.w, mag.h, 1);
    float neighbor1, neighbor2;

    // Iterate through the image and perform non-maximum suppression
    for (int y = 0; y < mag.h; y++) {
        for (int x = 0; x < mag.w; x++) {
            
            // TODO: Your code here
            NOT_IMPLEMENTED();

            // Get the direction of the gradient at the current pixel

            // Round the direction to the nearest multiple of PI/4

            // Get the magnitude of the gradient of the two neighbors along that direction
            // (Hint: use clamped_pixel to avoid going out of bounds)            

            // If the magnitude of the gradient of the current pixel is greater than that of both neighbors,
            // then it is a local maximum
        }
    }

    return nms;
}



/*
    Applies double thresholding to an image.
    Input:
        Image im: the input image
        float lowThreshold: the low threshold value
        float highThreshold: the high threshold value
        float strongVal: the value to use for strong edges
        float weakVal: the value to use for weak edges
    Output:
        Image: the thresholded image
*/
Image double_thresholding(const Image& im, float lowThreshold, float highThreshold, float strongVal, float weakVal)
{
    Image res(im.w, im.h, im.c);

    // TODO: Your code here
    NOT_IMPLEMENTED();

    return res;
}


/*
    Applies hysteresis thresholding to an image.
    Input:
        Image im: the input image
        float weak: the value of the weak edges
        float strong: the value of the strong edges
    Output:
        Image: the image after hysteresis thresholding, with only strong edges
*/
Image edge_tracking(const Image& im, float weak, float strong)
{
    Image res(im.w, im.h, im.c);

    for (int y=0; y < im.h; ++y) {
        for (int x=0; x < im.w; ++x) {
            // TODO: Your code here
            NOT_IMPLEMENTED();

            // Hint: use clamped_pixel when checking the neighbors to avoid going out of bounds
        }
    }
    return res;

}
