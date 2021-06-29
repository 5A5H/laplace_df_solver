#pragma once
#include <iostream>
#include <array>
#include <vector>
#include <string>
#include <cmath>
#include <fstream>
#include <sstream>
#include <iomanip>


/*
2D Grid
This grid expands from the origin (0,0) to (lx,ly) with spacing (nx, ny).
It creates nodes in a regular grid from [i, 0, nx] and [j, 0, ny] 
*/

namespace Laplace
{

class Grid2D
{
    public:
    Grid2D(const double lx_, const double ly_, const size_t nx_, const size_t ny_) : lx(lx_), ly(ly_), nx(nx_), ny(ny_), 
    dx(lx_/nx_), dy(ly_/ny_), noNodes((nx_+1)*(ny_+1)), temperatures(noNodes,0.0)
    {
        std::cout << "2DGrid initialized" << std::endl;
    };

    public:
    std::array<double, 2> XI(const size_t i, const size_t j) const
    {
        return std::array<double, 2>({i*dx, j*dy});
    }

    public:
    std::array<double, 2> XI(const size_t I) const
    {
        size_t j = floor(I/(nx+1)); 
        size_t i = floor(I - j*(nx+1)); 
        return std::array<double, 2>({i*dx, j*dy});
    }

    public:
    size_t I(const size_t i, const size_t j) const {return j * (nx+1) + i;}

    public:
    double T(const size_t i, const size_t j) const {return temperatures[j * (nx+1) + i];}


    public:
    bool vtk(const std::string outputpath, const size_t step)
    {
        // Prepar output name
        std::ostringstream oss;
        oss << std::setfill('0') << std::setw(6) << step;

        // Write a VTK File with all Contact Candidates
        std::ofstream VTKOut(outputpath + "_" + oss.str() + ".vtk");
        VTKOut << "# vtk DataFile Version 2.0" << std::endl;
        VTKOut << "Temperature of 2DGrid" << std::endl;
        VTKOut << "ASCII" << std::endl;
        VTKOut << "DATASET POLYDATA" << std::endl;
        VTKOut << "POINTS "<< noNodes <<" float" << std::endl;
            for (size_t i=0; i<noNodes; i++) VTKOut << XI(i)[0] << " " << XI(i)[1] << " " << 0.0 << " " << std::endl;
        VTKOut << "VERTICES "<< noNodes << " "  << noNodes * 2 << std::endl;
            for (size_t i=0; i<noNodes; i++) VTKOut << "1 " << i<<  std::endl;
        VTKOut << "POINT_DATA "<< noNodes << std::endl;
        VTKOut << "SCALARS Temperature float 1 LOOKUP_TABLE default" << std::endl;
            for (size_t i=0; i<noNodes; i++) VTKOut << temperatures[i] << " " << std::endl;
        VTKOut.close();


        return true;
    }

    public:
    const double lx, ly, dx, dy;
    const size_t nx, ny, noNodes;

    public:
    std::vector<double> temperatures;

};



}
