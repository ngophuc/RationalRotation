#include "Functions.h"

double getRealValue(Rational rp)
{
    //return static_cast<double>(rp.get_num())/rp.get_den();
    return rp.get_d();
}

Rational min(Rational r1, Rational r2)
{
    if(r1<r2)
        return r1;
    return r2;
}

Rational max(Rational r1, Rational r2)
{
    if(r1<r2)
        return r2;
    return r1;
}

RationalPoint getBaryCenter(std::vector<RationalPoint> vP)
{
    Rational x=0, y=0;
    for(int it=0; it<vP.size(); it++) {
        RationalPoint p = vP.at(it);
        x += p.first;
        y += p.second;
    }
    RationalPoint c = RationalPoint(x/vP.size(),y/vP.size());
    return c;
}

Z2i::RealPoint getBaryCenter(std::vector<Z2i::Point> vP)
{
    double x=0, y=0;
    for(int it=0; it<vP.size(); it++) {
        x += vP.at(it)[0];
        y += vP.at(it)[1];
    }
    Z2i::RealPoint c = Z2i::RealPoint(x/vP.size(),y/vP.size());
    return c;
}

template <typename T>
std::vector<size_t> sort_indexes(const std::vector<T> &v) {

  // initialize original index locations
  std::vector<size_t> idx(v.size());
  iota(idx.begin(), idx.end(), 0);

  // sort indexes based on comparing values in v
  // using std::stable_sort instead of std::sort
  // to avoid unnecessary index re-orderings
  // when v contains elements of equal values
  stable_sort(idx.begin(), idx.end(), [&v](size_t i1, size_t i2) {return v[i1] < v[i2];});
  return idx;
}

// To find orientation of ordered triplet (p, q, r).
// The function returns following values
// 0 --> p, q and r are colinear
// 1 --> Clockwise
// 2 --> Counterclockwise
// See https://www.geeksforgeeks.org/orientation-3-ordered-points/
int orientation(RationalPoint p, RationalPoint q, RationalPoint r)
{
    Rational v1 = (q.second - p.second);
    Rational v2 = (r.first - q.first);
    Rational v3 = (q.first - p.first);
    Rational v4 = (r.second - q.second);
    Rational val = v1 * v2 - v3 * v4;
    //Rational val = (q.second - p.second) * (r.first - q.first) - (q.first - p.first) * (r.second - q.second);
  
    if (val == Rational(0))
        return 0;  // colinear
  
    return (val > 0)? 1: 2; // clock or counterclock wise
}

bool isAllTrue(std::vector<bool> vec)
{
    for(int it=0; it<vec.size(); it++)
        if(vec.at(it)==false)
            return false;
    return true;
}

bool isAllFalse(std::vector<bool> vec)
{
    for(int it=0; it<vec.size(); it++)
        if(vec.at(it)==true)
            return false;
    return true;
}

int getFirstTrue(std::vector<bool> vec)
{
    for(int it=0; it<vec.size(); it++)
        if(vec.at(it)==true)
            return it;
    return -1;
}

int getFirstFalse(std::vector<bool> vec)
{
    for(int it=0; it<vec.size(); it++)
        if(vec.at(it)==false)
            return it;
    return -1;
}

//Find and return the index of a vertex in the list
int findVertex(const std::vector<RationalPoint>& vector, RationalPoint v)
{
    for(int it=0; it<vector.size(); it++)
        if(vector.at(it)==v)
            return it;
    return -1;
}

int findVertex(const std::vector<Z2i::Point>& vector, Z2i::Point v)
{
    for(int it=0; it<vector.size(); it++)
        if(vector.at(it)==v)
            return it;
    return -1;
}

bool containElement(const std::vector<int>& vector, int element)
{
    auto it = std::find(vector.begin(), vector.end(), element);
    if (it != vector.end())
        return true;
    return false;
}

bool containElement(const std::vector<RationalPoint>& vector, RationalPoint element)
{
    auto it = std::find(vector.begin(), vector.end(), element);
    if (it != vector.end())
        return true;
    return false;
}

bool containElement(const std::vector<Z2i::Point>& vector, Z2i::Point element)
{
    auto it = std::find(vector.begin(), vector.end(), element);
    if (it != vector.end())
        return true;
    return false;
}
/*
// Function that returns true if it is possible
// to form a polygon with the given sides
bool isConvex(std::vector<double> a)
{
    int n = a.size();
    // Sum stores the sum of all the sides
    // and maxS stores the length of
    // the largest side
    double sum = 0, maxS = 0;
    for (int i = 0; i < n; i++) {
        sum += a[i];
        maxS = std::max(a[i], maxS);
    }
  
    // If the length of the largest side
    // is less than the sum of the
    // other remaining sides
    if ((sum - maxS) > maxS)
        return true;
    return false;
}
*/
bool isEqual(RationalPoint p1, RationalPoint p2)
{
    return p1.first==p2.first && p1.second==p2.second;
}

bool isSameVector(const std::vector<int>& v1, const std::vector<int>& v2)
{
    if(v1.size() != v2.size())
        return false;
    for(int it=0; it<v1.size(); it++)
        if(v1.at(it) != v2.at(it))
            return false;
    return true;
}

bool isSameVector(const std::vector<Rational>& v1, const std::vector<Rational>& v2)
{
    if(v1.size() != v2.size())
        return false;
    for(int it=0; it<v1.size(); it++)
        if(v1.at(it) != v2.at(it))
            return false;
    return true;
}

bool isSameVector(const std::vector<RationalPoint>& v1, const std::vector<RationalPoint>& v2)
{
    if(v1.size() != v2.size())
        return false;
    for(int it=0; it<v1.size(); it++)
        if(!isEqual(v1.at(it), v2.at(it)))
            return false;
    return true;
}

std::vector<int> permuteCircularVector(const std::vector<int>& v, int k)
{
    int start = k % v.size();
    if(start==0)
        return v;
    std::vector<int> res;
    for(int it=start; it<v.size(); it++)
        res.push_back(v.at(it));
    for(int it=0; it<start; it++)
        res.push_back(v.at(it));
    return res;
}

bool isSameCircularVector(const std::vector<int>& v1, const std::vector<int>& v2)
{
    if(v1.size() != v2.size())
        return false;
    for(int it=0; it<v2.size(); it++) {
        std::vector<int> tmp = permuteCircularVector(v2, it);
        if(isSameVector(v1, tmp))
            return true;
    }
    return false;
}

std::vector<RationalPoint> permuteCircularVector(const std::vector<RationalPoint>& v, int k)
{
    int start = k % v.size();
    if(start==0)
        return v;
    std::vector<RationalPoint> res;
    for(int it=start; it<v.size(); it++)
        res.push_back(v.at(it));
    for(int it=0; it<start; it++)
        res.push_back(v.at(it));
    return res;
}
bool isSameCircularVector(const std::vector<RationalPoint>& v1, const std::vector<RationalPoint>& v2)
{
    if(v1.size() != v2.size())
        return false;
    for(int it=0; it<v2.size(); it++) {
        std::vector<RationalPoint> tmp = permuteCircularVector(v2, it);
        if(isSameVector(v1, tmp))
            return true;
    }
    return false;
}

double distance(RationalPoint p1, RationalPoint p2)
{
    Rational dx = p1.first - p2.first;
    Rational dy = p1.second - p2.second;
    Rational dd = dx*dx + dy*dy;
    double d = sqrt(getRealValue(dd));
    return d;
}

double distance(Z2i::Point p1, Z2i::Point p2)
{
    int dx = p1[0] - p2[0];
    int dy = p1[1] - p2[1];
    int dd = dx*dx + dy*dy;
    return sqrt(dd);
}

double distance(Z2i::RealPoint p1, Z2i::RealPoint p2)
{
    double dx = p1[0] - p2[0];
    double dy = p1[1] - p2[1];
    double dd = dx*dx + dy*dy;
    return sqrt(dd);
}

// Return the cross product AB x BC.
// The cross product is a vector perpendicular to AB
// and BC having length |AB| * |BC| * Sin(theta) and
// with direction given by the right-hand rule.
// For two vectors in the X-Y plane, the result is a
// vector with X and Y components 0 so the Z component
// gives the vector's length and direction.
double CrossProductLength(double Ax, double Ay, double Bx, double By, double Cx, double Cy)
{
    // Get the vectors' coordinates.
    double BAx = Ax - Bx;
    double BAy = Ay - By;
    double BCx = Cx - Bx;
    double BCy = Cy - By;
    // Calculate the Z coordinate of the cross product.
    return (BAx * BCy - BAy * BCx);
}
/*
bool isConvex(std::vector<RationalPoint> points)
{
    // For each set of three adjacent points A, B, C,
    // find the cross product AB · BC. If the sign of
    // all the cross products is the same, the angles
    // are all positive or negative (depending on the
    // order in which we visit them) so the polygon
    // is convex.
    bool got_negative = false;
    bool got_positive = false;
    int num_points = points.size();
    int B, C;
    for (int A = 0; A < num_points; A++)
    {
        B = (A + 1) % num_points;
        C = (B + 1) % num_points;
        double Ax = getRealValue(points.at(A).first);
        double Ay = getRealValue(points.at(A).second);
        double Bx = getRealValue(points.at(B).first);
        double By = getRealValue(points.at(B).second);
        double Cx = getRealValue(points.at(C).first);
        double Cy = getRealValue(points.at(C).second);
        double cross_product = CrossProductLength(Ax,Ay,Bx,By,Cx,Cy);
        if (cross_product < 0)
            got_negative = true;
        else if (cross_product > 0)
            got_positive = true;
        if (got_negative && got_positive)
            return false;
    }
    // If we got this far, the polygon is convex.
    return true;
}
*/
//Find the smallest positive integer V such that [XV] + 1 < YV
//Return V or -1 if V is not exist
int findSmallestValue(double X, double Y)
{
    int start=0;
    int end=ceil(fabs(1.0/(Y-X)));//1e6;
    for(int i=start; i<=end; i++)
        if((int(X*i)+1)<Y*i)
            return i;
    return -1;
}

//Approximage angle by Pythagore triangle (a,b,c) with a<b<c and a*a+b*b=c*c
//sin(B) = a/c and cos (B) = b/c
PythagoreanTriple convertAngle2Pythagore(double B, double e)
{
    PythagoreanTriple pt = std::make_tuple(0, 1, 1); //triple corresponding to 0 degree;
    if(B==0)
        return pt;
    int a, b, c;
    int quart=0;
    double angle=B;
    while(angle>M_PI/2){angle-=M_PI/2;quart++;};//Get <= PI/2 angle
    double aa,bb;
    if(fabs(angle-M_PI/2)<e) { //FIXME: Angle=kPI/2 !!!!!
        //std::make_tuple(1, 0, 1); //triple corresponding to 90 degree
        aa=1;
        bb=0;
        c=1;
    }
    else {
        double X=tan(angle-e)+1.0/cos(angle-e);
        double Y=tan(angle+e)+1.0/cos(angle+e);
        double Xp=1.0/tan(angle+e)+1.0/sin(angle+e);
        double Yp=1.0/tan(angle-e)+1.0/sin(angle-e);
        int V=findSmallestValue(X,Y);
        int Vp=findSmallestValue(Xp,Yp);
        if(V==-1 || Vp==-1)
            return pt; //error here, no triple is found !
        int U=int(X*V)+1;
        int Up=int(Xp*Vp)+1;
        if((U*U+V*V)<(Up*Up+Vp*Vp)) {//quart=0
            aa=2*U*V;
            bb=U*U-V*V;
            c=U*U+V*V;
            if(fabs(asin(aa/c)-angle)>e) {
                int tmp=aa;
                aa=bb;
                bb=tmp;
            }
        }
        else {
            aa=2*Up*Vp;
            bb=Up*Up-Vp*Vp;
            c=Up*Up+Vp*Vp;
        }
    }

    if(quart%4==0) {
        a=aa;//sinx
        b=bb;//cosx
    }
    else if(quart%4==1) {
        a=bb;//sin(x+pi/2)=cosx
        b=-aa;//cos(x+pi/2)=-sinx

    }
    else if(quart%4==2) {
        a=-aa;//sin(x+pi)=-sinx
        b=-bb;//cos(x+pi/2)=-cosx

    }
    else { //if(quart%4==3)
        a=-bb;//sin(x+pi/2)=-cosx
        b=aa;//cos(x+pi/2)=sinx
    }
    return std::make_tuple(a, b, c);
}

void writePoints(std::vector<Z2i::Point> pts, std::string filename)
{
    std::ofstream myfile;
    myfile.open (filename);
    myfile << pts.size()<<"\n";
    for(auto it=pts.begin(); it!=pts.end(); it++)
        myfile << (*it)[0]<<" "<<(*it)[1]<<"\n";
    myfile.close();
    return 0;
}

std::ostream& operator<<(std::ostream& os, const RationalPoint p)
{
    os<<"("<<p.first<<","<<p.second<<")";
    return os;
}
