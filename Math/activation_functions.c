#include "activation_functions.h"
#include <stdlib.h>
#include <stdio.h>

double sigmoid(double value){
  double val = 1.0 / (1.0 + exp(-value));
  if(val < 0.0){
    printf("%lf (%lf) WTF\n", val, value);
    exit(0);
  }
  return 1.0 / (1.0 + exp(-value));
}
