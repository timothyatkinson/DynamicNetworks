#include <time.h>
#include "common.h"
#include "debug.h"
#include "graph.h"
#include "graphStacks.h"
#include "parser.h"
#include "morphism.h"

#include "mutate_edge_pickEdge.h"
Morphism *M_mutate_edge_pickEdge = NULL;
#include "mutate_edge_pickNewSource.h"
Morphism *M_mutate_edge_pickNewSource = NULL;
#include "mutate_edge_pickNewTarget.h"
Morphism *M_mutate_edge_pickNewTarget = NULL;
#include "mutate_edge_mutateSource.h"
Morphism *M_mutate_edge_mutateSource = NULL;
#include "mutate_edge_mutateTarget.h"
Morphism *M_mutate_edge_mutateTarget = NULL;

static void mutate_edge_freeMorphisms(void)
{
   freeMorphism(M_mutate_edge_pickEdge);
   freeMorphism(M_mutate_edge_pickNewSource);
   freeMorphism(M_mutate_edge_pickNewTarget);
   freeMorphism(M_mutate_edge_mutateSource);
   freeMorphism(M_mutate_edge_mutateTarget);
}

Graph* mutate_edge_host = NULL;
int* mutate_edge_node_map = NULL;
MorphismPot* mutate_edge_pot = NULL;

static void mutate_edge_garbageCollect(void)
{
   mutate_edge_freeMorphisms();
   freePot(mutate_edge_pot);
}

bool mutate_edge_success = true;

int mutate_edge_execute(Graph* host_graph)
{
   mutate_edge_host = host_graph;
   mutate_edge_success = true;
   mutate_edge_pot = makeMorphismPot();
   emptyPot(mutate_edge_pot);
   M_mutate_edge_pickEdge = makeMorphism(2, 1, 3);
   M_mutate_edge_pickNewSource = makeMorphism(1, 0, 1);
   M_mutate_edge_pickNewTarget = makeMorphism(1, 0, 1);
   M_mutate_edge_mutateSource = makeMorphism(3, 1, 4);
   M_mutate_edge_mutateTarget = makeMorphism(3, 1, 4);

   /* Rule Call */
   emptyPot(mutate_edge_pot);
   fillpotmutate_edge_pickEdge(mutate_edge_pot, M_mutate_edge_pickEdge);
   if(potSize(mutate_edge_pot) > 0){
      MorphismHolder *holder = drawFromPot(mutate_edge_pot);
      duplicateMorphism(holder->morphism, M_mutate_edge_pickEdge, mutate_edge_host);
      freeMorphism(holder->morphism);
      free(holder);
      applymutate_edge_pickEdge(M_mutate_edge_pickEdge, false);
      mutate_edge_success = true;
   }
   else
   {
      printf("No output graph: rule mutate_edge_pickEdge not applicable.\n");
      mutate_edge_garbageCollect();
      return 0;
   }
   emptyPot(mutate_edge_pot);
   /* Rule Set Call */
   do
   {
   bool valid[2];
   double weight[2];
   double totalWeight = 0.0;
   bool someValid = false;
   valid[0] = false;
   weight[0] = 1.000000;
   if(matchmutate_edge_pickNewSource(M_mutate_edge_pickNewSource)){
      valid[0] = true;
      totalWeight = totalWeight + weight[0];
      someValid = true;
   }
   initialiseMorphism(M_mutate_edge_pickNewSource, mutate_edge_host);
   valid[1] = false;
   weight[1] = 1.000000;
   if(matchmutate_edge_pickNewTarget(M_mutate_edge_pickNewTarget)){
      valid[1] = true;
      totalWeight = totalWeight + weight[1];
      someValid = true;
   }
   initialiseMorphism(M_mutate_edge_pickNewTarget, mutate_edge_host);
   if (someValid){
      double r = ((double)rand() / (double)RAND_MAX);
      r = r * totalWeight;
      double sum = 0.0;
      if(valid[0]){
         sum = sum + weight[0];
         if(r <= sum){
            emptyPot(mutate_edge_pot);
            fillpotmutate_edge_pickNewSource(mutate_edge_pot, M_mutate_edge_pickNewSource);
            if(potSize(mutate_edge_pot) > 0){
               MorphismHolder *holder = drawFromPot(mutate_edge_pot);
               duplicateMorphism(holder->morphism, M_mutate_edge_pickNewSource, mutate_edge_host);
               freeMorphism(holder->morphism);
               free(holder);
               applymutate_edge_pickNewSource(M_mutate_edge_pickNewSource, false);
               mutate_edge_success = true;
               break;
            }
            emptyPot(mutate_edge_pot);
         }
      }
      if(valid[1]){
         sum = sum + weight[1];
         if(r <= sum && r > sum - weight[1]){
            emptyPot(mutate_edge_pot);
            fillpotmutate_edge_pickNewTarget(mutate_edge_pot, M_mutate_edge_pickNewTarget);
            if(potSize(mutate_edge_pot) > 0){
               MorphismHolder *holder = drawFromPot(mutate_edge_pot);
               duplicateMorphism(holder->morphism, M_mutate_edge_pickNewTarget, mutate_edge_host);
               freeMorphism(holder->morphism);
               free(holder);
               applymutate_edge_pickNewTarget(M_mutate_edge_pickNewTarget, false);
               mutate_edge_success = true;
               break;
            }
            emptyPot(mutate_edge_pot);
         }
      }
   } else {
   printf("No output graph: Fail statement invoked\n");
   mutate_edge_garbageCollect();
   return 0;
   }
   } while(false);
   /* Rule Set Call */
   do
   {
      if(matchmutate_edge_mutateSource(M_mutate_edge_mutateSource))
      {
         applymutate_edge_mutateSource(M_mutate_edge_mutateSource, false);
         mutate_edge_success = true;
         break;
      }
      if(matchmutate_edge_mutateTarget(M_mutate_edge_mutateTarget))
      {
         applymutate_edge_mutateTarget(M_mutate_edge_mutateTarget, false);
         mutate_edge_success = true;
      }
      else
      {
         printf("No output graph: rule mutate_edge_mutateTarget not applicable.\n");
         mutate_edge_garbageCollect();
         return 0;
      }
   } while(false);
   mutate_edge_garbageCollect();
   return 0;
}

