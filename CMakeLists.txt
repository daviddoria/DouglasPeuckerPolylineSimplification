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

ADD_EXECUTABLE(DouglasPeucker DouglasPeuckerExample.cxx DouglasPeucker.cxx ContourReaders.cpp ContourWriters.cpp point.cpp vector.cpp)
TARGET_LINK_LIBRARIES(DouglasPeucker ${ITK_LIBRARIES} ${VTK_LIBRARIES})
set_target_properties(DouglasPeucker PROPERTIES COMPILE_DEFINITIONS "${DEFINITIONS}")
INSTALL( TARGETS DouglasPeucker
  RUNTIME DESTINATION ${INSTALL_DIR} )

ADD_EXECUTABLE(DouglasPeuckerVTKExample DouglasPeuckerVTKExample.cxx DouglasPeucker.cxx ContourReaders.cpp ContourWriters.cpp point.cpp vector.cpp)
TARGET_LINK_LIBRARIES(DouglasPeuckerVTKExample ${ITK_LIBRARIES} ${VTK_LIBRARIES})

ADD_EXECUTABLE(DouglasPeuckerITKExample DouglasPeuckerITKExample.cxx DouglasPeucker.cxx ContourReaders.cpp ContourWriters.cpp point.cpp vector.cpp)
TARGET_LINK_LIBRARIES(DouglasPeuckerITKExample ${ITK_LIBRARIES} ${VTK_LIBRARIES})
