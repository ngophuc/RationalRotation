#ifndef FUNCTIONS_H
#define FUNCTIONS_H

#include <iostream>
#include <fstream>
#include <cassert>
#include <list>
#include <vector>
#include <numeric>
#include <algorithm>
#include <iterator>
#include <tuple>
#include <assert.h>

//#include <gmp.h>
#include <gmpxx.h>

#include "DGtal/base/BasicTypes.h"
#include "DGtal/base/Common.h"
#include "DGtal/helpers/StdDefs.h"

using namespace DGtal;

template<typename T1, typename T2, typename T3>
struct triplet
{
    T1 first;
    T2 middle;
    T3 last;
};

template<typename T1, typename T2, typename T3>
triplet<T1,T2,T3> make_triplet(const T1 &m1, const T2 &m2, const T3 &m3)
{
    triplet<T1,T2,T3> ans;
    ans.first = m1;
    ans.middle = m2;
    ans.last = m3;
    return ans;
}

// a/b
typedef mpq_class Rational;
// x,y
typedef std::pair<Rational,Rational> RationalPoint;
// x,y,z
typedef triplet<Rational,Rational,Rational> RationalPoint3D;

//(a,b,c) => a*a+b*bb=c*c, sin = a/c, cos = b/c
typedef std::tuple<int,int,int> PythagoreanTriplet;

double getRealValue(Rational rp);
Rational min(Rational r1, Rational r2);
Rational max(Rational r1, Rational r2);

//Functions for 2D
std::ostream& operator<<(std::ostream& os, const RationalPoint p);

RationalPoint getBaryCenter(std::vector<RationalPoint> vP);
Z2i::RealPoint getBaryCenter(std::vector<Z2i::Point> vP);

PythagoreanTriplet convertAngle2Pythagore(double B, double e);

bool isEqual(RationalPoint p1, RationalPoint p2);

double distance(RationalPoint p1, RationalPoint p2);
double distance(Z2i::Point p1, Z2i::Point p2);
double distance(Z2i::RealPoint p1, Z2i::RealPoint p2);

void writePoints(std::vector<Z2i::Point> pts, std::string filename);

//Functions for 3D
std::ostream& operator<<(std::ostream& os, const RationalPoint3D p);

RationalPoint3D getBaryCenter(std::vector<RationalPoint3D> vP);
Z3i::RealPoint getBaryCenter(std::vector<Z3i::Point> vP);

bool isEqual(RationalPoint3D p1, RationalPoint3D p2);

double distance(RationalPoint3D p1, RationalPoint3D p2);
double distance(Z3i::Point p1, Z3i::Point p2);
double distance(Z3i::RealPoint p1, Z3i::RealPoint p2);

//#include "Functions.ih" // Includes inline functions.
#endif // FUNCTIONS_H
