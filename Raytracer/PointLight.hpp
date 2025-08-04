#ifndef _POINTLIGHT_
#define _POINTLIGHT_

#include "Tuples.hpp"
#include "Material.hpp"


class pt_lght {
public:
	tuple m_pos = point(0, 0, 0);
	tuple m_intensity = color(0, 0, 0);

	pt_lght() = default;
	pt_lght(tuple pos, tuple col);
	~pt_lght() = default;
};

tuple lighting(material&, pt_lght&, tuple& pos, tuple& ray_dir, tuple& norm);

#endif