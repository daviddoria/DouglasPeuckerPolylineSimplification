#include "DouglasPeuckerVTK.h"

#include <vtkCellArray.h>
#include <vtkIdList.h>
#include <vtkLine.h>
#include <vtkPolyData.h>
#include <vtkSmartPointer.h>

#include <boost/geometry.hpp>
#include <boost/geometry/geometries/point_xy.hpp>
#include <boost/geometry/geometries/linestring.hpp>

void SimplifyPolyline( vtkPolyData* input, float tolerance, vtkPolyData* output)
{
  typedef boost::geometry::model::d2::point_xy<double> xy;
  boost::geometry::model::linestring<xy> line;
  
  input->GetLines()->InitTraversal();
  vtkSmartPointer<vtkIdList> idList = vtkSmartPointer<vtkIdList>::New();
  while(input->GetLines()->GetNextCell(idList))
    {
    double p[3];
    input->GetPoint(idList->GetId(0), p);
    line.push_back(xy(p[0], p[1]));
    }
    
  // Simplify the contour
  boost::geometry::model::linestring<xy> simplified;
  boost::geometry::simplify(line, simplified, tolerance);
  
  // Create a vtkPoints object and store the simplified points in it
  vtkSmartPointer<vtkPoints> points = vtkSmartPointer<vtkPoints>::New();
   
  for(unsigned int i = 0; i < simplified.size(); ++i)
    {
    double p[3] = {simplified[i].x(), simplified[i].y(), 0.0};
    points->InsertNextPoint(p);
    }
    
  // Create a cell array to store the lines in and add the lines to it
  vtkSmartPointer<vtkCellArray> lines = vtkSmartPointer<vtkCellArray>::New();
 
  for(unsigned int i = 0; i < points->GetNumberOfPoints(); i++)
    {
    vtkSmartPointer<vtkLine> vtkline = vtkSmartPointer<vtkLine>::New();
    vtkline->GetPointIds()->SetId(0,i);
    vtkline->GetPointIds()->SetId(1,i+1);
    lines->InsertNextCell(vtkline);
    }
 
  // Store everything in the output
  output->SetPoints(points);
  output->SetLines(lines);
      
}
