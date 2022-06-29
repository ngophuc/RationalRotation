#ifndef Rotation2D_H
#define Rotation2D_H

#include "Functions.h"

class Rotation2D
{
    public :
        Rational sin; //sin=a/c
        Rational cos; //cos=b/c
    
    Rotation2D () : sin(0), cos(1) {}
    //Rotation2D (Rational c, Rational s, Rational x, Rational y) : cos(c), sin(s) {}
    Rotation2D (Rational s, Rational c);
    Rotation2D (int a, int b, int c);
    Rotation2D (double angle, double error=1e-6); //approximate angle by pythagorean triangle
    friend std::ostream& operator<<(std::ostream& os, const Rotation2D& t);
    
    Rotation2D setAngle(double angle, double error=1e-6);
    
    RationalPoint transform(RationalPoint p);
    RationalPoint transform(Z2i::Point p);
    //Line transform(Line l);
};

RationalPoint transformPoint(RationalPoint p, Rotation2D t);

#endif // Rotation2D_H
