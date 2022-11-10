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
#include "DGtal/io/Color.h"
#include "DGtal/io/boards/Board2D.h"
#include "DGtal/helpers/StdDefs.h"

using namespace DGtal;

// a/b
typedef mpq_class Rational;
// x,y
typedef std::pair<Rational,Rational> RationalPoint;
//ax + by + c = 0
typedef std::tuple<Rational,Rational,Rational> Line;
//(a,b,c) => a*a+b*bb=c*c, sin = a/c, cos = b/c
typedef std::tuple<int,int,int> PythagoreanTriple;

std::ostream& operator<<(std::ostream& os, const RationalPoint p);

double getRealValue(Rational rp);
Rational min(Rational r1, Rational r2);
Rational max(Rational r1, Rational r2);

RationalPoint getBaryCenter(std::vector<RationalPoint> vP);
Z2i::RealPoint getBaryCenter(std::vector<Z2i::Point> vP);

bool isEqual(RationalPoint p1, RationalPoint p2);
bool isSameVector(const std::vector<int>& v1, const std::vector<int>& v2);
bool isSameVector(const std::vector<Rational>& v1, const std::vector<Rational>& v2);
bool isSameVector(const std::vector<RationalPoint>& v1, const std::vector<RationalPoint>& v2);
std::vector<int> permuteCircularVector(const std::vector<int>& v, int k);
bool isSameCircularVector(const std::vector<int>& v1, const std::vector<int>& v2);
std::vector<RationalPoint> permuteCircularVector(const std::vector<RationalPoint>& v, int k);
bool isSameCircularVector(const std::vector<RationalPoint>& v1, const std::vector<RationalPoint>& v2);

double distance(RationalPoint p1, RationalPoint p2);
double distance(Z2i::Point p1, Z2i::Point p2);
double distance(Z2i::RealPoint p1, Z2i::RealPoint p2);

bool isAllTrue(std::vector<bool> vec);
bool isAllFalse(std::vector<bool> vec);
int getFirstTrue(std::vector<bool> vec);
int getFirstFalse(std::vector<bool> vec);

int findVertex(const std::vector<RationalPoint>& vector, RationalPoint v);
int findVertex(const std::vector<Z2i::Point>& vector, Z2i::Point v);
bool containElement(const std::vector<int>& vector, int element);
bool containElement(const std::vector<RationalPoint>& vector, RationalPoint element);
bool containElement(const std::vector<Z2i::Point>& vector, Z2i::Point element);

PythagoreanTriple convertAngle2Pythagore(double B, double e=1e-6);

void writePoints(std::vector<Z2i::Point> pts, std::string filename);

//#include "Functions.ih" // Includes inline functions.
#endif // FUNCTIONS_H
