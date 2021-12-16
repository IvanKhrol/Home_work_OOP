#include "ball.hpp"
//===========================================================================================================


using namespace std;
//-----------------------------------------------------------------------------------------------------------
//                      Вспомогательные функции, вычисляет расстояние между двумя точками																										
//-----------------------------------------------------------------------------------------------------------
float distance(sf::Vector2f start, sf::Vector2f finish)
{
    return sqrtf((start.x - finish.x) * (start.x - finish.x) + (start.y - finish.y) * (start.y - finish.y));
}
//-----------------------------------------------------------------------------------------------------------
//							Вспомогательные функции, рисует линию на холсте окна window														
//-----------------------------------------------------------------------------------------------------------
void drawLine(sf::RenderWindow& window, sf::Vector2f start, sf::Vector2f finish, sf::Color color = sf::Color::White)
{
    sf::Vertex line_vertices[2] = {sf::Vertex(start, color), sf::Vertex(finish, color)};
    window.draw(line_vertices, 2, sf::Lines);
}
//-----------------------------------------------------------------------------------------------------------
//-----------------------------------------------------------------------------------------------------------
Ball::Ball(sf::Vector2f position, float radius, sf::Color color = sf::Color::White) : position_(position), radius_(radius), color_(color)
{
        this->isChoosen = false;
}
//-----------------------------------------------------------------------------------------------------------
// Метод, который рисует шарик на холстек окна window
void Ball::draw(sf::RenderWindow& window) const
{
    // Тут рисуем белый кружочек
    sf::CircleShape circle(this->radius_);
    circle.setFillColor(sf::Color::White);
    circle.setOrigin({this->radius_, this->radius_});
    circle.setPosition(this->position_);
    window.draw(circle);

    // Если шарик выбран
    if(isChoosen) 
    {
        // То рисуем "уголки"
        const float fraction = 0.7;
        drawLine(window, {position_.x - radius_, position_.y + radius_}, {position_.x - radius_, position_.y + radius_ * fraction});
        drawLine(window, {position_.x - radius_, position_.y + radius_}, {position_.x - fraction * radius_, position_.y + radius_});

        drawLine(window, {position_.x + radius_, position_.y + radius_}, {position_.x + radius_, position_.y + radius_ * fraction});
        drawLine(window, {position_.x + radius_, position_.y + radius_}, {position_.x + radius_ * fraction, position_.y + radius_});

        drawLine(window, {position_.x + radius_, position_.y - radius_}, {position_.x + radius_ * fraction, position_.y - radius_});
        drawLine(window, {position_.x + radius_, position_.y - radius_}, {position_.x + radius_, position_.y - radius_ * fraction});

        drawLine(window, {position_.x - radius_, position_.y - radius_}, {position_.x - radius_ * fraction, position_.y - radius_});
        drawLine(window, {position_.x - radius_, position_.y - radius_}, {position_.x - radius_, position_.y - radius_ * fraction});
    }
}
//-----------------------------------------------------------------------------------------------------------
//												GET														
//-----------------------------------------------------------------------------------------------------------
sf::Vector2f Ball::getPosition() const
{
    return this->position_;
}
//-----------------------------------------------------------------------------------------------------------
float Ball::getRadius() const
{
    return this->radius_;
}