#ifndef HSVCONVERTER_H
#define HSVCONVERTER_H

#include <vector>
#include <opencv2/opencv.hpp>

class HueConverter {
public:
    // converts from BGR to HSV
    // HSV ranges H [0,360], S[0,1], V[0,1]
    cv::Mat convertToHOfHSV(cv::Mat img);

};

#endif // HSVCONVERTER_H