#include "slider.hpp"

//===========================================================================================================

//-----------------------------------------------------------------------------------------------------------
//							Вспомогательные функции, рисует линию на холсте окна window														
//-----------------------------------------------------------------------------------------------------------
void drawLine(sf::RenderWindow& window, sf::Vector2f start_rect, sf::Vector2f finish, sf::Color color = sf::Color::White)
{
    sf::Vertex line_vertices[2] = {sf::Vertex(start_rect, color), sf::Vertex(finish, color)};
    window.draw(line_vertices, 2, sf::Lines);
}
//-----------------------------------------------------------------------------------------------------------
//                                              CОЗДАЁТ ПРЯМОУГОЛЬНИК
//-----------------------------------------------------------------------------------------------------------
void createRect(sf::RectangleShape& rect, sf::Vector2f size, sf::Vector2f position, sf::Color color = sf::Color::White)
{
    rect.setSize(size);
    // rect.setOrigin(size.x / 2, size.y / 2);
    rect.setPosition({position.x - size.x / 2, position.y - size.y / 2 });
    rect.setFillColor(color);
}
//-----------------------------------------------------------------------------------------------------------
//									    ПРОВЕРКА НА ПРИНАДЛЕЖНОСТЬ КВАРДРАТУ														
//-----------------------------------------------------------------------------------------------------------
bool isBelongs(sf::Vector2f start_rect, sf::Vector2f size_rect, sf::Vector2f point)
{
    // std::cout << start_rect.x << " " << start_rect.y << std::endl;
    // std::cout << size_rect.x << " " <<  size_rect.y << std::endl;
    Point_t  left_top;
    Point_t right_bot;
    if((start_rect.y + size_rect.y > start_rect.y))
    {
        left_top.y_ = start_rect.y;
        right_bot.y_ = start_rect.y + size_rect.y;
    }else
    {
        right_bot.y_ = start_rect.y;
        left_top.y_  = start_rect.y + size_rect.y;
    }

    if((start_rect.x + size_rect.x > start_rect.x))
    {
        left_top.x_ = start_rect.x;
        right_bot.x_ = start_rect.x + size_rect.x;
    }else
    {
        right_bot.x_ = start_rect.x;
        left_top.x_  = start_rect.x + size_rect.x;
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
//											CLASS POINT														
//-----------------------------------------------------------------------------------------------------------
// Конструктор по умолчанию
Point_t::Point_t() : x_(0), y_(0) {}
//-----------------------------------------------------------------------------------------------------------
// Основной конструктор
Point_t::Point_t(float x , float y) : x_(x), y_(y) {}
//-----------------------------------------------------------------------------------------------------------
Point_t::~Point_t() {}
//-----------------------------------------------------------------------------------------------------------
// Выввод точки
void Point_t::draw()
{
    std::cout << "(" << x_ << ", " << y_ << ")\n";
}
//-----------------------------------------------------------------------------------------------------------
//												CLASS SLIDER														
//-----------------------------------------------------------------------------------------------------------  
// Конструктор по умолчанию
Slider::Slider(sf::Font& font) : min_(0), max_(100)
{
    createRect(main_rect,  {200, 5}, {400, 300}, {200, 200, 200});
    createRect(slide_rect, {15, 40}, {400, 300}, {200, 200, 200});
    this->text_.setFont(font);
    this->text_.setCharacterSize(this->slide_rect.getSize().y * 0.6);
    this->text_.setFillColor(sf::Color::White);
    this->text_.setString(std::to_string(this->cur_));
    this->text_.setPosition({this->main_rect.getSize().x * 1.1f + this->main_rect.getPosition().x, this->slide_rect.getPosition().y});
}
//-----------------------------------------------------------------------------------------------------------
// Конструктор с оновными параметрами
Slider::Slider(sf::Vector2f position, sf::Vector2f main_size, sf::Font& font, long long int min = 0, long long int max = 100) 
                : min_(min), max_(max)
{
    createRect(main_rect,  main_size, position, {200, 200, 200});
    createRect(slide_rect, {main_size.y * 2, main_size.x / 6}, position, {200, 200, 200});
    this->text_.setFont(font);
    this->text_.setCharacterSize(this->slide_rect.getSize().y * 0.6);
    this->text_.setFillColor(sf::Color::White);
    this->text_.setString(std::to_string(this->cur_));
    this->text_.setPosition({this->main_rect.getSize().x * 1.1f + this->main_rect.getPosition().x, this->slide_rect.getPosition().y});
}

//-----------------------------------------------------------------------------------------------------------
Slider::~Slider() {};
//-----------------------------------------------------------------------------------------------------------
//												DRAW														
//-----------------------------------------------------------------------------------------------------------
void Slider::draw(sf::RenderWindow& window) const
{
    window.draw(this->main_rect);
    window.draw(this->slide_rect);
    window.draw(this->text_);
}
//-----------------------------------------------------------------------------------------------------------
//												SET NEW POSITION FOR SLIDER														
//-----------------------------------------------------------------------------------------------------------
void Slider::chang_slider_pos(const sf::Vector2f mouse_position)
{
    float left  = this->main_rect.getPosition().x;
    float right = left + this->main_rect.getSize().x;

    if(mouse_position.x > right)
        this->slide_rect.setPosition({right, this->slide_rect.getPosition().y});
    else if(mouse_position.x < left)
        this->slide_rect.setPosition({left - this->slide_rect.getSize().x, this->slide_rect.getPosition().y});
    else
        this->slide_rect.setPosition({mouse_position.x, this->slide_rect.getPosition().y});

    this->setCur(this->slide_rect.getPosition());
    this->text_.setString(std::to_string(this->getCur()));
}
//-----------------------------------------------------------------------------------------------------------
//											IF SLIDER WAS PRESSED														
//-----------------------------------------------------------------------------------------------------------
void Slider::pressed(const sf::Vector2f mouse_position)
{
    // Проверяем куда нажато
    if(isBelongs(this->slide_rect.getPosition(), this->slide_rect.getSize(), mouse_position))
    {
        this->isMoving = true;
    }
    
    if(isBelongs(this->main_rect.getPosition(), this->main_rect.getSize(), mouse_position) && !this->isMoving)
    {
        this->chang_slider_pos(mouse_position);
    }
}
//-----------------------------------------------------------------------------------------------------------
//											IF SLIDER WAS MOVED														
//-----------------------------------------------------------------------------------------------------------
void Slider::move(const sf::Vector2f mouse_position)
{
    int center = this->slide_rect.getPosition().x + this->slide_rect.getSize().x / 2;

    // if(center < this->main_rect.getPosition().x + this->main_rect.getSize().x  &&
    //    center > this->main_rect.getPosition().x )
    // {
        this->chang_slider_pos(mouse_position);
    // }
}
//-----------------------------------------------------------------------------------------------------------
//												SET														
//-----------------------------------------------------------------------------------------------------------
void Slider::setCur(const sf::Vector2f mouse_position)
{
    // float k = (mouse_position.x - this->main_rect.getPosition().x) / this->main_rect.getSize().x;
    float k = ((this->slide_rect.getPosition().x + this->slide_rect.getSize().x / 2)- this->main_rect.getPosition().x) / this->main_rect.getSize().x;
    this->cur_ = k * this->max_ + 1;
    if(this->cur_ > this->max_)
        this->cur_ = this->max_;
    else if(this->cur_ < this->min_)
        this->cur_ = this->min_;
}
//-----------------------------------------------------------------------------------------------------------
//												GET														
//-----------------------------------------------------------------------------------------------------------
long long int Slider::getCur() const
{
    return this->cur_;
}
//-----------------------------------------------------------------------------------------------------------
long long int Slider::getMin() const
{
    return this->min_;
}
//-----------------------------------------------------------------------------------------------------------
long long int Slider::getMax() const
{
    return this->max_;
}

