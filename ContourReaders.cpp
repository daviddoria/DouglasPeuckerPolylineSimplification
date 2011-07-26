#include "ContourReaders.h"

#include <vtkCellArray.h>
#include <vtkSmartPointer.h>

std::vector<Point> CreatePointVectorFromPolyData(vtkPolyData* polydata)
{
  std::vector<Point> points;
  
  polydata->GetLines()->InitTraversal();
  vtkSmartPointer<vtkIdList> idList = vtkSmartPointer<vtkIdList>::New();
  while(polydata->GetLines()->GetNextCell(idList))
    {
    double p[3];
    polydata->GetPoint(idList->GetId(0), p);
    Point point(p[0],p[1]);
    points.push_back(point);
    }
  return points;
}

std::vector<Point> CreatePointVectorFromPolyLineParametricPath(itk::PolyLineParametricPath< 2 >::Pointer path)
{
  std::vector<Point> points;
  
  const itk::PolyLineParametricPath< 2 >::VertexListType * vertexList = path->GetVertexList ();
  
  for(unsigned int i = 0; i < vertexList->Size(); ++i)
    {
    Point point(vertexList->GetElement(i)[0], vertexList->GetElement(i)[1]);
    points.push_back(point);
    }
  return points;
}

std::vector<Point> CreatePointVectorFromPointList(const std::string& fileName)
{
  std::vector<Point> points;

  // Open the input file
  std::ifstream fin(fileName.c_str());
 
  // Quit if the input file is not valid.
  if(fin == NULL)
    {
    std::cout << "Cannot open file." << std::endl;
    exit(-1);
    }

  // Read the input file into a vector of points.
  std::string line;
  
  while(getline(fin, line))
    {
    std::stringstream ss;
    ss << line;
    float x,y;
    ss >> x >> y;
    Point p(x,y);
    points.push_back(p);
    }
    
  //std::cout << "There are " << points.size() << " input points." << std::endl;  
  return points;
}

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
