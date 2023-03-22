#include "peano.h"

void pindex2xyOpt(unsigned long long int pindex, unsigned N, coord_t* xCoord, coord_t* yCoord);

void peano_V0(unsigned degree, coord_t* x, coord_t* y) {
    unsigned long long int xCounter = 0;
    unsigned long long int yCounter = 0;
    for (unsigned long long int i = 0; i < pow(3, 2 * (degree - 1)); i++) {
        pindex2xyOpt(i, degree, x + xCounter, y + yCounter);
        xCounter++;
        yCounter++;
    }
    coord_t transform = pow(3, (degree - 1));
    for (unsigned long long int i = 0; i < pow(3, 2 * (degree - 1)); i++) {
        x[xCounter++] = (pow(3, degree - 1) - 1) - x[i];
        y[yCounter++] = y[i] + transform;
    }
    for (unsigned long long int i = 0; i < pow(3, 2 * (degree - 1)); i++) {
        x[xCounter++] = x[i];
        y[yCounter++] = y[i] + 2 * transform;
    }
    for (unsigned long long int i = 0; i < pow(3, 2 * degree) / 3; i++) {
        x[xCounter++] = x[i] + transform;
        y[yCounter++] = (pow(3, degree) - 1) - y[i];
    }
    for (unsigned long long int i = 0; i < pow(3, 2 * degree) / 3; i++) {
        x[xCounter++] = x[i] + 2 * transform;
        y[yCounter++] = y[i];
    }
}

// Converts index of point in peano curve to x,y-Coordinates
// N is degree
void pindex2xyOpt(unsigned long long int pindex, unsigned N, coord_t* xCoord, coord_t* yCoord) {
    int tmp = pindex % 9;
    coord_t x = tmp / 3;
    coord_t y = x == 1 ? 2 - (tmp % 3) : tmp % 3;

    for (int n = 2; n <= N; n++) {
        tmp = pindex / (unsigned long long int) pow(9, n - 1);
        tmp = tmp % 9;
        coord_t length = pow(3, n - 1);
        coord_t length2 = length / 2;
        int tmp3 = tmp / 3;
        int tmpM3 = tmp % 3;
        if (tmpM3 == 1) {
            x = length2 + (length2 - x);
        }
        if (tmp3 == 1) {
            y = length2 + (length2 - y);
        }
        x += (tmp3) * length;
        y += tmp3 == 1 ? (2 - tmpM3) * length : tmpM3 * length;
    }
    *xCoord = x;
    *yCoord = y;
}





