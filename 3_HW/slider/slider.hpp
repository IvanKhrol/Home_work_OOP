#pragma once

#include <iostream>
#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
//======================================================================================================

//-----------------------------------------------------------------------------------------------------------
//												ОПИСАНИЕ ВСПОМОГАТЕЛЬНЫХ ФУНКЦИЙ														
//-----------------------------------------------------------------------------------------------------------  
void drawLine(sf::RenderWindow& window, sf::Vector2f start, sf::Vector2f finish, sf::Color color);      // рисует линию на холсте
void createRect(sf::RectangleShape& rect, sf::Vector2f size, sf::Vector2f position, sf::Color color);   // создаёт прямоугольник
bool isBelongs(sf::Vector2f start_rect, sf::Vector2f size_rect, sf::Vector2f point);                    // проверка напринадлежность квадрату
bool isBelongs(sf::RectangleShape rect, sf::Vector2f point);

//-----------------------------------------------------------------------------------------------------------
//								    ВСПОМОГАТЕЛЬНАЯ СТРУКТУРА ТОЧКИ														
//-----------------------------------------------------------------------------------------------------------
struct Point_t
{
    float x_;
    float y_;

    Point_t();
    Point_t(float x, float y);  

    ~Point_t();

    void draw();
};
//-----------------------------------------------------------------------------------------------------------
//								Класс Slider - описывает этемент интерфейса - ползунок														
//-----------------------------------------------------------------------------------------------------------   
class Slider
{
private:
    long long int min_, max_;
    long long int cur_ = 50;
public:
    sf::RectangleShape main_rect, slide_rect;
    Slider();
    Slider(sf::Vector2f position, sf::Vector2f main_size, long long int min, long long int max);
    ~Slider();

    long long int getCur();
    long long int getMin();
    long long int getMax();
    void setCur(sf::Vector2f new_position);
};