#include "Rotation2D.h"

Rotation2D::Rotation2D (Rational s, Rational c)
{
    assert(c*c+s*s==Rational(1));
    this->cos = c;
    this->sin = s;
}

Rotation2D::Rotation2D (int a, int b, int c)
{
    assert(a*a+b*b==c*c);
    assert(a!=0 && b!=0 && c!=0);
    this->sin = Rational(a,c);
    this->cos = Rational(b,c);
}

Rotation2D::Rotation2D (double angle, double error)
{
    PythagoreanTriple pt = convertAngle2Pythagore(angle,error);
    int a = std::get<0>(pt);
    int b = std::get<1>(pt);
    int c = std::get<2>(pt);
    assert(a*a+b*b==c*c);
    assert(a!=0 && b!=0 && c!=0);
    this->sin = Rational(a,c);
    this->cos = Rational(b,c);
}

Rotation2D Rotation2D::setAngle(double angle, double error)
{
    PythagoreanTriple pt = convertAngle2Pythagore(angle,error);
    int a = std::get<0>(pt);
    int b = std::get<1>(pt);
    int c = std::get<2>(pt);
    assert(a*a+b*b==c*c);
    assert(a!=0 && b!=0 && c!=0);
    this->sin = Rational(a,c);
    this->cos = Rational(b,c);
    return *this;
}

RationalPoint Rotation2D::transform(RationalPoint p)
{
    RationalPoint tp;
    Rational x = p.first;
    Rational y = p.second;
    tp.first = this->cos*x - this->sin*y;
    tp.second = this->sin*x + this->cos*y;
    //std::cout<<p<<" and "<<tp<<std::endl;
    return tp;
}

RationalPoint Rotation2D::transform(Z2i::Point p)
{
    RationalPoint rp = RationalPoint(Rational(p[0]),Rational(p[1]));
    return transform(rp);
}

RationalPoint transformPoint(RationalPoint p, Rotation2D t)
{
    return t.transform(p);
}

std::ostream& operator<<(std::ostream& os, const Rotation2D& t)
{
    os << "Print Rotation2D "<<std::endl;
    os << "Rotation: sin=" <<t.sin <<", cos=" <<t.cos<<std::endl;
    return os;
}
