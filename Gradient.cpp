#include "Gradient.h"
#include <math.h>

Gradient::Gradient()
{
    // Set defaults
    m_nDims = 0;
    m_stepSize = 0.0;
    m_maxIter = 1;
    m_h = 0.001;
    m_gradientThresh = 1e-09;
}

Gradient::~Gradient()
{
}

void Gradient::SetObjectFunc(std::function<double(std::vector<double> *)> objectFunc)
{
    m_objectFunc = objectFunc;
}

void Gradient::SetStartPoint(const std::vector<double> startPoint)
{
    // Copy start point
    m_startPoint = startPoint;

    // Determine number of degrees of freedom
    m_nDims = m_startPoint.size();
}

// Function to set step size
void Gradient::SetStepSize(double stepSize)
{
    m_stepSize = stepSize;
}

// Function to get max number of iterations
void Gradient::SetMaxIterations(int maxIterations)
{
    m_maxIter = maxIterations;
}

// Function to set gradient magnitude threshhold (stopping condition).
void Gradient::SetGradientThresh(double gradientThresh)
{
    m_gradientThresh = gradientThresh;
}

// Function to perform the optimization
// Returns bool because we want to know if it converged or not
// fails if maybe hit max iterations or got stuck
bool Gradient::Optimize(std::vector<double> *funcLoc, double *funcVal)
{
    // Set currentPoint to startPoint
    m_currentPoint = m_startPoint;

    // Loop up to max iterations or until threshold is reached
    int iterCount = 0;
    double gradientMagnitude = 1.0;
    while ((iterCount < m_maxIter) && (gradientMagnitude > m_gradientThresh))
    {
        // Compute gradient vector
        std::vector<double> gradientVector = ComputeGradientVector();
        gradientMagnitude = ComputeGradientMagnitude(gradientVector);

        // Compute new point
        std::vector<double> newPoint = m_currentPoint;
        for (int i = 0; i < m_nDims; i++)
        {
            newPoint[i] += -(gradientVector[i] * m_stepSize);
        }

        // Update current point
        m_currentPoint = newPoint;

        // Increment counter
        iterCount++;
    }

    // Return results
    *funcLoc = m_currentPoint;
    *funcVal = m_objectFunc(&m_currentPoint);
}

// Function to compute gradient in the specified dimension
double Gradient::ComputeGradient(int dim)
{
    // Make copy of the current location
    std::vector<double> newPoint = m_currentPoint;

    // Modify copy according to h and dim
    newPoint[dim] += m_h;

    // Compute two function values for these points
    double funcVal1 = m_objectFunc(&m_currentPoint);
    double funcVal2 = m_objectFunc(&newPoint);

    // Compute approximate numerical gradient
    return (funcVal2 - funcVal1) / m_h;
}

// Function to compute the gradient vector
std::vector<double> Gradient::ComputeGradientVector()
{
    std::vector<double> gradientVector = m_currentPoint;
    for (int i = 0; i < m_nDims; i++)
    {
        gradientVector[i] = ComputeGradient(i);
    }
    return gradientVector;
}

// Function to compute gradient magnitude
double Gradient::ComputeGradientMagnitude(std::vector<double> gradientVector)
{
    double vectorMagnitude = 0.0;
    for (int i = 0; i < m_nDims; i++)
    {
        vectorMagnitude += gradientVector[i] * gradientVector[i];
    }
    return sqrt(vectorMagnitude);
}
