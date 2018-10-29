#include "graph.h"
#include "label.h"
#include "graphStacks.h"
#include "parser.h"
#include "morphism.h"
#include "common.h"

bool matchmutate_bias_pickNode(Morphism *morphism);

void applymutate_bias_pickNode(Morphism *morphism, bool record_changes);
bool fillpotmutate_bias_pickNode(MorphismPot *pot, Morphism *morphism);

