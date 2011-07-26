#include "DouglasPeucker.h"
#include "point.h"
#include "ContourReaders.h"
#include "ContourWriters.h"

#include <fstream>
#include <iostream>
#include <sstream>
#include <vector>

#include <vtkSmartPointer.h>
#include <vtkXMLPolyDataReader.h>

int main(int argc, char *argv[])
{
  // Verify arguments
  if(argc < 4)
    {
    std::cerr << "Required: input.vtp tolerance output.vtp" << std::endl;
    return -1;
    }
  
  // Parse arguments
  std::string inputFileName = argv[1];
  
  std::stringstream ss;
  ss << argv[2];
  // The larger the tolerance, the more reduction will take place.
  float approximationTolerance = 0.0;
  ss >> approximationTolerance;
  
  std::string outputFileName = argv[3];
  
  // Output arguments
  std::cout << "Input: " << inputFileName << std::endl;
  std::cout << "Approximation tolerance: " << approximationTolerance << std::endl;
  std::cout << "Output: " << outputFileName << std::endl;
  
  vtkSmartPointer<vtkXMLPolyDataReader> reader =
    vtkSmartPointer<vtkXMLPolyDataReader>::New();
  reader->SetFileName(inputFileName.c_str());
  reader->Update();
  
  std::vector<Point> points = CreatePointVectorFromPolyData(reader->GetOutput());
  
  // Perform the simplification
  std::vector<Point> simplifiedPoints = SimplifyPolyline(approximationTolerance, points);

  std::cout << "There are " << simplifiedPoints.size() << " simplified points." << std::endl;
  
  WritePointsAsPolyDataLine(simplifiedPoints, outputFileName);
  
  return 0;
}
