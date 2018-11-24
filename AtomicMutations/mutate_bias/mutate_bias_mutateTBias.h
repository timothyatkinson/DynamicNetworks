#include "graph.h"
#include "label.h"
#include "graphStacks.h"
#include "parser.h"
#include "morphism.h"
#include "common.h"

bool matchmutate_bias_mutateTBias(Morphism *morphism);

void applymutate_bias_mutateTBias(Morphism *morphism, bool record_changes);
bool fillpotmutate_bias_mutateTBias(MorphismPot *pot, Morphism *morphism);

