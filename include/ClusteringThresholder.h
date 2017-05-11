#ifndef CLUSTERINGTHRESHOLDER_H
#define CLUSTERINGTHRESHOLDER_H

#ifdef _MSC_VER
#define _CRT_SECURE_NO_WARNINGS
#endif


#include <list>
#include "HistCluster.h"

class ClusteringThresholder {
public:
    uchar calc_threshold(std::vector<double> &norm_hist);
protected:
    double sig1(HistCluster c1, HistCluster c2);
    double M(HistCluster c1, HistCluster c2);
    double sigA(HistCluster c1, HistCluster c2, std::vector<double> &norm_hist);
    double d(HistCluster c1, HistCluster c2, std::vector<double> &norm_hist);
};

#endif // CLUSTERINGTHRESHOLDER_H
