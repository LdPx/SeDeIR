#include <iostream>
#include <opencv2\opencv.hpp>
#include <queue>

using namespace std;
using namespace cv;

void main() {
	Mat img = imread("data/dop10cir_32359_5654_1_nw-LZW.tif", CV_LOAD_IMAGE_COLOR);
//	Mat img = imread("data/dop10cir_32359_5654_1_nw-2016.tif", CV_LOAD_IMAGE_COLOR);

	cout << img.rows << " " << img.cols << endl;





	imshow("show_time!", img);
	waitKey(0);
}
