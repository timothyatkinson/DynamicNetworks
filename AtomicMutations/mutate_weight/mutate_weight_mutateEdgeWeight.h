#include "graph.h"
#include "label.h"
#include "graphStacks.h"
#include "parser.h"
#include "morphism.h"
#include "common.h"

bool matchmutate_weight_mutateEdgeWeight(Morphism *morphism);

void applymutate_weight_mutateEdgeWeight(Morphism *morphism, bool record_changes);
bool fillpotmutate_weight_mutateEdgeWeight(MorphismPot *pot, Morphism *morphism);

