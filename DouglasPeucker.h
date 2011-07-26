#ifndef DOUGLASPEUCKER_H
#define DOUGLASPEUCKER_H

#include "point.h"

#include <vector>

// This function is the only one that should be called by the user
std::vector<Point> SimplifyPolyline( float tolerance, std::vector<Point> points);

// This function is called from SimplifyPolyline
void simplifyDP( float tolerance, Point* points, int j, int k, int* mk );

// This structure defines a line segment by its end points
struct Segment
{
  Point P0, P1;
};

#endif
