#include "dataset.h"

dataset* alloc_dataset(){
  dataset* d = malloc(sizeof(dataset));
  return d;
}

void free_dataset(dataset* d){
  for(int i = 0; i < d->train_input_sequence_length; i++){
    gsl_matrix_free(d->train_input_sequence[i]);
  }
  free(d->train_input_sequence);
  gsl_matrix_free(d->train_output);
  for(int i = 0; i < d->validation_input_sequence_length; i++){
    gsl_matrix_free(d->validation_input_sequence[i]);
  }
  gsl_matrix_free(d->validation_output);
  free(d->validation_input_sequence);
  for(int i = 0; i < d->test_input_sequence_length; i++){
    gsl_matrix_free(d->test_input_sequence[i]);
  }
  gsl_matrix_free(d->test_output);
  free(d->test_input_sequence);
  free(d);
}
