#include <time.h>
#include "common.h"
#include "debug.h"
#include "graph.h"
#include "graphStacks.h"
#include "parser.h"
#include "morphism.h"

#include "mutate_param_mutateParam.h"
Morphism *M_mutate_param_mutateParam = NULL;
#include "mutate_param_mutateLeakRate.h"
Morphism *M_mutate_param_mutateLeakRate = NULL;

static void mutate_param_freeMorphisms(void)
{
   freeMorphism(M_mutate_param_mutateParam);
   freeMorphism(M_mutate_param_mutateLeakRate);
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
   M_mutate_param_mutateParam = makeMorphism(1, 0, 2);
   M_mutate_param_mutateLeakRate = makeMorphism(1, 0, 1);

   /* Rule Set Call */
   do
   {
      emptyPot(mutate_param_pot);
      fillpotmutate_param_mutateParam(mutate_param_pot, M_mutate_param_mutateParam);
      fillpotmutate_param_mutateLeakRate(mutate_param_pot, M_mutate_param_mutateLeakRate);
      if(potSize(mutate_param_pot) == 0){
      printf("No output graph: Fail statement invoked\n");
      mutate_param_garbageCollect();
      return 0;
      } else{
         MorphismHolder *holder = drawFromPot(mutate_param_pot);
         if(strcmp(holder->ruleName, "mutate_param_mutateParam") == 0){
            duplicateMorphism(holder->morphism, M_mutate_param_mutateParam, mutate_param_host);
            freeMorphism(holder->morphism);
            free(holder);
            applymutate_param_mutateParam(M_mutate_param_mutateParam, false);
            mutate_param_success = true;
            break;
         }
         if(strcmp(holder->ruleName, "mutate_param_mutateLeakRate") == 0){
            duplicateMorphism(holder->morphism, M_mutate_param_mutateLeakRate, mutate_param_host);
            freeMorphism(holder->morphism);
            free(holder);
            applymutate_param_mutateLeakRate(M_mutate_param_mutateLeakRate, false);
            mutate_param_success = true;
            break;
         }
      }
      emptyPot(mutate_param_pot);
   } while(false);
   mutate_param_garbageCollect();
   return 0;
}

