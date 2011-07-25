//#include "common.h"
#include "point.h"
#include "vector.h"

#include <vector>
#include <fstream>
#include <sstream>
#include <string>

int poly_simplify( float tol, Point* V, int n, Point* sV );

void simplifyDP( float tol, Point* v, int j, int k, int* mk );

struct Segment
{
  Point P0, P1;
};

// The larger the tolerance, the more reduction will take place.

int main(int argc, char *argv[])
{
  // Verify arguments
  if(argc < 4)
    {
    std::cerr << "Required: input.txt tolerance output.txt" << std::endl;
    return -1;
    }
  
  // Parse arguments
  std::string inputFileName = argv[1];
  
  std::stringstream ss;
  ss << argv[2];
  float approximationTolerance = 0.0;
  ss >> approximationTolerance;
  
  std::string outputFileName = argv[3];
  
  // Output arguments
  std::cout << "Input: " << inputFileName << std::endl;
  std::cout << "Approximation tolerance: " << approximationTolerance << std::endl;
  std::cout << "Output: " << outputFileName << std::endl;
  
  // Open the input file
  std::ifstream fin(inputFileName.c_str());
 
  // Quit if the input file is not valid.
  if(fin == NULL)
    {
    std::cout << "Cannot open file." << std::endl;
    return -1;
    }

  // Read the input file into a vector of points.
  std::string line;
  std::vector<Point> points;
  
  while(getline(fin, line))
    {
    std::stringstream ss;
    ss << line;
    float x,y;
    ss >> x >> y;
    Point p(x,y);
    points.push_back(p);
    }
    
  std::cout << "There are " << points.size() << " input points." << std::endl;
  
  // Perform the simplification
  Point simplifiedPoints[points.size()]; // There will be less than this number of points in the output
  int numberOfSimplifiedPoints = poly_simplify(approximationTolerance, &points[0], points.size(), simplifiedPoints );

  std::cout << "There are " << numberOfSimplifiedPoints << " simplified points." << std::endl;
  
  std::ofstream fout(outputFileName.c_str());
 
  for(unsigned int i = 0; i < numberOfSimplifiedPoints; ++i)
    {
    //std::cout << simplifiedPoints[i] << std::endl;
    fout << simplifiedPoints[i].x << " " << simplifiedPoints[i].y << std::endl;
    }
  fout.close();
  
  return 0;
}

// Copyright 2002, softSurfer (www.softsurfer.com)
// This code may be freely used and modified for any purpose
// providing that this copyright notice is included with it.
// SoftSurfer makes no warranty for this code, and cannot be held
// liable for any real or imagined damage resulting from its use.
// Users of this code must verify correctness for their application.


// dot product (3D) which allows vector operations in arguments
#define dot(u,v)   ((u).x * (v).x + (u).y * (v).y + (u).z * (v).z)
#define norm2(v)   dot(v,v)        // norm2 = squared length of vector
#define norm(v)    sqrt(norm2(v))  // norm = length of vector
#define d2(u,v)    norm2(u-v)      // distance squared = norm2 of difference
#define d(u,v)     norm(u-v)       // distance = norm of difference


// poly_simplify():
//    Input:  tol = approximation tolerance
//            V[] = polyline array of vertex points 
//            n   = the number of points in V[]
//    Output: sV[]= simplified polyline vertices (max is n)
//    Return: m   = the number of points in sV[]

int poly_simplify( float tol, Point* V, int n, Point* sV )
{
    int    i, k, m, pv;            // misc counters
    float  tol2 = tol * tol;       // tolerance squared
    Point* vt = new Point[n];      // vertex buffer
    //int*   mk = new int[n] = {0};  // marker buffer
    int*   mk = new int[n];  // marker buffer

    // STAGE 1.  Vertex Reduction within tolerance of prior vertex cluster
    vt[0] = V[0];              // start at the beginning
    for (i=k=1, pv=0; i<n; i++) {
        if (d2(V[i], V[pv]) < tol2)
            continue;
        vt[k++] = V[i];
        pv = i;
    }
    if (pv < n-1)
        vt[k++] = V[n-1];      // finish at the end

    // STAGE 2.  Douglas-Peucker polyline simplification
    mk[0] = mk[k-1] = 1;       // mark the first and last vertices
    simplifyDP( tol, vt, 0, k-1, mk );

    // copy marked vertices to the output simplified polyline
    for (i=m=0; i<k; i++) {
        if (mk[i])
            sV[m++] = vt[i];
    }
    //delete vt;
    delete mk;
    return m;         // m vertices in simplified polyline
}

// simplifyDP():
//  This is the Douglas-Peucker recursive simplification routine
//  It just marks vertices that are part of the simplified polyline
//  for approximating the polyline subchain v[j] to v[k].
//    Input:  tol = approximation tolerance
//            v[] = polyline array of vertex points 
//            j,k = indices for the subchain v[j] to v[k]
//    Output: mk[] = array of markers matching vertex array v[]

void simplifyDP( float tol, Point* v, int j, int k, int* mk )
{
    if (k <= j+1) // there is nothing to simplify
        return;

    // check for adequate approximation by segment S from v[j] to v[k]
    int     maxi = j;          // index of vertex farthest from S
    float   maxd2 = 0;         // distance squared of farthest vertex
    float   tol2 = tol * tol;  // tolerance squared
    Segment S = {v[j], v[k]};  // segment from v[j] to v[k]
    Vector  u = S.P1 - S.P0;   // segment direction vector
    double  cu = dot(u,u);     // segment length squared

    // test each vertex v[i] for max distance from S
    // compute using the Feb 2001 Algorithm's dist_Point_to_Segment()
    // Note: this works in any dimension (2D, 3D, ...)
    Vector  w;
    Point   Pb;                // base of perpendicular from v[i] to S
    double  b, cw, dv2;        // dv2 = distance v[i] to S squared

    for (int i=j+1; i<k; i++)
    {
        // compute distance squared
        w = v[i] - S.P0;
        cw = dot(w,u);
        if ( cw <= 0 )
            dv2 = d2(v[i], S.P0);
        else if ( cu <= cw )
            dv2 = d2(v[i], S.P1);
        else {
            b = cw / cu;
            Pb = S.P0 + b * u;
            dv2 = d2(v[i], Pb);
        }
        // test with current max distance squared
        if (dv2 <= maxd2) 
            continue;
        // v[i] is a new max vertex
        maxi = i;
        maxd2 = dv2;
    } 
    if (maxd2 > tol2)        // error is worse than the tolerance
    {
        // split the polyline at the farthest vertex from S
        mk[maxi] = 1;      // mark v[maxi] for the simplified polyline
        // recursively simplify the two subpolylines at v[maxi]
        simplifyDP( tol, v, j, maxi, mk );  // polyline v[j] to v[maxi]
        simplifyDP( tol, v, maxi, k, mk );  // polyline v[maxi] to v[k]
    }
    // else the approximation is OK, so ignore intermediate vertices
    return;
}

