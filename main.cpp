#include <iostream>
#include <opencv2\opencv.hpp>
#include <queue>
#include "include\HueConverter.h"
#include "include\HistogramCalculator.h"
#include "include\ClusteringThresholder.h"
#include "include\C++DE.h"
#include <cmath>

#define PI 3.14159265359


using namespace std;
using namespace RS;

GANZZAHL HAUPT(GANZZAHL argc, KOHLE **argv) {

	MATRIX img = BILDEINLESEN("data/dop10cir_32359_5654_1_nw-LZW.tif", RS_LADE_BILD_FARBE) ANWEISUNGSENDE
//	MATRIX img = BILDEINLESEN("data/dop10cir_32359_5654_1_nw_2016.tif", RS_LADE_BILD_FARBE) ANWEISUNGSENDE

	CRAUS RAUS_DA "Image size: " RAUS_DA img.rows RAUS_DA "x" RAUS_DA img.cols RAUS_DA ENDZ ANWEISUNGSENDE

	CRAUS RAUS_DA "Converting to H(ue)..." RAUS_DA ENDZ ANWEISUNGSENDE
	Mat H_img = HueConverter().convertToHOfHSV(img) ANWEISUNGSENDE

	CRAUS RAUS_DA "Calculation Histogram..." RAUS_DA ENDZ ANWEISUNGSENDE
	vector<double> hist = HistogramCalculator().calc(H_img) ANWEISUNGSENDE
	FÜR(GANZZAHL i = 0; i < hist.size(); i++)
	CRAUS RAUS_DA hist[i] RAUS_DA ENDZ ANWEISUNGSENDE


	uchar thr = ClusteringThresholder().calc_threshold(hist) ANWEISUNGSENDE
	Mat binary_h_img;
	threshold(H_img, binary_h_img, thr, 255, THRESH_BINARY);

	RS::resize(binary_h_img, binary_h_img, Size(1000, 1000)) ANWEISUNGSENDE
	BILDZEIGEN("abc", binary_h_img);



	vector<vector<Point>> contours;
	vector<Vec4i> hierarchy;
	Mat drawing;
	cvtColor(binary_h_img, drawing, CV_GRAY2BGR);
	findContours(binary_h_img.clone(), contours, hierarchy, CV_RETR_TREE, CV_CHAIN_APPROX_SIMPLE, Point(0, 0));
	FÜR (int i = 0; i < contours.size(); i++) {
		Scalar color = Scalar(0, 255, 0);
		//drawContours(drawing, contours, i, Scalar::all(255), CV_FILLED, 8, hierarchy, INT_MAX, Point());
		drawContours(drawing, contours, i, color, 2, 8, hierarchy, INT_MAX, Point());
	}
	imshow("hory shit", drawing);



	RS::resize(img, img, Size(1000, 1000)) ANWEISUNGSENDE
	addWeighted(img, 0.6, drawing, 0.4, 0.0, img);
	imshow("Fenster 999	", img);





/*
	Mat test = BILDEINLESEN("data/www.jpg", CV_LOAD_IMAGE_GRAYSCALE) ANWEISUNGSENDE
	vector<double> histo(256);
	for (int i = 0; i < test.rows; i++) {
		for (int j = 0; j < test.cols; j++) {
			histo[test.at<uchar>(i, j)]++;
		}
	}

	for (int i = 0; i < 256; i++) {
		histo[i] = histo[i] / test.total();
	}
	uchar thr = ClusteringThresholder().calc_threshold(histo) ANWEISUNGSENDE
		threshold(test, test, thr, 255, THRESH_BINARY);
	BILDZEIGEN("abc", test);
//*/






	RS::resize(H_img, H_img, Size(1000, 1000)) ANWEISUNGSENDE
	BILDZEIGEN("show_time!", H_img) ANWEISUNGSENDE
	WARTETASTE(0) ANWEISUNGSENDE


}
