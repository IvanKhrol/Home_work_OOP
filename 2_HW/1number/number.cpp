#include <iostream>
#include <iomanip>
#include <vector>
#include <algorithm>
#include <cstring>

/*
	Класс Number -- класс положительных больших чисел

	Большое число будет храниться в динамическом массиве data
	Каждый элемент этого массива содержит разряд числа в 100-ричной системе счисления
	(так как base = 100)
	По сути, каждый элемент data хранит две цифры числа в десятичной записи

	Значение 100 для системы счисления выбрано как компромис между
	эффективностью и удобством написания программы.
	Если выбрать значения базы 10 - то программа будет не так эффективна по памяти
	Если выбрать значения базы 256 (максимально эффективное использование памяти для типа char),
	то алгоритм печати на экран сильно усложнится
	В качестве альтернативы, можно было выбрать базу 1e9, 
	изменив при этом тип элементов c char на int

	capacity - размер массива data
	size - сколько ячеек занимет число в массиве data
	size <= capacity

	Для удобства разряды числа хранятся в обратном порядке
	Например, число 12345678 соответствует массиву
	data = {78, 56, 34, 12}
	(это упрощает многие алгоритмы с такими числами)
*/


class Number
{
private:
	static const int base = 100;
	size_t size;
	size_t capacity;
	char* data;
//-----------------------------------------------------------------------------------------------------------
//													КОНСТРУКТОРЫ
//-----------------------------------------------------------------------------------------------------------
public:
	// Конструктор, который создаёт наше число из числа типа int
	Number(int a) 
	{
		// Находим размер необходимой памяти под это число
		int temp = a;
		capacity = 0;
		while(temp != 0) 
		{
			temp /= base;
			++capacity;
		}
		// Отдельно обрабатываем случай, когда число равно 0
		if (capacity == 0) 
		{
			capacity = 1;
		}
		// Выделяем память
		data = new char[capacity];
		// Записывем число a в массив data
		// Например, число 12345678 представится в виде массива [78, 56, 34, 12]
		for (int i = 0; i < capacity; ++i) 
		{
			data[i] = a % base;
			a /= base;
		}
		// В данном случае размер будет равен вместимости
		size = capacity;
	}
//-----------------------------------------------------------------------------------------------------------
	Number()
	{
		size = 1;
		capacity = 1;
		data = new char[capacity];
		data[0] = 0;
	}
//-----------------------------------------------------------------------------------------------------------
	Number(const Number& n)
	{
		size = n.size;
		capacity = n.capacity;
		data = new char[capacity] {};
		for(int i = 0; i < size; ++i)
			data[i] = n.data[i];
	}
//-----------------------------------------------------------------------------------------------------------
	Number(const char* str)
	{
		size_t t_sz = strlen(str);
		capacity = t_sz % 2 + t_sz / 2;
		size = capacity;
		data = new char[capacity];
		for(int i = 0; i < size - 1; ++i)
		{
			//std::cout << "i: " << i << "\t" << str[t_sz - 2 * i - 1] << " " << str[t_sz - 2 * i - 2] << std::endl;
			data[i] = (str[t_sz - 2 * i - 1] - '0') + (str[t_sz - 2 * i - 2] - '0') * 10;
		}
		if(t_sz % 2 == 1)
			data[size - 1] = str[0] - '0';
		else
			data[size - 1] = (str[1] - '0') + (str[0] - '0') * 10;
	}
//-----------------------------------------------------------------------------------------------------------
//												ДЕСТРУКТОР
//-----------------------------------------------------------------------------------------------------------
	~Number() 
	{
		delete [] data;
	}
//-----------------------------------------------------------------------------------------------------------
//												ПРИСВАИВАНИЕ =														
//-----------------------------------------------------------------------------------------------------------
	Number& operator = (const Number& right)
	{
		if(this == &right)
			return *this;
		this->size = right.size;
		this->capacity = right.capacity;
		delete [] this->data;
		data = new char[this->capacity];
		for(int i = 0; i < this->size; ++i)
			data[i] = right.data[i];
		return *this;
	}
//-----------------------------------------------------------------------------------------------------------
//												СЛОЖЕНИЕ +=														
//-----------------------------------------------------------------------------------------------------------
	Number& operator += (const Number& right)
	{
		size_t max_size = std::max(this->size, right.size);
		if(this->capacity <= max_size)
		{
			this->resize(max_size + 2);
		}
		this->size = max_size;

		int ost = 0, cur = 0;
		for(int i = 0; i < max_size; ++i)
		{
			cur = 0;
			if(i < right.size)
				cur = right.data[i];
			
			cur += ost + this->data[i];

			this->data[i] = cur % this->base;
			ost = cur / this->base;
		}

		if(ost != 0)
		{
			this->data[this->size] = ost;
			++this->size;
		}
		return *this;
	}
//-----------------------------------------------------------------------------------------------------------
//												УМНОЖЕНИЕ *=														
//-----------------------------------------------------------------------------------------------------------
	Number& operator *= (const Number& right)
	{
		if((int)this->data[this->size - 1] == 0 || (int)right.data[right.size - 1] == 0)
			return (*this = 0);
		// for(int i = 0; i < this->size; ++i)
			// std::cout << (int)this->data[size - 1] << std::endl;
		size_t max_size = this->size + right.size + 1;
		if(this->capacity <= max_size)
			this->resize(max_size);
		// this->size = max_size;
		// std::cout << max_size << std::endl;
		Number tmp = 0, new_num = 0;
		int cur = 0, ost = 0;
		for(int j = 0; j < right.size; ++j)
		{
			tmp = 0;
			tmp.size = (j != 0) ? j : 1;
			ost = 0;
			cur = 0;
			for(int i = 0; i < this->size; ++i)
			{
				cur = this->data[i] * right.data[j] + ost;
				tmp.data[i + j] = cur  % this->base;
				// std::cout << tmp << std::endl;
				ost = cur / this->base;
				// std::cout << "(" << j << "; " << i << ")  " << cur << "  " << tmp << std::endl;	
				// std::cout << cur << std::endl;
				++tmp.size;
			}
			if(ost != 0)
			{
				tmp.data[tmp.size - 1] = ost;
				// ++tmp.size;
			}
			// std::cout << tmp << std::endl;
			new_num += tmp;
			// std::cout << new_num << std::endl;
		}
		
		*this = new_num;
		return *this;
	}
//-----------------------------------------------------------------------------------------------------------
//-----------------------------------------------------------------------------------------------------------
	void resize(size_t new_capacity)
	{
		char* new_data = new char[new_capacity] {};
		size_t copy_size = std::min(new_capacity, this->capacity);
		this->capacity = new_capacity;
		// std::cout << "Capacity: " << copy_size << " " << new_capacity << std::endl;
		for(int i = 0; i < copy_size; ++i)
		{
			new_data[i] = this->data[i];
			// std::cout << new_data[i] << std::endl; 
		}
		for(int  i = copy_size; i < new_capacity; ++i)
		{
			new_data[i] = '\0';
		}
		delete [] this->data;
		this->data = new_data;
	}
//-----------------------------------------------------------------------------------------------------------
//-----------------------------------------------------------------------------------------------------------
	bool isEven() const
	{
		if(this->data[0] % 2 == 0)
			return true;
		return false;
	}
//-----------------------------------------------------------------------------------------------------------
	// Дружественная функция печати на экран
	friend std::ostream& operator <<(std::ostream& stream, const Number& right);
//-----------------------------------------------------------------------------------------------------------
//												GET														
//-----------------------------------------------------------------------------------------------------------
// size, base, capacity, data
int    getBase() 	 const {return this->base	 ;}
size_t getSize() 	 const {return this->size	 ;}
size_t getCapacity() const {return this->capacity;}
char*  getData()     const {return this->data	 ;}
};


// Печать нашего числа на экран
// Эта функция может использовать приватные поля, так как она дружественная
std::ostream& operator <<(std::ostream& stream, const Number& right) 
{
	// Печатаем самый большой разряд
	stream << (int)right.data[right.size - 1];

	// Печатаем остальные разряды с заполнением нулями до 2-х цифр
	// setfill и setw это то же самое, что и в языке C спецификатор %02d
	for (size_t i = 0; i < right.size - 1; ++i) 
	{
		stream << std::setfill('0') << std::setw(2) << (int)right.data[right.size - 2 - i];
	}
	return stream;
}
//-----------------------------------------------------------------------------------------------------------
Number operator + (const Number& left, const Number& right)
{
	Number result = left;
	result += right;
	return result;
}
//-----------------------------------------------------------------------------------------------------------
//-----------------------------------------------------------------------------------------------------------


int main() 
{

	// Number* F = new Number [3];
	// F[0] = 0;
	// F[1] = 1;
	// int N = 0;
	// std::cout << "Vvedite kakoe chislo Fibonachchi vychislit': ";
	// std::cin >> N;
	// for(int i = 2; i <= N; ++i)
	// {
	// 	//std::cout << i << " " << (i % 3) << " " << ((i - 1) % 3) << " " << ((i - 2) % 3) << std::endl;
	// 	F[i % 3] = F[(i - 1) % 3] + F[(i - 2) % 3];
	// 	//std::cout << F[i % 3] << std::endl;
	// }
	// std::cout << F[N % 3] << std::endl;

	Number y = 123456789;
	Number x = 123456789;
	x *= y;
	std::cout << x << std::endl;
	
	

	return 0;
}