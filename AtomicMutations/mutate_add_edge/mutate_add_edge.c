#include <time.h>
#include "common.h"
#include "debug.h"
#include "graph.h"
#include "graphStacks.h"
#include "parser.h"
#include "morphism.h"

#include "mutate_add_edge_add_edge_H.h"
Morphism *M_mutate_add_edge_add_edge_H = NULL;
#include "mutate_add_edge_add_edge_T.h"
Morphism *M_mutate_add_edge_add_edge_T = NULL;
#include "mutate_add_edge_add_loop_H.h"
Morphism *M_mutate_add_edge_add_loop_H = NULL;
#include "mutate_add_edge_add_loop_T.h"
Morphism *M_mutate_add_edge_add_loop_T = NULL;

static void mutate_add_edge_freeMorphisms(void)
{
   freeMorphism(M_mutate_add_edge_add_edge_H);
   freeMorphism(M_mutate_add_edge_add_edge_T);
   freeMorphism(M_mutate_add_edge_add_loop_H);
   freeMorphism(M_mutate_add_edge_add_loop_T);
}

Graph* mutate_add_edge_host = NULL;
int* mutate_add_edge_node_map = NULL;
MorphismPot* mutate_add_edge_pot = NULL;

static void mutate_add_edge_garbageCollect(void)
{
   mutate_add_edge_freeMorphisms();
   freePot(mutate_add_edge_pot);
}

bool mutate_add_edge_success = true;

int mutate_add_edge_execute(Graph* host_graph)
{
   mutate_add_edge_host = host_graph;
   mutate_add_edge_success = true;
   mutate_add_edge_pot = makeMorphismPot();
   emptyPot(mutate_add_edge_pot);
   M_mutate_add_edge_add_edge_H = makeMorphism(2, 0, 2);
   M_mutate_add_edge_add_edge_T = makeMorphism(2, 0, 2);
   M_mutate_add_edge_add_loop_H = makeMorphism(1, 0, 1);
   M_mutate_add_edge_add_loop_T = makeMorphism(1, 0, 1);

   /* Rule Set Call */
   do
   {
      emptyPot(mutate_add_edge_pot);
      fillpotmutate_add_edge_add_edge_H(mutate_add_edge_pot, M_mutate_add_edge_add_edge_H);
      fillpotmutate_add_edge_add_edge_T(mutate_add_edge_pot, M_mutate_add_edge_add_edge_T);
      fillpotmutate_add_edge_add_loop_H(mutate_add_edge_pot, M_mutate_add_edge_add_loop_H);
      fillpotmutate_add_edge_add_loop_T(mutate_add_edge_pot, M_mutate_add_edge_add_loop_T);
      if(potSize(mutate_add_edge_pot) == 0){
      printf("No output graph: Fail statement invoked\n");
      mutate_add_edge_garbageCollect();
      return 0;
      } else{
         MorphismHolder *holder = drawFromPot(mutate_add_edge_pot);
         if(strcmp(holder->ruleName, "mutate_add_edge_add_edge_H") == 0){
            duplicateMorphism(holder->morphism, M_mutate_add_edge_add_edge_H, mutate_add_edge_host);
            freeMorphism(holder->morphism);
            free(holder);
            applymutate_add_edge_add_edge_H(M_mutate_add_edge_add_edge_H, false);
            mutate_add_edge_success = true;
            break;
         }
         if(strcmp(holder->ruleName, "mutate_add_edge_add_edge_T") == 0){
            duplicateMorphism(holder->morphism, M_mutate_add_edge_add_edge_T, mutate_add_edge_host);
            freeMorphism(holder->morphism);
            free(holder);
            applymutate_add_edge_add_edge_T(M_mutate_add_edge_add_edge_T, false);
            mutate_add_edge_success = true;
            break;
         }
         if(strcmp(holder->ruleName, "mutate_add_edge_add_loop_H") == 0){
            duplicateMorphism(holder->morphism, M_mutate_add_edge_add_loop_H, mutate_add_edge_host);
            freeMorphism(holder->morphism);
            free(holder);
            applymutate_add_edge_add_loop_H(M_mutate_add_edge_add_loop_H, false);
            mutate_add_edge_success = true;
            break;
         }
         if(strcmp(holder->ruleName, "mutate_add_edge_add_loop_T") == 0){
            duplicateMorphism(holder->morphism, M_mutate_add_edge_add_loop_T, mutate_add_edge_host);
            freeMorphism(holder->morphism);
            free(holder);
            applymutate_add_edge_add_loop_T(M_mutate_add_edge_add_loop_T, false);
            mutate_add_edge_success = true;
            break;
         }
      }
      emptyPot(mutate_add_edge_pot);
   } while(false);
   mutate_add_edge_garbageCollect();
   return 0;
}

