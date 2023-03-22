#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <ctype.h>
#include <math.h>

// Integer data type for coordinates on the curve
typedef unsigned long int coord_t;

void peano_V0(unsigned degree, coord_t* x, coord_t* y);
void peano_V1(unsigned degree, coord_t* x, coord_t* y);
void peano_V2(unsigned degree, coord_t* x, coord_t* y);