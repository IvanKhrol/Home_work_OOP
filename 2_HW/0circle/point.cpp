#include <iostream>
#include <cmath>

#include "point.hpp"


// Конструкторы
// Инициализация экземпляра производится с помощью
// списка инициализации
Point_t::Point_t(float ax, float ay) : x(ax), y(ay) {}
Point_t::Point_t() : x(0), y(0) {}

// Обычные методы класса Point_t:
float Point_t::get_x() const 
{
	return x;
}

float Point_t::get_y() const 
{
	return y;
}
void Point_t::set_x(float x) 
{
	this->x = x;
}
void Point_t::set_y(float y) 
{
	this->y = y;
}

float Point_t::norm() const 
{
	return sqrtf(x*x + y*y);
}

void Point_t::normalize() 
{
	float pnorm = norm();
	this->x /= pnorm;
	this->y /= pnorm;
}

float Point_t::distance(const Point_t& p) const 
{
	return sqrtf((p.x - x)*(p.x - x) + (p.y - y)*(p.y - y));
}

Point_t Point_t::operator + (const Point_t& right) const 
{
	Point_t result = {x + right.x, y + right.y};
	return result;
}

Point_t Point_t::operator * (float a) const 
{
	Point_t result = {a * x, a * y};
	return result;
}



// Дружественные функции класса Point_t
Point_t operator * (float a, const Point_t& p) 
{
	Point_t result = {a * p.x, a * p.y};
	return result;
}

std::ostream& operator << (std::ostream& left, const Point_t& right) 
{
	left << "(" << right.x << ", " << right.y << ")";
	return left;
}