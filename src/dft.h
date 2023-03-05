#ifndef __DFT_H__
#define __DFT_H__

/*
 * This header file is private
 * and not visible to library users.
 */

#include "dsplib.h"

class _DFT : public dsplib::DFT
{
public:
    _DFT(size_t DFTSize);
    ~_DFT();
    void forward(const double* input, double* output) override;
    void backward(const double* input, double* output) override;

private:
    size_t N;
    double twoPiByN;  
    double* twiddleFactors;
};

#endif

