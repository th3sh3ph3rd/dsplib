#ifndef __DSPLIB_H__
#define __DSPLIB_H__

/*
 * TODO:
 * - use templates/concepts to allow float and double as types
 *
 */

#include <stddef.h>

namespace dsplib
{
    class DFT
    {
    public:
        virtual ~DFT() {};
        virtual void forward(const double* input, double* output) = 0;
        virtual void backward(const double* input, double* output) = 0;
    };

    DFT* initDFT(size_t DFTSize);
}

#endif /* __DSPLIB_H__ */

