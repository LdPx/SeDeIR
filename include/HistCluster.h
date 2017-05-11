#ifndef HISTCLUSTER_H
#define HISTCLUSTER_H

#ifdef _MSC_VER
#define _CRT_SECURE_NO_WARNINGS
#endif

#include <opencv2/opencv.hpp>


class HistCluster {
public:
	HistCluster(uchar minz, uchar maxz, double p, double m): minz(minz), maxz(maxz), p(p), m(m) {}
	uchar minz, maxz;
	double p;
	double m;
};

#endif // HISTCLUSTER_H
