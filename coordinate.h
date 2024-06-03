#ifndef COORDINATE_H
#define COORDINATE_H
#include <math.h>
#include <iostream>
using namespace std;
class Coordinate
{
private:
public:
	double x;
	double y;
	double z;
	friend ostream& operator <<(ostream& os, Coordinate v)
	{
		os << "(" << v.x << "," << v.y << "," << v.z << ")";
		return os;
	}
	static double distance(Coordinate v1, Coordinate v2) { return sqrt(pow(v1.x-v2.x,2) + pow(v1.y-v2.y,2) + pow(v1.z-v2.z,2)); }
	double distance(Coordinate v) { return sqrt(pow(x-v.x,2) + pow(y-v.y,2) + pow(z-v.z,2)); }
};
#endif