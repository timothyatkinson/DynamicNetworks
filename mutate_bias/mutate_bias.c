#include <time.h>
#include "common.h"
#include "debug.h"
#include "graph.h"
#include "graphStacks.h"
#include "parser.h"
#include "morphism.h"

#include "mutate_bias_pickNode.h"
Morphism *M_mutate_bias_pickNode = NULL;
#include "mutate_bias_bias1.h"
Morphism *M_mutate_bias_bias1 = NULL;
#include "mutate_bias_bias2.h"
Morphism *M_mutate_bias_bias2 = NULL;
#include "mutate_bias_bias3.h"
Morphism *M_mutate_bias_bias3 = NULL;
#include "mutate_bias_bias4.h"
Morphism *M_mutate_bias_bias4 = NULL;
#include "mutate_bias_bias5.h"
Morphism *M_mutate_bias_bias5 = NULL;
#include "mutate_bias_bias6.h"
Morphism *M_mutate_bias_bias6 = NULL;
#include "mutate_bias_bias7.h"
Morphism *M_mutate_bias_bias7 = NULL;
#include "mutate_bias_bias8.h"
Morphism *M_mutate_bias_bias8 = NULL;

static void mutate_bias_freeMorphisms(void)
{
   freeMorphism(M_mutate_bias_pickNode);
   freeMorphism(M_mutate_bias_bias1);
   freeMorphism(M_mutate_bias_bias2);
   freeMorphism(M_mutate_bias_bias3);
   freeMorphism(M_mutate_bias_bias4);
   freeMorphism(M_mutate_bias_bias5);
   freeMorphism(M_mutate_bias_bias6);
   freeMorphism(M_mutate_bias_bias7);
   freeMorphism(M_mutate_bias_bias8);
}

Graph* mutate_bias_host = NULL;
int* mutate_bias_node_map = NULL;
MorphismPot* mutate_bias_pot = NULL;

static void mutate_bias_garbageCollect(void)
{
   mutate_bias_freeMorphisms();
   freePot(mutate_bias_pot);
}

bool mutate_bias_success = true;

int mutate_bias_execute(Graph* host_graph)
{
   mutate_bias_host = host_graph;
   mutate_bias_success = true;
   mutate_bias_pot = makeMorphismPot();
   emptyPot(mutate_bias_pot);
   M_mutate_bias_pickNode = makeMorphism(1, 0, 1);
   M_mutate_bias_bias1 = makeMorphism(1, 0, 2);
   M_mutate_bias_bias2 = makeMorphism(1, 0, 2);
   M_mutate_bias_bias3 = makeMorphism(1, 0, 2);
   M_mutate_bias_bias4 = makeMorphism(1, 0, 2);
   M_mutate_bias_bias5 = makeMorphism(1, 0, 2);
   M_mutate_bias_bias6 = makeMorphism(1, 0, 2);
   M_mutate_bias_bias7 = makeMorphism(1, 0, 2);
   M_mutate_bias_bias8 = makeMorphism(1, 0, 2);

   /* Rule Call */
   emptyPot(mutate_bias_pot);
   fillpotmutate_bias_pickNode(mutate_bias_pot, M_mutate_bias_pickNode);
   if(potSize(mutate_bias_pot) > 0){
      MorphismHolder *holder = drawFromPot(mutate_bias_pot);
      duplicateMorphism(holder->morphism, M_mutate_bias_pickNode, mutate_bias_host);
      freeMorphism(holder->morphism);
      free(holder);
      applymutate_bias_pickNode(M_mutate_bias_pickNode, false);
      mutate_bias_success = true;
   }
   else
   {
      printf("No output graph: rule mutate_bias_pickNode not applicable.\n");
      mutate_bias_garbageCollect();
      return 0;
   }
   emptyPot(mutate_bias_pot);
   /* Rule Set Call */
   do
   {
   bool valid[8];
   double weight[8];
   double totalWeight = 0.0;
   bool someValid = false;
   valid[0] = false;
   weight[0] = 1.000000;
   if(matchmutate_bias_bias1(M_mutate_bias_bias1)){
      valid[0] = true;
      totalWeight = totalWeight + weight[0];
      someValid = true;
   }
   initialiseMorphism(M_mutate_bias_bias1, mutate_bias_host);
   valid[1] = false;
   weight[1] = 1.000000;
   if(matchmutate_bias_bias2(M_mutate_bias_bias2)){
      valid[1] = true;
      totalWeight = totalWeight + weight[1];
      someValid = true;
   }
   initialiseMorphism(M_mutate_bias_bias2, mutate_bias_host);
   valid[2] = false;
   weight[2] = 1.000000;
   if(matchmutate_bias_bias3(M_mutate_bias_bias3)){
      valid[2] = true;
      totalWeight = totalWeight + weight[2];
      someValid = true;
   }
   initialiseMorphism(M_mutate_bias_bias3, mutate_bias_host);
   valid[3] = false;
   weight[3] = 1.000000;
   if(matchmutate_bias_bias4(M_mutate_bias_bias4)){
      valid[3] = true;
      totalWeight = totalWeight + weight[3];
      someValid = true;
   }
   initialiseMorphism(M_mutate_bias_bias4, mutate_bias_host);
   valid[4] = false;
   weight[4] = 1.000000;
   if(matchmutate_bias_bias5(M_mutate_bias_bias5)){
      valid[4] = true;
      totalWeight = totalWeight + weight[4];
      someValid = true;
   }
   initialiseMorphism(M_mutate_bias_bias5, mutate_bias_host);
   valid[5] = false;
   weight[5] = 1.000000;
   if(matchmutate_bias_bias6(M_mutate_bias_bias6)){
      valid[5] = true;
      totalWeight = totalWeight + weight[5];
      someValid = true;
   }
   initialiseMorphism(M_mutate_bias_bias6, mutate_bias_host);
   valid[6] = false;
   weight[6] = 1.000000;
   if(matchmutate_bias_bias7(M_mutate_bias_bias7)){
      valid[6] = true;
      totalWeight = totalWeight + weight[6];
      someValid = true;
   }
   initialiseMorphism(M_mutate_bias_bias7, mutate_bias_host);
   valid[7] = false;
   weight[7] = 1.000000;
   if(matchmutate_bias_bias8(M_mutate_bias_bias8)){
      valid[7] = true;
      totalWeight = totalWeight + weight[7];
      someValid = true;
   }
   initialiseMorphism(M_mutate_bias_bias8, mutate_bias_host);
   if (someValid){
      double r = ((double)rand() / (double)RAND_MAX);
      r = r * totalWeight;
      double sum = 0.0;
      if(valid[0]){
         sum = sum + weight[0];
         if(r <= sum){
            emptyPot(mutate_bias_pot);
            fillpotmutate_bias_bias1(mutate_bias_pot, M_mutate_bias_bias1);
            if(potSize(mutate_bias_pot) > 0){
               MorphismHolder *holder = drawFromPot(mutate_bias_pot);
               duplicateMorphism(holder->morphism, M_mutate_bias_bias1, mutate_bias_host);
               freeMorphism(holder->morphism);
               free(holder);
               applymutate_bias_bias1(M_mutate_bias_bias1, false);
               mutate_bias_success = true;
               break;
            }
            emptyPot(mutate_bias_pot);
         }
      }
      if(valid[1]){
         sum = sum + weight[1];
         if(r <= sum && r > sum - weight[1]){
            emptyPot(mutate_bias_pot);
            fillpotmutate_bias_bias2(mutate_bias_pot, M_mutate_bias_bias2);
            if(potSize(mutate_bias_pot) > 0){
               MorphismHolder *holder = drawFromPot(mutate_bias_pot);
               duplicateMorphism(holder->morphism, M_mutate_bias_bias2, mutate_bias_host);
               freeMorphism(holder->morphism);
               free(holder);
               applymutate_bias_bias2(M_mutate_bias_bias2, false);
               mutate_bias_success = true;
               break;
            }
            emptyPot(mutate_bias_pot);
         }
      }
      if(valid[2]){
         sum = sum + weight[2];
         if(r <= sum && r > sum - weight[2]){
            emptyPot(mutate_bias_pot);
            fillpotmutate_bias_bias3(mutate_bias_pot, M_mutate_bias_bias3);
            if(potSize(mutate_bias_pot) > 0){
               MorphismHolder *holder = drawFromPot(mutate_bias_pot);
               duplicateMorphism(holder->morphism, M_mutate_bias_bias3, mutate_bias_host);
               freeMorphism(holder->morphism);
               free(holder);
               applymutate_bias_bias3(M_mutate_bias_bias3, false);
               mutate_bias_success = true;
               break;
            }
            emptyPot(mutate_bias_pot);
         }
      }
      if(valid[3]){
         sum = sum + weight[3];
         if(r <= sum && r > sum - weight[3]){
            emptyPot(mutate_bias_pot);
            fillpotmutate_bias_bias4(mutate_bias_pot, M_mutate_bias_bias4);
            if(potSize(mutate_bias_pot) > 0){
               MorphismHolder *holder = drawFromPot(mutate_bias_pot);
               duplicateMorphism(holder->morphism, M_mutate_bias_bias4, mutate_bias_host);
               freeMorphism(holder->morphism);
               free(holder);
               applymutate_bias_bias4(M_mutate_bias_bias4, false);
               mutate_bias_success = true;
               break;
            }
            emptyPot(mutate_bias_pot);
         }
      }
      if(valid[4]){
         sum = sum + weight[4];
         if(r <= sum && r > sum - weight[4]){
            emptyPot(mutate_bias_pot);
            fillpotmutate_bias_bias5(mutate_bias_pot, M_mutate_bias_bias5);
            if(potSize(mutate_bias_pot) > 0){
               MorphismHolder *holder = drawFromPot(mutate_bias_pot);
               duplicateMorphism(holder->morphism, M_mutate_bias_bias5, mutate_bias_host);
               freeMorphism(holder->morphism);
               free(holder);
               applymutate_bias_bias5(M_mutate_bias_bias5, false);
               mutate_bias_success = true;
               break;
            }
            emptyPot(mutate_bias_pot);
         }
      }
      if(valid[5]){
         sum = sum + weight[5];
         if(r <= sum && r > sum - weight[5]){
            emptyPot(mutate_bias_pot);
            fillpotmutate_bias_bias6(mutate_bias_pot, M_mutate_bias_bias6);
            if(potSize(mutate_bias_pot) > 0){
               MorphismHolder *holder = drawFromPot(mutate_bias_pot);
               duplicateMorphism(holder->morphism, M_mutate_bias_bias6, mutate_bias_host);
               freeMorphism(holder->morphism);
               free(holder);
               applymutate_bias_bias6(M_mutate_bias_bias6, false);
               mutate_bias_success = true;
               break;
            }
            emptyPot(mutate_bias_pot);
         }
      }
      if(valid[6]){
         sum = sum + weight[6];
         if(r <= sum && r > sum - weight[6]){
            emptyPot(mutate_bias_pot);
            fillpotmutate_bias_bias7(mutate_bias_pot, M_mutate_bias_bias7);
            if(potSize(mutate_bias_pot) > 0){
               MorphismHolder *holder = drawFromPot(mutate_bias_pot);
               duplicateMorphism(holder->morphism, M_mutate_bias_bias7, mutate_bias_host);
               freeMorphism(holder->morphism);
               free(holder);
               applymutate_bias_bias7(M_mutate_bias_bias7, false);
               mutate_bias_success = true;
               break;
            }
            emptyPot(mutate_bias_pot);
         }
      }
      if(valid[7]){
         sum = sum + weight[7];
         if(r <= sum && r > sum - weight[7]){
            emptyPot(mutate_bias_pot);
            fillpotmutate_bias_bias8(mutate_bias_pot, M_mutate_bias_bias8);
            if(potSize(mutate_bias_pot) > 0){
               MorphismHolder *holder = drawFromPot(mutate_bias_pot);
               duplicateMorphism(holder->morphism, M_mutate_bias_bias8, mutate_bias_host);
               freeMorphism(holder->morphism);
               free(holder);
               applymutate_bias_bias8(M_mutate_bias_bias8, false);
               mutate_bias_success = true;
               break;
            }
            emptyPot(mutate_bias_pot);
         }
      }
   } else {
   printf("No output graph: Fail statement invoked\n");
   mutate_bias_garbageCollect();
   return 0;
   }
   } while(false);
   mutate_bias_garbageCollect();
   return 0;
}

