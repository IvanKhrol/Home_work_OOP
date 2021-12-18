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
    sf::Text text_;
    bool isMoving = false;

    Slider(sf::Font& font);
    Slider(sf::Vector2f position, sf::Vector2f main_size, sf::Font& font, long long int min, long long int max);
    ~Slider();

    void draw(sf::RenderWindow& window) const;
    void chang_slider_pos(const sf::Vector2f mouse_position);
    void pressed(const sf::Vector2f mouse_position);
    void move(const sf::Vector2f mouse_position);
    

    long long int getCur() const;
    long long int getMin() const;
    long long int getMax() const;
    void setCur(const sf::Vector2f mouse_position);
};