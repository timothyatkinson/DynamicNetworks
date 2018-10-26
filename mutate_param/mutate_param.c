#include <time.h>
#include "common.h"
#include "debug.h"
#include "graph.h"
#include "graphStacks.h"
#include "parser.h"
#include "morphism.h"

#include "mutate_param_pickParam.h"
Morphism *M_mutate_param_pickParam = NULL;
#include "mutate_param_param1.h"
Morphism *M_mutate_param_param1 = NULL;
#include "mutate_param_param2.h"
Morphism *M_mutate_param_param2 = NULL;
#include "mutate_param_param3.h"
Morphism *M_mutate_param_param3 = NULL;
#include "mutate_param_param4.h"
Morphism *M_mutate_param_param4 = NULL;

static void mutate_param_freeMorphisms(void)
{
   freeMorphism(M_mutate_param_pickParam);
   freeMorphism(M_mutate_param_param1);
   freeMorphism(M_mutate_param_param2);
   freeMorphism(M_mutate_param_param3);
   freeMorphism(M_mutate_param_param4);
}

Graph* mutate_param_host = NULL;
int* mutate_param_node_map = NULL;
MorphismPot* mutate_param_pot = NULL;

static void mutate_param_garbageCollect(void)
{
   mutate_param_freeMorphisms();
   freePot(mutate_param_pot);
}

bool mutate_param_success = true;

int mutate_param_execute(Graph* host_graph)
{
   mutate_param_host = host_graph;
   mutate_param_success = true;
   mutate_param_pot = makeMorphismPot();
   emptyPot(mutate_param_pot);
   M_mutate_param_pickParam = makeMorphism(1, 0, 1);
   M_mutate_param_param1 = makeMorphism(1, 0, 2);
   M_mutate_param_param2 = makeMorphism(1, 0, 2);
   M_mutate_param_param3 = makeMorphism(1, 0, 2);
   M_mutate_param_param4 = makeMorphism(1, 0, 2);

   /* Rule Call */
   emptyPot(mutate_param_pot);
   fillpotmutate_param_pickParam(mutate_param_pot, M_mutate_param_pickParam);
   if(potSize(mutate_param_pot) > 0){
      MorphismHolder *holder = drawFromPot(mutate_param_pot);
      duplicateMorphism(holder->morphism, M_mutate_param_pickParam, mutate_param_host);
      freeMorphism(holder->morphism);
      free(holder);
      applymutate_param_pickParam(M_mutate_param_pickParam, false);
      mutate_param_success = true;
   }
   else
   {
      printf("No output graph: rule mutate_param_pickParam not applicable.\n");
      mutate_param_garbageCollect();
      return 0;
   }
   emptyPot(mutate_param_pot);
   /* Rule Set Call */
   do
   {
   bool valid[4];
   double weight[4];
   double totalWeight = 0.0;
   bool someValid = false;
   valid[0] = false;
   weight[0] = 1.000000;
   if(matchmutate_param_param1(M_mutate_param_param1)){
      valid[0] = true;
      totalWeight = totalWeight + weight[0];
      someValid = true;
   }
   initialiseMorphism(M_mutate_param_param1, mutate_param_host);
   valid[1] = false;
   weight[1] = 1.000000;
   if(matchmutate_param_param2(M_mutate_param_param2)){
      valid[1] = true;
      totalWeight = totalWeight + weight[1];
      someValid = true;
   }
   initialiseMorphism(M_mutate_param_param2, mutate_param_host);
   valid[2] = false;
   weight[2] = 1.000000;
   if(matchmutate_param_param3(M_mutate_param_param3)){
      valid[2] = true;
      totalWeight = totalWeight + weight[2];
      someValid = true;
   }
   initialiseMorphism(M_mutate_param_param3, mutate_param_host);
   valid[3] = false;
   weight[3] = 1.000000;
   if(matchmutate_param_param4(M_mutate_param_param4)){
      valid[3] = true;
      totalWeight = totalWeight + weight[3];
      someValid = true;
   }
   initialiseMorphism(M_mutate_param_param4, mutate_param_host);
   if (someValid){
      double r = ((double)rand() / (double)RAND_MAX);
      r = r * totalWeight;
      double sum = 0.0;
      if(valid[0]){
         sum = sum + weight[0];
         if(r <= sum){
            emptyPot(mutate_param_pot);
            fillpotmutate_param_param1(mutate_param_pot, M_mutate_param_param1);
            if(potSize(mutate_param_pot) > 0){
               MorphismHolder *holder = drawFromPot(mutate_param_pot);
               duplicateMorphism(holder->morphism, M_mutate_param_param1, mutate_param_host);
               freeMorphism(holder->morphism);
               free(holder);
               applymutate_param_param1(M_mutate_param_param1, false);
               mutate_param_success = true;
               break;
            }
            emptyPot(mutate_param_pot);
         }
      }
      if(valid[1]){
         sum = sum + weight[1];
         if(r <= sum && r > sum - weight[1]){
            emptyPot(mutate_param_pot);
            fillpotmutate_param_param2(mutate_param_pot, M_mutate_param_param2);
            if(potSize(mutate_param_pot) > 0){
               MorphismHolder *holder = drawFromPot(mutate_param_pot);
               duplicateMorphism(holder->morphism, M_mutate_param_param2, mutate_param_host);
               freeMorphism(holder->morphism);
               free(holder);
               applymutate_param_param2(M_mutate_param_param2, false);
               mutate_param_success = true;
               break;
            }
            emptyPot(mutate_param_pot);
         }
      }
      if(valid[2]){
         sum = sum + weight[2];
         if(r <= sum && r > sum - weight[2]){
            emptyPot(mutate_param_pot);
            fillpotmutate_param_param3(mutate_param_pot, M_mutate_param_param3);
            if(potSize(mutate_param_pot) > 0){
               MorphismHolder *holder = drawFromPot(mutate_param_pot);
               duplicateMorphism(holder->morphism, M_mutate_param_param3, mutate_param_host);
               freeMorphism(holder->morphism);
               free(holder);
               applymutate_param_param3(M_mutate_param_param3, false);
               mutate_param_success = true;
               break;
            }
            emptyPot(mutate_param_pot);
         }
      }
      if(valid[3]){
         sum = sum + weight[3];
         if(r <= sum && r > sum - weight[3]){
            emptyPot(mutate_param_pot);
            fillpotmutate_param_param4(mutate_param_pot, M_mutate_param_param4);
            if(potSize(mutate_param_pot) > 0){
               MorphismHolder *holder = drawFromPot(mutate_param_pot);
               duplicateMorphism(holder->morphism, M_mutate_param_param4, mutate_param_host);
               freeMorphism(holder->morphism);
               free(holder);
               applymutate_param_param4(M_mutate_param_param4, false);
               mutate_param_success = true;
               break;
            }
            emptyPot(mutate_param_pot);
         }
      }
   } else {
   printf("No output graph: Fail statement invoked\n");
   mutate_param_garbageCollect();
   return 0;
   }
   } while(false);
   mutate_param_garbageCollect();
   return 0;
}

