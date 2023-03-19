#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <math.h>
#include <assert.h>
#include "image.h"


#define M_PI 3.14159265358979323846

// HW1 #2.1
// Image& im: image to L1-normalize
void l1_normalize(Image &im) {
    
    int dim = im.w*im.h;
    float norm = 1.0/dim;

    //printf("Valore normalizzato= %f\n",norm);

    for(int pixel=0; pixel< dim*im.c; pixel++){
        im.data[pixel] = norm;
    }

    return;
}

// HW1 #2.1
// int w: size of filter
// returns the filter Image of size WxW
Image make_box_filter(int w) {
    assert(w % 2); // w needs to be odd

    Image im(w,w,1);
    l1_normalize(im);

    return im;
}

// HW1 #2.2
// const Image&im: input image
// const Image& filter: filter to convolve with
// bool preserve: whether to preserve number of channels
// returns the convolved image
Image convolve_image(const Image &im, const Image &filter, bool preserve) {
    assert(filter.c == 1);

    int half = (int) (filter.w / 2);
    
    Image ret(im.w,im.h,im.c);
    
    //Image ret_n(im.w,im.h,1);
    Image channels[3];
    
    for(int ch=0; ch<im.c; ch++){
        
        Image ret_n(im.w,im.h,1);

        for(int row=0; row<im.h; row++){
            for(int col=0; col<im.w; col++){

                int x_low = col - half;
                int x_high = col + half;
                int y_low = row - half;
                int y_high = row + half;

                float count = 0;

                for(int i=y_low, i_i=0; i<=y_high ; i++, i_i++ ){
                    for(int j=x_low, j_j=0; j<=x_high ; j++, j_j++ ){
                        count += im.clamped_pixel(j,i,ch) * filter(j_j,i_i,0) ;
                    }
                }
                
                if(preserve) ret(col,row,ch) = count;
                else ret_n(col,row,0) = count;
            }
        }
        
        if(!preserve) channels[ch] = ret_n;
    }
    
    if (preserve) return ret;
    
    else{
        Image ret_f(im.w,im.h,1);

        for(int pixel=0; pixel<im.w*im.h; pixel++){
            float val = 0;

            for(int c=0; c<im.c; c++){
                val += channels[c].data[pixel] ;
            }
            
            ret_f.data[pixel] =  val;
            //if(pixel>(im.w*im.h)-5000) printf("pixel: %d\tvalue: %f\n",pixel,val);
        }
        
        return ret_f;
    }
}


// HW1 #2.2+ Fast convolution
// const Image&im: input image
// const Image& filter: filter to convolve with
// bool preserve: whether to preserve number of channels
// returns the convolved image
Image convolve_image_fast(const Image &im, const Image &filter, bool preserve) {
    assert(filter.c == 1);
    Image ret;
    // This is the case when we need to use the function clamped_pixel(x,y,c).
    // Otherwise you'll have to manually check whether the filter goes out of bounds

    // TODO: Make sure you set the sizes of ret properly. Use ret=Image(w,h,c) to reset ret
    // TODO: Do the fast convolution operator. Remember to use Eigen for matrix operations
    NOT_IMPLEMENTED();

    // Make sure to return ret and not im. This is just a placeholder
    return im;
}


// HW1 #2.3
// returns basic 3x3 high-pass filter
Image make_highpass_filter() {
    Image ret(3,3,1);
    ret.data[0] = 0 ;
    ret.data[1] = -1 ;
    ret.data[2] = 0 ;
    ret.data[3] = -1 ;
    ret.data[4] = 4 ;
    ret.data[5] = -1 ;
    ret.data[6] = 0 ;
    ret.data[7] = -1 ;
    ret.data[8] = 0 ;
    return ret;
}

// HW1 #2.3
// returns basic 3x3 sharpen filter
Image make_sharpen_filter() {
    Image ret(3,3,1);
    ret.data[0] = 0 ;
    ret.data[1] = -1 ;
    ret.data[2] = 0 ;
    ret.data[3] = -1 ;
    ret.data[4] = 5 ;
    ret.data[5] = -1 ;
    ret.data[6] = 0 ;
    ret.data[7] = -1 ;
    ret.data[8] = 0 ;
    return ret;
}

// HW1 #2.3
// returns basic 3x3 emboss filter
Image make_emboss_filter() {
    Image ret(3,3,1);
    ret.data[0] = -2 ;
    ret.data[1] = -1 ;
    ret.data[2] = 0 ;
    ret.data[3] = -1 ;
    ret.data[4] = 1 ;
    ret.data[5] = 1 ;
    ret.data[6] = 0 ;
    ret.data[7] = 1 ;
    ret.data[8] = 2 ;
    return ret;
}

// HW1 #2.4
// float sigma: sigma for the gaussian filter
// returns basic gaussian filter
Image make_gaussian_filter(float sigma) {
    int dim = ceil(6*sigma) ;
    if(dim%2==0) dim+=1;
    Image ret(dim,dim,1);
    

    double a = 1.0 / (2.0*M_PI*sigma*sigma) ;

    for (int row=0; row<dim; row++){
        int y = row - dim/2 ;

        for(int col=0; col<dim; col++){
            int x = col - dim/2 ;
            double b = - ( x*x+y*y ) / (2.0*sigma*sigma) ;

            ret(col,row,0) = a * exp(b) ;
        }
    }
    return ret;
}


// HW1 #3
// const Image& a: input image
// const Image& b: input image
// returns their sum
Image add_image(const Image &a, const Image &b) {
    assert(a.w == b.w && a.h == b.h && a.c == b.c); // assure images are the same size
    Image ret(a.w,a.h,a.c);

    for(int i=0; i<a.w*a.h*a.c; i++){
        ret.data[i] = a.data[i] + b.data[i] ;
    }

    return ret;
}

// HW1 #3
// const Image& a: input image
// const Image& b: input image
// returns their difference res=a-b
Image sub_image(const Image &a, const Image &b) {
    assert(a.w == b.w && a.h == b.h && a.c == b.c); // assure images are the same size
    Image ret(a.w,a.h,a.c);

    for(int i=0; i<a.w*a.h*a.c; i++){
        ret.data[i] = a.data[i] - b.data[i] ;
    }

    return ret;
}

// HW1 #4.1
// returns basic GX filter
Image make_gx_filter() {
    Image ret(3,3,1);
    ret.data[0] = -1 ;
    ret.data[1] = 0 ;
    ret.data[2] = 1 ;
    ret.data[3] = -2 ;
    ret.data[4] = 0 ;
    ret.data[5] = 2 ;
    ret.data[6] = -1 ;
    ret.data[7] = 0 ;
    ret.data[8] = 1 ;
    return ret;
}

// HW1 #4.1
// returns basic GY filter
Image make_gy_filter() {
    Image ret(3,3,1);
    ret.data[0] = -1 ;
    ret.data[1] = -2 ;
    ret.data[2] = -1 ;
    ret.data[3] = 0 ;
    ret.data[4] = 0 ;
    ret.data[5] = 0 ;
    ret.data[6] = 1 ;
    ret.data[7] = 2 ;
    ret.data[8] = 1 ;
    return ret;
}

// HW1 #4.2
// Image& im: input image
void feature_normalize(Image &im) {
    assert(im.w * im.h); // assure we have non-empty image

    for(int ch=0; ch<im.c; ch++){

        float min = im(0,0,ch);
        float max = im(0,0,ch);
        
        for(int row=0; row<im.h; row++){
            for(int col=0; col<im.w; col++){
                if(im(col,row,ch)<min) min = im(col,row,ch) ;
                if(im(col,row,ch)>max) max = im(col,row,ch) ;
            }
        }
        
        float range = max-min;
        //printf("max: %f\tmin: %f\trange: %f\n",max,min,range);
        assert(range>=0 && "pixel maggiore < pixel minore");

        for(int row=0; row<im.h; row++){
            for(int col=0; col<im.w; col++){
                if(range==0) im(col,row,ch) = 0;
                else im(col,row,ch) = (im(col,row,ch) - min) / range ;
            }
        }
    }
}


// Normalizes features across all channels
void feature_normalize_total(Image &im) {
    assert(im.w * im.h * im.c); // assure we have non-empty image

    int nc = im.c;
    im.c = 1;
    im.w *= nc;

    feature_normalize(im);

    im.w /= nc;
    im.c = nc;

}


// HW1 #4.3
// Image& im: input image
// return a pair of images of the same size
pair<Image, Image> sobel_image(const Image &im) {

    Image gx_im = convolve_image(im,make_gx_filter(),false);
    Image gy_im = convolve_image(im,make_gy_filter(),false);
    
    Image magnitude(im.w, im.h, 1);
    Image theta(im.w, im.h, 1);

    for(int row=0; row<im.h; row++){
        for(int col=0; col<im.w; col++){
            float gx = gx_im(col,row,0);
            float gy = gy_im(col,row,0);
            magnitude(col,row,0) =  sqrtf( gx*gx + gy*gy ) ;
            theta(col,row,0) = atan2( gy, gx ) / (2 * M_PI) + 0.5  ;
        }
    }
    feature_normalize(magnitude);
    //printf("channels of magnitude: %d\tchannels of theta: %d\n",magnitude.c, theta.c);
    return {magnitude, theta};
}


// HW1 #4.4
// const Image& im: input image
// returns the colorized Sobel image of the same size
Image colorize_sobel(const Image &im) {
    Image hsv(im.w, im.h, im.c);
    Image ret(im.w, im.h, im.c);

    pair<Image,Image> couple = sobel_image(im);
    Image mag = couple.first;
    Image theta = couple.second;
    
    Image gx_im = convolve_image(im,make_gx_filter(),false);
    Image gy_im = convolve_image(im,make_gy_filter(),false);

    //feature_normalize(gx_im);
    //feature_normalize(gy_im);


    for(int r=0; r<im.h; r++){
        for(int c=0; c<im.w; c++){
            
            //theta(c,r,0) = ( theta(c,r,0) / (2*M_PI) ) + 0.5 ;
            
            hsv(c,r,0) = theta(c,r) ;
            hsv(c,r,1) = gx_im(c,r) ;
            hsv(c,r,2) = gy_im(c,r) ;
        }
    }
    //feature_normalize(hsv);
    hsv_to_rgb(hsv);
    Image g_filter = make_gaussian_filter(4.0) ;
    ret = convolve_image(hsv,g_filter,true);


    return ret;
}


// HW1 #4.5
// const Image& im: input image
// float sigma1,sigma2: the two sigmas for bilateral filter
// returns the result of applying bilateral filtering to im
Image bilateral_filter(const Image &im, float sigma1, float sigma2) {
    Image bf = im;

    // TODO: Your bilateral code
    NOT_IMPLEMENTED();

    return bf;
}

// HW1 #4.5+ Fast bilateral filter
// const Image& im: input image
// float sigma1,sigma2: the two sigmas for bilateral filter
// returns the result of applying bilateral filtering to im
Image bilateral_filter_fast(const Image &im, float sigma1, float sigma2) {
    Image bf = im;

    // TODO: Your fast bilateral code
    NOT_IMPLEMENTED();

    return bf;
}

// HM #5
//
float *compute_histogram(const Image &im, int ch, int num_bins) {
    float *hist = (float *) malloc(sizeof(float) * num_bins);
    for (int i = 0; i < num_bins; ++i) {
        hist[i] = 0;
    }

    // TODO: Your histogram code
    NOT_IMPLEMENTED();

    return hist;
}

float *compute_CDF(float *hist, int num_bins) {
    float *cdf = (float *) malloc(sizeof(float) * num_bins);

    cdf[0] = hist[0];

    // TODO: Your cdf code
    NOT_IMPLEMENTED();

    return cdf;
}

Image histogram_equalization_hsv(const Image &im, int num_bins) {
    Image new_im(im);
    float eps = 1.0 / (num_bins * 1000);

    // TODO: Your histogram equalization code
    NOT_IMPLEMENTED();
    // convert to hsv
    // compute histograms for the luminance channel
    // compute cdf
    // equalization
    // convert back to rgb

    // delete the allocated memory!
//    delete hist;
//    delete cdf;

    return new_im;
}

Image histogram_equalization_rgb(const Image &im, int num_bins) {
    Image new_im(im);
    float eps = 1.0 / (num_bins * 1000);

    // compute histograms for each color channel
    for (int c = 0; c < im.c; ++c) {

        // TODO: Your equalization code
        NOT_IMPLEMENTED();

        // delete the allocated memory!
//        delete hist;
//        delete cdf;
    }

    return new_im;
}


// HELPER MEMBER FXNS

void Image::feature_normalize(void) { ::feature_normalize(*this); }

void Image::feature_normalize_total(void) { ::feature_normalize_total(*this); }

void Image::l1_normalize(void) { ::l1_normalize(*this); }

Image operator-(const Image &a, const Image &b) { return sub_image(a, b); }

Image operator+(const Image &a, const Image &b) { return add_image(a, b); }
