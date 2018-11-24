#ifndef DATASET_H
#define DATASET_H

#include <gsl/gsl_blas.h>
#include <gsl/gsl_eigen.h>
#include <gsl/gsl_linalg.h>

typedef struct dataset{
  gsl_matrix** train_input_sequence;
  int train_input_sequence_length;
  gsl_matrix* train_output;

  gsl_matrix** validation_input_sequence;
  int validation_input_sequence_length;
  gsl_matrix* validation_output;

  gsl_matrix** test_input_sequence;
  int test_input_sequence_length;
  gsl_matrix* test_output;
  int warmups;
} dataset;

dataset* alloc_dataset();

void free_dataset();
dataset* load_data_set(char* train_file, char* validation_file, char* test_file, int inputs, int outputs, int train_rows, int validation_rows, int test_rows, int warmups);
#endif
