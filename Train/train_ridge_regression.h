#ifndef TRAIN_RIDGE_H
#define TRAIN_RIDGE_H

#include "dataset.h"
#include "../dnet.h"
#include "matrix_util.h"

typedef struct t_r_result{
  double train_nmse;
  double validation_nmse;
  double test_nmse;
} t_r_result;

t_r_result* make_t_r_result(double train_nmse, double validation_nmse, double test_nmse);
void free_t_r_result(t_r_result* res);
void print_result(t_r_result* res);
double nmse(gsl_matrix* y_target, gsl_matrix* y_actual);
t_r_result* train_ridge_regression(dnet* dn, dataset* data);
#endif
