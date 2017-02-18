//
// Created by Illusion on 2017. 2. 12..
//

#include "seeds_superpixel.h"
#include "opencv2/ximgproc/seeds.hpp"

bool seeds_test(cv::Mat &image)
{

    cv::Mat converted_img;
    cv::Mat color_img(image.rows, image.cols, CV_8UC3, cv::Scalar(0, 0, 255));
    cv::cvtColor(image, converted_img, cv::COLOR_BGR2HSV);

#define SEEDS_NUM_SUPERPIXELS 50
#define SEEDS_NUM_LEVELS 5
#define SEEDS_NUM_ITERATIONS 5

    cv::Ptr<cv::ximgproc::SuperpixelSEEDS> super_pixel =
    cv::ximgproc::createSuperpixelSEEDS(image.cols, image.rows, image.channels(), SEEDS_NUM_SUPERPIXELS, SEEDS_NUM_LEVELS);

    double start = double(cv::getTickCount());

    //HSV color space or Lab COLOR space should be used
    super_pixel->iterate(converted_img, SEEDS_NUM_ITERATIONS);

    int nums = super_pixel->getNumberOfSuperpixels();
    std::cout << "number of super pixels: " << nums << std::endl;

    cv::Mat labels_out;
    super_pixel->getLabels(labels_out);

    //labels output: use the last x bits to determine the color
    int num_label_bits = 2;
    labels_out &= (1<<num_label_bits)-1;
    labels_out *= 1<<(16-num_label_bits);

    cv::Mat mask;
    //C++: void SuperpixelSEEDS::getLabelContourMask(OutputArray image, bool thick_line=false)
    super_pixel->getLabelContourMask(mask, true);

    //stitch foreground & background together
    cv::Mat mask_inv, result_bg, result_fg, result;
    cv::bitwise_not(mask, mask_inv);

    cv::bitwise_and(image, image, result_bg, mask=mask_inv);
    cv::bitwise_and(color_img, color_img, result_fg, mask=mask);
    cv::add(result_bg, result_fg, result);

    double duration_ms = (double(cv::getTickCount()) - start) * 1000 / cv::getTickFrequency();
    std::cout << "It took " << duration_ms << " ms." << std::endl;

    cv::imshow("SEEDS", result);
    cv::imshow("SEEDS_MASK", mask);
    cv::imshow("SEEDS_LABELS", labels_out);

    return true;
}