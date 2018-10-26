#include "graph.h"
#include "label.h"
#include "graphStacks.h"
#include "parser.h"
#include "morphism.h"

bool matchmutate_edge_mutateTarget(Morphism *morphism);

void applymutate_edge_mutateTarget(Morphism *morphism, bool record_changes);
bool fillpotmutate_edge_mutateTarget(MorphismPot *pot, Morphism *morphism);

