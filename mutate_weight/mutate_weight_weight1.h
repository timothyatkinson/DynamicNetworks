#include "graph.h"
#include "label.h"
#include "graphStacks.h"
#include "parser.h"
#include "morphism.h"

bool matchmutate_weight_weight1(Morphism *morphism);

void applymutate_weight_weight1(Morphism *morphism, bool record_changes);
bool fillpotmutate_weight_weight1(MorphismPot *pot, Morphism *morphism);
