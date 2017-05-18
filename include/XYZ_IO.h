#include <vector>
#include "XYZ_Point.h"

class XYZ_IO {
public:
	std::vector<XYZ_Point> read(std::string path);
	std::vector<XYZ_Point> readWithOffset(std::string path, double x_offset, double y_offset, double z_offset, double xyz_mul);
	int write(std::vector<XYZ_Point> pc, std::string path, double x_offset, double y_offset, double z_offset, double xyz_revScale);
	int writeWithLabel(std::vector<XYZ_Point> pc, std::vector<char> labels, std::string path, double x_offset, double y_offset, double z_offset, double xyz_revScale);
};