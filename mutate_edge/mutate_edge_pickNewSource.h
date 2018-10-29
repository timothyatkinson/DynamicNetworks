#include "graph.h"
#include "label.h"
#include "graphStacks.h"
#include "parser.h"
#include "morphism.h"
#include "common.h"

bool matchmutate_edge_pickNewSource(Morphism *morphism);

void applymutate_edge_pickNewSource(Morphism *morphism, bool record_changes);
bool fillpotmutate_edge_pickNewSource(MorphismPot *pot, Morphism *morphism);

