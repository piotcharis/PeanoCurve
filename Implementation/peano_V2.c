#include "peano.h"

unsigned long long int xCounter;
unsigned long long int yCounter;

void peano(coord_t x, coord_t y, coord_t lg, int i1, int i2, coord_t* xCoords, coord_t* yCoords);

void peano_V2(unsigned degree, coord_t* x, coord_t* y) {
    xCounter = 0;
    yCounter = 0;
    peano(0, 0, pow(3, degree), 0, 0, x, y);
}

// Generates the "Standard"-Variant (as per the assignment).
// Divides the field recursively into 9 quadrants until the length is 1.
// x and y describe the lower left corner of the current quadrant
// i1 and i2 determine the starting point of the curve in the current quadrant:
// i1: 0 -> Down; 1 -> Up
// i2: 0 -> Left; 1 -> Right
void peano(coord_t x, coord_t y, coord_t lg, int i1, int i2, coord_t* xCoords, coord_t* yCoords) {
    if (lg == 1) { /* Exit condition. */
        xCoords[xCounter++] = x;
        yCoords[yCounter++] = y;
        return;
    }
    lg = lg / 3;
    if (i1 == 0 && i2 == 0) { // Left down
        peano(x, y, lg, 0, 0, xCoords, yCoords);
        peano(x, y + lg, lg, 0, 1, xCoords, yCoords);
        peano(x, y + 2 * lg, lg, 0, 0, xCoords, yCoords);
        peano(x + lg, y + 2 * lg, lg, 1, 0, xCoords, yCoords);
        peano(x + lg, y + lg, lg, 1, 1, xCoords, yCoords);
        peano(x + lg, y, lg, 1, 0, xCoords, yCoords);
        peano(x + 2 * lg, y, lg, 0, 0, xCoords, yCoords);
        peano(x + 2 * lg, y + lg, lg, 0, 1, xCoords, yCoords);
        peano(x + 2 * lg, y + 2 * lg, lg, 0, 0, xCoords, yCoords);
    } else if (i1 == 0 && i2 == 1) { // Left up
        peano(x + 2 * lg, y, lg, 0, 1, xCoords, yCoords);
        peano(x + 2 * lg, y + lg, lg, 0, 0, xCoords, yCoords);
        peano(x + 2 * lg, y + 2 * lg, lg, 0, 1, xCoords, yCoords);
        peano(x + lg, y + 2 * lg, lg, 1, 1, xCoords, yCoords);
        peano(x + lg, y + lg, lg, 1, 0, xCoords, yCoords);
        peano(x + lg, y, lg, 1, 1, xCoords, yCoords);
        peano(x, y, lg, 0, 1, xCoords, yCoords);
        peano(x, y + lg, lg, 0, 0, xCoords, yCoords);
        peano(x, y + 2 * lg, lg, 0, 1, xCoords, yCoords);
    } else if (i1 == 1 && i2 == 0) { // Right down
        peano(x, y + 2 * lg, lg, 1, 0, xCoords, yCoords);
        peano(x, y + lg, lg, 1, 1, xCoords, yCoords);
        peano(x, y, lg, 1, 0, xCoords, yCoords);
        peano(x + lg, y, lg, 0, 0, xCoords, yCoords);
        peano(x + lg, y + lg, lg, 0, 1, xCoords, yCoords);
        peano(x + lg, y + 2 * lg, lg, 0, 0, xCoords, yCoords);
        peano(x + 2 * lg, y + 2 * lg, lg, 1, 0, xCoords, yCoords);
        peano(x + 2 * lg, y + lg, lg, 1, 1, xCoords, yCoords);
        peano(x + 2 * lg, y, lg, 1, 0, xCoords, yCoords);
    } else { //i1 == 1 && i2 == 1 -> Right up
        peano(x + 2 * lg, y + 2 * lg, lg, 1, 1, xCoords, yCoords);
        peano(x + 2 * lg, y + lg, lg, 1, 0, xCoords, yCoords);
        peano(x + 2 * lg, y, lg, 1, 1, xCoords, yCoords);
        peano(x + lg, y, lg, 0, 1, xCoords, yCoords);
        peano(x + lg, y + lg, lg, 0, 0, xCoords, yCoords);
        peano(x + lg, y + 2 * lg, lg, 0, 1, xCoords, yCoords);
        peano(x, y + 2 * lg, lg, 1, 1, xCoords, yCoords);
        peano(x, y + lg, lg, 1, 0, xCoords, yCoords);
        peano(x, y, lg, 1, 1, xCoords, yCoords);
    }
}

