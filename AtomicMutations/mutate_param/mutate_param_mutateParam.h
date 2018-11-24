#include "graph.h"
#include "label.h"
#include "graphStacks.h"
#include "parser.h"
#include "morphism.h"
#include "common.h"

bool matchmutate_param_mutateParam(Morphism *morphism);

void applymutate_param_mutateParam(Morphism *morphism, bool record_changes);
bool fillpotmutate_param_mutateParam(MorphismPot *pot, Morphism *morphism);

