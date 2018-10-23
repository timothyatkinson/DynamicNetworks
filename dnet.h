#ifndef DNET_H
#define DNET_H

#include <gsl/gsl_linalg.h>
#include "activation_functions.h"
#include <stdbool.h>
#include "matrix_util.h"
#include "rand_util.h"

static int LINEAR_OUTPUT = 0;
static int TANH_OUTPUT = 1;
static int SOFTMAX_OUTPUT = 2;

typedef struct dnet{
  int inputs;
  int nodes;
  gsl_matrix* W_In_H;
  gsl_matrix* W_In_T;
  gsl_matrix* W_Internal_H;
  gsl_matrix* W_Internal_T;
  gsl_matrix* W_Out;
  gsl_matrix* state;
  bool global_leak;
  double global_leak_rate;
} dnet;

dnet* rand_dnet(int inputs, int nodes, bool global_leak);

dnet* make_dnet(int inputs, int nodes, gsl_matrix* W_In_H, gsl_matrix* W_In_T, gsl_matrix* W_Internal_H, gsl_matrix* W_Internal_T);

void free_dnet(dnet* dn);

void warmup_dnet(dnet* dn, int warmups);

gsl_matrix* execute_dnet_sequentially(dnet* dn, gsl_matrix** input_sequence, int input_sequence_length, int warmups);

gsl_matrix* get_output(dnet* dn, gsl_matrix** input_sequence, int input_sequence_length, int warmups, int output_type);

#endif
