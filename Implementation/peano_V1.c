#include "peano.h"

void pindex2xy(unsigned long long int pindex, unsigned N, coord_t* xCoord, coord_t* yCoord);

void peano_V1(unsigned degree, coord_t* x, coord_t* y) {
    unsigned long long int xCounter = 0;
    unsigned long long int yCounter = 0;
    for (unsigned long long int i = 0; i < pow(3, 2 * degree); i++) {
        pindex2xy(i, degree, x + xCounter, y + yCounter);
        xCounter++;
        yCounter++;
    }
}

// Converts index of point in peano curve to x,y-Coordinates
// N is degree
void pindex2xy(unsigned long long int pindex, unsigned N, coord_t* xCoord, coord_t* yCoord) {
    int tmp = pindex % 9;
    coord_t x;
    coord_t y;
    switch (tmp) {
        case 0:
            x = 0;
            y = 0;
            break;
        case 1:
            x = 0;
            y = 1;
            break;
        case 2:
            x = 0;
            y = 2;
            break;
        case 3:
            x = 1;
            y = 2;
            break;
        case 4:
            x = 1;
            y = 1;
            break;
        case 5:
            x = 1;
            y = 0;
            break;
        case 6:
            x = 2;
            y = 0;
            break;
        case 7:
            x = 2;
            y = 1;
            break;
        default: // 8
            x = 2;
            y = 2;
            break;
    }

    for (int n = 2; n <= N; n++) {
        tmp = pindex / (unsigned long long int) pow(9, n - 1);
        tmp = tmp % 9;
        coord_t length = pow(3, n - 1);
        switch (tmp) {
            case 1:
                x = length / 2 + (length / 2 - x);
                y += length;
                break;
            case 2:
                y += 2 * length;
                break;
            case 3:
                y = length / 2 + (length / 2 - y);
                y += 2 * length;
                x += length;
                break;
            case 4:
                x = length / 2 + (length / 2 - x);
                y = length / 2 + (length / 2 - y);
                y += length;
                x += length;
                break;
            case 5:
                y = length / 2 + (length / 2 - y);
                x += length;
                break;
            case 6:
                x += 2 * length;
                break;
            case 7:
                x = length / 2 + (length / 2 - x);
                x += 2 * length;
                y += length;
                break;
            case 8:
                x += 2 * length;
                y += 2 * length;
                break;
            default:
                break;
        }
    }
    *xCoord = x;
    *yCoord = y;
}

