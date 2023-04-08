//
// Created by Samuel Barkley on 08/04/2023.
//

#include <time.h>
#include "Headers/TimeHelper.h"


double getTimeInSeconds(clock_t t) {
    return ((double) t) / CLOCKS_PER_SEC;
}

clock_t getTimeInTicks(double t) {
    return (clock_t) t * CLOCKS_PER_SEC;
}

double microToMilliSec(double microSeconds) {
    return microSeconds * 1000.0;
}

double microToSec(double microSeconds) {
    return microSeconds * 1000.0 * 1000.0;
}
