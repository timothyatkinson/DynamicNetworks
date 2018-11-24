#include "graph.h"
#include "label.h"
#include "graphStacks.h"
#include "parser.h"
#include "morphism.h"
#include "common.h"

bool matchmutate_delete_edge_deleteEdge(Morphism *morphism);

void applymutate_delete_edge_deleteEdge(Morphism *morphism, bool record_changes);
bool fillpotmutate_delete_edge_deleteEdge(MorphismPot *pot, Morphism *morphism);

