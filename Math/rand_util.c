#include "rand_util.h"

/**rand_double - RAND double
  *Computes a random double between 0 and 1 using C's inbuilt RNG
*/
double rand_double(){
  return (double)rand() / (double)RAND_MAX;
}

/**rand_double - RAND double
  *Computes a random double between min and max (inclusive ish) using C's inbuilt RNG
    * min. The minimum value
    * max. The maximum value
*/
double rand_range(double min, double max){
  return min + (rand_double() * fabs(max - min));
}

/**rand_bool - RAND BOOLEAN
  * Computes a random boolean which is true with probability p.
  * p. The probability of returning true
*/
bool rand_bool(double p){
  return rand_double() <= p;
}

double bound(double val, double min, double max){
  while(val < min){
    val = val + (max - min);
  }
  while(val > max){
    val = val - (max - min);
  }
  return val;
}

/* generate a random value weighted within the normal (gaussian) distribution */
double gauss(void)
{
  double x = (double)random() / RAND_MAX,
         y = (double)random() / RAND_MAX,
         z = sqrt(-2 * log(x)) * cos(2 * M_PI * y);
  return z;
}


int rand_int(int min, int max){
    return (int)round((rand_double() * ((max - 1) - min)) + min);
}
