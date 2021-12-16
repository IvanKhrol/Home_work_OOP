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
//----------------------------------------------------------------------------------------------------------
bool isBelongs(sf::Vector2f start, sf::Vector2f end, sf::Vector2f point)
{
    Point_t  left_top;
    Point_t right_bot;
    if((start.y + end.y > start.y))
    {
        left_top.y_ = start.y;
        right_bot.y_ = start.y + end.y;
    }else
    {
        right_bot.y_ = start.y;
        left_top.y_  = start.y + end.y;
    }

    if((start.x + end.x > start.x))
    {
        left_top.x_ = start.x;
        right_bot.x_ = start.x + end.x;
    }else
    {
        right_bot.x_ = start.x;
        left_top.x_  = start.x + end.x;
    }
    // left_top.draw();
    // right_bot.draw();
    if((-(point.x - left_top.x_)     * (right_bot.y_ - left_top.y_)  < 0) &&
       ((right_bot.x_ - left_top.x_) * (point.y - left_top.y_)       > 0) && 
       (-(point.x - right_bot.x_)    * (right_bot.y_ - left_top.y_)  > 0) &&
       ((left_top.x_ - right_bot.x_) * (point.y - right_bot.y_)      > 0))
            return true;

    return false;
}

//-----------------------------------------------------------------------------------------------------------
//												POINT														
//-----------------------------------------------------------------------------------------------------------
Point_t::Point_t() : x_(0), y_(0) {}
//-----------------------------------------------------------------------------------------------------------
Point_t::Point_t(float x , float y) : x_(x), y_(y) {}
//-----------------------------------------------------------------------------------------------------------
Point_t::~Point_t() {}
//-----------------------------------------------------------------------------------------------------------
//-----------------------------------------------------------------------------------------------------------
void Point_t::draw()
{
    std::cout << "(" << x_ << ", " << y_ << ")\n";
}

//-----------------------------------------------------------------------------------------------------------
//												BALL														
//-----------------------------------------------------------------------------------------------------------

//-----------------------------------------------------------------------------------------------------------
//-----------------------------------------------------------------------------------------------------------
Ball::Ball(sf::Vector2f position, float radius) : position_(position), radius_(radius)
{
        this->isChoosen = false;
}
//-----------------------------------------------------------------------------------------------------------
Ball::Ball(sf::Vector2f position, float radius, sf::Color color) : position_(position), radius_(radius), color_(color)
{
        this->isChoosen = false;
}
//-----------------------------------------------------------------------------------------------------------
Ball::~Ball()
{

}
//-----------------------------------------------------------------------------------------------------------
// Метод, который рисует шарик на холстек окна window
void Ball::draw(sf::RenderWindow& window) const
{
    // Тут рисуем белый кружочек
    sf::CircleShape circle(this->radius_);
    circle.setFillColor(color_);
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
//-----------------------------------------------------------------------------------------------------------
sf::Color Ball::getColor() const
{
    return this->color_;
}
//-----------------------------------------------------------------------------------------------------------
//												SET														
//-----------------------------------------------------------------------------------------------------------
void Ball::setColor(const sf::Color color)
{
    this->color_ = color;
}
//-----------------------------------------------------------------------------------------------------------
void Ball::setPosition(const sf::Vector2f new_position)
{
    this->position_.x = new_position.x;
    this->position_.y = new_position.y;    
}
//-----------------------------------------------------------------------------------------------------------
void Ball::setRadius(const float new_radius)
{
    this->radius_ = new_radius;
}