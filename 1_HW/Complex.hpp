#include <cstdio>
#include <iostream>
#include <cmath>

class Complex_t 
{
	private:
		
//-----------------------------------------------------------------------------------------------------------
	public:
		double re, im;
//-----------------------------------------------------------------------------------------------------------
		Complex_t(double x = 0, double y = 0):
			re(x),
			im(y)
		{};
//-----------------------------------------------------------------------------------------------------------
		~Complex_t() = default;
//-----------------------------------------------------------------------------------------------------------
		Complex_t &operator = (Complex_t &other)
    	{
    	    this->re = other.re;
    	    this->im = other.im;
    	    return *this;
    	}
		Complex_t &operator = (Complex_t &&other)
        {
            this->re = other.re;
            this->im = other.im;
            return *this;
        }
//-----------------------------------------------------------------------------------------------------------
		Complex_t(Complex_t &other)
        {
            this->re = other.re;
            this->im = other.im;
        }
        Complex_t(Complex_t &&other)
        {
            this->re = other.re;
            this->im = other.im;
        }
//-----------------------------------------------------------------------------------------------------------
//											СЛОЖЕНИЕ +=
//-----------------------------------------------------------------------------------------------------------
		Complex_t &operator += (Complex_t &other)
		{
			this->re += other.re;
			this->im += other.im;
			return *this;
		}
		Complex_t &operator += (Complex_t &&other)
		{
			this->re += other.re;
			this->im += other.im;
			return *this;
		}
//-----------------------------------------------------------------------------------------------------------
		Complex_t &operator += (double x)
		{
			this->re += x;
			return *this;
		}
//-----------------------------------------------------------------------------------------------------------
//											ВЫЧИТАНИЕ -=
//-----------------------------------------------------------------------------------------------------------
		Complex_t &operator -= (Complex_t &other)
		{
			this->re -= other.re;
			this->im -= other.im;
			return *this;
		}
		Complex_t &operator -= (Complex_t &&other)
		{
			this->re -= other.re;
			this->im -= other.im;
			return *this;
		}
//-----------------------------------------------------------------------------------------------------------
		Complex_t &operator -= (double x)
		{
			this->re -= x;
			return *this;
		}
//-----------------------------------------------------------------------------------------------------------
//											УМНОЖЕНИЕ *=
//-----------------------------------------------------------------------------------------------------------
		Complex_t &operator *= (Complex_t &other)
		{
			double tmp_re = this->re, tmp_im = this->im;
			this->re = (tmp_re * other.re - tmp_im * other.im);
			this->im = (tmp_re * other.im + tmp_im * other.re);
			return *this;
		}
		Complex_t &operator *= (Complex_t &&other)
		{
			double tmp_re = this->re, tmp_im = this->im;
			this->re = (tmp_re * other.re - tmp_im * other.im);
			this->im = (tmp_re * other.im + tmp_im * other.re);
			return *this;
		}
//-----------------------------------------------------------------------------------------------------------
		Complex_t &operator *= (double x)
		{
			this->re *= x;
			this->im *= x;
			return *this;
		}
//-----------------------------------------------------------------------------------------------------------
//											ДЕЛЕГИЕ /=
//-----------------------------------------------------------------------------------------------------------
		Complex_t &operator /= (Complex_t &other)
		{
			if(other.re == 0 && other.im == 0)
			{
				std::cout << "Error: dicision by 0\n";
				return *this;
			}

			double tmp_re = this->re, tmp_im = this->im;
			this->re = (tmp_re * other.re + tmp_im * other.im) / (other.re * other.re + other.im * other.im);
			this->im = (tmp_im * other.re - tmp_re * other.im) / (other.re * other.re + other.im * other.im);
			return *this;
		}
		Complex_t &operator /= (Complex_t &&other)
		{
			if(other.re == 0 && other.im == 0)
			{
				std::cout << "Error: dicision by 0\n";
				return *this;
			}

			double tmp_re = this->re, tmp_im = this->im;
			this->re = (tmp_re * other.re + tmp_im * other.im) / (other.re * other.re + other.im * other.im);
			this->im = (tmp_im * other.re - tmp_re * other.im) / (other.re * other.re + other.im * other.im);
			return *this;
		}
//-----------------------------------------------------------------------------------------------------------
		Complex_t &operator /= (double x)
		{
			if(x == 0)
			{
				std::cout << "Error: dicision by 0\n";
				return *this;
			}
			this->re /= x;
			this->im /= x;
			return *this;
		}
//-----------------------------------------------------------------------------------------------------------
//												УНАРНЫЙ МИНУС - 
//-----------------------------------------------------------------------------------------------------------
		Complex_t &operator - ()
		{
			this->re = - this->re;
			this->im = - this->im;
			return *this;
		}
//-----------------------------------------------------------------------------------------------------------
//												УНАРНЫЙ ПЛЮС + 
//-----------------------------------------------------------------------------------------------------------
		Complex_t &operator + ()
		{
			return *this;
		}
//-----------------------------------------------------------------------------------------------------------
//												СОПРЯЖЕНИЕ ~ 
//-----------------------------------------------------------------------------------------------------------
		Complex_t &operator ~ ()
		{
			this->re =   this->re;
			this->im = - this->im;
			return *this;
		}
//-----------------------------------------------------------------------------------------------------------
//-----------------------------------------------------------------------------------------------------------
		Complex_t expZ()
		{
			double tmp = exp(this->re);
			this->re = tmp * cos(this->im);
			this->im = tmp * sin(this->im);
			return *this;
		}
//-----------------------------------------------------------------------------------------------------------
		Complex_t sinZ()
		{
			double tmp = this->re;
			this->re = sin(tmp) * cosh(this->im);
			this->im = cos(tmp) * sinh(this->im);
			return *this;
		}
//-----------------------------------------------------------------------------------------------------------
		double absZ()
		{
			double result = 0;
			result = sqrt(this->re * this->re + this->im * this->im);	
			return result;
		}
//-----------------------------------------------------------------------------------------------------------
		void Print()
		{
			if(this->re != 0)
			{
				if(this->im > 0)
					if(this->im == 1)
						std::cout << this->re << " + i" << std::endl;
					else
						std::cout << this->re << " + " << this->im << "i" << std::endl;					
				else if(this->im < 0)
					if(this->im == -1)
						std::cout << this->re << " - i" << std::endl;
					else
						std::cout << this->re << " - " << -(this->im) << "i" << std::endl;
				else
					std::cout << this->re << std::endl;
			}
			else
			{
				if(this->im != 0)
					if(this->im == 1 )
						std::cout << "i" << std::endl;
					else if(this->im == -1)
						std::cout << "-i" << std::endl;
					else
					std::cout << this->im << "i" << std::endl;
				else
					std::cout << "0\n";
			}
		}
//-----------------------------------------------------------------------------------------------------------
};

//-----------------------------------------------------------------------------------------------------------
//									СЛОЖЕНИЕ
//-----------------------------------------------------------------------------------------------------------
Complex_t operator + (Complex_t &first, Complex_t &second) 
{
	Complex_t result = first;
	result += second;
	return result;
}
Complex_t operator + (Complex_t &first, Complex_t &&second) 
{
	Complex_t result = first;
	result += second;
	return result;
}
Complex_t operator + (Complex_t &&first, Complex_t &second) 
{
	Complex_t result = first;
	result += second;
	return result;
}
Complex_t operator + (Complex_t &&first, Complex_t &&second) 
{
	Complex_t result = first;
	result += second;
	return result;
}
//-----------------------------------------------------------------------------------------------------------
Complex_t operator + (Complex_t &first, double x) 
{
	Complex_t result = first;
	result += x;
	return result;
}
Complex_t operator + (Complex_t &&first, double x) 
{
	Complex_t result = first;
	result += x;
	return result;
}
Complex_t operator + (double x, Complex_t &first) 
{
	Complex_t result = first;
	result += x;
	return result;
}
Complex_t operator + (double x, Complex_t &&first) 
{
	Complex_t result = first;
	result += x;
	return result;
}
//-----------------------------------------------------------------------------------------------------------
//									ВЫЧИТАНИЕ
//-----------------------------------------------------------------------------------------------------------
Complex_t operator - (Complex_t &first, Complex_t &second) 
{
	Complex_t result = first;
	result -= second;
	return result;
}
Complex_t operator - (Complex_t &first, Complex_t &&second) 
{
	Complex_t result = first;
	result -= second;
	return result;
}
Complex_t operator - (Complex_t &&first, Complex_t &second) 
{
	Complex_t result = first;
	result -= second;
	return result;
}
Complex_t operator - (Complex_t &&first, Complex_t &&second) 
{
	Complex_t result = first;
	result -= second;
	return result;
}
//-----------------------------------------------------------------------------------------------------------
Complex_t operator - (Complex_t &first, double x) 
{
	Complex_t result = first;
	result -= x;
	return result;
}
Complex_t operator - (Complex_t &&first, double x) 
{
	Complex_t result = first;
	result -= x;
	return result;
}
Complex_t operator - (double x, Complex_t &first) 
{
	Complex_t result = first;
	result -= x;
	return result;
}
Complex_t operator - (double x, Complex_t &&first) 
{
	Complex_t result = first;
	result -= x;
	return result;
}
//-----------------------------------------------------------------------------------------------------------
//											УМНОЖЕНИЕ
//-----------------------------------------------------------------------------------------------------------
Complex_t operator * (Complex_t &first, Complex_t &second) 
{
	Complex_t result = first;
	result *= second;
	return result;
}
Complex_t operator * (Complex_t &first, Complex_t &&second) 
{
	Complex_t result = first;
	result *= second;
	return result;
}
Complex_t operator * (Complex_t &&first, Complex_t &second) 
{
	Complex_t result = first;
	result *= second;
	return result;
}
Complex_t operator * (Complex_t &&first, Complex_t &&second) 
{
	Complex_t result = first;
	result *= second;
	return result;
}
//-----------------------------------------------------------------------------------------------------------
Complex_t operator * (Complex_t &first, double x) 
{
	Complex_t result = first;
	result *= x;
	return result;
}
Complex_t operator * (Complex_t &&first, double x) 
{
	Complex_t result = first;
	result *= x;
	return result;
}
Complex_t operator * (double x, Complex_t &first) 
{
	Complex_t result = first;
	result *= x;
	return result;
}
Complex_t operator * (double x, Complex_t &&first) 
{
	Complex_t result = first;
	result *= x;
	return result;
}
//-----------------------------------------------------------------------------------------------------------
//											ДЕЛЕНИЕ
//-----------------------------------------------------------------------------------------------------------
Complex_t operator / (Complex_t &first, Complex_t &second) 
{
	Complex_t result = first;
	result /= second;
	return result;
}
Complex_t operator / (Complex_t &first, Complex_t &&second) 
{
	Complex_t result = first;
	result /= second;
	return result;
}
Complex_t operator / (Complex_t &&first, Complex_t &second) 
{
	Complex_t result = first;
	result /= second;
	return result;
}
Complex_t operator / (Complex_t &&first, Complex_t &&second) 
{
	Complex_t result = first;
	result /= second;
	return result;
}
//-----------------------------------------------------------------------------------------------------------
Complex_t operator / (Complex_t &first, double x) 
{
	Complex_t result = first;
	result /= x;
	return result;
}
Complex_t operator / (Complex_t &&first, double x) 
{
	Complex_t result = first;
	result /= x;
	return result;
}
Complex_t operator / (double x, Complex_t &first) 
{
	Complex_t result = first;
	result /= x;
	return result;
}
Complex_t operator / (double x, Complex_t &&first) 
{
	Complex_t result = first;
	result /= x;
	return result;
}
//-----------------------------------------------------------------------------------------------------------
//											СРАВНЕНИЕ ==
//-----------------------------------------------------------------------------------------------------------
bool operator == (Complex_t &first, Complex_t &second)
{
	if((first.re == second.re) && (first.im == second.im))
		return true;
	return false;
}
//-----------------------------------------------------------------------------------------------------------
//												COUT AND CIN
//-----------------------------------------------------------------------------------------------------------
std::ostream &operator << (std::ostream &left, Complex_t &right)  
{
	left << "(" << right.re << ", " << right.im << "i)"; 
	return left;
}
//-----------------------------------------------------------------------------------------------------------
std::istream &operator >> (std::istream &left, Complex_t &right)  
{
	left >> right.re >> right.im; 
	return left;
}
