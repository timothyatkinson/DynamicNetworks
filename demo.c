#include <time.h>
#include "graph.h"
#include "random_d_graph.h"
#include <stdlib.h>
#include "dataset.h"
#include "narma.h"
#include "dnet.h"
#include "train_ridge_regression.h"

int
main (void)
{
  srand(time(NULL));

  dataset* d = NARMA(10, 200, 2000, 3000, 3000, 0.3, 0.05, 0.1, NULL, 1.0, 0, 0.5);

  for(int i = 0; i < 2000; i++){
    dnet* rd = rand_dnet(1, 200, false);

    t_r_result* res = train_ridge_regression(rd, d);
    printf("%d:\n", i);
    print_result(res);

    free_t_r_result(res);

    free_dnet(rd);
  }

  for(int i = 0; i < 2000; i++){
    dnet* rd = rand_dnet(1, 200, true);

    t_r_result* res = train_ridge_regression(rd, d);
    printf("%d:\n", i);
    print_result(res);

    free_t_r_result(res);

    free_dnet(rd);
  }

  free_dataset(d);

  //printfGraph(random_d_graph_execute(0, 100, 0.001));
}
