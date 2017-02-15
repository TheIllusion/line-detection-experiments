//
// Created by Illusion on 2017. 2. 9..
//

#include "lsd_line_segment_detector.h"

bool lsd_detector(cv::Mat &image)
{
    // Create and LSD detector with standard or no refinement.
#if 1
    cv::Ptr<cv::LineSegmentDetector> ls = cv::createLineSegmentDetector(cv::LSD_REFINE_STD);
#else
    cv::Ptr<cv::LineSegmentDetector> ls = cv::createLineSegmentDetector(cv::LSD_REFINE_NONE);
#endif

    double start = double(cv::getTickCount());

    std::vector<cv::Vec4f> lines_std;
    std::vector<float> widths;

    cv::Mat processing_image = image.clone();

    // Detect the lines
    ls->detect(processing_image, lines_std, widths);

    double duration_ms = (double(cv::getTickCount()) - start) * 1000 / cv::getTickFrequency();
    std::cout << "It took " << duration_ms << " ms." << std::endl;

    // Show found lines
    ls->drawSegments(image, lines_std);

    return true;
}