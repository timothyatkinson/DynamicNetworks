#include <time.h>
#include "common.h"
#include "debug.h"
#include "graph.h"
#include "graphStacks.h"
#include "parser.h"
#include "morphism.h"

#include "mutate_edge_pickEdge.h"
Morphism *M_mutate_edge_pickEdge = NULL;
#include "mutate_edge_pickLoop.h"
Morphism *M_mutate_edge_pickLoop = NULL;
#include "mutate_edge_loop.h"
Morphism *M_mutate_edge_loop = NULL;
#include "mutate_edge_mutateLoopSource.h"
Morphism *M_mutate_edge_mutateLoopSource = NULL;
#include "mutate_edge_mutateLoopTarget.h"
Morphism *M_mutate_edge_mutateLoopTarget = NULL;
#include "mutate_edge_mutateEdgeSource.h"
Morphism *M_mutate_edge_mutateEdgeSource = NULL;
#include "mutate_edge_mutateEdgeTarget.h"
Morphism *M_mutate_edge_mutateEdgeTarget = NULL;
#include "mutate_edge_mutateEdgeSourceLoop.h"
Morphism *M_mutate_edge_mutateEdgeSourceLoop = NULL;
#include "mutate_edge_mutateEdgeTargetLoop.h"
Morphism *M_mutate_edge_mutateEdgeTargetLoop = NULL;

static void mutate_edge_freeMorphisms(void)
{
   freeMorphism(M_mutate_edge_pickEdge);
   freeMorphism(M_mutate_edge_pickLoop);
   freeMorphism(M_mutate_edge_loop);
   freeMorphism(M_mutate_edge_mutateLoopSource);
   freeMorphism(M_mutate_edge_mutateLoopTarget);
   freeMorphism(M_mutate_edge_mutateEdgeSource);
   freeMorphism(M_mutate_edge_mutateEdgeTarget);
   freeMorphism(M_mutate_edge_mutateEdgeSourceLoop);
   freeMorphism(M_mutate_edge_mutateEdgeTargetLoop);
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
   M_mutate_edge_pickLoop = makeMorphism(1, 1, 2);
   M_mutate_edge_loop = makeMorphism(1, 1, 2);
   M_mutate_edge_mutateLoopSource = makeMorphism(2, 1, 3);
   M_mutate_edge_mutateLoopTarget = makeMorphism(2, 1, 3);
   M_mutate_edge_mutateEdgeSource = makeMorphism(3, 1, 4);
   M_mutate_edge_mutateEdgeTarget = makeMorphism(3, 1, 4);
   M_mutate_edge_mutateEdgeSourceLoop = makeMorphism(2, 1, 3);
   M_mutate_edge_mutateEdgeTargetLoop = makeMorphism(2, 1, 3);

   /* Try Statement */
   /* Condition */
   int restore_point0 = graph_change_stack == NULL ? 0 : topOfGraphChangeStack();
   do
   {
      /* Rule Set Call */
      do
      {
         emptyPot(mutate_edge_pot);
         fillpotmutate_edge_pickEdge(mutate_edge_pot, M_mutate_edge_pickEdge);
         fillpotmutate_edge_pickLoop(mutate_edge_pot, M_mutate_edge_pickLoop);
         if(potSize(mutate_edge_pot) == 0){
         mutate_edge_success = false;
         break;
         } else{
            MorphismHolder *holder = drawFromPot(mutate_edge_pot);
            if(strcmp(holder->ruleName, "mutate_edge_pickEdge") == 0){
               duplicateMorphism(holder->morphism, M_mutate_edge_pickEdge, mutate_edge_host);
               freeMorphism(holder->morphism);
               free(holder);
               applymutate_edge_pickEdge(M_mutate_edge_pickEdge, true);
               mutate_edge_success = true;
               break;
            }
            if(strcmp(holder->ruleName, "mutate_edge_pickLoop") == 0){
               duplicateMorphism(holder->morphism, M_mutate_edge_pickLoop, mutate_edge_host);
               freeMorphism(holder->morphism);
               free(holder);
               applymutate_edge_pickLoop(M_mutate_edge_pickLoop, true);
               mutate_edge_success = true;
               break;
            }
         }
         emptyPot(mutate_edge_pot);
      } while(false);
      /* If Statement */
      /* Condition */
      do
      {
         /* Rule Call */
         if(matchmutate_edge_loop(M_mutate_edge_loop))
         {
            mutate_edge_success = true;
         }
         else
         {
            mutate_edge_success = false;
            break;
         }
      } while(false);

      /* Then Branch */
      if(mutate_edge_success)
      {
         /* Rule Set Call */
         do
         {
            emptyPot(mutate_edge_pot);
            fillpotmutate_edge_mutateLoopSource(mutate_edge_pot, M_mutate_edge_mutateLoopSource);
            fillpotmutate_edge_mutateLoopTarget(mutate_edge_pot, M_mutate_edge_mutateLoopTarget);
            if(potSize(mutate_edge_pot) == 0){
            mutate_edge_success = false;
            break;
            } else{
               MorphismHolder *holder = drawFromPot(mutate_edge_pot);
               if(strcmp(holder->ruleName, "mutate_edge_mutateLoopSource") == 0){
                  duplicateMorphism(holder->morphism, M_mutate_edge_mutateLoopSource, mutate_edge_host);
                  freeMorphism(holder->morphism);
                  free(holder);
                  applymutate_edge_mutateLoopSource(M_mutate_edge_mutateLoopSource, true);
                  mutate_edge_success = true;
                  break;
               }
               if(strcmp(holder->ruleName, "mutate_edge_mutateLoopTarget") == 0){
                  duplicateMorphism(holder->morphism, M_mutate_edge_mutateLoopTarget, mutate_edge_host);
                  freeMorphism(holder->morphism);
                  free(holder);
                  applymutate_edge_mutateLoopTarget(M_mutate_edge_mutateLoopTarget, true);
                  mutate_edge_success = true;
                  break;
               }
            }
            emptyPot(mutate_edge_pot);
         } while(false);
      }
      /* Else Branch */
      else
      {
         mutate_edge_success = true;
         /* Rule Set Call */
         do
         {
            emptyPot(mutate_edge_pot);
            fillpotmutate_edge_mutateEdgeSource(mutate_edge_pot, M_mutate_edge_mutateEdgeSource);
            fillpotmutate_edge_mutateEdgeTarget(mutate_edge_pot, M_mutate_edge_mutateEdgeTarget);
            fillpotmutate_edge_mutateEdgeSourceLoop(mutate_edge_pot, M_mutate_edge_mutateEdgeSourceLoop);
            fillpotmutate_edge_mutateEdgeTargetLoop(mutate_edge_pot, M_mutate_edge_mutateEdgeTargetLoop);
            if(potSize(mutate_edge_pot) == 0){
            mutate_edge_success = false;
            break;
            } else{
               MorphismHolder *holder = drawFromPot(mutate_edge_pot);
               if(strcmp(holder->ruleName, "mutate_edge_mutateEdgeSource") == 0){
                  duplicateMorphism(holder->morphism, M_mutate_edge_mutateEdgeSource, mutate_edge_host);
                  freeMorphism(holder->morphism);
                  free(holder);
                  applymutate_edge_mutateEdgeSource(M_mutate_edge_mutateEdgeSource, true);
                  mutate_edge_success = true;
                  break;
               }
               if(strcmp(holder->ruleName, "mutate_edge_mutateEdgeTarget") == 0){
                  duplicateMorphism(holder->morphism, M_mutate_edge_mutateEdgeTarget, mutate_edge_host);
                  freeMorphism(holder->morphism);
                  free(holder);
                  applymutate_edge_mutateEdgeTarget(M_mutate_edge_mutateEdgeTarget, true);
                  mutate_edge_success = true;
                  break;
               }
               if(strcmp(holder->ruleName, "mutate_edge_mutateEdgeSourceLoop") == 0){
                  duplicateMorphism(holder->morphism, M_mutate_edge_mutateEdgeSourceLoop, mutate_edge_host);
                  freeMorphism(holder->morphism);
                  free(holder);
                  applymutate_edge_mutateEdgeSourceLoop(M_mutate_edge_mutateEdgeSourceLoop, true);
                  mutate_edge_success = true;
                  break;
               }
               if(strcmp(holder->ruleName, "mutate_edge_mutateEdgeTargetLoop") == 0){
                  duplicateMorphism(holder->morphism, M_mutate_edge_mutateEdgeTargetLoop, mutate_edge_host);
                  freeMorphism(holder->morphism);
                  free(holder);
                  applymutate_edge_mutateEdgeTargetLoop(M_mutate_edge_mutateEdgeTargetLoop, true);
                  mutate_edge_success = true;
                  break;
               }
            }
            emptyPot(mutate_edge_pot);
         } while(false);
      }
      break;
   } while(false);

   /* Then Branch */
   if(mutate_edge_success)
   {
      discardChanges(restore_point0);
      /* Skip Statement */
      mutate_edge_success = true;
   }
   /* Else Branch */
   else
   {
      undoChanges(mutate_edge_host, restore_point0);
      mutate_edge_success = true;
      /* Skip Statement */
      mutate_edge_success = true;
   }
   mutate_edge_garbageCollect();
   return 0;
}

