#include "image.h"

// HW0 #1
// const Image& im: input image
// int x,y: pixel coordinates
// int ch: channel of interest
// returns the 0-based location of the pixel value in the data array
int pixel_address(const Image& im, int x, int y, int ch)
  {
  return y*im.w + x + ch * im.w * im.h ;
  }

// HW0 #1
// const Image& im: input image
// int x,y,ch: pixel coordinates and channel of interest
// returns the value of the clamped pixel at channel ch
float get_clamped_pixel(const Image& im, int x, int y, int ch)
  {
    int cla_x = x;
    int cla_y = y;
    
    if(x<0) cla_x = 0;
    if(x>=im.w-1) cla_x = im.w-1;

    if(y<0) cla_y = 0;
    if(y>=im.h-1) cla_y = im.h-1;

    return im(cla_x, cla_y, ch);
  }


// HW0 #1
// Image& im: input image
// int x,y,ch: pixel coordinates and channel of interest
void set_pixel(Image& im, int x, int y, int c, float value)
  {
    im.data[pixel_address(im,x,y,c)] = value;
  }



// HW0 #2
// Copies an image
// Image& to: destination image
// const Image& from: source image
void copy_image(Image& to, const Image& from)
  {
  // allocating data for the new image
  to.data=(float*)calloc(from.w*from.h*from.c,sizeof(float));
  to.c=from.c;
  to.w=from.w;
  to.h=from.h;
  
  for(int i=0; i < from.w*from.h*from.c ; i++){
    to.data[i] = from.data[i];
  }
  
  // You might want to check how 'memcpy' function works
  
  }
