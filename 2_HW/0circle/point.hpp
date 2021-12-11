#pragma once


// Поля x и y сделаны приватными
// Конкретно для этого класса их можно было сделать публичными
// Так как пользователь всё-равно будет иметь доступ без ограничений 
// к этим полям через геттеры и сеттеры
// Но они сделаны приватными для образовательных целей

class Point_t
{
private:
	float x, y;
	
public:
	// Конструкторы:
	Point_t(float x, float y);
	Point_t();
	// Методы класса
	float get_x() const;
	float get_y() const;
	void set_x(float x);
	void set_y(float y);

	void normalize();
	float distance(const Point_t& p) const;
	float norm() const;
	Point_t operator + (const Point_t& right) const;
	Point_t operator * 
	(float a) const;

	// Прототипы дружественных функций:
	// Дружественные функции - это обычные функции (а не методы),
	// которые имеют доступ к приватной части класса
	friend Point_t operator * (float a, const Point_t& p);
	friend std::ostream& operator << (std::ostream& left, const Point_t& right);
};


