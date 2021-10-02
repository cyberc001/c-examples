#ifndef PERFTEST_H
#define PERFTEST_H

#include <time.h>

#define PERFTEST_MEASURE(exp, out) {\
clock_t beg = clock();\
exp;\
(out) = clock() - beg;\
}
#define PERFTEST_MEASURE_LOOP(exp, times, out) {\
clock_t beg = clock();\
for(size_t i = 0; i < times; ++i)\
exp;\
(out) = clock() - beg;\
}

#endif
