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

#include "DouglasPeuckerVTK.h"

#include <fstream>
#include <iostream>
#include <sstream>

#include <vtkSmartPointer.h>
#include <vtkXMLPolyDataReader.h>
#include <vtkXMLPolyDataWriter.h>

void CreateContour(vtkPolyData* contour);

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
  
  vtkSmartPointer<vtkXMLPolyDataReader> reader = vtkSmartPointer<vtkXMLPolyDataReader>::New();
  reader->SetFileName(inputFileName.c_str());
  reader->Update();
  
  std::cout << "There are " << reader->GetOutput()->GetNumberOfPoints() << " points in the input path." << std::endl;
  
  // Perform the simplification
  vtkSmartPointer<vtkPolyData> simplifiedPath = vtkSmartPointer<vtkPolyData>::New();
  SimplifyPolyline(reader->GetOutput(), approximationTolerance, simplifiedPath);

  std::cout << "There are " << simplifiedPath->GetNumberOfPoints() << " on the simplified path." << std::endl;
  
  vtkSmartPointer<vtkXMLPolyDataWriter> writer = vtkSmartPointer<vtkXMLPolyDataWriter>::New();
  writer->SetFileName(outputFileName.c_str());
  writer->SetInputConnection(simplifiedPath->GetProducerPort());
  writer->Write();
  
  return 0;
}

void CreateContour(vtkPolyData* contour)
{
  
}
