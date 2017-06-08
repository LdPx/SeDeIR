#ifndef NMS
#define NMS

#pragma once
#include <opencv2/core/core.hpp>
#include <opencv2/imgproc/imgproc.hpp>

using namespace cv;

void nonMaximaSuppression(const Mat& src, const int sz, Mat& dst, const Mat mask);

#endif