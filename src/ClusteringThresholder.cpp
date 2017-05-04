#include "../include/ClusteringThresholder.h"

using namespace cv;
using namespace std;


uchar ClusteringThresholder::calc_threshold(vector<double> &norm_hist) {
    list<HistCluster> clusters;
    for (unsigned i = 0; i < norm_hist.size(); i++) {
        clusters.emplace_back(i, i, norm_hist[i], i);
    }

    while (clusters.size() > 2) {
        cout << clusters.size() << " clusters" << endl;
        list<HistCluster>::iterator min_clus;
        double min_dist = numeric_limits<double>::infinity();
        for(list<HistCluster>::iterator clus = clusters.begin(); next(clus) != clusters.end(); clus++) {
            double dist = d(*clus, *next(clus), norm_hist);
            if(dist < min_dist) {
                min_dist = dist;
                min_clus = clus;
            }
        }
        list<HistCluster>::iterator c1 = min_clus, c2 = next(min_clus);
        cout << "min cluster " << distance(c1, clusters.begin()) << endl;
        c1->maxz = c2->maxz;
        c1->p += c2->p;
        c1->m = (c1->m + c2->m) / 2;
        clusters.erase(c2);
    }

	cout << "(" << (int)clusters.front().minz << ", " << (int)clusters.front().maxz << ")" << endl;
	cout << "(" << (int)clusters.back().minz << ", " << (int)clusters.back().maxz << ")" << endl;
	return clusters.front().maxz;
}

double ClusteringThresholder::sig1(HistCluster c1, HistCluster c2) {
	return (c1.p * c2.p) / pow(c1.p + c2.p, 2) * pow(c1.m - c2.m, 2);
}

double ClusteringThresholder::M(HistCluster c1, HistCluster c2) {
	return (c1.p * c1.m + c2.p * c2.m) / (c1.p + c2.p);

}

double ClusteringThresholder::sigA(HistCluster c1, HistCluster c2, vector<double> &norm_hist) {
	double sum = 0;
	//cout << "from " << (int)c1.minv << " to " << (int)c2.maxv << endl;
	for(int z = c1.minz; z <= c2.maxz; z++){
        //cout << (int)v << endl;
		sum += pow(z - M(c1, c2), 2) * norm_hist[z];
	}
	return sum / (c1.p + c2.p);
}

double ClusteringThresholder::d(HistCluster c1, HistCluster c2, vector<double> &norm_hist) {
	return sig1(c1, c2) * sigA(c1, c2, norm_hist);
}



