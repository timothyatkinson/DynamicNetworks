#include "morphism.h"

extern Graph *random_d_graph_host;
extern int *random_d_graph_node_map;
extern MorphismPot *random_d_graph_pot;

Graph* random_d_graph_execute(int inputs, int n, double p);
