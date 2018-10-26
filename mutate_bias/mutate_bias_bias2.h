#include "graph.h"
#include "label.h"
#include "graphStacks.h"
#include "parser.h"
#include "morphism.h"

bool matchmutate_bias_bias2(Morphism *morphism);

void applymutate_bias_bias2(Morphism *morphism, bool record_changes);
bool fillpotmutate_bias_bias2(MorphismPot *pot, Morphism *morphism);

