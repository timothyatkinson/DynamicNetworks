#include "mutate_param_param4.h"

#include "mutate_param.h"

bool mutate_param_b5 = true;
bool mutate_param_b6 = true;
bool mutate_param_b7 = true;

static bool evaluateCondition(void)
{
   return ((mutate_param_b5 && mutate_param_b6) || mutate_param_b7);
}

static void evaluatePredicatemutate_param_5(Morphism *morphism)
{
   Assignment assignment_1 = getAssignment(morphism, 1);
   /* If the variable is not yet assigned, return. */
   if(assignment_1.type == 'n') return;
   int var_1 = getIntegerValue(morphism, 1);

   if(var_1 - 2 >= -1000) mutate_param_b5 = true;
   else mutate_param_b5 = false;
}

static void evaluatePredicatemutate_param_6(Morphism *morphism)
{
   Assignment assignment_0 = getAssignment(morphism, 0);
   /* If the variable is not yet assigned, return. */
   if(assignment_0.type == 'n') return;
   string var_0 = getStringValue(morphism, 0);

   int list_var_length0 = 0;
   int list_length0 = list_var_length0 + 1;
   HostAtom array0[list_length0];
   int index0 = 0;

   array0[index0].type = 's';
   array0[index0++].str = var_0;

   int list_var_length1 = 0;
   int list_length1 = list_var_length1 + 1;
   HostAtom array1[list_length1];
   int index1 = 0;

   array1[index1].type = 's';
   array1[index1++].str = "Leak_Rate";

   if(!equalHostLists(array0, array1, list_length0, list_length1)) mutate_param_b6 = true;
   else mutate_param_b6 = false;
}

static void evaluatePredicatemutate_param_7(Morphism *morphism)
{
   Assignment assignment_1 = getAssignment(morphism, 1);
   /* If the variable is not yet assigned, return. */
   if(assignment_1.type == 'n') return;
   int var_1 = getIntegerValue(morphism, 1);

   if(var_1 - 2 >= 0) mutate_param_b7 = true;
   else mutate_param_b7 = false;
}

static bool match_n0(Morphism *morphism);

bool matchmutate_param_param4(Morphism *morphism)
{
   if(1 > mutate_param_host->number_of_nodes || 0 > mutate_param_host->number_of_edges) return false;
   if(match_n0(morphism)) return true;
   else
   {
      initialiseMorphism(morphism, mutate_param_host);
      return false;
   }
}

static bool match_n0(Morphism *morphism)
{
   RootNodes *nodes;
   for(nodes = getRootNodeList(mutate_param_host); nodes != NULL; nodes = nodes->next)
   {
      Node *host_node = getNode(mutate_param_host, nodes->index);
      if(host_node == NULL) continue;
      if(host_node->matched) continue;
      if(host_node->label.mark != 1) continue;
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
         int result = -1;
         /* Matching string variable 0. */
         if(item->atom.type != 's') break;
         result = addStringAssignment(morphism, 0, item->atom.str);
         if(result >= 0)
         {
            new_assignments += result;
            /* Update global booleans for the variable's predicates. */
            evaluatePredicatemutate_param_6(morphism);
            if(!evaluateCondition())
            {
               /* Reset the boolean variables in the predicates of this variable. */
               mutate_param_b6 = true;
               break;
            }
         }
         else break;
         item = item->next;

         /* Matching rule atom 2. */
         /* Matching integer variable 1. */
         if(item->atom.type != 'i') break;
         result = addIntegerAssignment(morphism, 1, item->atom.num);
         if(result >= 0)
         {
            new_assignments += result;
            /* Update global booleans for the variable's predicates. */
            evaluatePredicatemutate_param_5(morphism);
            evaluatePredicatemutate_param_7(morphism);
            if(!evaluateCondition())
            {
               /* Reset the boolean variables in the predicates of this variable. */
               mutate_param_b5 = true;
               mutate_param_b7 = true;
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

void applymutate_param_param4(Morphism *morphism, bool record_changes)
{
   string var_0 = getStringValue(morphism, 0);
   int var_1 = getIntegerValue(morphism, 1);
   int host_node_index = lookupNode(morphism, 0);
   HostLabel label_n0 = getNodeLabel(mutate_param_host, host_node_index);
   HostLabel label;
   int list_var_length0 = 0;
   int list_length0 = list_var_length0 + 2;
   HostAtom array0[list_length0];
   int index0 = 0;

   array0[index0].type = 's';
   array0[index0++].str = var_0;
   array0[index0].type = 'i';
   array0[index0++].num = var_1 - 2;
   if(list_length0 > 0)
   {
      HostList *list0 = makeHostList(array0, list_length0, false);
      label = makeHostLabel(1, list_length0, list0);
   }
   else label = makeEmptyLabel(1);

   if(equalHostLabels(label_n0, label)) removeHostList(label.list);
   else
   {
      if(record_changes) pushRelabelledNode(host_node_index, label_n0);
      relabelNode(mutate_param_host, host_node_index, label);
   }
   host_node_index = lookupNode(morphism, 0);
   if(record_changes) pushChangedRootNode(host_node_index);
   changeRoot(mutate_param_host, host_node_index);
   /* Reset the morphism. */
   initialiseMorphism(morphism, mutate_param_host);
}

static bool fillpot_n0(MorphismPot *pot, Morphism *morphism);

bool fillpotmutate_param_param4(MorphismPot *pot, Morphism *morphism)
{
   if(1 > mutate_param_host->number_of_nodes || 0 > mutate_param_host->number_of_edges) return false;
   int oldPotsize = potSize(pot);
   morphism->weight = 1.000000;
   fillpot_n0(pot, morphism);
   if(potSize(pot) > oldPotsize){
      initialiseMorphism(morphism, mutate_param_host);
      return true;
   }
   else
   {
      initialiseMorphism(morphism, mutate_param_host);
      return false;
   }
}

static bool fillpot_n0(MorphismPot *pot, Morphism *morphism)
{
   RootNodes *nodes;
   for(nodes = getRootNodeList(mutate_param_host); nodes != NULL; nodes = nodes->next)
   {
      Node *host_node = getNode(mutate_param_host, nodes->index);
      if(host_node == NULL) continue;
      if(host_node->matched) continue;
      if(host_node->label.mark != 1) continue;
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
         int result = -1;
         /* Matching string variable 0. */
         if(item->atom.type != 's') break;
         result = addStringAssignment(morphism, 0, item->atom.str);
         if(result >= 0)
         {
            new_assignments += result;
            /* Update global booleans for the variable's predicates. */
            evaluatePredicatemutate_param_6(morphism);
            if(!evaluateCondition())
            {
               /* Reset the boolean variables in the predicates of this variable. */
               mutate_param_b6 = true;
               break;
            }
         }
         else break;
         item = item->next;

         /* Matching rule atom 2. */
         /* Matching integer variable 1. */
         if(item->atom.type != 'i') break;
         result = addIntegerAssignment(morphism, 1, item->atom.num);
         if(result >= 0)
         {
            new_assignments += result;
            /* Update global booleans for the variable's predicates. */
            evaluatePredicatemutate_param_5(morphism);
            evaluatePredicatemutate_param_7(morphism);
            if(!evaluateCondition())
            {
               /* Reset the boolean variables in the predicates of this variable. */
               mutate_param_b5 = true;
               mutate_param_b7 = true;
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
            putMorphism(pot, morphism, "mutate_param_param4", mutate_param_host);
            removeNodeMap(morphism, 0);
            host_node->matched = false;
      }
      else removeAssignments(morphism, new_assignments);
   }
   return false;
}

