#include "../include/HistogramCalculator.h"

using namespace std;
using namespace cv;

Mat HistogramCalculator::calc(Mat hsv_img){
	int hbins = 180;
	int histSize[] = { hbins };
	// hue varies from 0 to 179
	float hranges[] = { 0, 180 };
	const float* ranges[] = { hranges };
	MatND hist;
	int channels[] = { 0 };
	calcHist(&hsv_img, 1, channels, Mat(), hist, 1, histSize, ranges, true, false);

    return hist;
}

Mat HistogramCalculator::normalize(Mat hist){
    Mat norm_hist;
    cv::normalize(hist, norm_hist, 1, 0, cv::NORM_L1);
    return norm_hist;
}
