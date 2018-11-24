#include "narma.h"

dataset* NARMA(int n, int warmup, int train_length, int validation_length, int test_length, double a, double b, double c, double (*d)(double value), double d_param, double i_min, double i_max){

  dataset* data = alloc_dataset();
  data->train_input_sequence_length = train_length;
  data->validation_input_sequence_length = validation_length;
  data->test_input_sequence_length = test_length;
  data->warmups = warmup;

  double* x_train = malloc((warmup + train_length) * sizeof(double));
  double* y_train = malloc((warmup + train_length) * sizeof(double));
  double x_train_sum = 0.0;

  for(int i = 0; i < warmup + train_length; i++){
    if(i < warmup){
      x_train[i] = 0;
    }
    else{
      x_train[i] = random_range(i_min, i_max);
      x_train_sum += x_train[i];
    }

    double yt;
    if(i > 0){
      yt = y_train[i - 1];
    }
    else{
      yt = 0.0;
    }

    double sum = 0.0;
    for(int j = 0; j < n; j++){
      if((i - 1) - j > 0){
        int index = (i - 1) - j;
        sum += y_train[index];
      }
    }

    double ut;
    if(i > 0){
      ut = x_train[i - 1];
    }
    else{
      ut = 0.0;
    }
    double ut9;
    if(i - n > 0){
      ut9 = x_train[i - n];
    }
    else{
      ut9 = 0.0;
    }

    double y_pre_d = (a * yt) + (b * yt * sum) + (1.5 * ut * ut9) + c;
    double y;
    if(d_param == -1000){
      y = d(y_pre_d);
    }
    else{
      y = d_param * y_pre_d;
    }

    y_train[i] = y;
  }


  double* x_validation = malloc((warmup + validation_length) * sizeof(double));
  double* y_validation = malloc((warmup + validation_length) * sizeof(double));
  double x_validation_sum = 0.0;

  for(int i = 0; i < warmup + validation_length; i++){
    if(i < warmup){
      x_validation[i] = 0;
    }
    else{
      x_validation[i] = random_range(i_min, i_max);
      x_validation_sum += x_validation[i];
    }

    double yt;
    if(i > 0){
      yt = y_validation[i - 1];
    }
    else{
      yt = 0.0;
    }

    double sum = 0.0;
    for(int j = 0; j < n; j++){
      if((i - 1) - j > 0){
        int index = (i - 1) - j;
        sum += y_validation[index];
      }
    }

    double ut;
    if(i > 0){
      ut = x_validation[i - 1];
    }
    else{
      ut = 0.0;
    }
    double ut9;
    if(i - n > 0){
      ut9 = x_validation[i - n];
    }
    else{
      ut9 = 0.0;
    }

    double y_pre_d = (a * yt) + (b * yt * sum) + (1.5 * ut * ut9) + c;
    double y;
    if(d_param == -1000){
      y = d(y_pre_d);
    }
    else{
      y = d_param * y_pre_d;
    }

    y_validation[i] = y;
  }


  double* x_test = malloc((warmup + test_length) * sizeof(double));
  double* y_test = malloc((warmup + test_length) * sizeof(double));
  double x_test_sum = 0.0;

  for(int i = 0; i < warmup + test_length; i++){
    if(i < warmup){
      x_test[i] = 0;
    }
    else{
      x_test[i] = random_range(i_min, i_max);
      x_test_sum += x_test[i];
    }

    double yt;
    if(i > 0){
      yt = y_test[i - 1];
    }
    else{
      yt = 0.0;
    }

    double sum = 0.0;
    for(int j = 0; j < n; j++){
      if((i - 1) - j > 0){
        int index = (i - 1) - j;
        sum += y_test[index];
      }
    }

    double ut;
    if(i > 0){
      ut = x_test[i - 1];
    }
    else{
      ut = 0.0;
    }
    double ut9;
    if(i - n > 0){
      ut9 = x_test[i - n];
    }
    else{
      ut9 = 0.0;
    }

    double y_pre_d = (a * yt) + (b * yt * sum) + (1.5 * ut * ut9) + c;
    double y;
    if(d_param == -1000){
      y = d(y_pre_d);
    }
    else{
      y = d_param * y_pre_d;
    }

    y_test[i] = y;
  }

  data->train_input_sequence = malloc(sizeof(gsl_matrix*) * train_length);
  data->validation_input_sequence = malloc(sizeof(gsl_matrix*) * validation_length);
  data->test_input_sequence = malloc(sizeof(gsl_matrix*) * test_length);
  double x_train_mean = x_train_sum / (double)train_length;
  double x_validation_mean = x_validation_sum / (double)validation_length;
  double x_test_mean = x_test_sum / (double)test_length;

  data->train_output = gsl_matrix_calloc(1, train_length);
  for(int i = 0; i < train_length; i++){
    data->train_input_sequence[i] = gsl_matrix_calloc(2, 1);
    gsl_matrix_set(data->train_input_sequence[i], 0, 0, (2 * x_train[i + warmup]) - 0.5);
    gsl_matrix_set(data->train_input_sequence[i], 1, 0, 1.0);
    gsl_matrix_set(data->train_output, 0, i, (2 * y_train[i + warmup]) - 0.5);
  }

  data->validation_output = gsl_matrix_calloc(1, validation_length);
  for(int i = 0; i < validation_length; i++){
    data->validation_input_sequence[i] = gsl_matrix_calloc(2, 1);
    gsl_matrix_set(data->validation_input_sequence[i], 0, 0, (2 * x_validation[i + warmup]) - 0.5);
    gsl_matrix_set(data->validation_input_sequence[i], 1, 0, 1.0);
    gsl_matrix_set(data->validation_output, 0, i, (2 * y_validation[i + warmup]) - 0.5);
  }

  data->test_output = gsl_matrix_calloc(1, test_length);
  for(int i = 0; i < test_length; i++){
    data->test_input_sequence[i] = gsl_matrix_calloc(2, 1);
    gsl_matrix_set(data->test_input_sequence[i], 0, 0, (2 * x_test[i + warmup]) - 0.5);
    gsl_matrix_set(data->test_input_sequence[i], 1, 0, 1.0);
    gsl_matrix_set(data->test_output, 0, i, (2 * y_test[i + warmup]) - 0.5);
  }


  free(x_train);
  free(y_train);
  free(x_validation);
  free(y_validation);
  free(x_test);
  free(y_test);

  return data;

}
