#include <time.h>
#include "common.h"
#include "debug.h"
#include "graph.h"
#include "graphStacks.h"
#include "parser.h"
#include "morphism.h"

#include "mutate_bias_pickNode.h"
Morphism *M_mutate_bias_pickNode = NULL;
#include "mutate_bias_mutateHBias.h"
Morphism *M_mutate_bias_mutateHBias = NULL;
#include "mutate_bias_mutateTBias.h"
Morphism *M_mutate_bias_mutateTBias = NULL;

static void mutate_bias_freeMorphisms(void)
{
   freeMorphism(M_mutate_bias_pickNode);
   freeMorphism(M_mutate_bias_mutateHBias);
   freeMorphism(M_mutate_bias_mutateTBias);
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
   M_mutate_bias_mutateHBias = makeMorphism(1, 0, 2);
   M_mutate_bias_mutateTBias = makeMorphism(1, 0, 2);

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
   bool valid[2];
   double weight[2];
   double totalWeight = 0.0;
   bool someValid = false;
   valid[0] = false;
   weight[0] = 1.000000;
   if(matchmutate_bias_mutateHBias(M_mutate_bias_mutateHBias)){
      valid[0] = true;
      totalWeight = totalWeight + weight[0];
      someValid = true;
   }
   initialiseMorphism(M_mutate_bias_mutateHBias, mutate_bias_host);
   valid[1] = false;
   weight[1] = 1.000000;
   if(matchmutate_bias_mutateTBias(M_mutate_bias_mutateTBias)){
      valid[1] = true;
      totalWeight = totalWeight + weight[1];
      someValid = true;
   }
   initialiseMorphism(M_mutate_bias_mutateTBias, mutate_bias_host);
   if (someValid){
      double r = ((double)rand() / (double)RAND_MAX);
      r = r * totalWeight;
      double sum = 0.0;
      if(valid[0]){
         sum = sum + weight[0];
         if(r <= sum){
            emptyPot(mutate_bias_pot);
            fillpotmutate_bias_mutateHBias(mutate_bias_pot, M_mutate_bias_mutateHBias);
            if(potSize(mutate_bias_pot) > 0){
               MorphismHolder *holder = drawFromPot(mutate_bias_pot);
               duplicateMorphism(holder->morphism, M_mutate_bias_mutateHBias, mutate_bias_host);
               freeMorphism(holder->morphism);
               free(holder);
               applymutate_bias_mutateHBias(M_mutate_bias_mutateHBias, false);
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
            fillpotmutate_bias_mutateTBias(mutate_bias_pot, M_mutate_bias_mutateTBias);
            if(potSize(mutate_bias_pot) > 0){
               MorphismHolder *holder = drawFromPot(mutate_bias_pot);
               duplicateMorphism(holder->morphism, M_mutate_bias_mutateTBias, mutate_bias_host);
               freeMorphism(holder->morphism);
               free(holder);
               applymutate_bias_mutateTBias(M_mutate_bias_mutateTBias, false);
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

