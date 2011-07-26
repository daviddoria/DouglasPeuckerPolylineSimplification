#ifndef ContourWriters_H
#define ContourWriters_H

#include <string>
#include <vector>

#include "point.h"

#include "itkPolyLineParametricPath.h"

void WritePointsAsText(const std::vector<Point>& points, const std::string& fileName);
void WritePointsAsPolyDataLine(const std::vector<Point>& points, const std::string& fileName);

void PointsToPolyLineParametricPath(const std::vector<Point>& points, itk::PolyLineParametricPath< 2 >::Pointer path);

#endif
