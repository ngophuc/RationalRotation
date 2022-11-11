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

//Functions for 2D
bool isEqual(RationalPoint p1, RationalPoint p2)
{
  return p1.first==p2.first && p1.second==p2.second;
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
PythagoreanTriplet convertAngle2Pythagore(double B, double e)
{
  PythagoreanTriplet pt = std::make_tuple(0, 1, 1); //triple corresponding to 0 degree;
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
}

std::ostream& operator<<(std::ostream& os, const RationalPoint p)
{
  os<<"[RationalPoint] {"<<p.first<<", "<<p.second<<"}";
  return os;
}


//Functions for 3D
bool isEqual(RationalPoint3D p1, RationalPoint3D p2)
{
  return p1.first==p2.first && p1.middle==p2.middle && p1.last==p2.last;
}

RationalPoint3D getBaryCenter(std::vector<RationalPoint3D> vP)
{
  Rational x=0, y=0, z=0;
  for(int it=0; it<vP.size(); it++) {
    RationalPoint3D p = vP.at(it);
    x += p.first;
    y += p.middle;
    z += p.last;
  }
  RationalPoint3D c = make_triplet<Rational, Rational, Rational>(x/vP.size(),y/vP.size(),z/vP.size());
  return c;
}

Z3i::RealPoint getBaryCenter(std::vector<Z3i::Point> vP)
{
  double x=0, y=0, z=0;
  for(int it=0; it<vP.size(); it++) {
    x += vP.at(it)[0];
    y += vP.at(it)[1];
    z += vP.at(it)[2];
  }
  Z3i::RealPoint c = Z3i::RealPoint(x/vP.size(),y/vP.size(),z/vP.size());
  return c;
}

double distance(RationalPoint3D p1, RationalPoint3D p2)
{
  Rational dx = p1.first - p2.first;
  Rational dy = p1.middle - p2.middle;
  Rational dz = p1.last - p2.last;
  Rational dd = dx*dx + dy*dy + dz*dz;
  double d = sqrt(getRealValue(dd));
  return d;
}

double distance(Z3i::Point p1, Z3i::Point p2)
{
  int dx = p1[0] - p2[0];
  int dy = p1[1] - p2[1];
  int dz = p1[2] - p2[2];
  int dd = dx*dx + dy*dy + dz*dz;
  return sqrt(dd);
}

double distance(Z3i::RealPoint p1, Z3i::RealPoint p2)
{
  double dx = p1[0] - p2[0];
  double dy = p1[1] - p2[1];
  double dz = p1[2] - p2[2];
  double dd = dx*dx + dy*dy + dz*dz;
  return sqrt(dd);
}

std::ostream& operator<<(std::ostream& os, const RationalPoint3D p)
{
  os << "[RationalPoint3D] {" << p.first << ", " << p.middle << ", " << p.last << "}";
  return os;
}
