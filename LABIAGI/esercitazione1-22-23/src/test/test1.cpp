#include "../image.h"
#include "../utils.h"

#include <string>

using namespace std;

int main(int argc, char **argv){

  /*printf("%f\n", fmod(1,1));
  return 1; */

  // Testing red removal
  
  Image im1 = load_image("data/dog.jpg");
  for (int i=0; i<im1.w; i++)
      for (int j=0; j<im1.h; j++)
          im1(i, j, 0) = 0;
  im1.save_image("output/dog_pixel_modifying_output");
  
  //copy
  Image im2;
  copy_image(im2,load_image("data/dog.jpg"));
  im2.save_image("output/dog_copy.jpg");

  //rgb to gray
  Image im3 = rgb_to_grayscale(im2);
  im3.save_image("output/dog_rgb_to_gray.jpg");

  //shift
  Image im4;
  copy_image(im4,load_image("data/dog.jpg"));
  shift_image(im4, 0, 0.4);
  shift_image(im4, 1, 0.4);
  shift_image(im4, 2, 0.4);
  im4.save_image("output/dog_shifted.jpg");

  //clamping
  Image im5;
  copy_image(im5,im4);
  clamp_image(im5);
  im5.save_image("output/dog_clamp_01");

  // rgb to hsv
  Image im6 = load_image("data/dog.jpg");
  rgb_to_hsv(im6);
  im6.save_image("output/dog_HSV");

  //hsv to rgb
  Image im7;
  copy_image(im7,im6);
  //shift_image(im7,1,2);
  //clamp_image(im7);
  hsv_to_rgb(im7);
  im7.save_image("output/dog_HSVtoRGB");

  return 0;
  }
