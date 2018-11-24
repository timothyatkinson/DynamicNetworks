#include <time.h>
#include "common.h"
#include "debug.h"
#include "graph.h"
#include "graphStacks.h"
#include "parser.h"
#include "morphism.h"

#include "mutate_weight_mutateLoopWeight.h"
Morphism *M_mutate_weight_mutateLoopWeight = NULL;
#include "mutate_weight_mutateEdgeWeight.h"
Morphism *M_mutate_weight_mutateEdgeWeight = NULL;

static void mutate_weight_freeMorphisms(void)
{
   freeMorphism(M_mutate_weight_mutateLoopWeight);
   freeMorphism(M_mutate_weight_mutateEdgeWeight);
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
   M_mutate_weight_mutateLoopWeight = makeMorphism(1, 1, 3);
   M_mutate_weight_mutateEdgeWeight = makeMorphism(2, 1, 4);

   /* Try Statement */
   /* Condition */
   do
   {
      /* Rule Set Call */
      do
      {
      bool valid[2];
      double weight[2];
      double totalWeight = 0.0;
      bool someValid = false;
      valid[0] = false;
      weight[0] = 1.000000;
      if(matchmutate_weight_mutateLoopWeight(M_mutate_weight_mutateLoopWeight)){
         valid[0] = true;
         totalWeight = totalWeight + weight[0];
         someValid = true;
      }
      initialiseMorphism(M_mutate_weight_mutateLoopWeight, mutate_weight_host);
      valid[1] = false;
      weight[1] = 1.000000;
      if(matchmutate_weight_mutateEdgeWeight(M_mutate_weight_mutateEdgeWeight)){
         valid[1] = true;
         totalWeight = totalWeight + weight[1];
         someValid = true;
      }
      initialiseMorphism(M_mutate_weight_mutateEdgeWeight, mutate_weight_host);
      if (someValid){
         double r = ((double)rand() / (double)RAND_MAX);
         r = r * totalWeight;
         double sum = 0.0;
         if(valid[0]){
            sum = sum + weight[0];
            if(r <= sum){
               emptyPot(mutate_weight_pot);
               fillpotmutate_weight_mutateLoopWeight(mutate_weight_pot, M_mutate_weight_mutateLoopWeight);
               if(potSize(mutate_weight_pot) > 0){
                  MorphismHolder *holder = drawFromPot(mutate_weight_pot);
                  duplicateMorphism(holder->morphism, M_mutate_weight_mutateLoopWeight, mutate_weight_host);
                  freeMorphism(holder->morphism);
                  free(holder);
                  applymutate_weight_mutateLoopWeight(M_mutate_weight_mutateLoopWeight, false);
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
               fillpotmutate_weight_mutateEdgeWeight(mutate_weight_pot, M_mutate_weight_mutateEdgeWeight);
               if(potSize(mutate_weight_pot) > 0){
                  MorphismHolder *holder = drawFromPot(mutate_weight_pot);
                  duplicateMorphism(holder->morphism, M_mutate_weight_mutateEdgeWeight, mutate_weight_host);
                  freeMorphism(holder->morphism);
                  free(holder);
                  applymutate_weight_mutateEdgeWeight(M_mutate_weight_mutateEdgeWeight, false);
                  mutate_weight_success = true;
                  break;
               }
               emptyPot(mutate_weight_pot);
            }
         }
      } else {
      mutate_weight_success = false;
      break;
      }
      } while(false);
   } while(false);

   /* Then Branch */
   if(mutate_weight_success)
   {
      /* Skip Statement */
      mutate_weight_success = true;
   }
   /* Else Branch */
   else
   {
      mutate_weight_success = true;
      /* Skip Statement */
      mutate_weight_success = true;
   }
   mutate_weight_garbageCollect();
   return 0;
}

