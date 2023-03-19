#include "../image.h"
#include "../utils.h"

#include <string>

using namespace std;

int print_diff(const Image& im1, const Image& im2){
    assert(im1.h*im1.w*im1.c==im2.h*im2.w*im2.c);
    int c = 0;
    for (int i=0; i< im1.h*im1.w*im1.c; i++){
        if(im1.data[i] != im2.data[i]) {
            printf("i= %d\tim1: %f\tim2= %f\n", i,im1.data[i], im2.data[i]);
            c++;
        }
    }
    printf("Numero di pixel errati: %d\n", c);
}

int main(int argc, char **argv) {
    
    /*
    Image im = load_image("data/dogsmall.jpg");
    printf("dogsmall.jpg:\tim.w= %d\tim.h= %d\n",im.w,im.h);

    Image im3 = load_image("data/dog.jpg");
    printf("\ndog.jpg:\tim.w= %d\tim.h= %d\n",im3.w,im3.h);
    Image im4 = nearest_resize(im3, 713, 467);
    im4.save_image("output/dog-resize-nn.png");
    
    Image sol = load_image("data/dog-resize-nn.png");
    print_diff(sol,im4);
    */

    Image im5 = load_image("data/dog.jpg");

    /*
    Image filter_box = make_box_filter(7);
    Image im6 = convolve_image(im5, filter_box, true);
    im6.clamp();
    im6.save_image("output/dog_boxfilter.png");
    
    Image filter_high = make_highpass_filter();
    Image im7 = convolve_image(im5, filter_high, false);
    im7.clamp();
    im7.save_image("output/dog_high_pass_filter.png");
    */

    Image im8 = load_image("data/dog.jpg");
    pair <Image,Image> coppia = sobel_image(im8);
    coppia.first.save_image("output/magnitude.jpg");
    coppia.second.save_image("output/theta.jpg");

    /*
    im8.feature_normalize();
    im8.save_image("output/dog_feature_normalize.png");
    */

   Image im9 = colorize_sobel(im8);
   im9.save_image("output/dog_colorized_sobel.jpg");
   
   return 0;
}
