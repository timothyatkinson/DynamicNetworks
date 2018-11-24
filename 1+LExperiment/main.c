#include "train_ridge_regression.h"
#include "../dnet.h"
#include "../d_graph.h"

#include "dataset.h"
#include "util.h"

#include <stdlib.h>

void print_to_csv_file(char* file_path, double** data, int columns, int rows);
void print_to_csv_file(char* file_path, double** data, int columns, int rows){
  FILE* f = fopen(file_path, "w");
  printf("Writing to File %s\n", file_path);
  for(int i = 0; i < rows; i++){
    for(int j = 0; j < columns; j++){
      fprintf(f, "%lf\t", data[j][i]);
    }
    fprintf(f, "\n");
  }
  for(int i = 0; i < columns; i++){
    free(data[i]);
  }
  free(data);
  fclose(f);
}

int main(int argc, char *argv[]) {
  int mode = -1;
  int evolution = -1;
  char* narma10_path;
  char* narma20_path;
  char* narma30_path;
  if(strcmp(argv[1], "d-esn") == 0){
    mode = 0;
    printf("Running with D-ESNs\n");
  }
  if(strcmp(argv[1], "li-esn") == 0){
    printf("Running with LI-ESNs\n");
    mode = 1;
  }
  if(strcmp(argv[1], "esn") == 0){
    printf("Running with conventional ESNs\n");
    mode = 2;
  }
  if(strcmp(argv[1], "evolution") == 0){
    evolution = 0;
    printf("Using the 1 + 4 EA.\n");
    if(mode == 0){
      narma10_path = "Results/evolution_d-esn_n10.csv";
      narma20_path = "Results/evolution_d-esn_n20.csv";
      narma30_path = "Results/evolution_d-esn_n30.csv";
    }
    if(mode == 1){
      narma10_path = "Results/evolution_li-esn_n10.csv";
      narma20_path = "Results/evolution_li-esn_n20.csv";
      narma30_path = "Results/evolution_li-esn_n30.csv";
    }
    if(mode == 2){
      narma10_path = "Results/evolution_esn_n10.csv";
      narma20_path = "Results/evolution_esn_n20.csv";
      narma30_path = "Results/evolution_esn_n30.csv";
    }
  }
  else if (strcmp(argv[1], "random") == 0){
    evolution = 1;
    printf("Using random search\n");
    if(mode == 0){
      narma10_path = "Results/evolution_d-esn_n10.csv";
      narma20_path = "Results/evolution_d-esn_n20.csv";
      narma30_path = "Results/evolution_d-esn_n30.csv";
    }
    if(mode == 1){
      narma10_path = "Results/evolution_li-esn_n10.csv";
      narma20_path = "Results/evolution_li-esn_n20.csv";
      narma30_path = "Results/evolution_li-esn_n30.csv";
    }
    if(mode == 2){
      narma10_path = "Results/evolution_esn_n10.csv";
      narma20_path = "Results/evolution_esn_n20.csv";
      narma30_path = "Results/evolution_esn_n30.csv";
    }
  }
  if(mode == -1){
    printf("Error: network model not specified. Please specify \"d-esn\", \"li-esn\" or \"esn\" as the first parameter to the program\n");
    exit(0);
  }
  if(evolution == -1){
    printf("Error: search strategy not specified. Please specify \"evolution\" or \"random\" as the second parameter to the program\n");
    exit(0);
  }

  int runs = 50;
  int evaluations = 2000;


  printf("Executing search a total of %d times for each of our 3 datasets\n", runs);
  printf("Each search is allocated %d evaluations\n", evaluations);

  printf("Loading datasets\n");
  dataset* n10 = load_data_set("../Datasets/NARMA10/train2000.csv", "../Datasets/NARMA10/validation3000.csv", "../Datasets/NARMA10/test3000.csv", 1, 1, 2000, 3000, 3000, 100);
  dataset* n20 = load_data_set("../Datasets/NARMA20/train2000.csv", "../Datasets/NARMA20/validation3000.csv", "../Datasets/NARMA20/test3000.csv", 1, 1, 2000, 3000, 3000, 100);
  dataset* n30 = load_data_set("../Datasets/NARMA30/train2000.csv", "../Datasets/NARMA30/validation3000.csv", "../Datasets/NARMA30/test3000.csv", 1, 1, 2000, 3000, 3000, 100);
  printf("Datasets loaded\n");


  double** test_mse_n10 = malloc(runs * sizeof(double*));
  double** test_mse_n20 = malloc(runs * sizeof(double*));
  double** test_mse_n30 = malloc(runs * sizeof(double*));

  int runs = 300;
  int n = 100;
  for(int s = 1; s <= num; s++){

    double sparsity = (double)s / 400.0;

    printf("Running Experiment with %f\n", sparsity);


    double* test_mse_n10 = malloc(runs * sizeof(double));
    double* test_mse_n20 = malloc(runs * sizeof(double));
    double* test_mse_n30 = malloc(runs * sizeof(double));
    // double* ae_mse_n10 = malloc(runs * sizeof(double));
    // double* ae_mse_n20 = malloc(runs * sizeof(double));
    // double* ae_mse_n30 = malloc(runs * sizeof(double));
    // double* b_mse_n10 = malloc(runs * sizeof(double));
    // double* b_mse_n20 = malloc(runs * sizeof(double));
    // double* b_mse_n30 = malloc(runs * sizeof(double));
    // double* de_mse_n10 = malloc(runs * sizeof(double));
    // double* de_mse_n20 = malloc(runs * sizeof(double));
    // double* de_mse_n30 = malloc(runs * sizeof(double));
    // double* e_mse_n10 = malloc(runs * sizeof(double));
    // double* e_mse_n20 = malloc(runs * sizeof(double));
    // double* e_mse_n30 = malloc(runs * sizeof(double));
    // double* p_mse_n10 = malloc(runs * sizeof(double));
    // double* p_mse_n20 = malloc(runs * sizeof(double));
    // double* p_mse_n30 = malloc(runs * sizeof(double));
    // double* w_mse_n10 = malloc(runs * sizeof(double));
    // double* w_mse_n20 = malloc(runs * sizeof(double));
    // double* w_mse_n30 = malloc(runs * sizeof(double));
    test_mse_n10_all[s - 1] = test_mse_n10;
    test_mse_n20_all[s-1] = test_mse_n20;
    test_mse_n30_all[s-1] = test_mse_n30;
    // ae_mse_n10_all[s-1] = ae_mse_n10;
    // ae_mse_n20_all[s-1] = ae_mse_n20;
    // ae_mse_n30_all[s-1] = ae_mse_n30;
    // b_mse_n10_all[s-1] = b_mse_n10;
    // b_mse_n20_all[s-1] = b_mse_n20;
    // b_mse_n30_all[s-1] = b_mse_n30;
    // de_mse_n10_all[s-1] = de_mse_n10;
    // de_mse_n20_all[s-1] = de_mse_n20;
    // de_mse_n30_all[s-1] = de_mse_n30;
    // e_mse_n10_all[s-1] = e_mse_n10;
    // e_mse_n20_all[s-1] = e_mse_n20;
    // e_mse_n30_all[s-1] = e_mse_n30;
    // p_mse_n10_all[s-1] = p_mse_n10;
    // p_mse_n20_all[s-1] = p_mse_n20;
    // p_mse_n30_all[s-1] = p_mse_n30;
    // w_mse_n10_all[s-1] = w_mse_n10;
    // w_mse_n20_all[s-1] = w_mse_n20;
    // w_mse_n30_all[s-1] = w_mse_n30;

    for(int i = 0; i < runs; i++){
      printf("Run %d\n", i);
      printf("Gen Graph\n");
      Graph* d = random_d_graph(1, n, sparsity, sparsity);
      printf("Decode\n");
      dnet* dn = decode(d, false);

      printf("Evaluate N10\n");
      t_r_result* n10res = train_ridge_regression(dn, n10);
      printf("Evaluate N20\n");
      t_r_result* n20res = train_ridge_regression(dn, n20);
      printf("Evaluate N30\n");
      t_r_result* n30res = train_ridge_regression(dn, n30);
      test_mse_n10[i] = n10res->test_nmse;
      test_mse_n20[i] = n20res->test_nmse;
      test_mse_n30[i] = n30res->test_nmse;

      printf("%lf, %lf, %lf\n", test_mse_n10[i], test_mse_n20[i], test_mse_n30[i]);

      // Graph* d_ae = duplicate_graph(d);
      //
      // printf("Add Edge\n");
      // mutate_add_edge_execute(d_ae);
      //
      // dnet* dn_ae = decode(d_ae, false);
      //
      // t_r_result* n10res_ae = train_ridge_regression(dn_ae, n10);
      // t_r_result* n20res_ae = train_ridge_regression(dn_ae, n20);
      // t_r_result* n30res_ae = train_ridge_regression(dn_ae, n30);
      // ae_mse_n10[i] = n10res->test_nmse - n10res_ae->test_nmse;
      // ae_mse_n20[i] = n20res->test_nmse - n20res_ae->test_nmse;
      // ae_mse_n30[i] = n30res->test_nmse - n30res_ae->test_nmse;
      //
      // free_dnet(dn_ae);
      // freeGraph(d_ae);
      // free_t_r_result(n10res_ae);
      // free_t_r_result(n20res_ae);
      // free_t_r_result(n30res_ae);
      //
      // Graph* d_b = duplicate_graph(d);
      //
      // printf("Bias\n");
      // mutate_bias_execute(d_b);
      //
      // dnet* dn_b = decode(d_b, false);
      //
      // t_r_result* n10res_b = train_ridge_regression(dn_b, n10);
      // t_r_result* n20res_b = train_ridge_regression(dn_b, n20);
      // t_r_result* n30res_b = train_ridge_regression(dn_b, n30);
      // b_mse_n10[i] = n10res->test_nmse - n10res_b->test_nmse;
      // b_mse_n20[i] = n20res->test_nmse - n20res_b->test_nmse;
      // b_mse_n30[i] = n30res->test_nmse - n30res_b->test_nmse;
      //
      // free_dnet(dn_b);
      // freeGraph(d_b);
      // free_t_r_result(n10res_b);
      // free_t_r_result(n20res_b);
      // free_t_r_result(n30res_b);
      //
      // Graph* d_de = duplicate_graph(d);
      //
      // printf("Delete Edge Edge\n");
      // mutate_delete_edge_execute(d_de);
      //
      // dnet* dn_de = decode(d_de, false);
      //
      // t_r_result* n10res_de = train_ridge_regression(dn_de, n10);
      // t_r_result* n20res_de = train_ridge_regression(dn_de, n20);
      // t_r_result* n30res_de = train_ridge_regression(dn_de, n30);
      // de_mse_n10[i] = n10res->test_nmse - n10res_de->test_nmse;
      // de_mse_n20[i] = n20res->test_nmse - n20res_de->test_nmse;
      // de_mse_n30[i] = n30res->test_nmse - n30res_de->test_nmse;
      //
      // free_dnet(dn_de);
      // freeGraph(d_de);
      // free_t_r_result(n10res_de);
      // free_t_r_result(n20res_de);
      // free_t_r_result(n30res_de);
      //
      // Graph* d_e = duplicate_graph(d);
      //
      // printf("Mutate Edge\n");
      // mutate_edge_execute(d_e);
      //
      // dnet* dn_e = decode(d_e, false);
      //
      // t_r_result* n10res_e = train_ridge_regression(dn_e, n10);
      // t_r_result* n20res_e = train_ridge_regression(dn_e, n20);
      // t_r_result* n30res_e = train_ridge_regression(dn_e, n30);
      // e_mse_n10[i] = n10res->test_nmse - n10res_e->test_nmse;
      // e_mse_n20[i] = n20res->test_nmse - n20res_e->test_nmse;
      // e_mse_n30[i] = n30res->test_nmse - n30res_e->test_nmse;
      //
      // free_dnet(dn_e);
      // freeGraph(d_e);
      // free_t_r_result(n10res_e);
      // free_t_r_result(n20res_e);
      // free_t_r_result(n30res_e);
      //
      // Graph* d_p = duplicate_graph(d);
      //
      // mutate_param_execute(d_p);
      //
      // printf("Param\n");
      // dnet* dn_p = decode(d_p, false);
      //
      // t_r_result* n10res_p = train_ridge_regression(dn_p, n10);
      // t_r_result* n20res_p = train_ridge_regression(dn_p, n20);
      // t_r_result* n30res_p = train_ridge_regression(dn_p, n30);
      // p_mse_n10[i] = n10res->test_nmse - n10res_p->test_nmse;
      // p_mse_n20[i] = n20res->test_nmse - n20res_p->test_nmse;
      // p_mse_n30[i] = n30res->test_nmse - n30res_p->test_nmse;
      //
      // free_dnet(dn_p);
      // freeGraph(d_p);
      // free_t_r_result(n10res_p);
      // free_t_r_result(n20res_p);
      // free_t_r_result(n30res_p);
      //
      // Graph* d_w = duplicate_graph(d);
      //
      // mutate_weight_execute(d_w);
      //
      // printf("Weight\n");
      // dnet* dn_w = decode(d_w, false);
      //
      // t_r_result* n10res_w = train_ridge_regression(dn_w, n10);
      // t_r_result* n20res_w = train_ridge_regression(dn_w, n20);
      // t_r_result* n30res_w = train_ridge_regression(dn_w, n30);
      // w_mse_n10[i] = n10res->test_nmse - n10res_w->test_nmse;
      // w_mse_n20[i] = n20res->test_nmse - n20res_w->test_nmse;
      // w_mse_n30[i] = n30res->test_nmse - n30res_w->test_nmse;
      //
      // free_dnet(dn_w);
      // freeGraph(d_w);
      // free_t_r_result(n10res_w);
      // free_t_r_result(n20res_w);
      // free_t_r_result(n30res_w);

      free_t_r_result(n10res);
      free_t_r_result(n20res);
      free_t_r_result(n30res);
      free_dnet(dn);
      freeGraph(d);
    }
  }

  print_to_csv_file("Results/Main/n10.csv", test_mse_n10_all, (num), runs);
  print_to_csv_file("Results/Main/n20.csv", test_mse_n20_all, (num), runs);
  print_to_csv_file("Results/Main/n30.csv", test_mse_n30_all, (num), runs);
  // print_to_csv_file("Results/AddEdge/n10.csv", ae_mse_n10_all, (num), runs);
  // print_to_csv_file("Results/AddEdge/n20.csv", ae_mse_n20_all, (num), runs);
  // print_to_csv_file("Results/AddEdge/n30.csv", ae_mse_n30_all, (num), runs);
  // print_to_csv_file("Results/Bias/n10.csv", b_mse_n10_all, (num), runs);
  // print_to_csv_file("Results/Bias/n20.csv", b_mse_n20_all, (num), runs);
  // print_to_csv_file("Results/Bias/n30.csv", b_mse_n30_all, (num), runs);
  // print_to_csv_file("Results/DeleteEdge/n10.csv", de_mse_n10_all, (num), runs);
  // print_to_csv_file("Results/DeleteEdge/n20.csv", de_mse_n20_all, (num), runs);
  // print_to_csv_file("Results/DeleteEdge/n30.csv", de_mse_n30_all, (num), runs);
  // print_to_csv_file("Results/Edge/n10.csv", e_mse_n10_all, (num), runs);
  // print_to_csv_file("Results/Edge/n20.csv", e_mse_n20_all, (num), runs);
  // print_to_csv_file("Results/Edge/n30.csv", e_mse_n30_all, (num), runs);
  // print_to_csv_file("Results/Param/n10.csv", p_mse_n10_all, (num), runs);
  // print_to_csv_file("Results/Param/n20.csv", p_mse_n20_all, (num), runs);
  // print_to_csv_file("Results/Param/n30.csv", p_mse_n30_all, (num), runs);
  // print_to_csv_file("Results/Weights/n10.csv", w_mse_n10_all, (num), runs);
  // print_to_csv_file("Results/Weights/n20.csv", w_mse_n20_all, (num), runs);
  // print_to_csv_file("Results/Weights/n30.csv", w_mse_n30_all, (num), runs);

  printf("Freeing Datasets\n");
  free_dataset(n10);
  free_dataset(n20);
  free_dataset(n30);


  return 0;
}
