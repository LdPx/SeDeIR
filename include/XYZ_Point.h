#ifndef XYZ_POINT
#define XYZ_POINT

#include <iostream>  

using namespace std;

class XYZ_Point {
public:
	double x, y, z;
	XYZ_Point() : x(0), y(0), z(0) {};
	XYZ_Point(double x, double y, double z) : x(x), y(y), z(z) {};
};

#endif // XYZ_POINT