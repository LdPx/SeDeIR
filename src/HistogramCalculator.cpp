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
cout << hist.size() << endl;
vector<double> hist_vec(hbins);
for (int i = 0; i < hbins; i++) {
	hist_vec[i] = hist.at<float>(0, i);
	}

/*11*/	return hist_vec;
/*12*/	}
/*13*/
/*14*/	Mat HistogramCalculator::normalize(Mat hist){
/*15*/	Mat norm_hist;
/*16*/	cv::normalize(hist, norm_hist, 1, 0, cv::NORM_L1);
/*17*/	return norm_hist;
/*18*/}
