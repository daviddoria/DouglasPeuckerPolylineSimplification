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
