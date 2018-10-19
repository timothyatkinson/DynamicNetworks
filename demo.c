#include <time.h>
#include "graph.h"
#include "random_d_graph.h"
#include <stdlib.h>

int
main (void)
{
  srand(time(NULL));

  printfGraph(random_d_graph_execute(0, 100, 0.001));
}
