#include <time.h>
#include "graph.h"
#include <stdlib.h>
#include "dataset.h"
#include "narma.h"
#include "dnet.h"
#include "train_ridge_regression.h"
#include "d_graph.h"
#include "mutate_bias.h"
#include "mutate_weight.h"
#include "mutate_edge.h"
#include "mutate_param.h"

int
main (void)
{
  srand(time(NULL));

  Graph* dg = random_d_graph(1, 200, 0.05, 0.05);
  dnet* dn = decode(dg, true);


  dataset* d = NARMA(10, 100, 3000, 5000, 5000, 0.3, 0.05, 0.1, NULL, 1.0, 0, 0.5);

  t_r_result* res = train_ridge_regression(dn, d);
  print_result(res);

  free_t_r_result(res);

  free_dnet(dn);
  printf("Mutating Graph\n");
  simple_d_graph_mutation(dg, 0.02, 0.02, 0.01, 0.2);
  printf("Graph mutated\n");
  dn = decode(dg, true);
  res = train_ridge_regression(dn, d);
  print_result(res);
  free_t_r_result(res);
  free_dnet(dn);
  freeGraph(dg);
  free_dataset(d);

}
