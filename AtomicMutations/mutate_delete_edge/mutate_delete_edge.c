#include <time.h>
#include "common.h"
#include "debug.h"
#include "graph.h"
#include "graphStacks.h"
#include "parser.h"
#include "morphism.h"

#include "mutate_delete_edge_deleteEdge.h"
Morphism *M_mutate_delete_edge_deleteEdge = NULL;
#include "mutate_delete_edge_deleteLoop.h"
Morphism *M_mutate_delete_edge_deleteLoop = NULL;

static void mutate_delete_edge_freeMorphisms(void)
{
   freeMorphism(M_mutate_delete_edge_deleteEdge);
   freeMorphism(M_mutate_delete_edge_deleteLoop);
}

Graph* mutate_delete_edge_host = NULL;
int* mutate_delete_edge_node_map = NULL;
MorphismPot* mutate_delete_edge_pot = NULL;

static void mutate_delete_edge_garbageCollect(void)
{
   mutate_delete_edge_freeMorphisms();
   freePot(mutate_delete_edge_pot);
}

bool mutate_delete_edge_success = true;

int mutate_delete_edge_execute(Graph* host_graph)
{
   mutate_delete_edge_host = host_graph;
   mutate_delete_edge_success = true;
   mutate_delete_edge_pot = makeMorphismPot();
   emptyPot(mutate_delete_edge_pot);
   M_mutate_delete_edge_deleteEdge = makeMorphism(2, 1, 3);
   M_mutate_delete_edge_deleteLoop = makeMorphism(1, 1, 2);

   /* Try Statement */
   /* Condition */
   do
   {
      /* Rule Set Call */
      do
      {
         emptyPot(mutate_delete_edge_pot);
         fillpotmutate_delete_edge_deleteEdge(mutate_delete_edge_pot, M_mutate_delete_edge_deleteEdge);
         fillpotmutate_delete_edge_deleteLoop(mutate_delete_edge_pot, M_mutate_delete_edge_deleteLoop);
         if(potSize(mutate_delete_edge_pot) == 0){
         mutate_delete_edge_success = false;
         break;
         } else{
            MorphismHolder *holder = drawFromPot(mutate_delete_edge_pot);
            if(strcmp(holder->ruleName, "mutate_delete_edge_deleteEdge") == 0){
               duplicateMorphism(holder->morphism, M_mutate_delete_edge_deleteEdge, mutate_delete_edge_host);
               freeMorphism(holder->morphism);
               free(holder);
               applymutate_delete_edge_deleteEdge(M_mutate_delete_edge_deleteEdge, false);
               mutate_delete_edge_success = true;
               break;
            }
            if(strcmp(holder->ruleName, "mutate_delete_edge_deleteLoop") == 0){
               duplicateMorphism(holder->morphism, M_mutate_delete_edge_deleteLoop, mutate_delete_edge_host);
               freeMorphism(holder->morphism);
               free(holder);
               applymutate_delete_edge_deleteLoop(M_mutate_delete_edge_deleteLoop, false);
               mutate_delete_edge_success = true;
               break;
            }
         }
         emptyPot(mutate_delete_edge_pot);
      } while(false);
   } while(false);

   /* Then Branch */
   if(mutate_delete_edge_success)
   {
      /* Skip Statement */
      mutate_delete_edge_success = true;
   }
   /* Else Branch */
   else
   {
      mutate_delete_edge_success = true;
      /* Skip Statement */
      mutate_delete_edge_success = true;
   }
   mutate_delete_edge_garbageCollect();
   return 0;
}

