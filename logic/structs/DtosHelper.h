//
// Created by samue on 31/03/2023.
//

#ifndef TOWEROFHANOI_DTOSHELPER_H
#define TOWEROFHANOI_DTOSHELPER_H

typedef struct point {
    int x;
    int y;
} Point;

typedef struct shortPoint {
    short x;
    short y;
} ShortPoint;

short comparePoint(Point a, Point b);
short compareShortPoint(ShortPoint a, ShortPoint b);

#endif //TOWEROFHANOI_DTOSHELPER_H
