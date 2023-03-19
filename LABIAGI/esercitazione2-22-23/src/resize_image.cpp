#include <cmath>
#include "image.h"

#define MY_NEAREST 0
#define MY_BILINEAR 0

using namespace std;

// HW1 #1
// float x,y: inexact coordinates
// int c: channel
// returns the nearest neighbor to pixel (x,y,c)
float Image::pixel_nearest(float x, float y, int c) const {

  #if MY_NEAREST
  float d_11 = sqrt( pow(fmod(x,1),2) + pow(fmod(y,1),2) );
  float d_12 = sqrt( pow(1-fmod(x,1),2) + pow(fmod(y,1),2) );
  float d_21 = sqrt( pow(fmod(x,1),2) + pow(1-fmod(y,1),2) );
  float d_22 = sqrt( pow(1-fmod(x,1),2) + pow(1-fmod(y,1),2) ); 
  float p_11 = clamped_pixel(int(x), int(y), c);
  float p_12 = clamped_pixel(int(x)+1, int(y), c) ;
  float p_21 = clamped_pixel(int(x), int(y)+1, c) ;
  float p_22 = clamped_pixel(int(x)+1, int(y)+1, c) ;
  float min_a = min(d_11,d_12);
  float min_b = min(d_21,d_22);
  float d_min = min(min_a,min_b);
  if(d_min == d_11) return p_11;
  else if(d_min == d_12) return p_12;
  else if(d_min == d_21) return p_21;
  else if(d_min == d_22) return p_22;
  #endif
  
  int nearest_x = round(x);
  int nearest_y = round(y);

  return clamped_pixel(nearest_x, nearest_y, c);

}

// HW1 #1
// float x,y: inexact coordinates
// int c: channel
// returns the bilinearly interpolated pixel (x,y,c)
float Image::pixel_bilinear(float x, float y, int c) const {
  
  int x1 = floor(x);
  int x2 = ceil(x);
  int y1 = floor(y);
  int y2 = ceil(y);

  #if MY_BILINEAR
  x1 = (int) x;
  x2 = ((int) x )+ 1;
  y1 = (int) y;
  y2 = ((int) y )+ 1;
  #endif
  
  float a1 = (x2-x) * (y2-y) ;
  float a2 = (x-x1) * (y2-y) ;
  float a3 = (x2-x) * (y-y1) ;
  float a4 = (x-x1) * (y-y1) ;         

  //printf("\nx1= %d\tx2= %d\ty1= %d\ty2= %d\t\ta1= %f\ta2= %f\ta3= %f\ta4= %f\n",x1,x2,y1,y2,a1,a2,a3,a4);

  return a1 * clamped_pixel(x1,y1,c) +
         a2 * clamped_pixel(x2,y1,c) +
         a3 * clamped_pixel(x1,y2,c) +
         a4 * clamped_pixel(x2,y2,c) ;
  
}

// HW1 #1
// int w,h: size of new image
// const Image& im: input image
// return new Image of size (w,h,im.c)
Image nearest_resize(const Image& im, int w, int h){
  Image ret(w,h,im.c);

  float r_w = (float)w / (float)im.w;
  float r_h = (float)h / (float)im.h;

  float shift_w = ( (im.w-1) - (w-1)/(r_w) ) / 2 ;
  float shift_h = ( (im.h-1) - (h-1)/(r_h) ) / 2 ;

  //printf("w= %d\th= %d  \tim.w= %f\tim.h= %f\n", w, h, im.w, im.h);
  //printf("r_w= %f\tr_h= %f\n", r_w, r_h);

  for ( int ch= 0; ch<3; ch++){
    for ( int i= 0; i<h; i++){
      for ( int j= 0; j<w; j++){
        ret(j,i,ch)= im.pixel_nearest( (j/r_w) + shift_w  , (i/r_h) + shift_h , ch );
        //printf("pixel: %f\tj/r_w: %f\ti/r_h: %f\tj: %d\ti: %d\tch: %d\n",ret(j,i,ch) ,j/r_w, i/r_h,j,i,ch);
      }
    }
  }
  return ret;
}


// HW1 #1
// int w,h: size of new image
// const Image& im: input image
// return new Image of size (w,h,im.c)
Image bilinear_resize(const Image& im, int w, int h){

  Image ret(w,h,im.c);

  float r_w = (float)w / (float)im.w;
  float r_h = (float)h / (float)im.h;

  float shift_w = ( (im.w-1) - (w-1)/(r_w) ) / 2 ;
  float shift_h = ( (im.h-1) - (h-1)/(r_h) ) / 2 ;

  for ( int ch= 0; ch<3; ch++){
    for ( int i= 0; i<h; i++){
      for ( int j= 0; j<w; j++){
        ret(j,i,ch)= im.pixel_bilinear( (j/r_w) + shift_w  , (i/r_h) + shift_h , ch );
      }
    }
  }
  return ret;

}