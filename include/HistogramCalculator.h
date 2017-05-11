#ifndef HISTOGRAMCALCULATOR_H
#define HISTOGRAMCALCULATOR_H

#ifdef _MSC_VER
#define _CRT_SECURE_NO_WARNINGS
#endif


#include <vector>
#include <opencv2/opencv.hpp>

class HistogramCalculator {
public:
    cv::Mat calc(cv::Mat hsv_img);

    cv::Mat normalize(cv::Mat hist);
protected:
    cv::Vec3i nbins;
    cv::Vec3f range;
};

#endif // HISTOGRAMCALCULATOR_H