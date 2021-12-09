#include <SFML/Graphics.hpp>
#include <Windows.h>
#include <cstdlib>
#include "Complex.hpp"

/*
    Первый и второй агрумент - координаты центра
    Третий и четвертый       - координаты точки с
    Пятый аргумент           - радиус
*/

//-----------------------------------------------------------------------------------------------------------
//-----------------------------------------------------------------------------------------------------------
struct Color
{
    unsigned char r, g, b;
};
//-----------------------------------------------------------------------------------------------------------
//-----------------------------------------------------------------------------------------------------------
int  number_it(Complex_t z, Complex_t c, int n, Complex_t centre, double dist);
void iteration(Complex_t &z, Complex_t c);
//-----------------------------------------------------------------------------------------------------------
//												MAIN														
//-----------------------------------------------------------------------------------------------------------
int main(int argc, char **argv)
{                      
    int width = 10000, height = 10000;
    double x0 = atof(argv[1]) - atof(argv[5]), x1 = atof(argv[1]) + atof(argv[5]);
    double y0 = atof(argv[2]) - atof(argv[5]), y1 = atof(argv[2]) + atof(argv[5]);
    Complex_t centre {atof(argv[1]), atof(argv[2])};
    int n = 150;

    // std::cout << x0 << ", " << y0 << " ; " << x1 << ", " << y1 << std::endl; 
    Color* data = new Color [width * height];
    Complex_t z{atof(argv[3]), atof(argv[4])};
    // z.Print();


    for(int j = 0; j < height; ++j)
    {
        for(int i = 0; i < width; i++)
        {
            Complex_t c = {x0 + (double)(x1-x0) / width * i, y0 + (double)(y1-y0) / width * j}; 
            // c.Print();
            // std::cout << (x1 - x0) << std::endl;
            int clr = number_it(c, z, n, centre, atof(argv[5]));
            data[i + width * j].r = 0 + (double)0 * clr / n;
            data[i + width * j].g = 0 + (double)255 * clr / n;
            data[i + width * j].b = 0 + (double)255 * 2 * clr / n;
        }
    }

    FILE* file = fopen("julia.ppm", "wb");
	fprintf(file, "P6\n%d %d\n255\n", width, height);
	fwrite(data, sizeof(Color), height * width, file);
	fclose(file);

	delete [] data;

	return 0;
}
//-----------------------------------------------------------------------------------------------------------
//-----------------------------------------------------------------------------------------------------------
int number_it(Complex_t z, Complex_t c, int n, Complex_t centre, double dist)
{
    for(int i = 0; i < n; ++i)
    {
        iteration(z, c);
        if(z.re * z.re + z.im * z.im > (centre.re - dist) * (centre.re - dist) + (centre.im - dist) * (centre.im - dist))
            return i;
    }
    return n;
}

void iteration(Complex_t &z, Complex_t c)
{
    z= z * z + c;
}