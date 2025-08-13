#include "Helpers.hpp"

bool is_equal(double a, double b) 
{ 
	return (std::abs(a - b) < EPSILON); 
}
