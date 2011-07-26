#include "DouglasPeucker.h"
#include "point.h"
#include "ContourReaders.h"

#include <fstream>
#include <iostream>
#include <sstream>
#include <vector>

// The larger the tolerance, the more reduction will take place.

int main(int argc, char *argv[])
{
  // Verify arguments
  if(argc < 4)
    {
    std::cerr << "Required: input.txt tolerance output.txt" << std::endl;
    return -1;
    }
  
  // Parse arguments
  std::string inputFileName = argv[1];
  
  std::stringstream ss;
  ss << argv[2];
  float approximationTolerance = 0.0;
  ss >> approximationTolerance;
  
  std::string outputFileName = argv[3];
  
  // Output arguments
  std::cout << "Input: " << inputFileName << std::endl;
  std::cout << "Approximation tolerance: " << approximationTolerance << std::endl;
  std::cout << "Output: " << outputFileName << std::endl;
  
  std::vector<Point> points = CreatePointVectorFromPointList(inputFileName);
  
  // Perform the simplification
  Point simplifiedPoints[points.size()]; // There will be less than this number of points in the output
  int numberOfSimplifiedPoints = poly_simplify(approximationTolerance, &points[0], points.size(), simplifiedPoints );

  std::vector<Point> simplifiedPointsVector = ArrayToVector<Point>(simplifiedPoints, numberOfSimplifiedPoints);
  std::cout << "There are " << numberOfSimplifiedPoints << " simplified points." << std::endl;
  
  WritePointsAsText(simplifiedPointsVector, outputFileName);
  
  return 0;
}
