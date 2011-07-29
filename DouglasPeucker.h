#ifndef DOUGLASPEUCKER_H
#define DOUGLASPEUCKER_H

#include <vtkPolyData.h>

#include "itkPolyLineParametricPath.h"

void SimplifyPolyline( vtkPolyData* input, float tolerance, vtkPolyData* output);

void SimplifyPolyline( itk::PolyLineParametricPath< 2 >::Pointer input, float tolerance, itk::PolyLineParametricPath< 2 >::Pointer output);

#endif
