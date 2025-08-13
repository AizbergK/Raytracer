#include "Patterns.hpp"

Pattern::Pattern(Color4 col1, Color4 col2, mat4x4 mat, Styles st) : m_col1{ col1 }, m_col2{ col2 }, m_transform{ mat }, m_style{st} {}

Pattern no_pat(Color4 col)
{
	return Pattern{ col, col, i4x4, Styles::no_pattern };
}

Pattern stripe_pattern(Color4 col1, Color4 col2, mat4x4 mat)
{
	return Pattern{ col1, col2, mat, Styles::stripe };
}

Pattern gradient_pattern(Color4 col1, Color4 col2, mat4x4 mat)
{
	return Pattern{ col1, col2, mat, Styles::gradient };
}

Pattern ring_pattern(Color4 col1, Color4 col2, mat4x4 mat)
{
	return Pattern{ col1, col2, mat, Styles::ring };
}

Pattern checkers_pattern(Color4 col1, Color4 col2, mat4x4 mat)
{
	return Pattern{ col1, col2, mat, Styles::checkerboard };
}

Pattern test_pattern()
{
	return Pattern{ BLACK, BLACK, i4x4, Styles::test_pattern };
}