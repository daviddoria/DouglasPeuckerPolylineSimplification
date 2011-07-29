#include "DouglasPeucker.h"

#include <vtkSmartPointer.h>
#include <vtkIdList.h>
#include <vtkPolyData.h>
#include <vtkCellArray.h>

void SimplifyPolyline( vtkPolyData* input, float tolerance, vtkPolyData* output)
{
  typedef boost::geometry::model::d2::point_xy<double> xy;
  boost::geometry::model::linestring<xy> line;
  
  polydata->GetLines()->InitTraversal();
  vtkSmartPointer<vtkIdList> idList = vtkSmartPointer<vtkIdList>::New();
  while(polydata->GetLines()->GetNextCell(idList))
    {
    double p[3];
    polydata->GetPoint(idList->GetId(0), p);
    line.push_back(xy(p[0], p[1]));
    }
    
  // Simplify the contour
  boost::geometry::model::linestring<xy> simplified;
  boost::geometry::simplify(line, simplified, tolerance);
  
  // Create a vtkPoints object and store the simplified points in it
  vtkSmartPointer<vtkPoints> points = vtkSmartPointer<vtkPoints>::New();
   
  for(unsigned int i = 0; i < inputPoints.size(); ++i)
    {
    double p[3] = {line[i].x, line[i].y, 0.0};
    points->InsertNextPoint(p);
    }
    
  // Create a cell array to store the lines in and add the lines to it
  vtkSmartPointer<vtkCellArray> lines = vtkSmartPointer<vtkCellArray>::New();
 
  for(unsigned int i = 0; i < points->GetNumberOfPoints(); i++)
    {
    //Create the first line (between Origin and P0)
    vtkSmartPointer<vtkLine> line =
      vtkSmartPointer<vtkLine>::New();
    line->GetPointIds()->SetId(0,i);
    line->GetPointIds()->SetId(1,i+1);
    lines->InsertNextCell(line);
    }
 
  // Store everything in the output
  output->SetPoints(points);
  output->SetLines(lines);
      
}

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
  
  for(unsigned int i = 0; i < points.size(); ++i)
    {
    ContinuousIndexType cindex;
    cindex[0] = line[i].x;
    cindex[1] = line[i].y;
    
    output->AddVertex( cindex );
    }  
    
}
