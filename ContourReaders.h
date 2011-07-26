#ifndef ContourReaders_H
#define ContourReaders_H

#include "point.h"

#include "itkPolyLineParametricPath.h"

#include <vtkPolyData.h>

std::vector<Point> CreatePointVectorFromPolyData(vtkPolyData* polydata);

std::vector<Point> CreatePointVectorFromPolyLineParametricPath(itk::PolyLineParametricPath< 2 >::Pointer path);

std::vector<Point> CreatePointVectorFromPointList(const std::string& fileName);

void WritePointsAsText(const std::vector<Point>& points, const std::string& fileName);

template <typename T>
std::vector<T> ArrayToVector(T* inputArray, unsigned int inputLength)
{
  std::vector<T> outputVector(inputLength);
  for(unsigned int i = 0; i < inputLength; ++i)
    {
    outputVector[i] = inputArray[i];
    }
  return outputVector;
}

#endif
