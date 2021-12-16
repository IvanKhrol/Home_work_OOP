#pragma once

#include <iostream>
#include <cmath>
#include <list>
#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
//===========================================================================================================

float distance(sf::Vector2f start, sf::Vector2f finish);
//-----------------------------------------------------------------------------------------------------------
void drawLine(sf::RenderWindow& window, sf::Vector2f start, sf::Vector2f finish, sf::Color color);
//-----------------------------------------------------------------------------------------------------------
//-----------------------------------------------------------------------------------------------------------

//-----------------------------------------------------------------------------------------------------------
// Вспомагательный класс, описывет шарик
// position - положение шарика; radius - радиус
// is_chosen - говорит о том, выбран ли шарик или нет
//-----------------------------------------------------------------------------------------------------------
class Ball
{
private:
    sf::Vector2f position_;
    float radius_;
    sf::Color color_;

public:
    bool isChoosen;
//-----------------------------------------------------------------------------------------------------------
    Ball(sf::Vector2f position, float radius, sf::Color color);
//-----------------------------------------------------------------------------------------------------------
    // Метод, который рисует шарик на холстек окна window
    void draw(sf::RenderWindow& window) const;
//-----------------------------------------------------------------------------------------------------------
//												GET														
//-----------------------------------------------------------------------------------------------------------
    sf::Vector2f getPosition() const;
//-----------------------------------------------------------------------------------------------------------
    float getRadius() const;
//-----------------------------------------------------------------------------------------------------------
};

