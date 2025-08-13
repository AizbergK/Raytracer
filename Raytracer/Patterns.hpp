#ifndef _PATTERNS_
#define _PATTERNS_

#include "Tuples.hpp"
#include "Matrix.hpp"

enum class Styles
{
	test_pattern,
	no_pattern,
	stripe,
	gradient,
	ring,
	checkerboard,
};

class Pattern {
public:
	Color4 m_col1 = WHITE;
	Color4 m_col2 = WHITE;
	mat4x4 m_transform = i4x4;
	Styles m_style = Styles::no_pattern;

	Pattern() = default;
	Pattern(Color4, Color4, mat4x4, Styles);
	~Pattern() = default;
};

Pattern no_pat(Color4);
Pattern stripe_pattern(Color4, Color4, mat4x4 = i4x4);
Pattern gradient_pattern(Color4, Color4, mat4x4 = i4x4);
Pattern ring_pattern(Color4, Color4, mat4x4 = i4x4);
Pattern checkers_pattern(Color4, Color4, mat4x4 = i4x4);

Pattern test_pattern();

#endif