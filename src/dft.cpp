#include <cmath>

#include "dft.h"

_DFT::_DFT(size_t DFTSize) : N{DFTSize}
{
    twoPiByN = (double) (2*M_PI/N);
    twiddleFactors = new double[2*N*N];
    
    for (size_t k = 0; k < N; ++k)
    {
        for (size_t l = 0; l < N; ++l)
        {
            twiddleFactors[(2*N*k)+2*l] = (double) cos(k*l*twoPiByN);
            twiddleFactors[(2*N*k)+2*l+1] = (double) sin(k*l*twoPiByN);
        }
    }
}

_DFT::~_DFT()
{
    delete twiddleFactors;
}

void _DFT::forward(const double* input, double* output)
{
    for (size_t k = 0; k < N; ++k)
    {
        output[2*k] = 0;
        output[2*k+1] = 0;
        for (size_t l = 0; l < N; ++l)
        {
            double ir = input[2*l];
            double ii = input[2*l+1];
            double wr = twiddleFactors[(2*N*k)+2*l];
            double wi = twiddleFactors[(2*N*k)+2*l+1];
            output[2*k] += ir*wr + ii*wi;
            output[2*k+1] += -ir*wi + ii*wr;  
        }
    }
}

void _DFT::backward(const double* input, double* output)
{
    for (size_t k = 0; k < N; ++k)
    {
        output[2*k] = 0;
        output[2*k+1] = 0;
        for (size_t l = 0; l < N; ++l)
        {
            double ir = input[2*l];
            double ii = input[2*l+1];
            double wr = twiddleFactors[(2*N*k)+2*l];
            double wi = twiddleFactors[(2*N*k)+2*l+1];
            output[2*k] += ir*wr - ii*wi;
            output[2*k+1] += ir*wi + ii*wr;  
        }
    }
}

/*
 * This function allows the user to create
 * an instance of _DFT while being only able
 * to see DFT.
 */
dsplib::DFT* dsplib::initDFT(size_t DFTSize)
{
    dsplib::DFT* dft = new _DFT{DFTSize};
    return dft;
}

