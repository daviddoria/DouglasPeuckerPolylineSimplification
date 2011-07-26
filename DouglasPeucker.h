#ifndef DOUGLASPEUCKER_H
#define DOUGLASPEUCKER_H

#include "point.h"

int poly_simplify( float tol, Point* V, int n, Point* sV );

void simplifyDP( float tol, Point* v, int j, int k, int* mk );

struct Segment
{
  Point P0, P1;
};

#endif
