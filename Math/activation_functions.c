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

double lin_gate(double value){
  double val = 0.098 * (value + 5.0) + 0.01;
  if(val < 0.01){
    val = 0.01;
  }
  if(val > 0.99){
    val = 0.99;
  }
  return val;
}
