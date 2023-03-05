#include <cmath>
#include <iostream>

#include "dsplib.h"
#include "gnuplot_iostream.h"

#define NFFT 1024 
#define F_SAMP 1000 //Hz
#define F_SINE 25 //Hz

static void real(const double* input, double* output, size_t N)
{
    for (size_t k = 0; k < N; ++k)
        output[k] = input[2*k];
}

static void imag(const double* input, double* output, size_t N)
{
    for (size_t k = 0; k < N; ++k)
        output[k] = input[2*k+1];
}

static void mag(const double* input, double* output, size_t N)
{
    for (size_t k = 0; k < N; ++k)
        output[k] = sqrt(input[2*k]*input[2*k]+input[2*k+1]*input[2*k+1]);
}

static void fftshift(const double* input, double* output, size_t N)
{
    for (size_t k = 0; k < N/2; ++k)
        output[k] = input[k+N/2];
    for (size_t k = N/2; k < N; ++k)
        output[k] = input[k-N/2];
}

int main(int argc, char* argv[])
{
    Gnuplot gp;
    dsplib::DFT* dft = dsplib::initDFT(NFFT);

    double x[2*NFFT];
    double X[2*NFFT];
    double x_real[NFFT];
    double X_mag[NFFT];
    double X_mag_shifted[NFFT];

    for (size_t k = 0; k < NFFT; ++k)
    {
        x[2*k] = (double) sin(2*M_PI*F_SINE*k/F_SAMP); //real
        x[2*k+1] = 0; //imag
    }

    dft->forward(x, X);
    
    real(x, x_real, NFFT);
    gp << "set xrange [0:" << (NFFT-1) << "]\n";
    //gp << "set xtics 0," << 1/F_SAMP << "," << (NFFT-1)/F_SAMP << "\n";
    gp << "plot" << gp.file1d(x_real) << "with impulses lw 2" << std::endl;
    std::cin.get();
   
    mag(X, X_mag, NFFT);
    fftshift(X_mag, X_mag_shifted, NFFT);
    gp << "set xrange [0:" << (NFFT-1) << "]\n";
    //gp << "set logscale y 10\n";
    gp << "plot" << gp.file1d(X_mag_shifted) << "with impulses lw 2" << std::endl;
    std::cin.get();
    
    dft->backward(X, x);
    
    real(x, x_real, NFFT);
    gp << "set xrange [0:" << (NFFT-1) << "]\n";
    //gp << "set xtics 0," << 1/F_SAMP << "," << (NFFT-1)/F_SAMP << "\n";
    gp << "plot" << gp.file1d(x_real) << "with impulses lw 2" << std::endl;
    std::cin.get();
   
    unsigned int cnt = 0;
    double val = 1.0;
    for (size_t k = 0; k < NFFT; ++k)
    {
        if (cnt % 20 == 0)
            val *= -1.0;
        cnt++;
        x[2*k] = val; //real
        x[2*k+1] = 0; //imag
    }

    dft->forward(x, X);
    
    real(x, x_real, NFFT);
    gp << "set xrange [0:" << (NFFT-1) << "]\n";
    //gp << "set xtics 0," << 1/F_SAMP << "," << (NFFT-1)/F_SAMP << "\n";
    gp << "plot" << gp.file1d(x_real) << "with impulses lw 2" << std::endl;
    std::cin.get();

    mag(X, X_mag, NFFT);
    fftshift(X_mag, X_mag_shifted, NFFT);
    gp << "set xrange [0:" << (NFFT-1) << "]\n";
    //gp << "set logscale y 10\n";
    gp << "plot" << gp.file1d(X_mag_shifted) << "with impulses lw 2" << std::endl;
    std::cin.get();
    
    dft->backward(X, x);
    
    real(x, x_real, NFFT);
    gp << "set xrange [0:" << (NFFT-1) << "]\n";
    //gp << "set xtics 0," << 1/F_SAMP << "," << (NFFT-1)/F_SAMP << "\n";
    gp << "plot" << gp.file1d(x_real) << "with impulses lw 2" << std::endl;
    std::cin.get();

    return 0;
}

