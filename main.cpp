#ifdef _MSC_VER
#define _CRT_SECURE_NO_WARNINGS
#endif

#include <iostream>
#include <opencv2\opencv.hpp>
#include <queue>
#include "include\HueConverter.h"
#include "include\HistogramCalculator.h"


#define FUER for
#define WAEHREND while
#define SCHALTER switch
#define FALL case
#define GANZZAHL int
#define MATRIX Mat
#define RS_LADE_BILD_FARBE CV_LOAD_IMAGE_COLOR
#define CRAUS cout
#define ENDZ endl
#define BILDEINLESEN imread
#define BILDZEIGEN imshow
#define WARTETASTE waitKey

using namespace std;
using namespace cv;

int main(int argc, char **argv) {
	MATRIX img = BILDEINLESEN("C:\\Users\\lammbraten\\Dropbox\\Master\\2.Semester\\BAN\\Praktikum\\SeDeIR\\SeDeIR\\Implemetierung\\data\\dop10cir_32359_5654_1_nw-LZW.tif", RS_LADE_BILD_FARBE);
//	MATRIX img = BILDEINLESEN("data/dop10cir_32359_5654_1_nw_2016.tif", RS_LADE_BILD_FARBE);

	CRAUS << "Image size: " << img.rows << "x" << img.cols << ENDZ;

	CRAUS << "Converting to H(ue)..." << ENDZ;
	Mat H_img = HueConverter().convertToHOfHSV(img);

	CRAUS << "Calculation Histogram..." << ENDZ;
	Mat hist = HistogramCalculator().calc(H_img);
	CRAUS << hist << ENDZ;



	cv::resize(H_img, H_img, Size(1000, 1000));
	BILDZEIGEN("show_time!", H_img);
	WARTETASTE(0);
}
