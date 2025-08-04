#ifndef _COMPDATA_
#define _COMPDATA_

#include "Tuples.hpp"
#include "Intersection.hpp"

struct comp_data {
	intersection inter;
	tuple pt;
	tuple eyev;
	tuple normalv;
	bool is_inside = false;
};

#endif