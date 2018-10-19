#include "random_d_graph_remove_node_counter.h"

#include "random_d_graph.h"

static bool match_n0(Morphism *morphism);

bool matchrandom_d_graph_remove_node_counter(Morphism *morphism)
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
         ((host_node->outdegree + host_node->indegree - 0 - 0 - 0) != 0)) continue;

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
         if(item->atom.type != 'i') break;
         else if(item->atom.num != 0) break;
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

void applyrandom_d_graph_remove_node_counter(Morphism *morphism, bool record_changes)
{
   int count;
   for(count = 0; count < morphism->edges; count++)
   {
      if(record_changes)
      {
         Edge *edge = getEdge(random_d_graph_host, morphism->edge_map[count].host_index);
         /* A hole is created if the edge is not at the right-most index of the array. */
         pushRemovedEdge(edge->label, edge->source, edge->target, edge->index,
                         edge->index < random_d_graph_host->edges.size - 1);
      }
      removeEdge(random_d_graph_host, morphism->edge_map[count].host_index);
   }
   for(count = 0; count < morphism->nodes; count++)
   {
      if(record_changes)
      {
         Node *node = getNode(random_d_graph_host, morphism->node_map[count].host_index);
         /* A hole is created if the node is not at the right-most index of the array. */
         pushRemovedNode(node->root, node->label, node->index,
                         node->index < random_d_graph_host->nodes.size - 1);
      }
      removeNode(random_d_graph_host, morphism->node_map[count].host_index);
   }
   initialiseMorphism(morphism, NULL);
   }

static bool fillpot_n0(MorphismPot *pot, Morphism *morphism);

bool fillpotrandom_d_graph_remove_node_counter(MorphismPot *pot, Morphism *morphism)
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
         ((host_node->outdegree + host_node->indegree - 0 - 0 - 0) != 0)) continue;

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
         if(item->atom.type != 'i') break;
         else if(item->atom.num != 0) break;
         match = true;
      } while(false);

      if(match)
      {
         addNodeMap(morphism, 0, host_node->index, new_assignments);
         host_node->matched = true;
         /* All items matched! */
            putMorphism(pot, morphism, "random_d_graph_remove_node_counter", random_d_graph_host);
            removeNodeMap(morphism, 0);
            host_node->matched = false;
      }
      else removeAssignments(morphism, new_assignments);
   }
   return false;
}

