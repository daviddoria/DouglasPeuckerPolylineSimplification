#ifndef DOUGLASPEUCKERITK_H
#define DOUGLASPEUCKERITK_H

#include "itkPolyLineParametricPath.h"

void SimplifyPolyline( itk::PolyLineParametricPath< 2 >::Pointer input, float tolerance, itk::PolyLineParametricPath< 2 >::Pointer output);

#endif
