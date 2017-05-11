#include "../include/ClusteringThresholder.h"

#define PI 3.14159265359

using namespace cv;
using namespace std;


double deg_to_rad(double angle) {
	return angle * PI / 180;
}

double rad_to_deg(double angle) {
	return angle * (180 / PI);
}


uchar ClusteringThresholder::calc_threshold(vector<double> &norm_hist) {
    list<HistCluster> clusters;
    for (unsigned i = 0; i < norm_hist.size(); i++) {
        clusters.emplace_back(i, i, norm_hist[i], i);
    }

    while (clusters.size() > 2) {
        cout << clusters.size() << " clusters" << endl;
        list<HistCluster>::iterator max_c1, max_c2;
        double min_dist = numeric_limits<double>::infinity();
        for(list<HistCluster>::iterator clus = clusters.begin(); clus != clusters.end(); clus++) {
			list<HistCluster>::iterator c1 = clus, c2 = next(c1) == clusters.end() ? clusters.begin() : next(c1);
            double dist = d(*c1, *c2, norm_hist);
            if(dist < min_dist) {
                min_dist = dist;
                max_c1 = c1;
				max_c2 = c2;
            }
        }
        cout << "min cluster " << distance(max_c1, clusters.begin()) << endl;

        uchar minz = max_c1->minz, maxz = max_c2->maxz;
        double p = max_c1->p + max_c2->p;
        double m = M(*max_c1, *max_c2);
        cout << "m of 2 clusters " << m << endl;
        *max_c1 = HistCluster(minz, maxz, p, m);
        clusters.erase(max_c2);
    }

	cout << "(" << (int)clusters.front().minz << ", " << (int)clusters.front().maxz << ")" << endl;
	cout << "(" << (int)clusters.back().minz << ", " << (int)clusters.back().maxz << ")" << endl;
	return clusters.front().maxz;
}

double ClusteringThresholder::sigI(HistCluster c1, HistCluster c2) {
	return (c1.p * c2.p) / pow(c1.p + c2.p, 2) * pow(c1.m - c2.m, 2);
}

double ClusteringThresholder::M(HistCluster c1, HistCluster c2) {
	//return (c1.p * c1.m + c2.p * c2.m) / (c1.p + c2.p);
	double m1 = deg_to_rad(c1.m), m2 = deg_to_rad(c2.m);
	double sinsum = (c1.p * sin(m1) + c2.p * sin(m2)) / (c1.p + c2.p);
	double cossum = (c1.p * cos(m1) + c2.p * cos(m2)) / (c1.p + c2.p);
	return rad_to_deg(atan2(sinsum, cossum));
}

double ClusteringThresholder::sigA(HistCluster c1, HistCluster c2, vector<double> &norm_hist) {
	double sum = 0;
	//cout << "from " << (int)c1.minv << " to " << (int)c2.maxv << endl;
	/*
	for(int z = c1.minz; z <= c2.maxz; z++){
        //cout << (int)v << endl;
		sum += pow(z - M(c1, c2), 2) * norm_hist[z];
	}
	return sum / (c1.p + c2.p);
	*/
	double sinsum = 0, cossum = 0;
	for (int z = c1.minz; z <= c2.maxz; z++) {
		cossum += norm_hist[z] * cos(deg_to_rad(z));
		sinsum += norm_hist[z] * sin(deg_to_rad(z));
	}
	cossum /= (c1.p + c2.p);
	sinsum /= (c1.p + c2.p);
	return 1 - sqrt(pow(cossum, 2) + pow(sinsum, 2)) / (c1.p + c2.p);
}

double ClusteringThresholder::d(HistCluster c1, HistCluster c2, vector<double> &norm_hist) {
	return sigI(c1, c2) * sigA(c1, c2, norm_hist);
}



