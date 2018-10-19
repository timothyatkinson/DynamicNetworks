#include "random_d_graph_add_input.h"

#include "random_d_graph.h"

bool random_d_graph_b3 = false;

static bool evaluateCondition(void)
{
   return (!random_d_graph_b3);
}

static void evaluatePredicaterandom_d_graph_3(Morphism *morphism)
{
   int n0 = lookupNode(morphism, 0);
   /* If the node is not yet matched by the morphism, return. */
   if(n0 == -1) return;

   int n1 = lookupNode(morphism, 1);
   /* If the node is not yet matched by the morphism, return. */
   if(n1 == -1) return;

   Node *source = getNode(random_d_graph_host, n0);
   bool edge_found = false;
   int counter;
   for(counter = 0; counter < source->out_edges.size + 2; counter++)
   {
      Edge *edge = getNthOutEdge(random_d_graph_host, source, counter);
      if(edge != NULL && edge->target == n1)
      {
         random_d_graph_b3 = true;
         edge_found = true;
         break;
      }
   }
   if(!edge_found) random_d_graph_b3 = false;
}

static bool match_n0(Morphism *morphism);
static bool match_n1(Morphism *morphism);

bool matchrandom_d_graph_add_input(Morphism *morphism)
{
   if(2 > random_d_graph_host->number_of_nodes || 0 > random_d_graph_host->number_of_edges) return false;
   if(match_n0(morphism)) return true;
   else
   {
      initialiseMorphism(morphism, random_d_graph_host);
      return false;
   }
}

static bool match_n0(Morphism *morphism)
{
   int host_index;
   for(host_index = 0; host_index < random_d_graph_host->nodes.size; host_index++)
   {
      Node *host_node = getNode(random_d_graph_host, host_index);
      if(host_node == NULL || host_node->index == -1) continue;
      if(host_node->matched) continue;
      if(host_node->label.mark != 0) continue;
      if(host_node->indegree < 0 || host_node->outdegree < 0 ||
         ((host_node->outdegree + host_node->indegree - 0 - 0 - 0) < 0)) continue;

      HostLabel label = host_node->label;
      bool match = false;
      /* Label Matching */
      int new_assignments = 0;
      do
      {
         /* The rule list does not contain a list variable, so there is no
          * match if the host list has a different length. */
         if(label.length != 3) break;
         HostListItem *item = label.list->first;
         /* Matching rule atom 1. */
         if(item->atom.type != 's') break;
         else if(strcmp(item->atom.str, "Node") != 0) break;
         item = item->next;

         /* Matching rule atom 2. */
         int result = -1;
         /* Matching integer variable 0. */
         if(item->atom.type != 'i') break;
         result = addIntegerAssignment(morphism, 0, item->atom.num);
         if(result >= 0)
         {
            new_assignments += result;
         }
         else break;
         item = item->next;

         /* Matching rule atom 3. */
         /* Matching integer variable 1. */
         if(item->atom.type != 'i') break;
         result = addIntegerAssignment(morphism, 1, item->atom.num);
         if(result >= 0)
         {
            new_assignments += result;
         }
         else break;
         match = true;
      } while(false);

      if(match)
      {
         addNodeMap(morphism, 0, host_node->index, new_assignments);
         host_node->matched = true;
         /* Update global booleans representing the node's predicates. */
         evaluatePredicaterandom_d_graph_3(morphism);
         bool next_match_result = false;
         if(evaluateCondition()) next_match_result = match_n1(morphism);
         if(next_match_result) return true;
         else
         {
            /* Reset the boolean variables in the predicates of this node. */
            random_d_graph_b3 = false;
            removeNodeMap(morphism, 0);
            host_node->matched = false;
         }
      }
      else removeAssignments(morphism, new_assignments);
   }
   return false;
}

static bool match_n1(Morphism *morphism)
{
   int host_index;
   for(host_index = 0; host_index < random_d_graph_host->nodes.size; host_index++)
   {
      Node *host_node = getNode(random_d_graph_host, host_index);
      if(host_node == NULL || host_node->index == -1) continue;
      if(host_node->matched) continue;
      if(host_node->label.mark != 0) continue;
      if(host_node->indegree < 0 || host_node->outdegree < 0 ||
         ((host_node->outdegree + host_node->indegree - 0 - 0 - 0) < 0)) continue;

      HostLabel label = host_node->label;
      bool match = false;
      /* Label Matching */
      int new_assignments = 0;
      do
      {
         /* The rule list does not contain a list variable, so there is no
          * match if the host list has a different length. */
         if(label.length != 2) break;
         HostListItem *item = label.list->first;
         /* Matching rule atom 1. */
         if(item->atom.type != 's') break;
         else if(strcmp(item->atom.str, "Input") != 0) break;
         item = item->next;

         /* Matching rule atom 2. */
         int result = -1;
         /* Matching integer variable 2. */
         if(item->atom.type != 'i') break;
         result = addIntegerAssignment(morphism, 2, item->atom.num);
         if(result >= 0)
         {
            new_assignments += result;
         }
         else break;
         match = true;
      } while(false);

      if(match)
      {
         addNodeMap(morphism, 1, host_node->index, new_assignments);
         host_node->matched = true;
         /* Update global booleans representing the node's predicates. */
         evaluatePredicaterandom_d_graph_3(morphism);
         if(evaluateCondition())
         {
            /* All items matched! */
            return true;
         }
         else
         {
            /* Reset the boolean variables in the predicates of this node. */
            random_d_graph_b3 = false;
            removeNodeMap(morphism, 1);
            host_node->matched = false;
         }
      }
      else removeAssignments(morphism, new_assignments);
   }
   return false;
}

void applyrandom_d_graph_add_input(Morphism *morphism, bool record_changes)
{
   int host_edge_index;
   int source, target;
   int edge_array_size0 = random_d_graph_host->edges.size;
   source = lookupNode(morphism, 0);
   target = lookupNode(morphism, 1);
   HostLabel label;
   int list_var_length0 = 0;
   int list_length0 = list_var_length0 + 2;
   HostAtom array0[list_length0];
   int index0 = 0;

   array0[index0].type = 's';
   array0[index0++].str = "H";
   array0[index0].type = 'i';
   array0[index0++].num = 0;
   if(list_length0 > 0)
   {
      HostList *list0 = makeHostList(array0, list_length0, false);
      label = makeHostLabel(4, list_length0, list0);
   }
   else label = makeEmptyLabel(4);

   host_edge_index = addEdge(random_d_graph_host, label, source, target);
   /* If the edge array size has not increased after the edge addition, then
      the edge was added to a hole in the array. */
   if(record_changes)
      pushAddedEdge(host_edge_index, edge_array_size0 == random_d_graph_host->edges.size);
   int edge_array_size1 = random_d_graph_host->edges.size;
   source = lookupNode(morphism, 0);
   target = lookupNode(morphism, 1);
   int list_var_length1 = 0;
   int list_length1 = list_var_length1 + 2;
   HostAtom array1[list_length1];
   int index1 = 0;

   array1[index1].type = 's';
   array1[index1++].str = "T";
   array1[index1].type = 'i';
   array1[index1++].num = 0;
   if(list_length1 > 0)
   {
      HostList *list1 = makeHostList(array1, list_length1, false);
      label = makeHostLabel(4, list_length1, list1);
   }
   else label = makeEmptyLabel(4);

   host_edge_index = addEdge(random_d_graph_host, label, source, target);
   /* If the edge array size has not increased after the edge addition, then
      the edge was added to a hole in the array. */
   if(record_changes)
      pushAddedEdge(host_edge_index, edge_array_size1 == random_d_graph_host->edges.size);
   /* Reset the morphism. */
   initialiseMorphism(morphism, random_d_graph_host);
}

static bool fillpot_n0(MorphismPot *pot, Morphism *morphism);
static bool fillpot_n1(MorphismPot *pot, Morphism *morphism);

bool fillpotrandom_d_graph_add_input(MorphismPot *pot, Morphism *morphism)
{
   if(2 > random_d_graph_host->number_of_nodes || 0 > random_d_graph_host->number_of_edges) return false;
   int oldPotsize = potSize(pot);
   morphism->weight = 1.000000;
   fillpot_n0(pot, morphism);
   if(potSize(pot) > oldPotsize){
      initialiseMorphism(morphism, random_d_graph_host);
      return true;
   }
   else
   {
      initialiseMorphism(morphism, random_d_graph_host);
      return false;
   }
}

static bool fillpot_n0(MorphismPot *pot, Morphism *morphism)
{
   int host_index;
   for(host_index = 0; host_index < random_d_graph_host->nodes.size; host_index++)
   {
      Node *host_node = getNode(random_d_graph_host, host_index);
      if(host_node == NULL || host_node->index == -1) continue;
      if(host_node->matched) continue;
      if(host_node->label.mark != 0) continue;
      if(host_node->indegree < 0 || host_node->outdegree < 0 ||
         ((host_node->outdegree + host_node->indegree - 0 - 0 - 0) < 0)) continue;

      HostLabel label = host_node->label;
      bool match = false;
      /* Label Matching */
      int new_assignments = 0;
      do
      {
         /* The rule list does not contain a list variable, so there is no
          * match if the host list has a different length. */
         if(label.length != 3) break;
         HostListItem *item = label.list->first;
         /* Matching rule atom 1. */
         if(item->atom.type != 's') break;
         else if(strcmp(item->atom.str, "Node") != 0) break;
         item = item->next;

         /* Matching rule atom 2. */
         int result = -1;
         /* Matching integer variable 0. */
         if(item->atom.type != 'i') break;
         result = addIntegerAssignment(morphism, 0, item->atom.num);
         if(result >= 0)
         {
            new_assignments += result;
         }
         else break;
         item = item->next;

         /* Matching rule atom 3. */
         /* Matching integer variable 1. */
         if(item->atom.type != 'i') break;
         result = addIntegerAssignment(morphism, 1, item->atom.num);
         if(result >= 0)
         {
            new_assignments += result;
         }
         else break;
         match = true;
      } while(false);

      if(match)
      {
         addNodeMap(morphism, 0, host_node->index, new_assignments);
         host_node->matched = true;
         /* Update global booleans representing the node's predicates. */
         evaluatePredicaterandom_d_graph_3(morphism);
         bool next_match_result = false;
         if(evaluateCondition()) next_match_result = fillpot_n1(pot, morphism);
         if(next_match_result) return true;
         else
         {
            /* Reset the boolean variables in the predicates of this node. */
            random_d_graph_b3 = false;
            removeNodeMap(morphism, 0);
            host_node->matched = false;
         }
      }
      else removeAssignments(morphism, new_assignments);
   }
   return false;
}

static bool fillpot_n1(MorphismPot *pot, Morphism *morphism)
{
   int host_index;
   for(host_index = 0; host_index < random_d_graph_host->nodes.size; host_index++)
   {
      Node *host_node = getNode(random_d_graph_host, host_index);
      if(host_node == NULL || host_node->index == -1) continue;
      if(host_node->matched) continue;
      if(host_node->label.mark != 0) continue;
      if(host_node->indegree < 0 || host_node->outdegree < 0 ||
         ((host_node->outdegree + host_node->indegree - 0 - 0 - 0) < 0)) continue;

      HostLabel label = host_node->label;
      bool match = false;
      /* Label Matching */
      int new_assignments = 0;
      do
      {
         /* The rule list does not contain a list variable, so there is no
          * match if the host list has a different length. */
         if(label.length != 2) break;
         HostListItem *item = label.list->first;
         /* Matching rule atom 1. */
         if(item->atom.type != 's') break;
         else if(strcmp(item->atom.str, "Input") != 0) break;
         item = item->next;

         /* Matching rule atom 2. */
         int result = -1;
         /* Matching integer variable 2. */
         if(item->atom.type != 'i') break;
         result = addIntegerAssignment(morphism, 2, item->atom.num);
         if(result >= 0)
         {
            new_assignments += result;
         }
         else break;
         match = true;
      } while(false);

      if(match)
      {
         addNodeMap(morphism, 1, host_node->index, new_assignments);
         host_node->matched = true;
         /* Update global booleans representing the node's predicates. */
         evaluatePredicaterandom_d_graph_3(morphism);
         if(evaluateCondition())
         {
            /* All items matched! */
            putMorphism(pot, morphism, "random_d_graph_add_input", random_d_graph_host);
            /* Reset the boolean variables in the predicates of this node. */
            random_d_graph_b3 = false;
            removeNodeMap(morphism, 1);
            host_node->matched = false;
            return false;
         }
         else
         {
            /* Reset the boolean variables in the predicates of this node. */
            random_d_graph_b3 = false;
            removeNodeMap(morphism, 1);
            host_node->matched = false;
         }
      }
      else removeAssignments(morphism, new_assignments);
   }
   return false;
}

