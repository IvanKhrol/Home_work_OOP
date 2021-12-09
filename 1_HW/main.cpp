#include "Vector3f.hpp"
#include "Complex.hpp"

int main()
{
    Vector3f_t a = {1.0, 2.0, -2.0};
    Vector3f_t b = {4.0, -1.0, 3.0};
    std::cout << "a = " << a << "b = " << b << std::endl;
    std::cout << "a + b = " << a + b << std::endl;
    std::cout << "-a = " << -a << std::endl;
    std::cout << "Scalar product of a and b = " << a * b << std::endl;
    a /= 5;
    std::cout << "a after a /= 5;" << a << std::endl;
    normalize(b);
    std::cout << "Normalized b:" << b << std::endl;
    a += b;
    std::cout << "a after a+= b;" << a << std::endl;
//-----------------------------------------------------------------------------------------------------------
//-----------------------------------------------------------------------------------------------------------
	Complex_t z1(3,  4);
	Complex_t z2(-1, 8);
	z1.Print();
	z2.Print();
	std::cout << std::endl;
	
	std::cin >> z1;
	z1.Print();

}