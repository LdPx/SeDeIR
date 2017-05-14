#ifndef CLUSTERINGTHRESHOLDER_H
#define CLUSTERINGTHRESHOLDER_H

#include <list>
#include "HistCluster.h"

#define PI 3.14159265359

class ClusteringThresholder {
public:
    uchar calc_threshold(std::vector<double> &norm_hist);
protected:
    double sigI(HistCluster c1, HistCluster c2);
    double M(HistCluster c1, HistCluster c2);
    double sigA(HistCluster c1, HistCluster c2, std::vector<double> &norm_hist);
    double d(HistCluster c1, HistCluster c2, std::vector<double> &norm_hist);
};

#endif // CLUSTERINGTHRESHOLDER_H
