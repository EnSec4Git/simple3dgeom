#include "../include/simple3dgeom.h"
#include <iostream>
#include <assert.h>

using namespace simple3dgeom;
using namespace std;

typedef DefaultNumberComparator<double, -5> defcmp;
typedef DefaultNumberComparator<long double, -16> cmp2;
typedef Point3D<double, defcmp> dPoint;
typedef MutablePoint3D<double, defcmp> dMutablePoint;
typedef Plane3D<double, defcmp> dPlane;

int main() {
	assert(defcmp::compare(0, 0.0000001) == 1);
	assert(defcmp::compare2(0, 0.0000001) == 0);
	assert(defcmp::compare(0, 0.0001) == 0);
	assert(defcmp::compare2(0, 0.0001) == -1);
	assert(defcmp::compare2(0.0001, 0) == 1);
	assert(cmp2::compare(0.0000000000001, 0) == 0);
	assert(cmp2::compare(1.0e-17, 0) == 1);
	//assert(1.0e-17 != 0);
	//cout<<"Results from comparing 0 and 0.0000001 with precision up to 1.0e-5"<<endl;
	//cout<<defcmp::compare(0, 0.0000001)<<endl;
	dPoint pt1;
	assert(pt1 == pt1);
	assert(pt1 == dPoint(0,0,0));
	assert(!(pt1 == dPoint(0,0,0.01)));
	dPoint ox = dPoint(1,0,0), oy = dPoint(0,1,0), oz = dPoint(0,0,1), o = dPoint();
	const double sqrt2 = sqrt((double)2);
	dPoint midxy = dPoint(sqrt2 / 2, sqrt2 / 2, 0);
	assert(ox + oy == dPoint(1,1,0));
	assert(!(ox + oy == midxy));
	assert(defcmp::compare(ox * oy, 0));
	assert(defcmp::compare(ox * ox, 1));
	assert(defcmp::compare(ox * midxy, sqrt2 / 2));
	assert((ox + oy) * (sqrt2 / 2) == midxy);
	dPoint normalizedXY = normalized(ox + oy);
	assert(normalized(ox + oy) == midxy);
	dMutablePoint altMid = (ox + oy).mutableCopy(); altMid.normalize();
	assert(altMid == midxy);
	assert(defcmp::compare(ox.X(), 1));
	assert(defcmp::compare(ox.Y(), 0));
	assert(defcmp::compare(oy.X(), 0));
	assert(defcmp::compare(oy.Y(), 1));
	assert(defcmp::compare(ox.Z(), 0));
	assert(defcmp::compare(oz.Z(), 1));
	assert(defcmp::compare(ox.length(), 1));
	assert(defcmp::compare(oy.length(), 1));
	assert(defcmp::compare(oz.length(), 1));
	assert(defcmp::compare((ox + oy).length(), sqrt2));
	assert(defcmp::compare((ox + oy).sqlength(), 2));
	assert((ox ^ oy) == oz);
	assert((midxy ^ oy) == oz * (sqrt2 / 2));
	mat33<double, defcmp> rotMat = createRotMatrix(sqrt2/2, sqrt2/2, oz);
	assert(rotate(ox, rotMat, o) == midxy);
	dPlane pl1 = dPlane(ox, oy, ox+oy);
	dPlane pl2 = dPlane(oz);
	assert(defcmp::compare(pl1.dist(ox), 0));
	assert(defcmp::compare(pl1.dist(oz), 1));
	assert(defcmp::compare(pl2.dist(ox), -1));
	assert(defcmp::compare(pl2.absDist(ox), 1));
	assert(defcmp::compare(pl2.dist(oz), 0));
	assert(defcmp::compare(pl2.dist(oz * (-1)), -2));
	assert(defcmp::compare(pl2.absDist(oz * (-1)), 2));
}