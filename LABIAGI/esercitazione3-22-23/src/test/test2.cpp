#include "../image.h"
#include "../utils.h"

#include <string>

using namespace std;


void test_smooth_image()
{
    Image im = load_image("data/iguana.jpg");
    im = rgb_to_grayscale(im);
    im = smooth_image(im, 1.4);
    im.save_png("output/smooth_iguana");
    Image check_gt = load_image("data/smooth_iguana.png");
    TEST(same_image(im, check_gt));
}


void test_gradient()
{
    Image im = load_image("data/iguana.jpg");
    im = rgb_to_grayscale(im);
    im = smooth_image(im, 1.4);
    pair<Image,Image> grad = compute_gradient(im);
    Image mag = grad.first;
    Image dir = grad.second;
    feature_normalize(dir);
    mag.save_png("output/mag_iguana");
    dir.save_png("output/dir_iguana");
    Image check_gt_mag = load_image("data/mag_iguana.png");
    Image check_gt_dir = load_image("data/dir_iguana.png");
    TEST(same_image(mag, check_gt_mag));
    TEST(same_image(dir, check_gt_dir));
}


void test_non_max_suppression()
{
    Image im = load_image("data/iguana.jpg");
    im = rgb_to_grayscale(im);
    im = smooth_image(im, 1.4);
    pair<Image,Image> grad = compute_gradient(im);
    Image mag = grad.first;
    Image dir = grad.second;
    Image nms = non_maximum_suppression(mag, dir);
    nms.save_png("output/nms_iguana");
    Image check_nms = load_image("data/nms_iguana.png");
    TEST(same_image(nms, check_nms));

}


void test_double_thresholding()
{
    Image im = load_image("data/iguana.jpg");
    im = rgb_to_grayscale(im);
    im = smooth_image(im, 1.4);
    pair<Image,Image> grad = compute_gradient(im);
    Image mag = grad.first;
    Image dir = grad.second;
    Image nms = non_maximum_suppression(mag, dir);
    Image dt = double_thresholding(nms, 0.03, 0.17, 1.0, 0.25);
    dt.save_png("output/double_threshold_iguana");
    Image dt_check = load_image("data/double_threshold_iguana.png");
    TEST(same_image(dt, dt_check));

}

void test_edge_tracking()
{
    Image im = load_image("data/iguana.jpg");
    im = rgb_to_grayscale(im);
    im = smooth_image(im, 1.4);
    pair<Image,Image> grad = compute_gradient(im);
    Image mag = grad.first;
    Image dir = grad.second;
    Image nms = non_maximum_suppression(mag, dir);
    float strong = 1.0;
    float weak = 0.25;
    Image dt = double_thresholding(nms, 0.03, 0.17, strong, weak);
    Image edge_track = edge_tracking(dt, weak, strong);
    edge_track.save_png("output/edge_track_iguana");
    Image et_check = load_image("data/edge_track_iguana.png");
    TEST(same_image(edge_track, et_check));
}


void run_tests()
{
    test_smooth_image();
    test_gradient();
    test_non_max_suppression();
    test_double_thresholding();
    test_edge_tracking();

    printf("%d tests, %d passed, %d failed\n", tests_total, tests_total - tests_fail, tests_fail);
}

int main(int argc, char **argv)
{
    run_tests();
    return 0;
}

