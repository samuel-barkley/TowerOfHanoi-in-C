//
// Created by samue on 31/03/2023.
//

#include "DtosHelper.h"

short comparePoint(Point a, Point b) {
    if (a.x == b.x && a.y == b.y) {
        return 1;
    }
    return 0;
}

short compareShortPoint(ShortPoint a, ShortPoint b) {
    if (a.x == b.x && a.y == b.y) {
        return 1;
    }
    return 0;
}