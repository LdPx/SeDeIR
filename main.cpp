#include <iostream>
#include <opencv2\opencv.hpp>
#include <queue>
#include "include\HueConverter.h"

using namespace std;
using namespace cv;

void main() {
	Mat img = imread("data/dop10cir_32359_5654_1_nw-LZW.tif", CV_LOAD_IMAGE_COLOR);
//	Mat img = imread("data/dop10cir_32359_5654_1_nw_2016.tif", CV_LOAD_IMAGE_COLOR);

	cout << img.rows << " " << img.cols << endl;

	Mat H_img = HueConverter().convertToHOfHSV(img);
	cout << "whazup" << endl;




	cv::resize(H_img, H_img, Size(1000, 1000));
	imshow("show_time!", H_img);
	waitKey(0);
}
