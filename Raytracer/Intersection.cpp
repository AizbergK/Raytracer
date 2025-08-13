#include "Intersection.hpp"

Intersection::Intersection(double t, std::shared_ptr<Shape> sp) : m_time{ t }, m_obj{ sp } {}

bool Intersection::operator==(Intersection& other)
{
	return this->m_time == other.m_time && this->m_obj == other.m_obj;
}