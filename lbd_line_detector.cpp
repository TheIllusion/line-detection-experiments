//
// Created by Illusion on 2017. 2. 9..
//

#include "lbd_line_detector.h"
#include "opencv2/line_descriptor.hpp"

#define THE_SMALLEST_LINE_SEGMENT_LENGTH 50

bool lbd_detector(cv::Mat &image)
{
    // BinaryDescriptor
    cv::Ptr<cv::line_descriptor::BinaryDescriptor> lbd = cv::line_descriptor::BinaryDescriptor::createBinaryDescriptor();

    double start = double(cv::getTickCount());

    std::vector<cv::line_descriptor::KeyLine> lines;
    std::vector<float> widths;

    cv::Mat processing_image = image.clone();

    // Detect the lines
    lbd->detect(processing_image, lines);

    double duration_ms = (double(cv::getTickCount()) - start) * 1000 / cv::getTickFrequency();
    std::cout << "It took " << duration_ms << " ms." << std::endl;

    // Show found lines
    for ( size_t i = 0; i < lines.size(); i++ )
    {
        cv::line_descriptor::KeyLine kl = lines[i];
        if( kl.octave == 0 && kl.lineLength > THE_SMALLEST_LINE_SEGMENT_LENGTH)
        {
            /* get a random color */
            /*
            int R = ( rand() % (int) ( 255 + 1 ) );
            int G = ( rand() % (int) ( 255 + 1 ) );
            int B = ( rand() % (int) ( 255 + 1 ) );
            */

            /* get extremes of line */
            cv::Point pt1 = cv::Point( kl.startPointX, kl.startPointY );
            cv::Point pt2 = cv::Point( kl.endPointX, kl.endPointY );

            /* draw line */
            //cv::line( image, pt1, pt2, cv::Scalar( B, G, R ), 5 );
            cv::line( image, pt1, pt2, cv::Scalar( 0, 0, 255 ), 3 );
        }
    }

    return true;
}