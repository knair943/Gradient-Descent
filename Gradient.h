#include <vector>
#include <functional>

class Gradient
{
public:
    Gradient();
    ~Gradient();

    // Function to add a pointer to the object function
    void SetObjectFunc(std::function<double(std::vector<double> *)> objectFunc);

    // Function to set start point, also sets number of degrees of freedom
    void SetStartPoint(const std::vector<double> startPoint);

    // Function to set step size
    void SetStepSize(double stepSize);

    // Function to get max number of iterations
    void SetMaxIterations(int maxIterations);

    // Function to set gradient magnitude threshhold (stopping condition).
    void SetGradientThresh(double gradientThresh);

    // Function to perform the optimization
    // Returns bool because we want to know if it converged or not
    // fails if maybe hit max iterations or got stuck
    bool Optimize(std::vector<double> *funcLoc, double *funcVal);

private:
    // Function to compute gradient in the specified dimension
    double ComputeGradient(int dim);

    // Function to compute the gradient vector
    std::vector<double> ComputeGradientVector();

    // Function to compute gradient magnitude
    double ComputeGradientMagnitude(std::vector<double> gradientVector);

private:
    // Number of degrees of freedom of the system
    int m_nDims;

    // Step size
    double m_stepSize;

    // Max number of iterations
    int m_maxIter;

    // Gradient step size (h)
    double m_h;

    // Gradient magnitude threshold (stopping condition)
    double m_gradientThresh;

    // Starting point
    std::vector<double> m_startPoint;

    // Current point
    std::vector<double> m_currentPoint;

    // Function-pointer to the object function
    std::function<double(std::vector<double> *)> m_objectFunc;
};