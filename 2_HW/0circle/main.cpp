#include <iostream>
#include <cmath>
#include "point.hpp"
#include "circle.hpp"

//-----------------------------------------------------------------------------------------------------------
//												MAIN														
//-----------------------------------------------------------------------------------------------------------
int main()
{
	Point_t p = {7, -1};
	Point_t q = {-4, 2};
	std::cout << "Point p = " << p <<   std::endl;
	std::cout << "Point q = " << q <<   std::endl;
	std::cout << "p + q = " << p + q << std::endl;


	Circle_t a {{4, 1}, 3};
	Circle_t b;

	std::cout << "Circle a: center: " << a.get_center() << " radius: " << a.get_radius() << std::endl; 
	std::cout << "Circle b: center: " << b.get_center() << " radius: " << b.get_radius() << std::endl;

	std::cout << "Area of a = " << a.get_area() << std::endl;
	std::cout << "Distance from point p to circle a = " << a.get_distance(p) << std::endl;



	std::cout << "Collisions:" << std::endl;
	if (a.isColliding(b))
		std::cout << "Yes, a is colliding b" << std::endl;
	else
		std::cout << "No, a isn't colliding b" << std::endl;



	std::cout << std::endl << "Moving b by {1, 1}:" << std::endl;
	b.move({1, 1});
	if (a.isColliding(b))
		std::cout << "Yes, a is colliding b" << std::endl;
	else
		std::cout << "No, a isn't colliding b" << std::endl;
}