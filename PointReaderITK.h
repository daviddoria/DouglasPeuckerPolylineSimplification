#ifndef PointReaderITK_H
#define PointReaderITK_H

#include <string>

#include "itkPolyLineParametricPath.h"

// ITK does not have a file format for handling point lists, so we have included this function
// to convert a list of points in a file to a itk::PolyLineParametricPath.

void ReadFileIntoPolyLineParametricPath(const std::string& fileName, itk::PolyLineParametricPath< 2 >::Pointer path);

#endif
