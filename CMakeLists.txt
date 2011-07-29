cmake_minimum_required(VERSION 2.6)


# Specify where to copy executables when 'make install' is run
SET( INSTALL_DIR ${CMAKE_INSTALL_PREFIX} )

# Tell CMake to also look in the source directory to find some .cmake files (Eigen3 and Umfpack)
set(CMAKE_MODULE_PATH ${CMAKE_SOURCE_DIR} ${CMAKE_MODULE_PATH})

PROJECT(DouglasPeucker)

FIND_PACKAGE(ITK REQUIRED)
INCLUDE(${ITK_USE_FILE})

FIND_PACKAGE(VTK REQUIRED)
INCLUDE(${VTK_USE_FILE})

FIND_PACKAGE(Boost 1.38 COMPONENTS required)
INCLUDE_DIRECTORIES(${INCLUDE_DIRECTORIES} ${Boost_INCLUDE_DIRS})

## VTK ##
ADD_EXECUTABLE(DouglasPeuckerVTKExample DouglasPeuckerVTKExample.cxx DouglasPeuckerVTK.cxx)
TARGET_LINK_LIBRARIES(DouglasPeuckerVTKExample ${VTK_LIBRARIES})

ADD_EXECUTABLE(DouglasPeuckerVTKDemo DouglasPeuckerVTKDemo.cxx DouglasPeuckerVTK.cxx)
TARGET_LINK_LIBRARIES(DouglasPeuckerVTKDemo ${VTK_LIBRARIES})

## ITK ##
ADD_EXECUTABLE(DouglasPeuckerITKExample DouglasPeuckerITKExample.cxx DouglasPeuckerITK.cxx PointReaderITK.cxx)
TARGET_LINK_LIBRARIES(DouglasPeuckerITKExample ${ITK_LIBRARIES})

ADD_EXECUTABLE(DouglasPeuckerITKDemo DouglasPeuckerITKDemo.cxx DouglasPeuckerITK.cxx)
TARGET_LINK_LIBRARIES(DouglasPeuckerITKDemo ${ITK_LIBRARIES})
