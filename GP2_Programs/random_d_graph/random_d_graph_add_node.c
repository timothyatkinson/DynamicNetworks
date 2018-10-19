#include "random_d_graph_add_node.h"

#include "random_d_graph.h"

bool random_d_graph_b0 = true;

static bool evaluateCondition(void)
{
   return (random_d_graph_b0);
}

static void evaluatePredicaterandom_d_graph_0(Morphism *morphism)
{
   Assignment assignment_0 = getAssignment(morphism, 0);
   /* If the variable is not yet assigned, return. */
   if(assignment_0.type == 'n') return;
   int var_0 = getIntegerValue(morphism, 0);

   if(var_0 > 0) random_d_graph_b0 = true;
   else random_d_graph_b0 = false;
}

static bool match_n0(Morphism *morphism);

bool matchrandom_d_graph_add_node(Morphism *morphism)
{
   if(1 > random_d_graph_host->number_of_nodes || 0 > random_d_graph_host->number_of_edges) return false;
   if(match_n0(morphism)) return true;
   else
   {
      initialiseMorphism(morphism, random_d_graph_host);
      return false;
   }
}

static bool match_n0(Morphism *morphism)
{
   RootNodes *nodes;
   for(nodes = getRootNodeList(random_d_graph_host); nodes != NULL; nodes = nodes->next)
   {
      Node *host_node = getNode(random_d_graph_host, nodes->index);
      if(host_node == NULL) continue;
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
         else if(strcmp(item->atom.str, "Nodes") != 0) break;
         item = item->next;

         /* Matching rule atom 2. */
         int result = -1;
         /* Matching integer variable 0. */
         if(item->atom.type != 'i') break;
         result = addIntegerAssignment(morphism, 0, item->atom.num);
         if(result >= 0)
         {
            new_assignments += result;
            /* Update global booleans for the variable's predicates. */
            evaluatePredicaterandom_d_graph_0(morphism);
            if(!evaluateCondition())
            {
               /* Reset the boolean variables in the predicates of this variable. */
               random_d_graph_b0 = true;
               break;
            }
         }
         else break;
         match = true;
      } while(false);

      if(match)
      {
         addNodeMap(morphism, 0, host_node->index, new_assignments);
         host_node->matched = true;
         /* All items matched! */
            return true;
      }
      else removeAssignments(morphism, new_assignments);
   }
   return false;
}

void applyrandom_d_graph_add_node(Morphism *morphism, bool record_changes)
{
   int var_0 = getIntegerValue(morphism, 0);
   int host_node_index = lookupNode(morphism, 0);
   HostLabel label_n0 = getNodeLabel(random_d_graph_host, host_node_index);
   HostLabel label;
   int list_var_length0 = 0;
   int list_length0 = list_var_length0 + 2;
   HostAtom array0[list_length0];
   int index0 = 0;

   array0[index0].type = 's';
   array0[index0++].str = "Nodes";
   array0[index0].type = 'i';
   array0[index0++].num = var_0 - 1;
   if(list_length0 > 0)
   {
      HostList *list0 = makeHostList(array0, list_length0, false);
      label = makeHostLabel(0, list_length0, list0);
   }
   else label = makeEmptyLabel(0);

   if(equalHostLabels(label_n0, label)) removeHostList(label.list);
   else
   {
      if(record_changes) pushRelabelledNode(host_node_index, label_n0);
      relabelNode(random_d_graph_host, host_node_index, label);
   }
   int node_array_size1 = random_d_graph_host->nodes.size;
   int list_var_length1 = 0;
   int list_length1 = list_var_length1 + 3;
   HostAtom array1[list_length1];
   int index1 = 0;

   array1[index1].type = 's';
   array1[index1++].str = "Node";
   array1[index1].type = 'i';
   array1[index1++].num = 0;
   array1[index1].type = 'i';
   array1[index1++].num = -1000;
   if(list_length1 > 0)
   {
      HostList *list1 = makeHostList(array1, list_length1, false);
      label = makeHostLabel(0, list_length1, list1);
   }
   else label = makeEmptyLabel(0);

   host_node_index = addNode(random_d_graph_host, 0, label);
   /* If the node array size has not increased after the node addition, then
      the node was added to a hole in the array. */
   if(record_changes)
      pushAddedNode(host_node_index, node_array_size1 == random_d_graph_host->nodes.size);
   /* Reset the morphism. */
   initialiseMorphism(morphism, random_d_graph_host);
}

static bool fillpot_n0(MorphismPot *pot, Morphism *morphism);

bool fillpotrandom_d_graph_add_node(MorphismPot *pot, Morphism *morphism)
{
   if(1 > random_d_graph_host->number_of_nodes || 0 > random_d_graph_host->number_of_edges) return false;
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
   RootNodes *nodes;
   for(nodes = getRootNodeList(random_d_graph_host); nodes != NULL; nodes = nodes->next)
   {
      Node *host_node = getNode(random_d_graph_host, nodes->index);
      if(host_node == NULL) continue;
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
         else if(strcmp(item->atom.str, "Nodes") != 0) break;
         item = item->next;

         /* Matching rule atom 2. */
         int result = -1;
         /* Matching integer variable 0. */
         if(item->atom.type != 'i') break;
         result = addIntegerAssignment(morphism, 0, item->atom.num);
         if(result >= 0)
         {
            new_assignments += result;
            /* Update global booleans for the variable's predicates. */
            evaluatePredicaterandom_d_graph_0(morphism);
            if(!evaluateCondition())
            {
               /* Reset the boolean variables in the predicates of this variable. */
               random_d_graph_b0 = true;
               break;
            }
         }
         else break;
         match = true;
      } while(false);

      if(match)
      {
         addNodeMap(morphism, 0, host_node->index, new_assignments);
         host_node->matched = true;
         /* All items matched! */
            putMorphism(pot, morphism, "random_d_graph_add_node", random_d_graph_host);
            removeNodeMap(morphism, 0);
            host_node->matched = false;
      }
      else removeAssignments(morphism, new_assignments);
   }
   return false;
}

