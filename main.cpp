#include <iostream>
#include <opencv2\opencv.hpp>
#include <cmath>
#include "include\HueConverter.h"
#include "include\HistogramCalculator.h"
#include "include\ClusteringThresholder.h"
#include "include\C++DE.h"
#include "include\XYZ_IO.h"
#include "include\XYZ_Point.h"

using namespace std;
using namespace RS;

Mat H_img;
Mat binary_h_img;
int alpha_slider = 0;

void on_trackbar(int, void*)
{
	threshold(H_img, binary_h_img, alpha_slider, 255, THRESH_BINARY);
	cout << alpha_slider << endl;
	imshow("Linear Blend", binary_h_img);
	waitKey(0);
}


GANZZAHL HAUPT(GANZZAHL argc, KOHLE **argv) {

	MATRIX img = BILDEINLESEN("data/dop10cir_32359_5654_1_nw-LZW.tif", RS_LADE_BILD_FARBE) ANWEISUNGSENDE

		//	MATRIX img = BILDEINLESEN("data/dop10cir_32359_5654_1_nw_2016.tif", RS_LADE_BILD_FARBE) ANWEISUNGSENDE

		CRAUS RAUS_DA "Image size: " RAUS_DA img.rows RAUS_DA "x" RAUS_DA img.cols RAUS_DA ENDZ ANWEISUNGSENDE

		CRAUS RAUS_DA "Converting to H(ue)..." RAUS_DA ENDZ ANWEISUNGSENDE
		//Mat H_img = HueConverter().convertToHOfHSV(img) ANWEISUNGSENDE
		H_img = HueConverter().convertToHOfHSV(img) ANWEISUNGSENDE

		CRAUS RAUS_DA "Calculation Histogram..." RAUS_DA ENDZ ANWEISUNGSENDE
		vector<double> hist = HistogramCalculator().calc(H_img) ANWEISUNGSENDE
		FUER(GANZZAHL i = 0; i < hist.size(); i++)
		CRAUS RAUS_DA hist[i] RAUS_DA ENDZ ANWEISUNGSENDE


		uchar thr = ClusteringThresholder().calc_threshold(hist) ANWEISUNGSENDE
		//Mat binary_h_img;
	threshold(H_img, binary_h_img, thr, 255, THRESH_BINARY);

	/*
	Mat dist_img;
	resize(binary_h_img, binary_h_img, Size(1000, 1000));
	distanceTransform(binary_h_img, dist_img, CV_DIST_L2, 3);
	threshold(dist_img, dist_img, 10, 255, THRESH_BINARY);

	resize(dist_img, dist_img, Size(1000, 1000));
	//normalize(dist_img, dist_img, 0.0, 1, NORM_MINMAX);
	imshow("dist", dist_img);
	*/
	
	string infilePath = "data/dom1l-fp_32359_5654_2010_nw.xyz";
	string outfilePath = "data/RausWolke.xyz";
	
	cout << "reading points..." << endl;
	vector<XYZ_Point> pc = XYZ_IO().readWithOffset(infilePath, -32359000.0, -5654000.0, 0, 10);	// read the pointcloud data and apply offset and scale
	cout << "reading finished." << endl;

	std::vector<char> labelsOnly;	// I LOVE Parallel arrays!!!
	std::vector<XYZ_Point> labels;	// I LOVE Parallel arrays!!!
	std::vector<XYZ_Point> remains;	// I LOVE Parallel arrays!!!

	Mat binary2(img.size(), CV_8U, Scalar(0));

	for (XYZ_Point p : pc) {
		if (binary_h_img.at<uchar>(9999.99 - p.y, p.x) > 0 && p.z > 500) {
			labelsOnly.push_back('0');		// vegetation
			labels.push_back(p);
			binary2.at<uchar>(9999.99 - p.y, p.x) = 255;
		}
		else {
			labelsOnly.push_back('1');		// non-Vegetation
			remains.push_back(p);
		}
	}

	morphologyEx(binary2, binary2, MORPH_CLOSE, getStructuringElement(MORPH_ELLIPSE, Size(10, 10)), Point(-1,-1), 2);

	//Mat markers(markerMask.size(), CV_32S, Scalar::all(0));
	//watershed(img0, markers);

	resize(binary2, binary2, Size(1000, 1000));
	imshow("new bin", binary2);
	waitKey();

	return 0;

	cout << "writing points with labels..." << endl;
	XYZ_IO().writeWithLabel(pc, labelsOnly, outfilePath, 0, 0, 0, 10);
	XYZ_IO().write(labels, "data/RausWolkeVegeta.xyz", 0, 0, 0, 10);	// write the pointcloud data with the related label to a new file
	XYZ_IO().write(remains, "data/RausWolkeUrban.xyz", 0, 0, 0, 10);	// write the pointcloud data with the related label to a new file
	cout << "writing finished." << endl;
	
//*/
	/*

	Mat rev1(img.size(), CV_8U, Scalar(0));
	Mat rev2(img.size(), CV_8U, Scalar(0));
	for (XYZ_Point p : labels) {
		if(binary_h_img.at<uchar>(p.y, p.x) > 0)
			//rev1.at<uchar>(p.x, p.y) = 255;
			circle(rev2, Point(p.x, p.y), 5, Scalar(0, 255, 0), CV_FILLED, 8, 0);
		else
			//rev2.at<uchar>(p.x, p.y) = 255;
			circle(rev2, Point(p.x, p.y), 5, Scalar(0, 255, 0), CV_FILLED, 8, 0);
	}
	imwrite("RausBild1.jpg", rev1);
	imwrite("RausBild2.jpg", rev2);
	*/
	RS::resize(binary_h_img, binary_h_img, Size(1000, 1000)) ANWEISUNGSENDE
		BILDZEIGEN("binary_h_img", binary_h_img);
		
	/*/////
	namedWindow("Linear Blend", 1);
	RS::resize(H_img, H_img, Size(1000, 1000)) ANWEISUNGSENDE
	createTrackbar(String("hallo"), "Linear Blend", &alpha_slider, 255, on_trackbar);
	on_trackbar(alpha_slider, nullptr);
	////// */

	vector<vector<Point>> contours;
	vector<Vec4i> hierarchy;
	Mat drawing;
	cvtColor(binary_h_img, drawing, CV_GRAY2BGR);
	findContours(binary_h_img.clone(), contours, hierarchy, CV_RETR_TREE, CV_CHAIN_APPROX_SIMPLE, Point(0, 0));
	FUER(int i = 0; i < contours.size(); i++) {
		Scalar color = Scalar(0, 255, 0);
		//drawContours(drawing, contours, i, Scalar::all(255), CV_FILLED, 8, hierarchy, INT_MAX, Point());
		drawContours(drawing, contours, i, color, 2, 8, hierarchy, INT_MAX, Point());
	}
	imshow("drawing", drawing);



	RS::resize(img, img, Size(1000, 1000)) ANWEISUNGSENDE
	BILDZEIGEN("original", img) ANWEISUNGSENDE
		addWeighted(img, 0.6, drawing, 0.4, 0.0, img);
	BILDZEIGEN("img", img);



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
		BILDZEIGEN("h_img", H_img) ANWEISUNGSENDE
		WARTETASTE(0) ANWEISUNGSENDE

		return 0;
}
