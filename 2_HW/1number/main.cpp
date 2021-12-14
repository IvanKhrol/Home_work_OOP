#include "number.hpp"
#include <iostream>
//===========================================================================================================

void hail_numbers(Number &hail) ;
//-----------------------------------------------------------------------------------------------------------
//-----------------------------------------------------------------------------------------------------------

int main() 
{
	std::cout << "Enter what you want to check: ";
	std::string str = "";
	std::cin >> str;
	while(str != "exit" )
	{
		if(str == "help")
		{
			std::cout << "fib - Fibonacci; fact - Factorial;hail - Hailstone  Numbers; exit - Stop program\n";
		}else

		// Fibonacci
		if(str == "fib" || str == "Fib")
		{
			Number* F = new Number [3];
			F[0] = 0;
			F[1] = 1;
			int N = 0;
			std::cout << "Enter what Fibonacci number to calculate: ";
			std::cin >> N;
			for(int i = 2; i <= N; ++i)
			{
				//std::cout << i << " " << (i % 3) << " " << ((i - 1) % 3) << " " << ((i - 2) % 3) << std::endl;
				F[i % 3] = F[(i - 1) % 3] + F[(i - 2) % 3];
				//std::cout << F[i % 3] << std::endl;
			}
			std::cout << F[N % 3] << std::endl;
		}else

		// Factorial 
		if(str == "fact" || str == "fact")
		{

				Number fact = 1;
				std::cout << "Enter the factorial number to be calculated: ";
				int n = 1;
				std::cin >> n;
				for(int i = 1; i <= n; ++i)
				{
					// std::cout << i << "  " << fact << std::endl;
					fact *= i;
				}
				std::cout << fact << std::endl; 
		}else

		// Hailstone  Numbers
		if(str == "hail" || str == "Hail")
		{
			std::string num_str;
			std::cout << "Enter the seed for the sequence: ";
			std::cin >> num_str;
			Number num(num_str);
			hail_numbers(num);
		}else
		{
			std::cout << "Unknown operation!\nEnter \"help\" for help\n";
		}

		std::cout << "Enter what you want to check: ";
		std::cin >> str;
	}
	
	return 0;
}

void hail_numbers(Number &hail) 
{
	long long int steps = 1;
	Number max = hail;
	while(hail != 1)
	{
		if(hail.isEven())
			hail.div2();
		else
			hail = hail * 3 + 1;
		if(hail > max)
			max = hail;
		if(hail != 1)
			++steps;
	}
	std::cout << "steps = " << steps << "\tmax = " << max << std::endl;
}