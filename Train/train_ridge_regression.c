#include "train_ridge_regression.h"

t_r_result* make_t_r_result(double train_nmse, double validation_nmse, double test_nmse){
  t_r_result* res = malloc(sizeof(t_r_result));
  res->train_nmse = train_nmse;
  res->validation_nmse = validation_nmse;
  res->test_nmse = test_nmse;
  return res;
}

void free_t_r_result(t_r_result* res){
  free(res);
}

void print_result(t_r_result* res){
  printf("Result is [%lf train] [%lf validation] [%lf test].\n", res->train_nmse, res->validation_nmse, res->test_nmse);
}

t_r_result* train_ridge_regression(dnet* dn, dataset* data){

  double* b = malloc(5 * sizeof(double));
  b[0] = 0.1;
  b[1] = 0.001;
  b[2] = 0.00001;
  b[3] = 0.0000001;
  b[4] = 0.000000001;
  int betas = 5;

  gsl_matrix* X_train = execute_dnet_sequentially(dn, data->train_input_sequence, data->train_input_sequence_length, data->warmups);

  gsl_matrix* XXt = gsl_matrix_multiply_transpose_b(X_train, X_train);

  gsl_matrix* y_target = data->train_output;
  gsl_matrix* id = gsl_matrix_alloc(XXt->size1, XXt->size1);
  gsl_matrix_set_identity(id);

  gsl_matrix* y_Xt = gsl_matrix_multiply_transpose_b(y_target, X_train);

  gsl_matrix* best_Wout = dn->W_Out;
  double best_validation = 9999999999999999999999.9;

  for(int i = 0; i < betas; i++){
    gsl_matrix* beta_id = gsl_matrix_alloc(XXt->size1, XXt->size1);
    gsl_matrix_memcpy(beta_id, id);
    gsl_matrix_scale(beta_id, b[i]);

    gsl_matrix_add(beta_id, XXt);
    gsl_matrix* inverse = gsl_matrix_inverse(beta_id);
    gsl_matrix* w_candidate = gsl_matrix_multiply(y_Xt, inverse);

    gsl_matrix_free(inverse);

    dn->W_Out = w_candidate;

    gsl_matrix* validation_output = get_output(dn, data->validation_input_sequence, data->validation_input_sequence_length, data->warmups, LINEAR_OUTPUT);

    double score = nmse(validation_output, data->validation_output);

    gsl_matrix_free(validation_output);

    if(score < best_validation){
      gsl_matrix_free(best_Wout);
      best_Wout = w_candidate;
      best_validation = score;
    }
    else{
      gsl_matrix_free(w_candidate);
    }

    gsl_matrix_free(beta_id);
  }

  dn->W_Out = best_Wout;

  gsl_matrix* train_output = get_output(dn, data->train_input_sequence, data->train_input_sequence_length, data->warmups, LINEAR_OUTPUT);
  gsl_matrix* validation_output = get_output(dn, data->validation_input_sequence, data->validation_input_sequence_length, data->warmups, LINEAR_OUTPUT);
  gsl_matrix* test_output = get_output(dn, data->test_input_sequence, data->test_input_sequence_length, data->warmups, LINEAR_OUTPUT);

  t_r_result* res = make_t_r_result(nmse(train_output, data->train_output), nmse(validation_output, data->validation_output), nmse(test_output, data->test_output));

  gsl_matrix_free(train_output);
  gsl_matrix_free(validation_output);
  gsl_matrix_free(test_output);

  gsl_matrix_free(X_train);
  gsl_matrix_free(XXt);
  gsl_matrix_free(id);
  gsl_matrix_free(y_Xt);

  free(b);

  return res;
}

double mean(gsl_matrix* row);
double mean(gsl_matrix* row){
  double sum = 0.0;
  for(int i = 0; i < row->size2; i++){
    sum += gsl_matrix_get(row, 0, i);
  }
  return sum / (double)row->size2;
}

double variance(gsl_matrix* row);
double variance(gsl_matrix* row){
  double m = mean(row);
  double sum = 0.0;
  for(int i = 0; i < row->size2; i++){
    double diff = gsl_matrix_get(row, 0, i) - m;
    sum += (diff * diff);
  }
  return sum / (double)row->size2;
}

double nmse(gsl_matrix* y_target, gsl_matrix* y_actual){
  double sum = 0.0;
  double v = variance(y_target);
  for(int i = 0; i < y_target->size2; i++){
    for(int j = 0; j < y_target->size1; j++){
      sum += ((gsl_matrix_get(y_target, j, i) - gsl_matrix_get(y_actual, j, i)) * (gsl_matrix_get(y_target, j, i) - gsl_matrix_get(y_actual, j, i)) /v );
    }
  }
  return sum / (double)y_target->size2;
}
