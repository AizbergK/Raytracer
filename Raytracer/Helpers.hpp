#ifndef _HELPERS_
#define _HELPERS_

#include <cstdlib>
#include <cmath>

constexpr double EPSILON = 0.00001;
constexpr double PI		 = 3.1415926535897931;
constexpr double DEG_90  = PI / 2.0;
constexpr double DEG_60  = PI / 3.0;
constexpr double DEG_45  = PI / 4.0;
constexpr double DEG_30  = PI / 6.0;

bool is_equal(double a, double b);

#endif