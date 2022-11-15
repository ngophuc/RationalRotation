#ifndef Rotation3D_H
#define Rotation3D_H

#include "Functions.h"

class Rotation3D
{
  public :
    //a (=2acos(theta)) = rotation angle
    //(b,c,d) = rotation axis
    Rational a, b, c, d; //quaternion q = a + bi + c j + dk is equivalent to a rational rotation
    
    Rotation3D () : a(0), b(1), c(0), d(0) {}
    Rotation3D (int a_, int b_, int c_, int d_);// : a(a_), b(b_), c(c_), d(d_) {}
    
    Rotation3D (double angle, int ax, int ay, int az, double error=1e-6); //approximate angle by pythagorean triangle
    friend std::ostream& operator<<(std::ostream& os, const Rotation3D& t);
    
    Rotation3D getAngle();
    
    RationalPoint3D transform(RationalPoint3D p);
    RationalPoint3D transform(Z3i::Point p);
    //Line transform(Line l);
};

RationalPoint3D transformPoint(RationalPoint3D p, Rotation3D t);

#endif // Rotation3D_H
