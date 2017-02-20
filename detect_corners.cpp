//
// Created by Illusion on 2017. 2. 20..
//

#include "detect_corners.h"

bool detect_corners(cv::Mat &image)
{
#if HARRIS_CORNERS
    cv::Mat cornerStrenth;
    cv::cornerHarris(image, cornerStrenth, 3, 3, 0.01);

    cv::Mat harrisCorners;
    double threshold = 0.0001;
    cv::threshold(cornerStrenth, harrisCorners, threshold, 255, cv::THRESH_BINARY);

    cv::namedWindow("HarrisCorners");
    cv::imshow("HarrisCorners", harrisCorners);

#elif GFTT_GOOD_FEATURE_TO_TRACK
    std::vector<cv::Point2f> corners;
    cv::goodFeaturesToTrack(image, corners, 500, 0.01, 10);

    cv::namedWindow("GFTT");
    cv::imshow("GFTT", corners);
#endif

    return true;
}