#ifndef NARMA_H
#define NARMA_H

#include "dataset.h"
#include <gsl/gsl_blas.h>
#include <gsl/gsl_eigen.h>
#include <gsl/gsl_linalg.h>
#include "rand_util.h"

dataset* NARMA(int n, int warmup, int train_length, int validation_length, int test_length, double a, double b, double c, double (*d)(double value), double d_param, double i_min, double i_max);

#endif
