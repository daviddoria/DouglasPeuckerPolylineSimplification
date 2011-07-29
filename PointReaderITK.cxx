#include "PointReaderITK.h"

#include <fstream>

void ReadFileIntoPolyLineParametricPath(const std::string& fileName, itk::PolyLineParametricPath< 2 >::Pointer path)
{
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
  
    
  path->Initialize();
  typedef itk::PolyLineParametricPath< 2 >::ContinuousIndexType    ContinuousIndexType;
  
  while(getline(fin, line))
    {
    std::stringstream ss;
    ss << line;

    ContinuousIndexType cindex;
    ss >> cindex[0] >> cindex[1];
    
    path->AddVertex( cindex );
    }
}

void PolyLineParametricPathWriter(itk::PolyLineParametricPath< 2 >::Pointer path, const std::string& fileName)
{
  std::ofstream fout(fileName.c_str());
 
  const itk::PolyLineParametricPath< 2 >::VertexListType * vertexList = path->GetVertexList ();

  for(unsigned int i = 0; i < vertexList->Size(); ++i)
    {
    fout << vertexList->GetElement(i)[0] << " " << vertexList->GetElement(i)[1] << std::endl;
    }
    
  fout.close();
}
