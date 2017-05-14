#include "../include/HistogramCalculator.h"

using namespace std;
using namespace cv;

// Erneuern der Zeilennummerierung.
// Hier fängt der Kot an.
/* 1*/	vector<double> HistogramCalculator::calc(Mat hsv_img){
/* 2*/	int hbins = 180;
/* 3*/	int histSize[] = { hbins };
/* 4*/	// hue varies from 0 to 179
/* 5*/	float hranges[] = { 0, hbins };
/* 6*/	const float* ranges[] = { hranges };
/* 7*/	MatND hist;
/* 8*/	int channels[] = { 0 };
/* 9*/	calcHist(&hsv_img, 1, channels, Mat(), hist, 1, histSize, ranges, true, false);
/*10*/	
/*11*/	cout << hist.size() << endl;
/*12*/	vector<double> hist_vec(hbins);
/*13*/	for (int i = 0; i < hbins; i++) {
/*14*/		hist_vec[i] = hist.at<float>(0, i);
/*15*/	}
/*16*/	
/*17*/	return hist_vec;
/*18*/	}
/*19*/
/*20*/	Mat HistogramCalculator::normalize(Mat hist){
/*21*/	Mat norm_hist;
/*22*/	cv::normalize(hist, norm_hist, 1, 0, cv::NORM_L1);
/*23*/	return norm_hist;
/*24*/}
