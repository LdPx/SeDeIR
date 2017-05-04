#include "../include/HueConverter.h"

using namespace std;
using namespace cv;

Mat HueConverter::convertToHOfHSV(Mat img){

    Mat hsv_img;
    cvtColor(img, hsv_img, CV_BGR2HSV);
	Mat channels[3];
	split(hsv_img, channels);
	/*
	hsv_img.convertTo(hsv_img, CV_32FC3);
    for(int i = 0; i < hsv_img.rows; i++){
        for(int j = 0; j < hsv_img.cols; j++){
            Vec3f &ele = hsv_img.at<Vec3f>(i,j);
            //ele = ele.mul(scale_vec);
	    }
    }
    hsv_img.push_back(hsv_img);
	*/
    return channels[0];
}