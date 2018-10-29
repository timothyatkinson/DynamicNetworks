#include "graph.h"
#include "label.h"
#include "graphStacks.h"
#include "parser.h"
#include "morphism.h"
#include "common.h"

bool matchmutate_param_pickParam(Morphism *morphism);

void applymutate_param_pickParam(Morphism *morphism, bool record_changes);
bool fillpotmutate_param_pickParam(MorphismPot *pot, Morphism *morphism);

