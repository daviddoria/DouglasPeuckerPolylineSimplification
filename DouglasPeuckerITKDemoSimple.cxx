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

static void CreateContour(itk::PolyLineParametricPath< 2 >::Pointer contour);

int main(int, char *[])
{
  // The larger the tolerance, the more reduction will take place.
  float approximationTolerance = 1.0;
  
  itk::PolyLineParametricPath< 2 >::Pointer path = itk::PolyLineParametricPath< 2 >::New();
  CreateContour(path);  
  std::cout << "There are " << path->GetVertexList()->Size() << " points in the input path." << std::endl;
  
  itk::PolyLineParametricPath< 2 >::Pointer simplifiedPath = itk::PolyLineParametricPath< 2 >::New();
  SimplifyPolyline( path, approximationTolerance, simplifiedPath);
  
  std::cout << "There are " << simplifiedPath->GetVertexList()->Size() << " points in the simplified path." << std::endl;
  for(unsigned int i = 0; i < simplifiedPath->GetVertexList()->Size(); ++i)
  {
    std::cout << simplifiedPath->GetVertexList()->GetElement(i) << std::endl;
  }
  
  return 0;
}

void CreateContour(itk::PolyLineParametricPath< 2 >::Pointer contour)
{
  float points[6] = {
  0.0, 0.0,
  0.0, 1.0,
  0.0, 2.0};

  typedef itk::PolyLineParametricPath< 2 >::ContinuousIndexType    ContinuousIndexType;
  ContinuousIndexType cindex;

  contour->Initialize();
  for(unsigned int i = 0; i < 3; ++i)
  {
    cindex[0] = points[2*i+0];
    cindex[1] = points[2*i+1];
    contour->AddVertex( cindex );
  }
}
