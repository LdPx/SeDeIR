#ifndef HISTOGRAMCALCULATOR_H
#define HISTOGRAMCALCULATOR_H

#include <vector>
#include <opencv2/opencv.hpp>

class HistogramCalculator {
public:
	std::vector<double> calc(cv::Mat hsv_img);

	cv::Mat normalize(cv::Mat hist);
protected:
	cv::Vec3i nbins;
	cv::Vec3f range;
};

#endif // HISTOGRAMCALCULATOR_H
