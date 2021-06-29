#include <iostream>
#include <vector>
#include <string>

#include "grid2d.hpp"

using namespace std;

int main()
{

    std::cout << "Run laplace simulation" << std::endl; 
    
    // simulation parameter
    size_t no_steps = 1e6;      // number of time steps
    double dt       = 1e-2;     // time step increment
    size_t pfrec    = 100;      // postprocessing frequency
    double alpha    = 1e1;      // heat transfer coefficient
    double tgt_err  = 1e-6;     // target error

    // simulation setup
    Laplace::Grid2D CG = Laplace::Grid2D(10.0, 10.0, 100, 100);

    // setup temperature increment vector
    std::vector<double> delta_T(CG.noNodes,0.0);

    // boundary conditions
    for (size_t i=0; i<CG.noNodes; i++) 
    {
        double x = CG.XI(i)[0];
        double y = CG.XI(i)[1];
        if (y==10.0) CG.temperatures[i] = 1000.0;
    }

    // initialize abort criterion
    double norm_dT      = 0.0;
    double norm_dT_n    = 0.0;
    double norm_error    = 0.0;
    double norm_error_n  = 0.0;

    // start time loop
    double time = 0.0;
    CG.vtk("/Users/sash/c_coding/laplace_playground/postprocessing/output", 0);
    for (size_t step = 0; step<no_steps; step++)
    {
        // compute temperature increments for all inner nodes
        for (size_t i = 1; i<CG.nx; i++)
            for (size_t j = 1; j<CG.ny; j++)
                delta_T[j * (1+CG.nx)+i] = dt * alpha * (
                    ((CG.T(i+1,j)-2*CG.T(i,j)+CG.T(i-1,j))/(CG.dx*CG.dx)) + 
                    ((CG.T(i,j+1)-2*CG.T(i,j)+CG.T(i,j-1))/(CG.dy*CG.dy)) );

        // check for convergence in steady state solution
        norm_dT     = 0.0;
        for (auto T : delta_T) norm_dT += std::sqrt(T*T);
        
        norm_error = abs(norm_dT_n)-abs(norm_dT);
        if (step>0 && abs(norm_error)<tgt_err) 
        {
            std::cout << "converged with error : " << abs(norm_error) << std::endl;
            break;
        }

        if (step>0 && (abs(norm_dT) - abs(norm_dT_n)) > 1e-12)
        {
            dt /= 2;
            std::cout << "reduce step size to : " << dt << std::endl;
            continue; 
        }
        

        // update grid
        for (size_t i = 0; i<CG.noNodes; i++)
            CG.temperatures[i] += delta_T[i];

        
        // postprocessing
        if (step%pfrec<=1e-12) 
        {
            std::cout << "current time: " << time << " current error: " << norm_error << " error trend :" << abs(norm_error) - abs(norm_error_n) << " (negative is good)" << std::endl;
            CG.vtk("/Users/sash/c_coding/laplace_playground/postprocessing/output", step);
        }

        // next step
        norm_error_n = norm_error;
        norm_dT_n    = norm_dT;
        time += dt;

    }
    std::cout << "Finished time integraton at :" << time << std::endl; 

    return -1;
}