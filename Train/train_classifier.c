#include "train_classifier.h"

class_result* make_class_result(double train_mse, double train_accuracy, double validation_mse, double validation_accuracy, double test_mse, double test_accuracy){
  class_result* res = malloc(sizeof(class_result));
  res->train_mse = train_mse;
  res->train_accuracy = train_accuracy;
  res->validation_mse = validation_mse;
  res->validation_accuracy = validation_accuracy;
  res->test_mse = test_mse;
  res->test_accuracy = test_accuracy;
  return res;
}

void free_class_result(class_result* res){
  free(res);
}

void print_class_result(class_result* res){
  printf("Result is [%lf, %lf train] [%lf, %lf validation] [%lf, %lf test].\n", res->train_mse, res->train_accuracy, res->validation_mse, res->validation_accuracy, res->test_mse, res->test_accuracy);
}

class_result* train_classifier_regression(dnet* dn, dataset* data){

  double* b = malloc(5 * sizeof(double));
  b[0] = 0.1;
  b[1] = 0.001;
  b[2] = 0.00001;
  b[3] = 0.0000001;
  b[4] = 0.000000001;
  int betas = 5;

  gsl_matrix* X_train = execute_dnet_batch(dn, data->train_input_sequence, data->train_input_sequence_length, data->warmups);

  gsl_matrix* XXt = gsl_matrix_multiply_transpose_b(X_train, X_train);

  gsl_matrix* y_target = data->train_output;

  gsl_matrix* y_Xt = gsl_matrix_multiply_transpose_b(y_target, X_train);

  gsl_matrix* best_Wout = dn->W_Out;
  double best_validation = 1000000000000.0;
  bool first = true;

  for(int i = 0; i < betas; i++){
    gsl_matrix* beta_id = gsl_matrix_alloc(XXt->size1, XXt->size1);
    gsl_matrix_set_identity(beta_id);
    gsl_matrix_scale(beta_id, b[i]);

    gsl_matrix_add(beta_id, XXt);
    gsl_matrix* inverse = gsl_matrix_inverse(beta_id);
    gsl_matrix* w_candidate = gsl_matrix_multiply(y_Xt, inverse);

    gsl_matrix_free(inverse);

    dn->W_Out = w_candidate;

    gsl_matrix* validation_output = get_output_batch(dn, data->validation_input_sequence, data->validation_input_sequence_length, data->warmups, SOFTMAX_OUTPUT);

    double score = mse(data->validation_output,validation_output);

    gsl_matrix_free(validation_output);

    if(score < best_validation || first){
      gsl_matrix_free(best_Wout);
      best_Wout = w_candidate;
      best_validation = score;
      first = false;
    }
    else{
      gsl_matrix_free(w_candidate);
    }


    gsl_matrix_free(beta_id);
  }

  dn->W_Out = best_Wout;

  gsl_matrix* train_output = get_output_batch(dn, data->train_input_sequence, data->train_input_sequence_length, data->warmups, SOFTMAX_OUTPUT);
  gsl_matrix* validation_output = get_output_batch(dn, data->validation_input_sequence, data->validation_input_sequence_length, data->warmups, SOFTMAX_OUTPUT);
  gsl_matrix* test_output = get_output_batch(dn, data->test_input_sequence, data->test_input_sequence_length, data->warmups, SOFTMAX_OUTPUT);

  class_result* res = make_class_result(mse(data->train_output, train_output), accuracy(data->train_output, train_output),
                    mse(data->validation_output, validation_output), accuracy(data->validation_output, validation_output),
                    mse(data->test_output, test_output), accuracy(data->test_output, test_output));

  gsl_matrix_free(train_output);
  gsl_matrix_free(validation_output);
  gsl_matrix_free(test_output);

  gsl_matrix_free(X_train);
  gsl_matrix_free(XXt);
  gsl_matrix_free(y_Xt);

  free(b);

  return res;
}

double mse(gsl_matrix* y_target, gsl_matrix* y_actual){
  double sum = 0.0;
  for(int i = 0; i < y_target->size2; i++){
    for(int j = 0; j < y_target->size1; j++){
      sum += ((gsl_matrix_get(y_target, j, i) - gsl_matrix_get(y_actual, j, i)) * (gsl_matrix_get(y_target, j, i) - gsl_matrix_get(y_actual, j, i)));
    }
  }
  return sum / (double)y_target->size2;
}

double accuracy(gsl_matrix* y_target, gsl_matrix* y_actual){
  double correct = 0.0;
  for(int i = 0; i < y_target->size2; i++){
    int target = -1;
    int target_max = -999999.9;
    int actual = -1;
    int actual_max = -999999.9;
    for(int j = 0; j < y_target->size1; j++){
      if(gsl_matrix_get(y_target, j, i) > target_max){
        target_max = gsl_matrix_get(y_target, j, i);
        target = j;
      }
      if(gsl_matrix_get(y_actual, j, i) > actual_max){
        actual_max = gsl_matrix_get(y_actual, j, i);
        actual = j;
      }
    }
    if(target == actual){
      correct += 1.0;
    }
  }
  return correct / (double)y_target->size2;
}
