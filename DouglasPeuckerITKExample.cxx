/*=========================================================================
 *
 *  Copyright David Doria 2011 daviddoria@gmail.com
 *
 *  Licensed under the Apache License, Version 2.0 (the "License");
 *  you may not use this file except in compliance with the License.
 *  You may obtain a copy of the License at
 *
 *         http://www.apache.org/licenses/LICENSE-2.0.txt
 *
 *  Unless required by applicable law or agreed to in writing, software
 *  distributed under the License is distributed on an "AS IS" BASIS,
 *  WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 *  See the License for the specific language governing permissions and
 *  limitations under the License.
 *
 *=========================================================================*/
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
