/*=========================================================================
 *
 *  Copyright David Doria 2011 daviddoria@gmail.com
 *
 *  Licensed under the Apache License, Version 2.0 (the "License");
 *  you may not use this file except in compliance with the License.
 *  You may obtain a copy of the License at
 *
 *         http://www.apache.org/licenses/LICENSE-2.0.txt
 *
 *  Unless required by applicable law or agreed to in writing, software
 *  distributed under the License is distributed on an "AS IS" BASIS,
 *  WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 *  See the License for the specific language governing permissions and
 *  limitations under the License.
 *
 *=========================================================================*/

#ifndef PointReaderITK_H
#define PointReaderITK_H

#include <string>

#include "itkPolyLineParametricPath.h"

// ITK does not have a file format for handling point lists, so we have included this function
// to convert a list of points in a file to a itk::PolyLineParametricPath.

void ReadFileIntoPolyLineParametricPath(const std::string& fileName, itk::PolyLineParametricPath< 2 >::Pointer path);

#endif
