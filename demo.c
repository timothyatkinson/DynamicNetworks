#include <time.h>
#include "graph.h"
#include <stdlib.h>
#include "dataset.h"
#include "narma.h"
#include "dnet.h"
#include "train_ridge_regression.h"
#include "train_classifier.h"
#include "d_graph.h"
#include "mutate_bias.h"
#include "mutate_weight.h"
#include "mutate_edge.h"
#include "mutate_param.h"
#include "mutate_add_edge.h"
#include "mutate_delete_edge.h"
#include "cifar10.h"

int
main (void)
{
  srand(time(NULL));

  Graph* dg = random_d_graph(1, 100, 0.05, 0.05);
  dnet* dn = decode(dg, false);
  dnet* dn2 = rand_dnet(1, 300, true, false);

  dnet* cf10 = rand_dnet(3, 300, true, false);

  dataset* d = NARMA(10, 100, 3000, 5000, 5000, 0.3, 0.05, 0.1, NULL, 1.0, 0, 0.5);

  printf("Loading CIFAR10\n");
  dataset* d2 = load_CIFAR_10();

  printf("Training CIFAR10\n");
  class_result* class_res = train_classifier_regression(cf10, d2);
  print_class_result(class_res);
  free_class_result(class_res);


  printf("Freeing CIFAR10\n");
  free_dataset(d2);

  t_r_result* res = train_ridge_regression(dn, d);
  t_r_result* res2 = train_ridge_regression(dn2, d);
  print_result(res);
  print_result(res2);

  free_t_r_result(res);
  free_t_r_result(res2);

  free_dnet(dn);
  printf("Mutating Graph\n");
  mutate_delete_edge_execute(dg);
  printf("Graph mutated\n");
  dn = decode(dg, false);
  res = train_ridge_regression(dn, d);
  print_result(res);
  free_t_r_result(res);
  free_dnet(dn);
  free_dnet(dn2);
  freeGraph(dg);
  free_dataset(d);

}
