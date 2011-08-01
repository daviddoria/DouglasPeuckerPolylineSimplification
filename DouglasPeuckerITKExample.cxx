#include "DouglasPeuckerITK.h"

#include "PointReaderITK.h"

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
  // The larger the tolerance, the more reduction will take place.
  float approximationTolerance = 0.0;
  ss >> approximationTolerance;
  
  std::string outputFileName = argv[3];
  
  // Output arguments
  std::cout << "Input: " << inputFileName << std::endl;
  std::cout << "Approximation tolerance: " << approximationTolerance << std::endl;
  std::cout << "Output: " << outputFileName << std::endl;
  
  itk::PolyLineParametricPath< 2 >::Pointer path = itk::PolyLineParametricPath< 2 >::New();
  ReadFileIntoPolyLineParametricPath(inputFileName, path);
  std::cout << "There are " << path->GetVertexList()->Size() << " points in the input path." << std::endl;
  
  itk::PolyLineParametricPath< 2 >::Pointer simplifiedPath = itk::PolyLineParametricPath< 2 >::New();
  // Perform the simplification
  SimplifyPolyline(path, approximationTolerance, simplifiedPath);

  std::cout << "There are " << simplifiedPath->GetVertexList()->Size() << " points on the simplified path." << std::endl;
  
  //WritePointsAsText(simplifiedPoints, outputFileName);
  
  return 0;
}
