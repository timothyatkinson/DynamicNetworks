#include "graph.h"
#include "label.h"
#include "graphStacks.h"
#include "parser.h"
#include "morphism.h"
#include "common.h"

bool matchmutate_param_mutateLeakRate(Morphism *morphism);

void applymutate_param_mutateLeakRate(Morphism *morphism, bool record_changes);
bool fillpotmutate_param_mutateLeakRate(MorphismPot *pot, Morphism *morphism);

