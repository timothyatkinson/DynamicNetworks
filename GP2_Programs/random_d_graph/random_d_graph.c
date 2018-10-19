#include <time.h>
#include "common.h"
#include "debug.h"
#include "graph.h"
#include "graphStacks.h"
#include "parser.h"
#include "morphism.h"
#include "util.h"

#include "random_d_graph_add_node.h"
Morphism *M_random_d_graph_add_node = NULL;
#include "random_d_graph_add_loop.h"
Morphism *M_random_d_graph_add_loop = NULL;
#include "random_d_graph_add_edge.h"
Morphism *M_random_d_graph_add_edge = NULL;
#include "random_d_graph_add_input.h"
Morphism *M_random_d_graph_add_input = NULL;
#include "random_d_graph_pick_loop.h"
Morphism *M_random_d_graph_pick_loop = NULL;
#include "random_d_graph_keep_loop.h"
Morphism *M_random_d_graph_keep_loop = NULL;
#include "random_d_graph_delete_loop.h"
Morphism *M_random_d_graph_delete_loop = NULL;
#include "random_d_graph_pick_edge.h"
Morphism *M_random_d_graph_pick_edge = NULL;
#include "random_d_graph_keep_edge.h"
Morphism *M_random_d_graph_keep_edge = NULL;
#include "random_d_graph_delete_edge.h"
Morphism *M_random_d_graph_delete_edge = NULL;
#include "random_d_graph_remove_node_counter.h"
Morphism *M_random_d_graph_remove_node_counter = NULL;

static void random_d_graph_freeMorphisms(void)
{
   freeMorphism(M_random_d_graph_add_node);
   freeMorphism(M_random_d_graph_add_loop);
   freeMorphism(M_random_d_graph_add_edge);
   freeMorphism(M_random_d_graph_add_input);
   freeMorphism(M_random_d_graph_pick_loop);
   freeMorphism(M_random_d_graph_keep_loop);
   freeMorphism(M_random_d_graph_delete_loop);
   freeMorphism(M_random_d_graph_pick_edge);
   freeMorphism(M_random_d_graph_keep_edge);
   freeMorphism(M_random_d_graph_delete_edge);
   freeMorphism(M_random_d_graph_remove_node_counter);
}

Graph* random_d_graph_host = NULL;
int* random_d_graph_node_map = NULL;
MorphismPot* random_d_graph_pot = NULL;

static void random_d_graph_garbageCollect(void)
{
   random_d_graph_freeMorphisms();
   freePot(random_d_graph_pot);
}

bool random_d_graph_success = true;


Graph* random_d_graph_execute(int inputs, int n, double p)
{
   random_d_graph_host = build_empty_host_graph();


   for(int i = 0; i < inputs; i++){
     HostAtom array[2];
     HostLabel label;
     array[0].type = 's';
     array[0].str = "Input";
     array[1].type = 'i';
     array[1].num = i;
     HostList *list = makeHostList(array, 2, false);
     label = makeHostLabel(0, 2, list);
     addNode(random_d_graph_host, 0, label);
   }

   HostAtom array[2];
   HostLabel label;
   array[0].type = 's';
   array[0].str = "Nodes";
   array[1].type = 'i';
   array[1].num = n;
   HostList *list = makeHostList(array, 2, false);
   label = makeHostLabel(0, 2, list);
   addNode(random_d_graph_host, 1, label);

   random_d_graph_success = true;
   random_d_graph_pot = makeMorphismPot();
   emptyPot(random_d_graph_pot);
   M_random_d_graph_add_node = makeMorphism(1, 0, 1);
   M_random_d_graph_add_loop = makeMorphism(1, 0, 2);
   M_random_d_graph_add_edge = makeMorphism(2, 0, 4);
   M_random_d_graph_add_input = makeMorphism(2, 0, 3);
   M_random_d_graph_pick_loop = makeMorphism(1, 1, 2);
   M_random_d_graph_keep_loop = makeMorphism(1, 1, 2);
   M_random_d_graph_delete_loop = makeMorphism(1, 1, 2);
   M_random_d_graph_pick_edge = makeMorphism(2, 1, 3);
   M_random_d_graph_keep_edge = makeMorphism(2, 1, 3);
   M_random_d_graph_delete_edge = makeMorphism(2, 1, 3);
   M_random_d_graph_remove_node_counter = makeMorphism(1, 0, 0);

   /* Loop Statement */
   while(random_d_graph_success)
   {
      /* Rule Call */
      if(matchrandom_d_graph_add_node(M_random_d_graph_add_node))
      {
         applyrandom_d_graph_add_node(M_random_d_graph_add_node, false);
         random_d_graph_success = true;
      }
      else
      {
         random_d_graph_success = false;
      }
   }
   random_d_graph_success = true;
   /* Loop Statement */
   while(random_d_graph_success)
   {
      /* Rule Call */
      if(matchrandom_d_graph_add_loop(M_random_d_graph_add_loop))
      {
         applyrandom_d_graph_add_loop(M_random_d_graph_add_loop, false);
         random_d_graph_success = true;
      }
      else
      {
         random_d_graph_success = false;
      }
   }
   random_d_graph_success = true;
   /* Loop Statement */
   while(random_d_graph_success)
   {
      /* Rule Call */
      if(matchrandom_d_graph_add_edge(M_random_d_graph_add_edge))
      {
         applyrandom_d_graph_add_edge(M_random_d_graph_add_edge, false);
         random_d_graph_success = true;
      }
      else
      {
         random_d_graph_success = false;
      }
   }
   random_d_graph_success = true;
   /* Loop Statement */
   while(random_d_graph_success)
   {
      /* Rule Call */
      if(matchrandom_d_graph_add_input(M_random_d_graph_add_input))
      {
         applyrandom_d_graph_add_input(M_random_d_graph_add_input, false);
         random_d_graph_success = true;
      }
      else
      {
         random_d_graph_success = false;
      }
   }
   random_d_graph_success = true;
   /* Loop Statement */
   int restore_point0 = graph_change_stack == NULL ? 0 : topOfGraphChangeStack();
   while(random_d_graph_success)
   {
      /* Rule Call */
      if(matchrandom_d_graph_pick_loop(M_random_d_graph_pick_loop))
      {
         applyrandom_d_graph_pick_loop(M_random_d_graph_pick_loop, true);
         random_d_graph_success = true;
      }
      else
      {
         random_d_graph_success = false;
         undoChanges(random_d_graph_host, restore_point0);
      }
      if(!random_d_graph_success) break;

      /* Rule Set Call */
      do
      {
      bool valid[2];
      double weight[2];
      double totalWeight = 0.0;
      bool someValid = false;
      valid[0] = false;
      weight[0] = p;
      if(matchrandom_d_graph_keep_loop(M_random_d_graph_keep_loop)){
         valid[0] = true;
         totalWeight = totalWeight + weight[0];
         someValid = true;
      }
      initialiseMorphism(M_random_d_graph_keep_loop, random_d_graph_host);
      valid[1] = false;
      weight[1] = 1.0 - p;
      if(matchrandom_d_graph_delete_loop(M_random_d_graph_delete_loop)){
         valid[1] = true;
         totalWeight = totalWeight + weight[1];
         someValid = true;
      }
      initialiseMorphism(M_random_d_graph_delete_loop, random_d_graph_host);
      if (someValid){
         double r = ((double)rand() / (double)RAND_MAX);
         r = r * totalWeight;
         double sum = 0.0;
         if(valid[0]){
            sum = sum + weight[0];
            if(r <= sum){
               emptyPot(random_d_graph_pot);
               fillpotrandom_d_graph_keep_loop(random_d_graph_pot, M_random_d_graph_keep_loop);
               if(potSize(random_d_graph_pot) > 0){
                  MorphismHolder *holder = drawFromPot(random_d_graph_pot);
                  duplicateMorphism(holder->morphism, M_random_d_graph_keep_loop, random_d_graph_host);
                  freeMorphism(holder->morphism);
                  free(holder);
                  applyrandom_d_graph_keep_loop(M_random_d_graph_keep_loop, true);
                  random_d_graph_success = true;
                  break;
               }
               emptyPot(random_d_graph_pot);
            }
         }
         if(valid[1]){
            sum = sum + weight[1];
            if(r <= sum && r > sum - weight[1]){
               emptyPot(random_d_graph_pot);
               fillpotrandom_d_graph_delete_loop(random_d_graph_pot, M_random_d_graph_delete_loop);
               if(potSize(random_d_graph_pot) > 0){
                  MorphismHolder *holder = drawFromPot(random_d_graph_pot);
                  duplicateMorphism(holder->morphism, M_random_d_graph_delete_loop, random_d_graph_host);
                  freeMorphism(holder->morphism);
                  free(holder);
                  applyrandom_d_graph_delete_loop(M_random_d_graph_delete_loop, true);
                  random_d_graph_success = true;
                  break;
               }
               emptyPot(random_d_graph_pot);
            }
         }
      } else {
      random_d_graph_success = false;
      undoChanges(random_d_graph_host, restore_point0);
      }
      } while(false);
      /* Graph changes from loop body may not have been used.
         Discard them so that future graph roll backs are uncorrupted. */
      if(random_d_graph_success) discardChanges(restore_point0);
   }
   random_d_graph_success = true;
   /* Loop Statement */
   int restore_point1 = graph_change_stack == NULL ? 0 : topOfGraphChangeStack();
   while(random_d_graph_success)
   {
      /* Rule Call */
      if(matchrandom_d_graph_pick_edge(M_random_d_graph_pick_edge))
      {
         applyrandom_d_graph_pick_edge(M_random_d_graph_pick_edge, true);
         random_d_graph_success = true;
      }
      else
      {
         random_d_graph_success = false;
         undoChanges(random_d_graph_host, restore_point1);
      }
      if(!random_d_graph_success) break;

      /* Rule Set Call */
      do
      {
      bool valid[2];
      double weight[2];
      double totalWeight = 0.0;
      bool someValid = false;
      valid[0] = false;
      weight[0] = p;
      if(matchrandom_d_graph_keep_edge(M_random_d_graph_keep_edge)){
         valid[0] = true;
         totalWeight = totalWeight + weight[0];
         someValid = true;
      }
      initialiseMorphism(M_random_d_graph_keep_edge, random_d_graph_host);
      valid[1] = false;
      weight[1] = 1.0 - p;
      if(matchrandom_d_graph_delete_edge(M_random_d_graph_delete_edge)){
         valid[1] = true;
         totalWeight = totalWeight + weight[1];
         someValid = true;
      }
      initialiseMorphism(M_random_d_graph_delete_edge, random_d_graph_host);
      if (someValid){
         double r = ((double)rand() / (double)RAND_MAX);
         r = r * totalWeight;
         double sum = 0.0;
         if(valid[0]){
            sum = sum + weight[0];
            if(r <= sum){
               emptyPot(random_d_graph_pot);
               fillpotrandom_d_graph_keep_edge(random_d_graph_pot, M_random_d_graph_keep_edge);
               if(potSize(random_d_graph_pot) > 0){
                  MorphismHolder *holder = drawFromPot(random_d_graph_pot);
                  duplicateMorphism(holder->morphism, M_random_d_graph_keep_edge, random_d_graph_host);
                  freeMorphism(holder->morphism);
                  free(holder);
                  applyrandom_d_graph_keep_edge(M_random_d_graph_keep_edge, true);
                  random_d_graph_success = true;
                  break;
               }
               emptyPot(random_d_graph_pot);
            }
         }
         if(valid[1]){
            sum = sum + weight[1];
            if(r <= sum && r > sum - weight[1]){
               emptyPot(random_d_graph_pot);
               fillpotrandom_d_graph_delete_edge(random_d_graph_pot, M_random_d_graph_delete_edge);
               if(potSize(random_d_graph_pot) > 0){
                  MorphismHolder *holder = drawFromPot(random_d_graph_pot);
                  duplicateMorphism(holder->morphism, M_random_d_graph_delete_edge, random_d_graph_host);
                  freeMorphism(holder->morphism);
                  free(holder);
                  applyrandom_d_graph_delete_edge(M_random_d_graph_delete_edge, true);
                  random_d_graph_success = true;
                  break;
               }
               emptyPot(random_d_graph_pot);
            }
         }
      } else {
      random_d_graph_success = false;
      undoChanges(random_d_graph_host, restore_point1);
      }
      } while(false);
      /* Graph changes from loop body may not have been used.
         Discard them so that future graph roll backs are uncorrupted. */
      if(random_d_graph_success) discardChanges(restore_point1);
   }
   random_d_graph_success = true;
   /* Rule Call */
   if(matchrandom_d_graph_remove_node_counter(M_random_d_graph_remove_node_counter))
   {
      applyrandom_d_graph_remove_node_counter(M_random_d_graph_remove_node_counter, false);
      random_d_graph_success = true;
   }
   else
   {
      printf("No output graph: rule random_d_graph_remove_node_counter not applicable.\n");
      random_d_graph_garbageCollect();
      return random_d_graph_host;
   }
   random_d_graph_garbageCollect();
   return random_d_graph_host;
}
