#include "dnet.h"
#include "matrix_util.h"

dnet* rand_dnet(int inputs, int nodes, bool global_leak){

  gsl_matrix* W_In_H = gsl_matrix_calloc(nodes, inputs + 1);
  gsl_matrix* W_In_T = gsl_matrix_calloc(nodes, inputs + 1);
  gsl_matrix* W_Internal_H = gsl_matrix_calloc(nodes, nodes);
  gsl_matrix* W_Internal_T = gsl_matrix_calloc(nodes, nodes);

  double h_sparsity = rand_range(0.001, 1.0);
  double input_scaling_H = rand_range(-1.0, 1.0);
  double spectral_radius_H = rand_range(-1.0, 1.0);

  for(int i = 0; i < nodes; i++){
    for(int j = 0; j < inputs + 1; j++){
      gsl_matrix_set(W_In_H, i, j, rand_range(-1.0, 1.0));
    }
  }
  for(int i = 0; i < nodes; i++){
    for(int j = 0; j < nodes; j++){
      if(rand_bool(h_sparsity)){
        gsl_matrix_set(W_Internal_H, i, j, rand_range(-0.5, 0.5));
      }
    }
  }

  gsl_matrix_scale(W_In_H, input_scaling_H);
  if(gsl_matrix_max_eigenvalue(W_Internal_H) != 0.0){
    gsl_matrix_scale(W_Internal_H, 1.0/gsl_matrix_max_eigenvalue(W_Internal_H));
    gsl_matrix_scale(W_Internal_H, spectral_radius_H);
  }

  dnet* d = make_dnet(inputs, nodes, W_In_H, W_In_T, W_Internal_H, W_Internal_T);

  if(global_leak){
    d->global_leak = true;
    d->global_leak_rate = rand_range(0.0, 1.0);
    return d;
  }
  else{

    double t_sparsity = rand_range(0.001, 1.0);
    double input_scaling_T = rand_range(-1.0, 1.0);
    double spectral_radius_T = rand_range(-1.0, 1.0);

    double t_center = rand_range(0.0, 1.0);
    double x = -log((1/t_center) - 1.0);

    for(int i = 0; i < nodes; i++){
      for(int j = 0; j < inputs + 1; j++){
        if(j == inputs){
          gsl_matrix_set(W_In_T, i, j, x + gauss());
        }
      }
    }
    for(int i = 0; i < nodes; i++){
      for(int j = 0; j < nodes; j++){
        if(rand_bool(t_sparsity)){
          gsl_matrix_set(W_Internal_T, i, j, rand_range(-0.5, 0.5));
        }
      }
    }

    gsl_matrix_scale(W_In_T, input_scaling_T);
    if(gsl_matrix_max_eigenvalue(W_Internal_T) != 0.0){
      gsl_matrix_scale(W_Internal_T, 1.0/gsl_matrix_max_eigenvalue(W_Internal_T));
      gsl_matrix_scale(W_Internal_T, spectral_radius_T);
    }

    return d;
  }
}

dnet* make_dnet(int inputs, int nodes, gsl_matrix* W_In_H, gsl_matrix* W_In_T, gsl_matrix* W_Internal_H, gsl_matrix* W_Internal_T){
  dnet* dn = malloc(sizeof(dnet));
  dn->W_In_H = W_In_H;
  dn->W_In_T = W_In_T;
  dn->W_Internal_H = W_Internal_H;
  dn->W_Internal_T = W_Internal_T;
  dn->W_Out = gsl_matrix_calloc(1, 1);
  dn->state = gsl_matrix_calloc(1, 1);
  dn->global_leak = false;
  dn->global_leak_rate = 0.0;
  dn->nodes = nodes;
  dn->inputs = inputs;
  return dn;
}

void free_dnet(dnet* dn){
  gsl_matrix_free(dn->W_In_H);
  gsl_matrix_free(dn->W_In_T);
  gsl_matrix_free(dn->W_Internal_H);
  gsl_matrix_free(dn->W_Internal_T);
  gsl_matrix_free(dn->W_Out);
  gsl_matrix_free(dn->state);
  free(dn);
}

void warmup_dnet(dnet* dn, int warmups){
  gsl_matrix* state = gsl_matrix_calloc(dn->nodes, 1);
  gsl_matrix* zero = gsl_matrix_calloc(dn->inputs + 1, 1);
  gsl_matrix_set(zero, dn->inputs, 0, 1.0);

  gsl_matrix** zero_sequence = malloc(warmups * sizeof(gsl_matrix*));
  for(int i = 0; i < warmups; i++){
    zero_sequence[i] = zero;
  }
  gsl_matrix_free(dn->state);
  dn->state = state;
  gsl_matrix_free(execute_dnet_sequentially(dn, zero_sequence, warmups, 0));
  gsl_matrix_free(zero);
  free(zero_sequence);
}

gsl_matrix* execute_dnet_sequentially(dnet* dn, gsl_matrix** input_sequence, int input_sequence_length, int warmups){

  if(warmups > 0){
    warmup_dnet(dn, warmups);
  }

  gsl_matrix* out = gsl_matrix_calloc(dn->inputs + 1 + dn->nodes, input_sequence_length);

  for(int i = 0; i < input_sequence_length; i++){

    gsl_matrix* W_In_H_x = gsl_matrix_multiply(dn->W_In_H, input_sequence[i]);
    gsl_matrix* W_In_H_internal = gsl_matrix_multiply(dn->W_Internal_H, dn->state);
    gsl_matrix* W_H_x = gsl_matrix_sum(W_In_H_x, W_In_H_internal);
    gsl_matrix_free(W_In_H_x);
    gsl_matrix_free(W_In_H_internal);
    gsl_matrix* H = apply_function(W_H_x, tanh);
    gsl_matrix_free(W_H_x);
    gsl_matrix* T;
    if(dn->global_leak == false){

      gsl_matrix* W_In_T_x = gsl_matrix_multiply(dn->W_In_T, input_sequence[i]);
      gsl_matrix* W_In_T_internal = gsl_matrix_multiply(dn->W_Internal_T, dn->state);
      gsl_matrix* W_T_x = gsl_matrix_sum(W_In_T_x, W_In_T_internal);
      gsl_matrix_free(W_In_T_x);
      gsl_matrix_free(W_In_T_internal);
      T = apply_function(W_T_x, sigmoid);
      gsl_matrix_free(W_T_x);
    }
    else{
      T = gsl_matrix_calloc(dn->state->size1, 1);
      for(int i = 0; i < dn->state->size1; i++){
        gsl_matrix_set(T, i, 0, dn->global_leak_rate);
      }
    }
    gsl_matrix* TH = gsl_matrix_dot(T, H);
    gsl_matrix_scale(T, -1.0);
    gsl_matrix_add_constant(T, 1.0);
    gsl_matrix* TInternal = gsl_matrix_dot(T, dn->state);
    gsl_matrix* new_state = gsl_matrix_sum(TH, TInternal);
    gsl_matrix_free(TH);
    gsl_matrix_free(TInternal);
    gsl_matrix_free(H);
    gsl_matrix_free(T);

    for(int j = 0; j < dn->inputs + 1; j++){
      gsl_matrix_set(out, j, i, gsl_matrix_get(input_sequence[i], j, 0));
    }
    for(int j = dn->inputs + 1; j < dn->inputs + 1 + dn->nodes; j++){
      gsl_matrix_set(out, j, i, gsl_matrix_get(new_state, j - (dn->inputs + 1), 0));
    }

    gsl_matrix_free(dn->state);
    dn->state = new_state;
  }

  return out;
}

gsl_matrix* get_output(dnet* dn, gsl_matrix** input_sequence, int input_sequence_length, int warmups, int output_type){
  gsl_matrix* out = execute_dnet_sequentially(dn, input_sequence, input_sequence_length, warmups);

  if(output_type == LINEAR_OUTPUT){
    gsl_matrix* linear = gsl_matrix_multiply(dn->W_Out, out);
    gsl_matrix_free(out);
    return linear;
  }
  else if(output_type = SOFTMAX_OUTPUT){
    gsl_matrix* linear = gsl_matrix_multiply(dn->W_Out, out);
    gsl_matrix* ex = apply_function(linear, exp);
    gsl_matrix_free(linear);
    gsl_matrix_free(out);
    for(int i = 0; i < ex->size2; i++){
      double sum = 0.0;
      for(int j = 0; j < ex->size1; j++){
        sum += gsl_matrix_get(ex, j, i);
      }
      for(int j = 0; j < ex->size1; j++){
        gsl_matrix_set(ex, j, i, gsl_matrix_get(ex, j, i) / sum);
      }

    }

    return ex;
  }
  else if(output_type = TANH_OUTPUT){
    gsl_matrix* linear = gsl_matrix_multiply(dn->W_Out, out);
    gsl_matrix* ex = apply_function(linear, tanh);
    gsl_matrix_free(linear);
    gsl_matrix_free(out);
    return ex;
  }
  return NULL;
}
