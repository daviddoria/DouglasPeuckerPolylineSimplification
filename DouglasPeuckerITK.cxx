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

#include <boost/geometry.hpp>
#include <boost/geometry/geometries/point_xy.hpp>
#include <boost/geometry/geometries/linestring.hpp>

void SimplifyPolyline( itk::PolyLineParametricPath< 2 >::Pointer input, float tolerance, itk::PolyLineParametricPath< 2 >::Pointer output)
{
  typedef boost::geometry::model::d2::point_xy<double> xy;
  boost::geometry::model::linestring<xy> line;

  const itk::PolyLineParametricPath< 2 >::VertexListType * vertexList = input->GetVertexList ();

  for(unsigned int i = 0; i < vertexList->Size(); ++i)
    {
    line.push_back(xy(vertexList->GetElement(i)[0], vertexList->GetElement(i)[1]));
    }

  // Simplify the contour
  boost::geometry::model::linestring<xy> simplified;
  boost::geometry::simplify(line, simplified, tolerance);
  
  output->Initialize();
  typedef itk::PolyLineParametricPath< 2 >::ContinuousIndexType    ContinuousIndexType;
  
  for(unsigned int i = 0; i < simplified.size(); ++i)
    {
    ContinuousIndexType cindex;
    cindex[0] = simplified[i].x();
    cindex[1] = simplified[i].y();
    
    output->AddVertex( cindex );
    }  
    
}
