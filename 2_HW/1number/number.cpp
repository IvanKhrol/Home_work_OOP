#include "number.hpp"

//-----------------------------------------------------------------------------------------------------------
//													КОНСТРУКТОРЫ
//-----------------------------------------------------------------------------------------------------------
	// Конструктор, который создаёт наше число из числа типа int
Number::Number(int a) 
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
Number::Number()
	{
		size = 1;
		capacity = 1;
		data = new char[capacity];
		data[0] = 0;
	}
//-----------------------------------------------------------------------------------------------------------
Number::Number(const Number& n)
	{
		size = n.size;
		capacity = n.capacity;
		data = new char[capacity] {};
		for(int i = 0; i < size; ++i)
			data[i] = n.data[i];
	}
//-----------------------------------------------------------------------------------------------------------
Number::Number(const std::string str)
	{
		size_t t_sz = str.size();
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
Number::~Number() 
	{
		delete [] data;
	}
//-----------------------------------------------------------------------------------------------------------
//												ПРИСВАИВАНИЕ =														
//-----------------------------------------------------------------------------------------------------------
Number& Number::operator = (const Number& right)
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
Number& Number::operator += (const Number& right)
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
Number& Number::operator *= (const Number& right)
	{
		if((int)this->data[this->size - 1] == 0 || (int)right.data[right.size - 1] == 0)
			return (*this = 0);

		size_t max_size = 2 * std::max(this->size, right.size) + 2;
		if(this->capacity <= max_size)
			this->resize(max_size);


		Number tmp = 0, new_num = 0;

		tmp.resize(max_size);
		// new_num.resize(max_size);	

		long long int cur = 0, ost = 0;
		for(int j = 0; j < right.size; ++j)
		{
			tmp.size = j + this->size;
			ost = 0;

			for(int i = 0; i < this->size; ++i)
			{
				cur = this->data[i] * right.data[j] + ost;
				tmp.data[i + j] = cur  % this->base;
				// std::cout << tmp << std::endl;
				ost = cur / this->base;
				// std::cout << "(" << j << "; " << i << ")  " << cur << "  " << tmp << std::endl;	
			}
			if(ost != 0)
			{
				tmp.data[tmp.size] = ost;
				++tmp.size;
			}
			// std::cout << tmp.size << std::endl;
			// std::cout << "Gay?" << std::endl;

			new_num += tmp;
			// std::cout << new_num << std::endl;
		}
		this->capacity = new_num.capacity;
		this->size	   = new_num.size;
		std::swap(this->data, new_num.data);
		return *this;
	}
//-----------------------------------------------------------------------------------------------------------
//												OPERATORS COMPARISONS														
//-----------------------------------------------------------------------------------------------------------
bool Number::operator == (const Number &other) const
	{
		if(this->size != other.size)
			return false;
		
		for(int i = 0; i < this->size; ++i)
		{
			if(this->data[i] != other.data[i])
				return false;
		}

		return true;
	} 
//-----------------------------------------------------------------------------------------------------------
bool Number::operator != (const Number &other) const
	{
		return !(*this == other);
	}
//-----------------------------------------------------------------------------------------------------------
bool Number::operator > (const Number &other) const 
	{
		if(this->size > other.size)
			return true;
		if(this->size < other.size)
			return false;
		
		for(int i = this->size - 1; i >= 0; --i)
		{
			if(this->data[i] > other.data[i])
				return true;
			if(this->data[i] != other.data[i])
				return false;
		}

		return false;
	}
//-----------------------------------------------------------------------------------------------------------
bool Number::operator >= (const Number &other) const
	{
		if(*this == other || *this > other)
			return true;
		return false;
	}
//-----------------------------------------------------------------------------------------------------------
bool Number::operator < (const Number &other) const
	{
		return !(*this >= other);
	}
//-----------------------------------------------------------------------------------------------------------
bool Number::operator <= (const Number &other) const
	{
		return !(*this > other);
	}
//-----------------------------------------------------------------------------------------------------------
//-----------------------------------------------------------------------------------------------------------
void Number::div2()
	{
		int ost = 0, cur = 0;
		for (int i = this->size - 1; i >= 0; --i) {
			cur = this->data[i] + ost * this->base;
			this->data[i] = cur / 2 ;
			ost = cur % 2;
		}
		if (this->size != 0 && this->data[size - 1] == 0)
			this->size--;
	}
//-----------------------------------------------------------------------------------------------------------
//-----------------------------------------------------------------------------------------------------------
void Number::resize(size_t new_capacity)
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
bool Number::isEven() const
	{
		if(this->data[0] % 2 == 0)
			return true;
		return false;
	}
//-----------------------------------------------------------------------------------------------------------
//												GET														
//-----------------------------------------------------------------------------------------------------------
// size, base, capacity, data
int    Number::getBase() 	 const {return this->base	 ;}
size_t Number::getSize() 	 const {return this->size	 ;}
size_t Number::getCapacity() const {return this->capacity;}
char*  Number::getData()     const {return this->data	 ;}



// Печать нашего числа на экран
// Эта функция может использовать приватные поля, так как она дружественная
//-----------------------------------------------------------------------------------------------------------
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
Number operator * (const Number& left, const Number& right)
{
	Number result = left;
	result *= right;
	return result;
}
//-----------------------------------------------------------------------------------------------------------
//-----------------------------------------------------------------------------------------------------------


