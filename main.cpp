#include "Gradient.h"
#include <functional>
#include <iostream>

double ObjectFunc(std::vector<double> *funcLoc)
{
    // y = x^2
    double x = funcLoc->at(0);
    // double y = funcLoc->at(1);
    //  return (x*x*x) + (2*(x*x)) - (2*x);
    return (x * x);
    // return (x * x * x * x) + (2 * (x * x * x)) - (6 * (x * x)) + (4 * x) + 2;
    // return (x * x) + (x * y) + (y * y);
}
int main(int argc, char *argv[])
{
    // Create function pointer for object function
    std::function<double(std::vector<double> *)> p_objectFunc{ObjectFunc};

    // Create instance of gradient class
    Gradient solver;

    // Assign object function
    solver.SetObjectFunc(p_objectFunc);

    // Set start point
    std::vector<double> startPoint = {7.0};
    solver.SetStartPoint(startPoint);

    // Set max iterations
    solver.SetMaxIterations(100);

    // Set step size
    solver.SetStepSize(0.1);

    // Call optimize
    std::vector<double> funcLoc;
    double funcVal;
    bool converged = solver.Optimize(&funcLoc, &funcVal);
    if (!converged)
    {
        std::cout << "Warning, did not converge, result may be inaccurate" << std::endl;
    }

    // Display results
    std::cout << "Function location: " << funcLoc[0] << std::endl;
    std::cout << "Function value: " << funcVal << std::endl;

    return 0;
}
