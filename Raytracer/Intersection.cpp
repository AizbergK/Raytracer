#include "Intersection.hpp"

Intersection::Intersection(double t, Shape* sp) : m_time{ t }, m_obj{ sp } {}
Intersection::Intersection(std::pair<double, Shape*> p) : m_time { p.first }, m_obj{ p.second } {}
bool Intersection::operator==(Intersection& other)
{
	return this->m_time == other.m_time && this->m_obj == other.m_obj;
}