#include <time.h>
#include "common.h"
#include "debug.h"
#include "graph.h"
#include "graphStacks.h"
#include "parser.h"
#include "morphism.h"

#include "mutate_weight_pickEdge.h"
Morphism *M_mutate_weight_pickEdge = NULL;
#include "mutate_weight_weight1.h"
Morphism *M_mutate_weight_weight1 = NULL;
#include "mutate_weight_weight2.h"
Morphism *M_mutate_weight_weight2 = NULL;
#include "mutate_weight_weight3.h"
Morphism *M_mutate_weight_weight3 = NULL;
#include "mutate_weight_weight4.h"
Morphism *M_mutate_weight_weight4 = NULL;

static void mutate_weight_freeMorphisms(void)
{
   freeMorphism(M_mutate_weight_pickEdge);
   freeMorphism(M_mutate_weight_weight1);
   freeMorphism(M_mutate_weight_weight2);
   freeMorphism(M_mutate_weight_weight3);
   freeMorphism(M_mutate_weight_weight4);
}

Graph* mutate_weight_host = NULL;
int* mutate_weight_node_map = NULL;
MorphismPot* mutate_weight_pot = NULL;

static void mutate_weight_garbageCollect(void)
{
   mutate_weight_freeMorphisms();
   freePot(mutate_weight_pot);
}

bool mutate_weight_success = true;

int mutate_weight_execute(Graph* host_graph)
{
   mutate_weight_host = host_graph;
   mutate_weight_success = true;
   mutate_weight_pot = makeMorphismPot();
   emptyPot(mutate_weight_pot);
   M_mutate_weight_pickEdge = makeMorphism(2, 1, 3);
   M_mutate_weight_weight1 = makeMorphism(2, 1, 4);
   M_mutate_weight_weight2 = makeMorphism(2, 1, 4);
   M_mutate_weight_weight3 = makeMorphism(2, 1, 4);
   M_mutate_weight_weight4 = makeMorphism(2, 1, 4);

   /* Rule Call */
   emptyPot(mutate_weight_pot);
   fillpotmutate_weight_pickEdge(mutate_weight_pot, M_mutate_weight_pickEdge);
   if(potSize(mutate_weight_pot) > 0){
      MorphismHolder *holder = drawFromPot(mutate_weight_pot);
      duplicateMorphism(holder->morphism, M_mutate_weight_pickEdge, mutate_weight_host);
      freeMorphism(holder->morphism);
      free(holder);
      applymutate_weight_pickEdge(M_mutate_weight_pickEdge, false);
      mutate_weight_success = true;
   }
   else
   {
      printf("No output graph: rule mutate_weight_pickEdge not applicable.\n");
      mutate_weight_garbageCollect();
      return 0;
   }
   emptyPot(mutate_weight_pot);
   /* Rule Set Call */
   do
   {
   bool valid[4];
   double weight[4];
   double totalWeight = 0.0;
   bool someValid = false;
   valid[0] = false;
   weight[0] = 1.000000;
   if(matchmutate_weight_weight1(M_mutate_weight_weight1)){
      valid[0] = true;
      totalWeight = totalWeight + weight[0];
      someValid = true;
   }
   initialiseMorphism(M_mutate_weight_weight1, mutate_weight_host);
   valid[1] = false;
   weight[1] = 1.000000;
   if(matchmutate_weight_weight2(M_mutate_weight_weight2)){
      valid[1] = true;
      totalWeight = totalWeight + weight[1];
      someValid = true;
   }
   initialiseMorphism(M_mutate_weight_weight2, mutate_weight_host);
   valid[2] = false;
   weight[2] = 1.000000;
   if(matchmutate_weight_weight3(M_mutate_weight_weight3)){
      valid[2] = true;
      totalWeight = totalWeight + weight[2];
      someValid = true;
   }
   initialiseMorphism(M_mutate_weight_weight3, mutate_weight_host);
   valid[3] = false;
   weight[3] = 1.000000;
   if(matchmutate_weight_weight4(M_mutate_weight_weight4)){
      valid[3] = true;
      totalWeight = totalWeight + weight[3];
      someValid = true;
   }
   initialiseMorphism(M_mutate_weight_weight4, mutate_weight_host);
   if (someValid){
      double r = ((double)rand() / (double)RAND_MAX);
      r = r * totalWeight;
      double sum = 0.0;
      if(valid[0]){
         sum = sum + weight[0];
         if(r <= sum){
            emptyPot(mutate_weight_pot);
            fillpotmutate_weight_weight1(mutate_weight_pot, M_mutate_weight_weight1);
            if(potSize(mutate_weight_pot) > 0){
               MorphismHolder *holder = drawFromPot(mutate_weight_pot);
               duplicateMorphism(holder->morphism, M_mutate_weight_weight1, mutate_weight_host);
               freeMorphism(holder->morphism);
               free(holder);
               applymutate_weight_weight1(M_mutate_weight_weight1, false);
               mutate_weight_success = true;
               break;
            }
            emptyPot(mutate_weight_pot);
         }
      }
      if(valid[1]){
         sum = sum + weight[1];
         if(r <= sum && r > sum - weight[1]){
            emptyPot(mutate_weight_pot);
            fillpotmutate_weight_weight2(mutate_weight_pot, M_mutate_weight_weight2);
            if(potSize(mutate_weight_pot) > 0){
               MorphismHolder *holder = drawFromPot(mutate_weight_pot);
               duplicateMorphism(holder->morphism, M_mutate_weight_weight2, mutate_weight_host);
               freeMorphism(holder->morphism);
               free(holder);
               applymutate_weight_weight2(M_mutate_weight_weight2, false);
               mutate_weight_success = true;
               break;
            }
            emptyPot(mutate_weight_pot);
         }
      }
      if(valid[2]){
         sum = sum + weight[2];
         if(r <= sum && r > sum - weight[2]){
            emptyPot(mutate_weight_pot);
            fillpotmutate_weight_weight3(mutate_weight_pot, M_mutate_weight_weight3);
            if(potSize(mutate_weight_pot) > 0){
               MorphismHolder *holder = drawFromPot(mutate_weight_pot);
               duplicateMorphism(holder->morphism, M_mutate_weight_weight3, mutate_weight_host);
               freeMorphism(holder->morphism);
               free(holder);
               applymutate_weight_weight3(M_mutate_weight_weight3, false);
               mutate_weight_success = true;
               break;
            }
            emptyPot(mutate_weight_pot);
         }
      }
      if(valid[3]){
         sum = sum + weight[3];
         if(r <= sum && r > sum - weight[3]){
            emptyPot(mutate_weight_pot);
            fillpotmutate_weight_weight4(mutate_weight_pot, M_mutate_weight_weight4);
            if(potSize(mutate_weight_pot) > 0){
               MorphismHolder *holder = drawFromPot(mutate_weight_pot);
               duplicateMorphism(holder->morphism, M_mutate_weight_weight4, mutate_weight_host);
               freeMorphism(holder->morphism);
               free(holder);
               applymutate_weight_weight4(M_mutate_weight_weight4, false);
               mutate_weight_success = true;
               break;
            }
            emptyPot(mutate_weight_pot);
         }
      }
   } else {
   printf("No output graph: Fail statement invoked\n");
   mutate_weight_garbageCollect();
   return 0;
   }
   } while(false);
   mutate_weight_garbageCollect();
   return 0;
}

