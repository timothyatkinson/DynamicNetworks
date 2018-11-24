#ifndef TRAIN_CLASS_H
#define TRAIN_CLASS_H

#include "dataset.h"
#include "../dnet.h"
#include "matrix_util.h"

typedef struct class_result{
  double train_mse;
  double validation_mse;
  double test_mse;
  double train_accuracy;
  double validation_accuracy;
  double test_accuracy;
} class_result;

class_result* make_class_result(double train_mse, double train_accuracy, double validation_mse, double validation_accuracy, double test_mse, double test_accuracy);
void free_class_result(class_result* res);
void print_class_result(class_result* res);
double mse(gsl_matrix* y_target, gsl_matrix* y_actual);
double accuracy(gsl_matrix* y_target, gsl_matrix* y_actual);
class_result* train_classifier_regression(dnet* dn, dataset* data);
#endif
