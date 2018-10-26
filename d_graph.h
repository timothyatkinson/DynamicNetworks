#ifndef D_GRAPH_H
#define D_GRAPH_H

#include "graph.h"
#include "label.h"
#include "util.h"
#include "dnet.h"
#include "stdbool.h"

Graph* random_d_graph(int inputs, int n, double p_H, double p_T);
dnet* decode(Graph* d_graph, bool global_leak);
void simple_d_graph_mutation(Graph* d_graph, double bias_m_rate, double weight_m_rate, double edge_m_rate, double param_m_rate);
#endif
