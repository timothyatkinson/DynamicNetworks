#include "train_ridge_regression.h"
#include "../dnet.h"
#include "../d_graph.h"

#include "dataset.h"

//Mutations
#include "mutate_add_edge.h"
#include "mutate_bias.h"
#include "mutate_delete_edge.h"
#include "mutate_edge.h"
#include "mutate_param.h"
#include "mutate_weight.h"
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
  printf("Loading datasets\n");
  dataset* n10 = load_data_set("../Datasets/NARMA10/train2000.csv", "../Datasets/NARMA10/validation3000.csv", "../Datasets/NARMA10/test3000.csv", 1, 1, 2000, 3000, 3000, 100);
  dataset* n20 = load_data_set("../Datasets/NARMA20/train2000.csv", "../Datasets/NARMA20/validation3000.csv", "../Datasets/NARMA20/test3000.csv", 1, 1, 2000, 3000, 3000, 100);
  dataset* n30 = load_data_set("../Datasets/NARMA30/train2000.csv", "../Datasets/NARMA30/validation3000.csv", "../Datasets/NARMA30/test3000.csv", 1, 1, 2000, 3000, 3000, 100);

  int num = 2000;
  double** results = malloc(12 * sizeof(double*));
  for(int i = 0; i < 12; i++){
    results[i] = malloc(num * sizeof(double));
  }

  for(int i = 0; i < num; i++){
    printf("Iteration %d\n", i);
    dnet* dn1 = rand_dnet(1, 100, false, false);
    dnet* dn2 = rand_dnet(1, 100, false, true);
    dnet* dn3 = rand_dnet(1, 100, true, false);
    dnet* dn4 = rand_esn(1, 100);
    t_r_result* r1 = train_ridge_regression(dn1, n10);
    results[0][i] = r1->test_nmse;
    free_t_r_result(r1);
    t_r_result* r2 = train_ridge_regression(dn1, n20);
    results[1][i] = r2->test_nmse;
    free_t_r_result(r2);
    t_r_result* r3 = train_ridge_regression(dn1, n30);
    results[2][i] = r3->test_nmse;
    free_t_r_result(r3);
    t_r_result* r4 = train_ridge_regression(dn2, n10);
    results[3][i] = r4->test_nmse;
    free_t_r_result(r4);
    t_r_result* r5 = train_ridge_regression(dn2, n20);
    results[4][i] = r5->test_nmse;
    free_t_r_result(r5);
    t_r_result* r6 = train_ridge_regression(dn2, n30);
    results[5][i] = r6->test_nmse;
    free_t_r_result(r6);
    t_r_result* r7 = train_ridge_regression(dn3, n10);
    results[6][i] = r7->test_nmse;
    free_t_r_result(r7);
    t_r_result* r8 = train_ridge_regression(dn3, n20);
    results[7][i] = r8->test_nmse;
    free_t_r_result(r8);
    t_r_result* r9 = train_ridge_regression(dn3, n30);
    results[8][i] = r9->test_nmse;
    free_t_r_result(r9);
    t_r_result* r10 = train_ridge_regression(dn4, n10);
    results[9][i] = r10->test_nmse;
    free_t_r_result(r10);
    t_r_result* r11 = train_ridge_regression(dn4, n20);
    results[10][i] = r11->test_nmse;
    free_t_r_result(r11);
    t_r_result* r12 = train_ridge_regression(dn4, n30);
    results[11][i] = r12->test_nmse;
    free_t_r_result(r12);
    printf("[%lf, %lf, %lf, %lf, %lf, %lf, %lf, %lf, %lf, %lf, %lf, %lf]\n", results[0][i], results[1][i], results[2][i], results[3][i], results[4][i], results[5][i], results[6][i], results[7][i], results[8][i], results[9][i], results[10][i], results[11][i]);
    free_dnet(dn1);
    free_dnet(dn2);
    free_dnet(dn3);
  }

  printf("Writing to File\n");
  print_to_csv_file("result2000.csv", results, 12, num);

  free_dataset(n10);
  free_dataset(n20);
  free_dataset(n30);

}
