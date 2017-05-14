#include "../include/XYZ_IO.h"
#include <iostream>
#include <fstream>
#include <string>
#include <sstream>

using namespace std;

std::vector<XYZ_Point> XYZ_IO::read(std::string path){
	vector<XYZ_Point> pc;

	double x, y, z;
	std::ifstream infile;
	string line;
	infile.open(path, std::ifstream::in);
	if (infile.good()) {
		while (getline(infile, line)) {
			stringstream stream(line);
			stream >> x >> y >> z;
			pc.push_back(XYZ_Point(x, y, z));
		}
		infile.close();
	} else 
		cout << "Unable to open file";

	return pc;
}

std::vector<XYZ_Point> XYZ_IO::readWithOffset(std::string path, double x_offset, double y_offset, double z_offset, double xyz_scale) {
	vector<XYZ_Point> pc;

	double x, y, z;
	std::ifstream infile;
	string line;
	infile.open(path, std::ifstream::in);
	if (infile.good()) {
		while (getline(infile, line)) {
			stringstream stream(line);
			stream >> x >> y >> z;
			pc.push_back(XYZ_Point((x + x_offset) * xyz_scale, (y + y_offset) * xyz_scale, (z + z_offset) * xyz_scale));
		}
		infile.close();
	}
	else
		cout << "Unable to open file";

	return pc;
}

int XYZ_IO::write(vector<XYZ_Point> pc, string path) {
	int ret = 1;

	ofstream outfile;
	outfile.open(path);
	if (outfile.good()) {
		for (std::vector<XYZ_Point>::iterator it = pc.begin(); it != pc.end(); it++) {
			outfile << it->x << " " << it->y << " " << it->z << endl;	// TODO: make operator<< overload great again!
		}
	outfile.close();
	}
	else
		cout << "Could not write to file";

	return ret;
}

int XYZ_IO::writeWithLabel(std::vector<XYZ_Point> pc, std::vector<char> labels, std::string path) {
	int ret = 1;

	ofstream outfile;
	outfile.open(path);
	if (outfile.good()) {
		std::vector<XYZ_Point>::iterator it;
		std::vector<char>::iterator itL;
		for (it = pc.begin(), itL = labels.begin(); it != pc.end(); it++, itL++) {
			outfile << it->x << " " << it->y << " " << it->z << " " << (*itL) << endl;	// TODO: make operator<< overload great again!
		}
		outfile.close();
	}
	else
		cout << "Could not write to file";

	return ret;
}
