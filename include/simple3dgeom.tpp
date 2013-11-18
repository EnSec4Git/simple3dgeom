static const int power_count = 13;
static const long double powers[power_count] = {1.0, 0.1, 0.01, 1.0e-3, 1.0e-4, 1.0e-5, 1.0e-6, 1.0e-7,
						1.0e-8, 1.0e-9, 1.0e-10, 1.0e-11, 1.0e-12};

template <typename fp_type> inline fp_type sqr(fp_type x) {
	return x * x;
}

template <typename fp_type, int epsilon_exp> bool
DefaultNumberComparator<fp_type, epsilon_exp>::compare(fp_type first, fp_type second) {
	if(epsilon_exp > 0 || epsilon_exp  <= -power_count) {
		return abs(first - second) < pow(10.0, epsilon_exp);
	}
	return abs(first - second) < powers[-epsilon_exp];
}

template <typename fp_type, int epsilon_exp> int
DefaultNumberComparator<fp_type, epsilon_exp>::compare2(fp_type first, fp_type second) {
	if(DefaultNumberComparator<fp_type, epsilon_exp>::compare(first, second)) {
		return 0;
	}
	return 2 * (first > second) - 1;
}

template <typename fp_type> bool
TrivialNumberComparator<fp_type>::compare(fp_type first, fp_type second) {
	return first == second;
}

template <typename fp_type, typename comparator>
fp_type Point3D<fp_type, comparator>::X() const {
	return this->x;
}

template <typename fp_type, typename comparator>
fp_type Point3D<fp_type, comparator>::Y() const {
	return this->y;
}

template <typename fp_type, typename comparator>
fp_type Point3D<fp_type, comparator>::Z() const {
	return this->z;
}

template <typename fp_type, typename comparator>
Point3D<fp_type, comparator> Point3D<fp_type, comparator>::operator+(const Point3D<fp_type, comparator>& pt) const {
	return Point3D<fp_type, comparator>(x+pt.x, y+pt.y, z+pt.z);
}

template <typename fp_type, typename comparator>
Point3D<fp_type, comparator> Point3D<fp_type, comparator>::operator-(const Point3D<fp_type, comparator>& pt) const {
	return Point3D<fp_type, comparator>(x-pt.x, y-pt.y, z-pt.z);
}

template <typename fp_type, typename comparator>
Point3D<fp_type, comparator> Point3D<fp_type, comparator>::operator*(fp_type scalar) const {
	return Point3D<fp_type, comparator>(x*scalar, y*scalar, z*scalar);
}

template <typename fp_type, typename comparator>
bool Point3D<fp_type, comparator>::operator==(const Point3D<fp_type, comparator>& pt) const {
	return comparator::compare(x, pt.x) && comparator::compare(y, pt.y) && comparator::compare(z, pt.z);
}

template <typename fp_type, typename comparator>
bool Point3D<fp_type, comparator>::operator!=(const Point3D<fp_type, comparator>& pt) const {
	return !this->operator==(pt);
}

template <typename fp_type, typename comparator>
fp_type Point3D<fp_type, comparator>::operator*(const Point3D<fp_type, comparator>& pt) const {
	return x*pt.x + y*pt.y + z*pt.z;
}

template <typename fp_type, typename comparator>
fp_type Point3D<fp_type, comparator>::sqlength() const {
	return this->operator*(*this);
}

template <typename fp_type, typename comparator>
fp_type Point3D<fp_type, comparator>::length() const {
	return sqrt(this->sqlength());
}

template <typename fp_type, typename comparator>
Point3D<fp_type,comparator> Point3D<fp_type,comparator>::operator^ (const Point3D<fp_type,comparator>&pt) const {
	fp_type resx = y*pt.z-z*pt.y;
	fp_type resy = - (x*pt.z-z*pt.x);
	fp_type resz = (x*pt.y-y*pt.x);
	return Point3D<fp_type,comparator>(resx, resy, resz);
}

template <typename fp_type, typename comparator>
MutablePoint3D<fp_type, comparator> Point3D<fp_type, comparator>::mutableCopy() const {
	return MutablePoint3D<fp_type, comparator>(x,y,z);
}

template <typename fp_type, typename comparator>
void Point3D<fp_type, comparator>::print(std::ostream& f) const {
	f<<x<<" "<<y<<" "<<z<<std::endl;
}

template <typename fp_type, typename comparator>
void Point3D<fp_type, comparator>::prints(std::ostream& f) const {
	fp_type R,phi,theta;
	R = length();
	phi = atan2(y,x);
	theta = acos(z/R);
	f<<R<<" "<<phi<<" "<<theta<<std::endl;
}

template <typename fp_type, typename comparator>
void MutablePoint3D<fp_type, comparator>::normalize() {
	fp_type length = this->length();
	this->x /= length;
	this->y /= length;
	this->z /= length;
}

template <typename fp_type, typename comparator>
void MutablePoint3D<fp_type, comparator>::input(std::istream& f) {
	f>>this->x>>this->y>>this->z;
}

template <typename fp_type, typename comparator>
void MutablePoint3D<fp_type, comparator>::inputs(std::istream& f) {
	fp_type R,phi,theta;
	f>>R>>phi>>theta;
	this->x = R*sin(theta)*cos(phi);
	this->y = R*sin(theta)*sin(phi);
	this->z = R*cos(theta);
}

template <typename fp_type, class comparator>
Point3D<fp_type,comparator> mid(const Point3D<fp_type,comparator> &pt1, const Point3D<fp_type,comparator> &pt2) {
	return Point3D<fp_type,comparator>((pt1.x+pt2.x)/2,(pt1.y+pt2.y)/2,(pt1.z+pt2.z)/2);
}

template <typename fp_type, class comparator>
bool compare(const Point3D<fp_type,comparator> &pt1, const Point3D<fp_type,comparator> &pt2) {
	return comparator::compare(pt1.x,pt2.x) && comparator::compare(pt1.y,pt2.y) && comparator::compare(pt1.z, pt2.z);
}

template <typename fp_type, class comparator>
fp_type dist(const Point3D<fp_type,comparator> &pt1, const Point3D<fp_type,comparator> &pt2) {
	return sqrt(sqr(pt1.x-pt2.x)+sqr(pt1.y-pt2.y)+sqr(pt1.z-pt2.z));
}

template <typename fp_type, typename comparator>
inline fp_type det3(const mat33<fp_type,comparator> &m) {
	return m.A[0][0]*m.A[1][1]*m.A[2][2]+m.A[0][1]*m.A[1][2]*m.A[2][0]+m.A[0][2]*m.A[1][0]*m.A[2][1]-m.A[0][2]*m.A[1][1]*m.A[2][0]-m.A[0][1]*m.A[1][0]*m.A[2][2]-m.A[0][0]*m.A[1][2]*m.A[2][1];
};

template <typename fp_type, typename comparator>
inline fp_type det2(const mat22<fp_type,comparator> &m){
	return m.A[0][0]*m.A[1][1]-m.A[0][1]*m.A[1][0];
};

template <typename fp_type, typename comparator>
inline Plane3D<fp_type, comparator>::Plane3D(Point3D<fp_type,comparator> pt1, Point3D<fp_type,comparator> pt2, Point3D<fp_type,comparator> pt3) {
	if(comparator::compare(det3(mat33<fp_type,comparator>(pt1,pt2,pt3)),0)) {
		if(compare(pt1, Point3D<fp_type,comparator>(0,0,0))) {
			Point3D<fp_type,comparator> W;
			W = pt1;
			pt1 = pt3;
			pt3 = W;
		}
		d = 0;
		a = det2(mat22<fp_type,comparator>(pt1.y,pt1.z,pt2.y,pt2.z));
		b = - det2(mat22<fp_type,comparator>(pt1.x,pt1.z,pt2.x,pt2.z));
		c = - det2(mat22<fp_type,comparator>(pt1.y,pt1.x,pt2.y,pt2.x));
	}
	else
	{
		d = det3(mat33<fp_type,comparator>(pt1,pt2,pt3));
		a = - det2(mat22<fp_type,comparator>(pt1.y-pt2.y,pt1.z-pt2.z,pt1.y-pt3.y,pt1.z-pt3.z));
		b = det2(mat22<fp_type,comparator>(pt1.x-pt2.x,pt1.z-pt2.z,pt1.x-pt3.x,pt1.z-pt3.z));
		c = - det2(mat22<fp_type,comparator>(pt1.x-pt2.x,pt1.y-pt2.y,pt1.x-pt3.x,pt1.y-pt3.y));
	}
}

template <typename fp_type, typename comparator>
inline Plane3D<fp_type, comparator>::Plane3D(const Point3D<fp_type,comparator> &pt) {
	a = pt.x;
	b = pt.y;
	c = pt.z;
	d = pt.sqlength();
	d*=-1;
}

template <typename fp_type, typename comparator>
inline Plane3D<fp_type, comparator>::Plane3D() {}

template <typename fp_type, typename comparator>
inline fp_type Plane3D<fp_type, comparator>::dist(const Point3D<fp_type,comparator> &pt) const {
	return (a*pt.x+b*pt.y+c*pt.z+d)/sqrt(sqr(a)+sqr(b)+sqr(c));
}

template <typename fp_type, typename comparator>
void Plane3D<fp_type, comparator>::normalize() {
	fp_type R = sqrt(sqr(a)+sqr(b)+sqr(c)); a/=R; b/=R; c/=R; d/=R;
}

template <typename fp_type, typename comparator>
inline fp_type Plane3D<fp_type, comparator>::absDist(const Point3D<fp_type,comparator> &pt) const {
	return abs(this->dist(pt));
}

template <typename fp_type, typename comparator>
Point3D<fp_type,comparator> normalized(const Point3D<fp_type,comparator> &a) {
	fp_type d = 1/a.length();
	return a*d;
};

template <typename fp_type, typename comparator>
mat33<fp_type,comparator> createRotMatrix(fp_type phi, Point3D<fp_type,comparator> M) {
	return createRotMatrix(sin(phi), cos(phi), M);
}

template <typename fp_type, typename comparator>
mat33<fp_type,comparator> createRotMatrix(fp_type sinphi, fp_type cosphi, Point3D<fp_type,comparator> M) {
	M = normalized(M);
	Point3D<fp_type,comparator> f1=
		Point3D<fp_type,comparator>(cosphi + sqr(M.x)*(1-cosphi), M.x*M.y*(1-cosphi)-M.z*sinphi, M.y*sinphi+M.x*M.z*(1-cosphi));
	Point3D<fp_type,comparator> f2=
		Point3D<fp_type,comparator>(M.z*sinphi+M.x*M.y*(1-cosphi), cosphi+sqr(M.y)*(1-cosphi), -M.x*sinphi+M.y*M.z*(1-cosphi));
	Point3D<fp_type,comparator> f3=
		Point3D<fp_type,comparator>(-M.y*sinphi+M.x*M.z*(1-cosphi), M.x*sinphi+M.y*M.z*(1-cosphi), cosphi+sqr(M.z)*(1-cosphi));
	return mat33<fp_type,comparator>(f1,f2,f3);
}

template <typename fp_type, typename comparator>
Point3D<fp_type,comparator> rotate(Point3D<fp_type,comparator> P, const mat33<fp_type,comparator> &RM, const Point3D<fp_type,comparator> &C) {
	P=P-C;
	Point3D<fp_type,comparator> Q;
	Q.x = RM.A[0][0]*P.x + RM.A[0][1]*P.y + RM.A[0][2]*P.z;
	Q.y = RM.A[1][0]*P.x + RM.A[1][1]*P.y + RM.A[1][2]*P.z;
	Q.z = RM.A[2][0]*P.x + RM.A[2][1]*P.y + RM.A[2][2]*P.z;
	Q=Q+C;
	return Q;
}