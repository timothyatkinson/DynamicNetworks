#include "graph.h"
#include "label.h"
#include "graphStacks.h"
#include "parser.h"
#include "morphism.h"
#include "common.h"

bool matchmutate_edge_mutateEdgeSource(Morphism *morphism);

void applymutate_edge_mutateEdgeSource(Morphism *morphism, bool record_changes);
bool fillpotmutate_edge_mutateEdgeSource(MorphismPot *pot, Morphism *morphism);

