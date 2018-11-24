#include <time.h>
#include "dataset.h"
#include "narma.h"
#include "graph.h"
#include "dnet.h"
#include "train_ridge_regression.h"
#include "d_graph.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "matrix_util.h"

void store_dataset(char* tdir, char* vdir, char* tedir, dataset* d);
void store_dataset(char* tdir, char* vdir, char* tedir, dataset* d){
  FILE * fp;
  int i;
  /* open the file for writing*/
  printf("%s\n", tdir);
  fp = fopen (tdir,"w");

  for(i = 0; i < d->train_input_sequence_length;i++){
      fprintf (fp, "%.17g\t %.17g\n", gsl_matrix_get(d->train_input_sequence[i], 0, 0), gsl_matrix_get(d->train_output, 0, i));
  }

  /* close the file*/
  fclose (fp);

  printf("%s\n", vdir);
  fp = fopen (vdir, "w");

  for(i = 0; i < d->validation_input_sequence_length;i++){
      fprintf (fp, "%.17g\t %.17g\n", gsl_matrix_get(d->validation_input_sequence[i], 0, 0), gsl_matrix_get(d->validation_output, 0, i));
  }

  /* close the file*/
  fclose(fp);

  printf("%s\n", tedir);
  fp = fopen (tedir, "w");

  for(i = 0; i < d->test_input_sequence_length;i++){
      fprintf (fp, "%.17g\t %.17g\n", gsl_matrix_get(d->test_input_sequence[i], 0, 0), gsl_matrix_get(d->test_output, 0, i));
  }

  /* close the file*/
  fclose (fp);
}

int
main (void)
{
  srand(time(NULL));

  //NARMA10
  printf("Generating and storing NARMA 10\n");

  dataset* d = NARMA(10, 100, 2000, 3000, 3000, 0.3, 0.05, 0.1, NULL, 1.0, 0, 0.5);

  store_dataset("NARMA10/train2000.csv", "NARMA10/validation3000.csv", "NARMA10/test3000.csv", d);

  dnet* dn = rand_dnet(1, 100, false, false);

  t_r_result* res = train_ridge_regression(dn, d);

  printf("Pre store performance on NARMA 10:\n");
  print_result(res);
  free_t_r_result(res);
  res = train_ridge_regression(dn, d);
  free_dataset(d);

  d = load_data_set("NARMA10/train2000.csv", "NARMA10/validation3000.csv", "NARMA10/test3000.csv", 1, 1, 2000, 3000, 3000, 100);
  res = train_ridge_regression(dn, d);

  printf("Post store performance on NARMA 10:\n");
  print_result(res);
  free_t_r_result(res);
  free_dataset(d);

  //NARMA20
  printf("Generating and storing NARMA 20\n");
  d = NARMA(20, 100, 2000, 3000, 3000, 0.3, 0.05, 0.01, tanh,-1000, 0, 0.5);

  store_dataset("NARMA20/train2000.csv", "NARMA20/validation3000.csv", "NARMA20/test3000.csv", d);

  res = train_ridge_regression(dn, d);

  printf("Pre store performance on NARMA 20:\n");
  print_result(res);
  free_t_r_result(res);
  free_dataset(d);
  d = load_data_set("NARMA20/train2000.csv", "NARMA20/validation3000.csv", "NARMA20/test3000.csv", 1, 1, 2000, 3000, 3000, 100);
  res = train_ridge_regression(dn, d);

  printf("Post store performance on NARMA 20:\n");
  print_result(res);
  free_t_r_result(res);
  free_dataset(d);

  //NARMA30
  printf("Generating and storing NARMA 30\n");
  d = NARMA(30, 100, 2000, 3000, 3000, 0.2, 0.04, 0.001, NULL, 1.0, 0, 0.5);

  store_dataset("NARMA30/train2000.csv", "NARMA30/validation3000.csv", "NARMA30/test3000.csv", d);

  res = train_ridge_regression(dn, d);

  printf("Pre store performance on NARMA 30:\n");
  print_result(res);
  free_t_r_result(res);
  free_dataset(d);
  d = load_data_set("NARMA30/train2000.csv", "NARMA30/validation3000.csv", "NARMA30/test3000.csv", 1, 1, 2000, 3000, 3000, 100);
  res = train_ridge_regression(dn, d);

  printf("Post store performance on NARMA 30:\n");
  print_result(res);
  free_t_r_result(res);
  free_dataset(d);
  free_dnet(dn);
  printf("Done\n");

}
