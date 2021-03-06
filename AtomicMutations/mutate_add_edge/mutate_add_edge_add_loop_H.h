#include "graph.h"
#include "label.h"
#include "graphStacks.h"
#include "parser.h"
#include "morphism.h"
#include "common.h"

bool matchmutate_add_edge_add_loop_H(Morphism *morphism);

void applymutate_add_edge_add_loop_H(Morphism *morphism, bool record_changes);
bool fillpotmutate_add_edge_add_loop_H(MorphismPot *pot, Morphism *morphism);

