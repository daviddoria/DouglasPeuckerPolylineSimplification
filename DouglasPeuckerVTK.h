#ifndef DOUGLASPEUCKERVTK_H
#define DOUGLASPEUCKERVTK_H

#include <vtkPolyData.h>

void SimplifyPolyline( vtkPolyData* input, float tolerance, vtkPolyData* output);

#endif
