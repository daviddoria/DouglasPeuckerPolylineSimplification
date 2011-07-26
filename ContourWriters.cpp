#include "ContourWriters.h"

#include <fstream>

#include <vtkCellArray.h>
#include <vtkLine.h>
#include <vtkPoints.h>
#include <vtkPolyData.h>
#include <vtkSmartPointer.h>
#include <vtkXMLPolyDataWriter.h>

void WritePointsAsText(const std::vector<Point>& points, const std::string& fileName)
{
  std::ofstream fout(fileName.c_str());
 
  for(unsigned int i = 0; i < points.size(); ++i)
    {
    //std::cout << simplifiedPoints[i] << std::endl;
    fout << points[i].x << " " << points[i].y << std::endl;
    }
  fout.close();
}

void WritePointsAsPolyDataLine(const std::vector<Point>& inputPoints, const std::string& fileName)
{
  // Create a vtkPoints object and store the points in it
  vtkSmartPointer<vtkPoints> points =
    vtkSmartPointer<vtkPoints>::New();
   
  for(unsigned int i = 0; i < inputPoints.size(); ++i)
    {
    double p[3] = {inputPoints[i].x, inputPoints[i].y, 0.0};
    points->InsertNextPoint(p);
    }
    
  // Create a cell array to store the lines in and add the lines to it
  vtkSmartPointer<vtkCellArray> lines =
    vtkSmartPointer<vtkCellArray>::New();
 
  for(unsigned int i = 0; i < points->GetNumberOfPoints(); i++)
    {
    //Create the first line (between Origin and P0)
    vtkSmartPointer<vtkLine> line =
      vtkSmartPointer<vtkLine>::New();
    line->GetPointIds()->SetId(0,i);
    line->GetPointIds()->SetId(1,i+1);
    lines->InsertNextCell(line);
    }
 
  // Create a polydata to store everything in
  vtkSmartPointer<vtkPolyData> linesPolyData =
    vtkSmartPointer<vtkPolyData>::New();
 
  // Add the points to the dataset
  linesPolyData->SetPoints(points);
 
  // Add the lines to the dataset
  linesPolyData->SetLines(lines);
      
  vtkSmartPointer<vtkXMLPolyDataWriter> writer =  
    vtkSmartPointer<vtkXMLPolyDataWriter>::New();
  writer->SetFileName(fileName.c_str());
  writer->SetInputConnection(linesPolyData->GetProducerPort());
  writer->Write();
}

void PointsToPolyLineParametricPath(const std::vector<Point>& points, itk::PolyLineParametricPath< 2 >::Pointer path)
{
  path->Initialize();
  typedef itk::PolyLineParametricPath< 2 >::ContinuousIndexType    ContinuousIndexType;
  
  for(unsigned int i = 0; i < points.size(); ++i)
    {
    ContinuousIndexType cindex;
    cindex[0] = points[i].x;
    cindex[1] = points[i].y;
    
    path->AddVertex( cindex );
    }  
}
