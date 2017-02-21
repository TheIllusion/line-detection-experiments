//
// Created by Illusion on 2017. 2. 9..
//

#include "lsd_line_segment_detector.h"

#define MIN_LINE_SEG_LENGTH_LSD 50.0

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
    std::cout << "Number of line segments " << lines_std.size() << std::endl;

    for(std::vector<cv::Vec4f>::iterator it = lines_std.begin(); it != lines_std.end(); it++)
    {
        double dist = cv::sqrt( (it->val[0] - it->val[2]) * (it->val[0] - it->val[2]) +
                                (it->val[1] - it->val[3]) * (it->val[1] - it->val[3]));
        if(dist < MIN_LINE_SEG_LENGTH_LSD)
        {
            it = lines_std.erase(it);
            --it;
        }
        else
        {
            //std::cout << "dist = " << dist << std::endl;
        }
    }

    std::cout << "Number of line segments(after deletion) " << lines_std.size() << std::endl;

    // Show found lines
    ls->drawSegments(image, lines_std);

    return true;
}