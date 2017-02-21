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

    cv::Mat gftt_corners = image.clone();
    for(std::vector<cv::Point2f>::iterator it = corners.begin(); it != corners.end(); it++)
    {
        cv::circle(gftt_corners, *it, 3, cv::Scalar(0, 0, 255), 3);
    }

    cv::namedWindow("GFTT");
    cv::imshow("GFTT", gftt_corners);

#elif FAST_FEATURES_FROM_ACCELERATED_SEGMENT_TEST
    cv::Mat fast_corners = image.clone();

    std::vector<cv::KeyPoint> keyPoints;

    cv::Ptr<cv::FeatureDetector> fast = cv::FastFeatureDetector::create(40);

    fast->detect(image, keyPoints);

    cv::drawKeypoints(image, keyPoints, fast_corners, cv::Scalar(0, 0, 255), cv::DrawMatchesFlags::DRAW_OVER_OUTIMG);

    cv::namedWindow("FAST");
    cv::imshow("FAST", fast_corners);

#endif

    return true;
}
