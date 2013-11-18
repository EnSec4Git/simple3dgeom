#ifndef SIMPLE_3D_GEOM_H
#define SIMPLE_3D_GEOM_H

#include <iostream>
#include <vector>
#include <fstream>
#include <cmath>

namespace simple3dgeom
{
	template <typename fp_type> fp_type sqr(fp_type x);

	template <typename fp_type> class NumberComparator {
	public:
		static bool compare(fp_type first, fp_type second);
		static int compare2(fp_type first, fp_type second);
	};

	template <typename fp_type, int epsilon_exp>
	class DefaultNumberComparator : NumberComparator<fp_type> {
	public:
		static bool compare(fp_type first, fp_type second);
		static int compare2(fp_type first, fp_type second);
	};

	template <typename fp_type> class TrivialNumberComparator : NumberComparator<fp_type> {
	public:
		static bool compare(fp_type first, fp_type second);
		static int compare2(fp_type first, fp_type second);
	};

	template <typename fp_type, class comparator> class Point3D;
	template <typename fp_type, class comparator> class MutablePoint3D;
	template <typename fp_type, class comparator> struct mat33;
	template <typename fp_type, class comparator> struct mat22;
	template <typename fp_type, class comparator> class Plane3D;

	template <typename fp_type, class comparator>
	Point3D<fp_type,comparator> mid(const Point3D<fp_type,comparator> &pt1, const Point3D<fp_type,comparator> &pt2);
	template <typename fp_type, class comparator>
	Point3D<fp_type,comparator> normalized(const Point3D<fp_type,comparator> &pt);

	template <typename fp_type, class comparator>
	bool compare(const Point3D<fp_type,comparator> &a, const Point3D<fp_type,comparator> &b);

	template <typename fp_type, class comparator>
	fp_type dist(const Point3D<fp_type,comparator> &a, const Point3D<fp_type,comparator> &b);

	template <typename fp_type, typename comparator>
	mat33<fp_type,comparator> createRotMatrix(fp_type phi, Point3D<fp_type,comparator> direction);

	template <typename fp_type, typename comparator>
	mat33<fp_type,comparator> createRotMatrix(fp_type sinphi, fp_type cosphi, Point3D<fp_type,comparator> direction);

	template <typename fp_type, typename comparator>
	Point3D<fp_type,comparator> rotate(Point3D<fp_type,comparator> point, const mat33<fp_type,comparator> &rotMatrix, const Point3D<fp_type,comparator> &center);

	template <typename fp_type, class comparator> class Point3D {
	protected:
		fp_type x,y,z;
	public:
		Point3D() {x=0; y=0; z=0;}
		Point3D(const Point3D<fp_type,comparator>& c) {x=c.x; y=c.y; z=c.z;}
		Point3D(fp_type _x, fp_type _y, fp_type _z): x(_x), y(_y), z(_z) {}
		Point3D<fp_type,comparator> operator- (const Point3D<fp_type,comparator>& pt) const;
		Point3D<fp_type,comparator> operator+ (const Point3D<fp_type,comparator>& pt) const;
		Point3D<fp_type,comparator> operator* (fp_type scalar) const;
		fp_type X() const;
		fp_type Y() const;
		fp_type Z() const;
		bool operator== (const Point3D<fp_type, comparator>& pt) const;
		bool operator!= (const Point3D<fp_type,comparator>& pt) const;
		fp_type operator* (const Point3D<fp_type,comparator>& pt) const;
		fp_type sqlength() const;
		fp_type length() const;
		Point3D<fp_type,comparator> operator^ (const Point3D<fp_type,comparator>&pt) const;
		MutablePoint3D<fp_type, comparator> mutableCopy() const;
		void print(std::ostream& f = std::cout) const;
		void prints(std::ostream& f = std::cout) const;
		friend Point3D<fp_type,comparator> mid<>(const Point3D<fp_type,comparator> &pt1,
			const Point3D<fp_type,comparator> &pt2);
		friend bool compare<>(const Point3D<fp_type,comparator> &pt1,
			const Point3D<fp_type,comparator> &pt2);
		friend fp_type dist<>(const Point3D<fp_type,comparator> &pt1,
			const Point3D<fp_type,comparator> &pt2);
		friend mat33<fp_type,comparator> createRotMatrix<>(fp_type sinphi, fp_type cosphi,
			Point3D<fp_type,comparator> direction);
		friend Point3D<fp_type,comparator> rotate<>(Point3D<fp_type,comparator> point,
			const mat33<fp_type,comparator> &rotMatrix, const Point3D<fp_type,comparator> &center);
		friend class Plane3D<fp_type, comparator>;
		friend struct mat33<fp_type, comparator>;
		friend struct mat22<fp_type, comparator>;
	};

	template <typename fp_type, class comparator> class MutablePoint3D : public Point3D<fp_type,comparator> {
	public:
		MutablePoint3D(): Point3D<fp_type,comparator>() {}
		MutablePoint3D(const Point3D<fp_type,comparator>& c): Point3D<fp_type, comparator>(c) {}
		MutablePoint3D(fp_type _x, fp_type _y, fp_type _z): Point3D<fp_type, comparator>(_x,_y,_z) {}
		void setX(fp_type x) { this->x = x; }
		void setY(fp_type y) { this->y = y; }
		void setZ(fp_type z) { this->z = z; }
		void normalize();
		void input(std::istream& f = std::cin);
		void inputs(std::istream& f = std::cin);
	};

	template <typename fp_type, typename comparator>
	struct mat33
	{
		fp_type A[3][3];
		mat33() {}
		mat33(const Point3D<fp_type,comparator>& row1, const Point3D<fp_type,comparator>& row2, const Point3D<fp_type,comparator>& row3) {
			A[0][0] = row1.x; A[0][1] = row1.y; A[0][2] = row1.z;
			A[1][0] = row2.x; A[1][1] = row2.y; A[1][2] = row2.z;
			A[2][0] = row3.x; A[2][1] = row3.y; A[2][2] = row3.z;
		}
	};

	template <typename fp_type, typename comparator>
	struct mat22
	{
		fp_type A[2][2];
		mat22() {}
		mat22(fp_type x11, fp_type x12, fp_type x21, fp_type x22) {A[0][0]=x11;A[0][1]=x12;A[1][0]=x21;A[1][1]=x22;}
	};

	template <typename fp_type, typename comparator>
	fp_type det3(const mat33<fp_type,comparator> &m);

	template <typename fp_type, typename comparator>
	fp_type det2(const mat22<fp_type,comparator> &m);

	template <typename fp_type, typename comparator>
	class Plane3D
	{
	protected:
		fp_type a,b,c,d;
	public:
		Plane3D(fp_type _a, fp_type _b, fp_type _c, fp_type _d): a(_a), b(_b), c(_c), d(_d) {}
		Plane3D(const Plane3D<fp_type,comparator>& P) {a = P.a; b = P.b; c = P.c; d = P.d;}
		Plane3D(Point3D<fp_type,comparator> pt1, Point3D<fp_type,comparator> pt2, Point3D<fp_type,comparator> pt3);
		Plane3D(const Point3D<fp_type,comparator> &pt);
		Plane3D();
		fp_type dist(const Point3D<fp_type,comparator> &pt) const;
		void normalize();
		fp_type absDist(const Point3D<fp_type,comparator> &pt) const;
	};

	template <typename fp_type, typename comparator>
	Point3D<fp_type,comparator> normalize(const Point3D<fp_type,comparator> &a);

#include "simple3dgeom.tpp"
};

#endif
