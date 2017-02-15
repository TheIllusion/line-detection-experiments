//
// Created by Illusion on 2017. 2. 14..
//

#include "simple_blob_detector.h"

bool simple_blob_detector(cv::Mat &image)
{
    //using namespace cv;
    // Read image
    //Mat im = imread( "blob.jpg", IMREAD_GRAYSCALE );

    // Setup SimpleBlobDetector parameters.
    cv::SimpleBlobDetector::Params params;

    // Change thresholds
    params.minThreshold = 10;
    params.maxThreshold = 200;

    // Filter by Area.
    params.filterByArea = true;
    //params.minArea = 1500;
    params.minArea = 500;

    // Filter by Circularity
    params.filterByCircularity = true;
    params.minCircularity = 0.1;

    // Filter by Convexity
    params.filterByConvexity = true;
    params.minConvexity = 0.87;

    // Filter by Inertia
    params.filterByInertia = true;
    params.minInertiaRatio = 0.01;

    // Set up the detector with default parameters.
    //cv::SimpleBlobDetector detector;

    // Set up detector with params
    cv::Ptr<cv::SimpleBlobDetector> detector = cv::SimpleBlobDetector::create(params);

    // Detect blobs.
    std::vector<cv::KeyPoint> keypoints;
    detector->detect(image, keypoints);

    if(keypoints.size() > 0)
    {
        // Draw detected blobs as red circles.
        // DrawMatchesFlags::DRAW_RICH_KEYPOINTS flag ensures the size of the circle corresponds to the size of blob
        cv::Mat im_with_keypoints;
        drawKeypoints(image, keypoints, im_with_keypoints, cv::Scalar(0,0,255), cv::DrawMatchesFlags::DRAW_RICH_KEYPOINTS );

        // Show blobs
        imshow("keypoints", im_with_keypoints );
        //  waitKey(0);
        return true;
    }
    else
        return false;

}
