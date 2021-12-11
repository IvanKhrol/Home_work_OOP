#include <iostream>
#include <cmath>

#include "point.hpp"
#include "circle.hpp"


//-----------------------------------------------------------------------------------------------------------
//												КОНСТРУКТОРЫ														
//-----------------------------------------------------------------------------------------------------------
Circle_t::Circle_t(const Point_t& acenter, float aradius): center(acenter), radius(aradius) {}
Circle_t::Circle_t(): center(0, 0), radius(1) {}
//-----------------------------------------------------------------------------------------------------------
Circle_t::Circle_t(const Circle_t& circle)
{
	center = circle.center;
	radius = circle.radius;
}
//-----------------------------------------------------------------------------------------------------------
//												SET AND GET														
//-----------------------------------------------------------------------------------------------------------
void Circle_t::set_centre(const Point_t& acenter)
{
	this->center = acenter;
}
//-----------------------------------------------------------------------------------------------------------
void Circle_t::set_radius(float aradius)
{
	if(aradius < 0)
	{
		std::cout << "The radius cannot be negative! Radius set to 0" << std::endl;
		aradius = 0;
	}
	this->radius = aradius;
}
//-----------------------------------------------------------------------------------------------------------
//-----------------------------------------------------------------------------------------------------------
Point_t Circle_t::get_center() const
{
	Point_t result = this->center;
	return result;
}
//-----------------------------------------------------------------------------------------------------------
float Circle_t::get_radius() const
{
	return this->radius;
}
//-----------------------------------------------------------------------------------------------------------
//												МЕТОДЫ КЛАССА CIRCLE_T														
//-----------------------------------------------------------------------------------------------------------
float Circle_t::get_area() const
{
	return (atan(1) * 4 * this->radius * this->radius);
}
//-----------------------------------------------------------------------------------------------------------
//-----------------------------------------------------------------------------------------------------------
float Circle_t::get_distance(const Point_t& p) const
{
	float dist = p.distance(this->center);
	dist -= this->radius;
	return std::abs(dist);
}
//-----------------------------------------------------------------------------------------------------------
//-----------------------------------------------------------------------------------------------------------
bool Circle_t::isColliding(const Circle_t& c) const
{
	if((c.center.distance(this->center)) <= (c.radius + this->radius))
		return true;
	return false;
}
//-----------------------------------------------------------------------------------------------------------
//-----------------------------------------------------------------------------------------------------------
void Circle_t::move(const Point_t& p)
{
	this->center.set_x(this->center.get_x() + p.get_x());
	this->center.set_y(this->center.get_y() + p.get_y());
}