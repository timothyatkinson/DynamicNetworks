#include "graph.h"
#include "label.h"
#include "graphStacks.h"
#include "parser.h"
#include "morphism.h"
#include "common.h"

bool matchmutate_weight_mutateLoopWeight(Morphism *morphism);

void applymutate_weight_mutateLoopWeight(Morphism *morphism, bool record_changes);
bool fillpotmutate_weight_mutateLoopWeight(MorphismPot *pot, Morphism *morphism);

