#ifndef ContourWriters_H
#define ContourWriters_H

#include <string>
#include <vector>

#include "point.h"

void WritePointsAsText(const std::vector<Point>& points, const std::string& fileName);
void WritePointsAsPolyDataLine(const std::vector<Point>& points, const std::string& fileName);

#endif
