//
// Created by Illusion on 2017. 2. 9..
//

#include "opencv2/ximgproc/segmentation.hpp"
#include "selective_search.h"

using namespace cv;
using namespace cv::ximgproc::segmentation;

bool selective_search(Mat &image)
{
    double start = double(cv::getTickCount());

    Ptr<SelectiveSearchSegmentation> gs = createSelectiveSearchSegmentation();
    gs->setBaseImage(image);

    //gs->switchToSingleStrategy();
    gs->switchToSelectiveSearchFast();
    //gs->switchToSelectiveSearchQuality();

    std::vector<Rect> rects;
    gs->process(rects);

    double duration_ms = (double(cv::getTickCount()) - start) * 1000 / cv::getTickFrequency();
    std::cout << "It took " << duration_ms << " ms." << std::endl;

    int nb_rects = 10;

    int i = 0;

    for(std::vector<Rect>::iterator it = rects.begin(); it != rects.end(); ++it) {
        if (i++ < nb_rects) {
            rectangle(image, *it, Scalar(0, 0, 255));
        }
    }

    return true;
}