#include <iostream>
#include "opencv2/opencv.hpp"
#include "parameters.h"
#include "lsd_line_segment_detector.h"
#include "lbd_line_detector.h"
#include "selective_search.h"
#include "seeds_superpixel.h"
#include "simple_blob_detector.h"
#include "watershed.h"
#include "detect_corners.h"

using namespace std;

#define TEST_SET_ROOT_PATH "/home/illusion/ClionProjects/line-detection-experiments-git/Document_Aligner_TestSet/Document_Aligner_TestSet/normal_set/original/"
//#define TEST_SET_ROOT_PATH "/Users/Illusion/Documents/Data/Document_Aligner_TestSet/normal_set/original/"

static char filename_buff[100];

static const char* file_name =
        //"/Users/Illusion/Documents/Data/Document_Aligner_TestSet/normal_set/original/IMG_1415_iphone.jpg";
        //"/Users/Illusion/Documents/Data/Document_Aligner_TestSet/normal_set/original/IMG_1416_iphone.jpg";
        //"/Users/Illusion/Documents/Data/Document_Aligner_TestSet/normal_set/original/IMG_1417_iphone.jpg";
        //"/Users/Illusion/Documents/Data/Document_Aligner_TestSet/normal_set/original/IMG_1418_iphone.jpg";
        //"/Users/Illusion/Documents/Data/Document_Aligner_TestSet/normal_set/original/IMG_1419_iphone.jpg";
        //"/Users/Illusion/Documents/Data/Document_Aligner_TestSet/normal_set/original/IMG_1420_iphone.jpg";
        //"/Users/Illusion/Documents/Data/Document_Aligner_TestSet/normal_set/original/IMG_1421_iphone.jpg";
        //"/Users/Illusion/Documents/Data/Document_Aligner_TestSet/normal_set/original/IMG_1427_iphone.jpg";
        //"/Users/Illusion/Documents/Data/Document_Aligner_TestSet/normal_set/original/20170125_152406_galaxy.jpg";
        //"/Users/Illusion/Documents/Data/Document_Aligner_TestSet/normal_set/original/20170125_152538_galaxy.jpg";
        //"/Users/Illusion/Documents/Data/Document_Aligner_TestSet/normal_set/original/20170125_153220_galaxy.jpg";
        //"/Users/Illusion/Documents/Data/Document_Aligner_TestSet/normal_set/original/20170125_153230_galaxy.jpg";
        //"/Users/Illusion/Documents/Data/Document_Aligner_TestSet/normal_set/original/20170125_153242_galaxy.jpg";

        //Head Cams for people counting
        //"/Users/Illusion/Documents/Video/Head_Cam/3.png";
        //"/Users/Illusion/Documents/Video/Head_Cam/two_persons.png";

        //i7-2600k
        //"IMG_1415_iphone.jpg";
        //"IMG_1415_iphone.jpg";
        //"IMG_1416_iphone.jpg";
        //"IMG_1417_iphone.jpg";
        //"IMG_1418_iphone.jpg";
        //"IMG_1419_iphone.jpg";
        //"IMG_1420_iphone.jpg";
        //"IMG_1421_iphone.jpg";
        //"20170125_152406_galaxy.jpg";
        "20170125_152538_galaxy.jpg";
        //"20170125_153220_galaxy.jpg";
        //"20170125_153230_galaxy.jpg";
        //"20170125_153242_galaxy.jpg";

int main() {
    cout << "Hello, World!" << endl;

    strcpy(filename_buff, TEST_SET_ROOT_PATH);
    strcat(filename_buff, file_name);

    // open the image file
#if !LINE_SEGMENT_DETECTION_TEST && !HARRIS_CORNERS &&!GFTT_GOOD_FEATURE_TO_TRACK
    //&& !BLOB_DETECTION_TEST
    cv::Mat image = cv::imread(filename_buff, cv::IMREAD_COLOR);
#else
    cv::Mat image = cv::imread(filename_buff, cv::IMREAD_GRAYSCALE);
#endif

    if (image.data == NULL)
    {
        std::cout << "Error loading input image";
        return -1;
    }

    // resize the frame size if necessary
    if (image.cols > RESIZED_IMAGE_WIDTH)
    {
        cv::resize(image, image, cv::Size(), (double) RESIZED_IMAGE_WIDTH / image.cols,
                   (double) RESIZED_IMAGE_WIDTH / image.cols, cv::INTER_CUBIC);
    }

#if LINE_SEGMENT_DETECTION_TEST
    bool ret = lsd_detector(image);
    if (ret == false)
        return -1;
#elif LINE_BAND_DESCRIPTOR_TEST
    bool ret = lbd_detector(image);
    if (ret == false)
        return -1;
#elif SELECTIVE_SEARCH_TEST
    bool ret = selective_search(image);
    if (ret == false)
        return -1;
#elif SEEDS_TEST
    bool ret = seeds_test(image);
    if (ret == false)
        return -1;
#elif BLOB_DETECTION_TEST
    bool ret = simple_blob_detector(image);
    if (ret == false)
        return -1;
#elif WATERSHED_TEST
    bool ret = process_watershed(image);
    if (ret == false)
        return -1;
#elif CORNER_DETECTION_TEST
    bool ret = detect_corners(image);
    if (ret == false)
        return -1;

    ret = lbd_detector(image);
    if (ret == false)
        return -1;
#endif

    cv::namedWindow("Display");
    cv::imshow("Display", image);
    cv::waitKey();

    return 0;
}