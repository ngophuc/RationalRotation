#include "Rotation3D.h"

Rotation3D::Rotation3D (int a_, int b_, int c_, int d_)
{
  a=Rational(a_,1);
  b=Rational(b_,1);
  c=Rational(c_,1);
  d=Rational(d_,1);
}

Rotation3D::Rotation3D (double angle, int ax, int ay, int az, double error)
{
  //TODO: Coversion to quaternion here
  a=Rational(cos(angle/2.0));
  /*
  double n = sqrt(ax*ax+ay*ay+az*az);
  double xp = 1.0*ax/n;
  double yp = 1.0*ay/n;
  double zp = 1.0*az/n;
  b=Rational(xp);
  c=Rational(yp);
  d=Rational(zp);
  */
  b=Rational(ax,1);
  c=Rational(ay,1);
  d=Rational(az,1);
  
}

Rotation3D Rotation3D::setAngle(double angle, double error)
{
  a=Rational(cos(angle/2.0));//TODO: Coversion to quaternion here
  return *this;
}

Rotation3D Rotation3D::setAxis(int ax, int ay, int az)
{
  b=Rational(ax,1);
  c=Rational(ay,1);
  d=Rational(az,1);
  return *this;
}

RationalPoint3D Rotation3D::transform(RationalPoint3D p)
{
  RationalPoint3D tp;
  Rational x = p.first;
  Rational y = p.middle;
  Rational z = p.last;
  //TODO: Matrix multiplication here
  Rational rotMatrix[3][3];
  Rational n2= a*a+b*b+c*c+d*d;
  rotMatrix[0][0]=(a*a+b*b-c*c-d*d)/n2;
  rotMatrix[0][1]=2*(b*c-a*d)/n2;
  rotMatrix[0][2]=2*(a*c+b*d)/n2;
  
  rotMatrix[1][0]=2*(a*d+b*c)/n2;
  rotMatrix[1][1]=(a*a-b*b+c*c-d*d)/n2;
  rotMatrix[1][2]=2*(c*d-a*b)/n2;
  
  rotMatrix[2][0]=2*(b*d-a*c)/n2;
  rotMatrix[2][1]=2*(a*b+c*d/n2);
  rotMatrix[2][2]=(a*a-b*b-c*c+d*d)/n2;
  
  //std::cout<<p<<" and "<<tp<<std::endl;
  tp.first = rotMatrix[0][0]*x+rotMatrix[0][1]*y+rotMatrix[0][2]*z;
  tp.middle = rotMatrix[0][0]*x+rotMatrix[0][1]*y+rotMatrix[0][2]*z;
  tp.last = rotMatrix[0][0]*x+rotMatrix[0][1]*y+rotMatrix[0][2]*z;
  return tp;
}

RationalPoint3D Rotation3D::transform(Z3i::Point p)
{
  RationalPoint3D rp = make_triplet(Rational(p[0]),Rational(p[1]),Rational(p[2]));
  return transform(rp);
}

RationalPoint3D transformPoint(RationalPoint3D p, Rotation3D t)
{
  return t.transform(p);
}

std::ostream& operator<<(std::ostream& os, const Rotation3D& t)
{
  os << "Print Rotation3D "<<std::endl;
  os << "Quaternion (" <<t.a <<", "<<t.b<<", "<<t.c<<", "<<t.d<<")"<<std::endl;
  double ra = getRealValue(t.a);
  double rb = getRealValue(t.b);
  double rc = getRealValue(t.c);
  double rd = getRealValue(t.d);
  
  double n = sqrt(ra*ra+rb*rb+rc*rc+rd*rd);
  double ap = ra/n;
  double bp = rb/n;
  double cp = rc/n;
  double dp = rd/n;
  os << "Rotation angle: alpha=" <<2*acos(ap) <<", axis= (" <<bp<<", "<<cp<<", "<<dp<<")"<<std::endl;
  return os;
}
