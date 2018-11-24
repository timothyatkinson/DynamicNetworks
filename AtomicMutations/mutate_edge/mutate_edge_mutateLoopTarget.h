#include "graph.h"
#include "label.h"
#include "graphStacks.h"
#include "parser.h"
#include "morphism.h"
#include "common.h"

bool matchmutate_edge_mutateLoopTarget(Morphism *morphism);

void applymutate_edge_mutateLoopTarget(Morphism *morphism, bool record_changes);
bool fillpotmutate_edge_mutateLoopTarget(MorphismPot *pot, Morphism *morphism);

