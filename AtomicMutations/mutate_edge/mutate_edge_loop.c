#include "mutate_edge_loop.h"

#include "mutate_edge.h"

static bool match_n0(Morphism *morphism);
static bool match_e0(Morphism *morphism);

bool matchmutate_edge_loop(Morphism *morphism)
{
   if(1 > mutate_edge_host->number_of_nodes || 1 > mutate_edge_host->number_of_edges) return false;
   bool match = match_n0(morphism);
   initialiseMorphism(morphism, mutate_edge_host);
   return match;
}

static bool match_n0(Morphism *morphism)
{
   RootNodes *nodes;
   for(nodes = getRootNodeList(mutate_edge_host); nodes != NULL; nodes = nodes->next)
   {
      Node *host_node = getNode(mutate_edge_host, nodes->index);
      if(host_node == NULL) continue;
      if(host_node->matched) continue;
      if(host_node->label.mark != 0) continue;
      if(host_node->indegree < 1 || host_node->outdegree < 1 ||
         ((host_node->outdegree + host_node->indegree - 1 - 1 - 0) < 0)) continue;

      HostLabel label = host_node->label;
      bool match = false;
      /* Label Matching */
      int new_assignments = 0;
      /* Match list variable 0 against the whole host list. */
      int result = -1;
      if(label.length == 1)
      {
         if(label.list->first->atom.type == 'i')
            result = addIntegerAssignment(morphism, 0, label.list->first->atom.num);
         else result = addStringAssignment(morphism, 0, label.list->first->atom.str);
      }
      else result = addListAssignment(morphism, 0, label.list);
      if(result >= 0)
      {
         new_assignments += result;
         match = true;
      }
      if(match)
      {
         addNodeMap(morphism, 0, host_node->index, new_assignments);
         host_node->matched = true;
         if(match_e0(morphism)) return true;
         else
         {
         removeNodeMap(morphism, 0);
         host_node->matched = false;
         }
      }
      else removeAssignments(morphism, new_assignments);
   }
   return false;
}

static bool match_e0(Morphism *morphism)
{
   /* Matching a loop. */
   int node_index = lookupNode(morphism, 0);
   if(node_index < 0) return false;
   Node *host_node = getNode(mutate_edge_host, node_index);

   int counter;
   for(counter = 0; counter < host_node->out_edges.size + 2; counter++)
   {
      Edge *host_edge = getNthOutEdge(mutate_edge_host, host_node, counter);
      if(host_edge == NULL) continue;
      if(host_edge->matched) continue;
      if(host_edge->source != host_edge->target) continue;
      if(host_edge->label.mark != 3) continue;

      HostLabel label = host_edge->label;
      bool match = false;
      /* Label Matching */
      int new_assignments = 0;
      /* Match list variable 1 against the whole host list. */
      int result = -1;
      if(label.length == 1)
      {
         if(label.list->first->atom.type == 'i')
            result = addIntegerAssignment(morphism, 1, label.list->first->atom.num);
         else result = addStringAssignment(morphism, 1, label.list->first->atom.str);
      }
      else result = addListAssignment(morphism, 1, label.list);
      if(result >= 0)
      {
         new_assignments += result;
         match = true;
      }
      if(match)
      {
         addEdgeMap(morphism, 0, host_edge->index, new_assignments);
         host_edge->matched = true;
      /* All items matched! */
            return true;
      }
      else removeAssignments(morphism, new_assignments);
   }
   return false;
}

static bool fillpot_n0(MorphismPot *pot, Morphism *morphism);
static bool fillpot_e0(MorphismPot *pot, Morphism *morphism);

bool fillpotmutate_edge_loop(MorphismPot *pot, Morphism *morphism)
{
   if(1 > mutate_edge_host->number_of_nodes || 1 > mutate_edge_host->number_of_edges) return false;
   int oldPotsize = potSize(pot);
   morphism->weight = 1.000000;
   fillpot_n0(pot, morphism);
   if(potSize(pot) > oldPotsize){
      initialiseMorphism(morphism, mutate_edge_host);
      return true;
   }
   else
   {
      initialiseMorphism(morphism, mutate_edge_host);
      return false;
   }
}

static bool fillpot_n0(MorphismPot *pot, Morphism *morphism)
{
   RootNodes *nodes;
   for(nodes = getRootNodeList(mutate_edge_host); nodes != NULL; nodes = nodes->next)
   {
      Node *host_node = getNode(mutate_edge_host, nodes->index);
      if(host_node == NULL) continue;
      if(host_node->matched) continue;
      if(host_node->label.mark != 0) continue;
      if(host_node->indegree < 1 || host_node->outdegree < 1 ||
         ((host_node->outdegree + host_node->indegree - 1 - 1 - 0) < 0)) continue;

      HostLabel label = host_node->label;
      bool match = false;
      /* Label Matching */
      int new_assignments = 0;
      /* Match list variable 0 against the whole host list. */
      int result = -1;
      if(label.length == 1)
      {
         if(label.list->first->atom.type == 'i')
            result = addIntegerAssignment(morphism, 0, label.list->first->atom.num);
         else result = addStringAssignment(morphism, 0, label.list->first->atom.str);
      }
      else result = addListAssignment(morphism, 0, label.list);
      if(result >= 0)
      {
         new_assignments += result;
         match = true;
      }
      if(match)
      {
         addNodeMap(morphism, 0, host_node->index, new_assignments);
         host_node->matched = true;
         if(fillpot_e0(pot, morphism)) return true;
         else
         {
         removeNodeMap(morphism, 0);
         host_node->matched = false;
         }
      }
      else removeAssignments(morphism, new_assignments);
   }
   return false;
}

static bool fillpot_e0(MorphismPot *pot, Morphism *morphism)
{
   /* Matching a loop. */
   int node_index = lookupNode(morphism, 0);
   if(node_index < 0) return false;
   Node *host_node = getNode(mutate_edge_host, node_index);

   int counter;
   for(counter = 0; counter < host_node->out_edges.size + 2; counter++)
   {
      Edge *host_edge = getNthOutEdge(mutate_edge_host, host_node, counter);
      if(host_edge == NULL) continue;
      if(host_edge->matched) continue;
      if(host_edge->source != host_edge->target) continue;
      if(host_edge->label.mark != 3) continue;

      HostLabel label = host_edge->label;
      bool match = false;
      /* Label Matching */
      int new_assignments = 0;
      /* Match list variable 1 against the whole host list. */
      int result = -1;
      if(label.length == 1)
      {
         if(label.list->first->atom.type == 'i')
            result = addIntegerAssignment(morphism, 1, label.list->first->atom.num);
         else result = addStringAssignment(morphism, 1, label.list->first->atom.str);
      }
      else result = addListAssignment(morphism, 1, label.list);
      if(result >= 0)
      {
         new_assignments += result;
         match = true;
      }
      if(match)
      {
         addEdgeMap(morphism, 0, host_edge->index, new_assignments);
         host_edge->matched = true;
      /* All items matched! */
            putMorphism(pot, morphism, "mutate_edge_loop", mutate_edge_host);
            removeEdgeMap(morphism, 0);
            host_edge->matched = false;
            return false;
      }
      else removeAssignments(morphism, new_assignments);
   }
   return false;
}

