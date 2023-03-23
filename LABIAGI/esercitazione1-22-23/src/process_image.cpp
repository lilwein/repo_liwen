#include <cstdio>
#include <cstring>
#include <cassert>
#include <cmath>

#include "image.h"

using namespace std;

// HW0 #3
// const Image& im: input image
// return the corresponding grayscale image
Image rgb_to_grayscale(const Image& im)
  {
  assert(im.c == 3); // only accept RGB images
  Image gray(im.w,im.h,1); // create a new grayscale image (note: 1 channel)
  
  for(int i=0; i < im.w*im.h; i++){
    gray.data[i] = 0.299 * im.data[i] + 0.587 * im.data[i+im.w*im.h] + 0.114 * im.data[i+2*im.w*im.h];
  }

  return gray;
  }



// Example function that changes the color of a grayscale image
Image grayscale_to_rgb(const Image& im, float r, float g, float b)
  {
  assert(im.c == 1);
  Image rgb(im.w,im.h,3);
  
  for(int q2=0;q2<im.h;q2++)for(int q1=0;q1<im.w;q1++)
    {
    rgb(q1,q2,0)=r*im(q1,q2);
    rgb(q1,q2,1)=g*im(q1,q2);
    rgb(q1,q2,2)=b*im(q1,q2);
    }
  
  return rgb;
  }




// HW0 #4
// Image& im: input image to be modified in-place
// int c: which channel to shift
// float v: how much to shift
void shift_image(Image& im, int c, float v){
  assert(c>=0 && c<im.c); // needs to be a valid channel
  
  for(int i=0; i < im.w*im.h; i++){
    im.data[i + c*im.w*im.h] = im.data[i + c*im.w*im.h] + v;
  }
}

// HW0 #8
// Image& im: input image to be modified in-place
// int c: which channel to scale
// float v: how much to scale
void scale_image(Image& im, int c, float v){
  assert(c>=0 && c<im.c); // needs to be a valid channel
  
  for(int i=0; i < im.w*im.h; i++){
    im.data[i + c*im.w*im.h] = im.data[i + c*im.w*im.h] * v;
  }
  
}


// HW0 #5
// Image& im: input image to be modified in-place
void clamp_image(Image& im)
  {
  for(int i=0; i < im.c*im.w*im.h; i++){
    
    if(im.data[i]<0) im.data[i]=0;

    if(im.data[i]>1) {
      im.data[i]=1;
      //printf("pixel %d: valore: %f\n",i,im.data[i]);
    }

  }
  
  }

// These might be handy
float max(float a, float b, float c)
  {
  return max({a,b,c});
  }

float min(float a, float b, float c)
  {
  return min({a,b,c});
  }


// HW0 #6
// Image& im: input image to be modified in-place
void rgb_to_hsv(Image& im)
  {
  assert(im.c==3 && "only works for 3-channels images");

  int dim = im.w*im.h;
  for(int i=0; i< dim; i++){
    float saturation, value, minimo;
    
    // R=G=B
    if(im.data[i]==0 && im.data[i+dim]==0 && im.data[i+2*dim]==0){
      value = 0;
      minimo = 0;
      saturation = 0;
    }
    // value,min,saturation
    else{ 
      value = max(im.data[i], im.data[i+dim], im.data[i+2*dim]);
      minimo = min(im.data[i], im.data[i+dim], im.data[i+2*dim]);
      saturation = (value-minimo)/value;
    }
    
    // hue_aux
    float hue_aux, hue;
    if(value-minimo==0) hue = 0;
    else{
      //printf("value= %f\n",value);
      if(value==im.data[i]) hue_aux = (im.data[i+dim]-im.data[i+2*dim])/(value-minimo);
      else if(value==im.data[i+dim]) hue_aux = ((im.data[i+2*dim]-im.data[i])/(value-minimo))+2;
      else if(value==im.data[i+2*dim]) hue_aux = ((im.data[i]-im.data[i+dim])/(value-minimo))+4;

      //hue
      if(hue_aux<0) hue = hue_aux/6 +1;
      else hue = hue_aux/6;
    }
    //overflow hue
    if(hue<0) hue+=1;
    else if (hue>=1) hue-=1;

    //set pixel
    im.data[i] = hue;
    im.data[i+dim] = saturation;
    im.data[i+2*dim] = value;
  }
  
  }

// HW0 #7
// Image& im: input image to be modified in-place
void hsv_to_rgb(Image& im)
  {
  assert(im.c==3 && "only works for 3-channels images");
  
  int dim = im.w*im.h;
  for(int i=0; i< dim; i++){
    float hue, saturation, value;
    hue = im.data[i];
    saturation = im.data[i+dim];
    value = im.data[i+2*dim];

    //if(hue>1||saturation>1||value>1)
    //printf("pixel %d:\thue: %f\tsat: %f\tval:%f\n",i,hue,saturation,value);

    float c, x, m;
    c = value*saturation;
    x = c * (1 - abs( fmod(6*hue, 2) - 1) );
    m = value - c;
    //printf("pixel %d:\tc: %f\tx: %f\tm:%f\n",i,c,x,m);

    if( hue>=0 && hue<(1.0/6) ){
      im.data[i] = value;
      im.data[i+dim] = x+m;
      im.data[i+2*dim] = m;
    }
    else if( hue>=(1.0/6) && hue<(2.0/6) ){
      im.data[i] = x+m;
      im.data[i+dim] = value;
      im.data[i+2*dim] = m;
    }
    else if( hue>=(2.0/6) && hue<(3.0/6) ){
      im.data[i] = m;
      im.data[i+dim] = value;
      im.data[i+2*dim] = x+m;
    }
    else if( hue>=(3.0/6) && hue<(4.0/6) ){
      im.data[i] = m;
      im.data[i+dim] = x+m;
      im.data[i+2*dim] = value;
    }
    else if( hue>=(4.0/6) && hue<(5.0/6) ){
      im.data[i] = x+m;
      im.data[i+dim] = m;
      im.data[i+2*dim] = value;
    }
    else if( hue>=(5.0/6) && hue<1 ){
      im.data[i] = value;
      im.data[i+dim] = m;
      im.data[i+2*dim] = x+m;
    }
  }
}

// HW0 #9
// Image& im: input image to be modified in-place
void rgb_to_lch(Image& im)
  {
  assert(im.c==3 && "only works for 3-channels images");
  
  // TODO: Convert all pixels from RGB format to LCH format
  
  
  NOT_IMPLEMENTED();
  
  }

// HW0 #9
// Image& im: input image to be modified in-place
void lch_to_rgb(Image& im)
  {
  assert(im.c==3 && "only works for 3-channels images");
  
  // TODO: Convert all pixels from LCH format to RGB format
  
  NOT_IMPLEMENTED();
  
  }



// Implementation of member functions
void Image::clamp(void) { clamp_image(*this); }
void Image::shift(int c, float v) { shift_image(*this,c,v); }
void Image::scale(int c, float v) { scale_image(*this,c,v); }

void Image::HSVtoRGB(void) { hsv_to_rgb(*this); }
void Image::RGBtoHSV(void) { rgb_to_hsv(*this); }
void Image::LCHtoRGB(void) { lch_to_rgb(*this); }
void Image::RGBtoLCH(void) { rgb_to_lch(*this); }
