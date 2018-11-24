#include "graph.h"
#include "label.h"
#include "graphStacks.h"
#include "parser.h"
#include "morphism.h"
#include "common.h"

bool matchmutate_bias_mutateHBias(Morphism *morphism);

void applymutate_bias_mutateHBias(Morphism *morphism, bool record_changes);
bool fillpotmutate_bias_mutateHBias(MorphismPot *pot, Morphism *morphism);

