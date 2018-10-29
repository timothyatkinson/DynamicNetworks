#include "d_graph.h"
#include "rand_util.h"
#include "mutate_bias.h"
#include "mutate_weight.h"
#include "mutate_edge.h"
#include "mutate_param.h"
void add_H_edge(Graph* g, int source, int target);
void add_H_edge(Graph* g, int source, int target){
  HostAtom array[2];
  HostLabel label;
  array[0].type = 's';
  array[0].str = "H";
  array[1].type = 'i';
  array[1].num = rand_range(-1000, 1000);
  HostList *list = makeHostList(array, 2, false);
  label = makeHostLabel(0, 2, list);
  addEdge(g, label, source, target);
}

void add_T_edge(Graph* g, int source, int target);
void add_T_edge(Graph* g, int source, int target){
  HostAtom array[2];
  HostLabel label;
  array[0].type = 's';
  array[0].str = "T";
  array[1].type = 'i';
  array[1].num = rand_range(-1000, 1000);
  HostList *list = makeHostList(array, 2, false);
  label = makeHostLabel(0, 2, list);
  addEdge(g, label, source, target);
}


Graph* random_d_graph(int inputs, int n, double p_H, double p_T)
{
   Graph* random_d_graph = build_empty_host_graph();

   int* input_map = malloc(inputs * sizeof(int));
   for(int i = 0; i < inputs; i++){
     HostAtom array[2];
     HostLabel label;
     array[0].type = 's';
     array[0].str = "Input";
     array[1].type = 'i';
     array[1].num = i;
     HostList *list = makeHostList(array, 2, false);
     label = makeHostLabel(0, 2, list);
     input_map[i] = addNode(random_d_graph, 0, label);
   }

   do{
     HostAtom array[2];
     HostLabel label;
     array[0].type = 's';
     array[0].str = "Leak_Rate";
     array[1].type = 'i';
     array[1].num = rand_range(0, 1000);
     HostList *list = makeHostList(array, 2, false);
     label = makeHostLabel(1, 2, list);
     addNode(random_d_graph, 0, label);
     break;
   } while(1);

   do{
     HostAtom array[2];
     HostLabel label;
     array[0].type = 's';
     array[0].str = "Spectral_Radius_H";
     array[1].type = 'i';
     array[1].num = rand_range(-1000, 1000);
     HostList *list = makeHostList(array, 2, false);
     label = makeHostLabel(1, 2, list);
     addNode(random_d_graph, 0, label);
     break;
   } while(1);

   do{
     HostAtom array[2];
     HostLabel label;
     array[0].type = 's';
     array[0].str = "Spectral_Radius_T";
     array[1].type = 'i';
     array[1].num = rand_range(-1000, 1000);
     HostList *list = makeHostList(array, 2, false);
     label = makeHostLabel(1, 2, list);
     addNode(random_d_graph, 0, label);
     break;
   } while(1);

   do{
     HostAtom array[2];
     HostLabel label;
     array[0].type = 's';
     array[0].str = "Input_Scaling_H";
     array[1].type = 'i';
     array[1].num = rand_range(-1000, 1000);
     HostList *list = makeHostList(array, 2, false);
     label = makeHostLabel(1, 2, list);
     addNode(random_d_graph, 0, label);
     break;
   } while(1);

   do{
     HostAtom array[2];
     HostLabel label;
     array[0].type = 's';
     array[0].str = "Input_Scaling_T";
     array[1].type = 'i';
     array[1].num = rand_range(-1000, 1000);
     HostList *list = makeHostList(array, 2, false);
     label = makeHostLabel(1, 2, list);
     addNode(random_d_graph, 0, label);
     break;
   } while(1);

   int* node_map = malloc(n * sizeof(int));

   for(int i = 0; i < n; i++){
     HostAtom array[3];
     HostLabel label;
     array[0].type = 's';
     array[0].str = "Node";
     array[1].type = 'i';
     array[1].num = rand_integer(-1000, 1000);
     array[2].type = 'i';
     array[2].num = rand_integer(-1000, 1000);
     HostList *list = makeHostList(array, 3, false);
     label = makeHostLabel(0, 3, list);
     node_map[i] = addNode(random_d_graph, 0, label);
   }

   for(int i = 0; i < n; i++){

     for(int j = 0; j < inputs; j++){
       if(rand_bool(p_H)){
         add_H_edge(random_d_graph, node_map[i], input_map[j]);
       }
       if(rand_bool(p_H)){
         add_T_edge(random_d_graph, node_map[i], input_map[j]);
       }
     }
     for(int j = 0; j < n; j++){
       if(rand_bool(p_H)){
         add_H_edge(random_d_graph, node_map[i], node_map[j]);
       }
       if(rand_bool(p_H)){
         add_T_edge(random_d_graph, node_map[i], node_map[j]);
       }
     }
   }
   free(input_map);
   free(node_map);
   return random_d_graph;
 }

int count_inputs(Graph* d_graph);
int count_inputs(Graph* d_graph){
  int inputs = 0;
  for(int host_index = 0; host_index < d_graph->nodes.size; host_index++)
  {
     Node *host_node = getNode(d_graph, host_index);
     if(host_node == NULL || host_node->index == -1) continue;
     HostLabel node_label = host_node->label;
     char* grp = node_label.list->first->atom.str;
     if(strcmp(grp, "Input") == 0){
       inputs++;
     }
   }
   return inputs;
}


double get_spectral_radius_H(Graph* d_graph);
double get_spectral_radius_H(Graph* d_graph){
  int sp = -1000;
  for(int host_index = 0; host_index < d_graph->nodes.size; host_index++)
  {
     Node *host_node = getNode(d_graph, host_index);
     if(host_node == NULL || host_node->index == -1) continue;
     HostLabel node_label = host_node->label;
     char* grp = node_label.list->first->atom.str;
     if(strcmp(grp, "Spectral_Radius_H") == 0){
       sp = node_label.list->first->next->atom.num;
     }
   }
   return (double)sp / 1000.0;
}


double get_spectral_radius_T(Graph* d_graph);
double get_spectral_radius_T(Graph* d_graph){
  int sp = -1000;
  for(int host_index = 0; host_index < d_graph->nodes.size; host_index++)
  {
     Node *host_node = getNode(d_graph, host_index);
     if(host_node == NULL || host_node->index == -1) continue;
     HostLabel node_label = host_node->label;
     char* grp = node_label.list->first->atom.str;
     if(strcmp(grp, "Spectral_Radius_T") == 0){
       sp = node_label.list->first->next->atom.num;
     }
   }
   return (double)sp / 1000.0;
}


double get_input_scaling_H(Graph* d_graph);
double get_input_scaling_H(Graph* d_graph){
  int sp = -1000;
  for(int host_index = 0; host_index < d_graph->nodes.size; host_index++)
  {
     Node *host_node = getNode(d_graph, host_index);
     if(host_node == NULL || host_node->index == -1) continue;
     HostLabel node_label = host_node->label;
     char* grp = node_label.list->first->atom.str;
     if(strcmp(grp, "Input_Scaling_H") == 0){
       sp = node_label.list->first->next->atom.num;
     }
   }
   return (double)sp / 1000.0;
}


double get_input_scaling_T(Graph* d_graph);
double get_input_scaling_T(Graph* d_graph){
  int sp = -1000;
  for(int host_index = 0; host_index < d_graph->nodes.size; host_index++)
  {
     Node *host_node = getNode(d_graph, host_index);
     if(host_node == NULL || host_node->index == -1) continue;
     HostLabel node_label = host_node->label;
     char* grp = node_label.list->first->atom.str;
     if(strcmp(grp, "Input_Scaling_T") == 0){
       sp = node_label.list->first->next->atom.num;
     }
   }
   return (double)sp / 1000.0;
}


double get_leak_rate(Graph* d_graph);
double get_leak_rate(Graph* d_graph){
  int sp = -1000;
  for(int host_index = 0; host_index < d_graph->nodes.size; host_index++)
  {
     Node *host_node = getNode(d_graph, host_index);
     if(host_node == NULL || host_node->index == -1) continue;
     HostLabel node_label = host_node->label;
     char* grp = node_label.list->first->atom.str;
     if(strcmp(grp, "Leak_Rate") == 0){
       sp = node_label.list->first->next->atom.num;
     }
   }
   return (double)sp / 1000.0;
}

bool is_target_input(Graph* d_graph, Edge* edge);
bool is_target_input(Graph* d_graph, Edge* edge){
  Node* target_node = getNode(d_graph, edge->target);
  HostLabel label = target_node->label;
  char* grp = label.list->first->atom.str;
  int num = label.list->first->next->atom.num;
  return strcmp(grp, "Input") == 0;
}

dnet* decode(Graph* d_graph, bool global_leak){
  printf("%d inputs\n", count_inputs(d_graph));
  int inputs = count_inputs(d_graph);

  int nodes = d_graph->number_of_nodes - (inputs + 5);
  printf("%d nodes\n", nodes);

  double spectral_radius_H = get_spectral_radius_H(d_graph);
  double spectral_radius_T = get_spectral_radius_T(d_graph);

  double input_scaling_H = get_input_scaling_H(d_graph);
  double input_scaling_T = get_input_scaling_T(d_graph);

  double leak_rate = get_leak_rate(d_graph);

  printf("Spectral Radii %lf %lf\n", spectral_radius_H, spectral_radius_T);
  printf("Input Scaling %lf %lf\n", input_scaling_H, input_scaling_T);
  printf("Leak Rate %lf\n", leak_rate);

  int* input_map = malloc(d_graph->nodes.size * sizeof(int));
  int* node_map = malloc(d_graph->nodes.size * sizeof(int));
  int n = 0;

  gsl_matrix* W_In_H = gsl_matrix_calloc(nodes, inputs + 1);
  gsl_matrix* W_In_T = gsl_matrix_calloc(nodes, inputs + 1);
  gsl_matrix* W_Internal_H = gsl_matrix_calloc(nodes, nodes);
  gsl_matrix* W_Internal_T = gsl_matrix_calloc(nodes, nodes);

  printf("Decoding Weights\n");

  for(int host_index = 0; host_index < d_graph->nodes.size; host_index++)
  {
     Node *host_node = getNode(d_graph, host_index);
     if(host_node == NULL || host_node->index == -1) continue;
     HostLabel node_label = host_node->label;
     char* grp = node_label.list->first->atom.str;
     if(strcmp(grp, "Input") == 0){
       int x = node_label.list->first->next->atom.num;
       input_map[host_index] = x;
     }
     else if(strcmp(grp, "Node") == 0){
       node_map[host_index] = n;
       n++;
       int h = node_label.list->first->next->atom.num;
       int t = node_label.list->first->next->next->atom.num;
       double h_bias = (double)h / 1000.0;
       double t_bias = (double)t / 1000.0;
       gsl_matrix_set(W_In_H, node_map[host_index], inputs, h_bias);
       gsl_matrix_set(W_In_T, node_map[host_index], inputs, t_bias);
     }
   }

   for(int host_index = 0; host_index < d_graph->nodes.size; host_index++)
   {
    Node *host_node = getNode(d_graph, host_index);
    if(host_node == NULL || host_node->index == -1) continue;
    HostLabel node_label = host_node->label;
    char* grp = node_label.list->first->atom.str;
    if(strcmp(grp, "Node") == 0){
      for(int counter = 0; counter < host_node->out_edges.size + 2; counter++)
      {
        Edge *host_edge = getNthOutEdge(d_graph, host_node, counter);
        if(host_edge == NULL) continue;
        int target = host_edge->target;

       HostLabel label = host_edge->label;
       char* s = label.list->first->atom.str;
       double w = (double)(label.list->first->next->atom.num) / 1000.0;
       if(strcmp(s, "H") == 0){
         int wIndex = label.list->first->next->atom.num;
         int src = host_edge->source;
         int target = host_edge->target;

         if(is_target_input(d_graph, host_edge)){
           gsl_matrix_set(W_In_H, node_map[src], input_map[target], w);
         }
         else{
           gsl_matrix_set(W_Internal_H, node_map[src], node_map[target], w);
         }
       }
       if(strcmp(s, "T") == 0){
         int wIndex = label.list->first->next->atom.num;
         int src = host_edge->source;
         int target = host_edge->target;

         if(is_target_input(d_graph, host_edge)){
           gsl_matrix_set(W_In_T, node_map[src], input_map[target], w);
         }
         else{
           gsl_matrix_set(W_Internal_T, node_map[src], node_map[target], w);
         }
       }
      }
    }
  }

  gsl_matrix_scale(W_In_H, input_scaling_H);
  if(gsl_matrix_max_eigenvalue(W_Internal_H) != 0.0){
    gsl_matrix_scale(W_Internal_H, 1.0/gsl_matrix_max_eigenvalue(W_Internal_H));
    gsl_matrix_scale(W_Internal_H, spectral_radius_H);
  }

  gsl_matrix_scale(W_In_T, input_scaling_T);
  if(gsl_matrix_max_eigenvalue(W_Internal_T) != 0.0){
    gsl_matrix_scale(W_Internal_T, 1.0/gsl_matrix_max_eigenvalue(W_Internal_T));
    gsl_matrix_scale(W_Internal_T, spectral_radius_T);
  }

  printf("Weights Decoded\n");
  dnet* dn = make_dnet(inputs, nodes, W_In_H, W_In_T, W_Internal_H, W_Internal_T);

  if(global_leak){
    dn->global_leak = true;
    dn->global_leak_rate = leak_rate;
  }

  free(input_map);
  free(node_map);
  return dn;
}

void simple_d_graph_mutation(Graph* d_graph, double bias_m_rate, double weight_m_rate, double edge_m_rate, double param_m_rate){
  int bias = binomial(d_graph->number_of_nodes - (count_inputs(d_graph) + 5), bias_m_rate);
  int weight = binomial(d_graph->number_of_edges, weight_m_rate);
  int edge = binomial(d_graph->number_of_edges, edge_m_rate);
  int param = binomial(5, param_m_rate);

  for(int i = 0; i < bias; i++){
    mutate_bias_execute(d_graph);
  }

  for(int i = 0; i < weight; i++){
    mutate_weight_execute(d_graph);
  }

  for(int i = 0; i < edge; i++){
    mutate_edge_execute(d_graph);
  }

  for(int i = 0; i < param; i++){
    mutate_param_execute(d_graph);
  }
}
