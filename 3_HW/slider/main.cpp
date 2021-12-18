#include <iostream>
#include <string>
#include <algorithm>

#include "slider.hpp"
//===========================================================================================================

int main()
{
//-----------------------------------------------------------------------------------------------------------
//												ЗАДАЕМ ОКНО														
//-----------------------------------------------------------------------------------------------------------   
    sf::ContextSettings settings;
    settings.antialiasingLevel = 8;
    sf::RenderWindow window(sf::VideoMode(800, 600), "Slider!", sf::Style::Default, settings);
    window.setFramerateLimit(60);
//-----------------------------------------------------------------------------------------------------------
//-----------------------------------------------------------------------------------------------------------
//                                              ПОДКЛЮЧАЕМ ШРИФТ
//-----------------------------------------------------------------------------------------------------------
    sf::Font font;
    if(!font.loadFromFile("./consolas.ttf")) 
    {
        std::cout << "Can't load font" << std::endl;
    }
//-----------------------------------------------------------------------------------------------------------
//												SLIDERS														
//-----------------------------------------------------------------------------------------------------------
    Slider slider_size({400, 400}, {200, 8}, font, 0, 100); // slider меняющий размер шарика
    Slider slider_color_r({400, 450}, {200, 8}, font, 0, 255); // slider меняющий красную компоненту цвета
    Slider slider_color_g({400, 500}, {200, 8}, font, 0, 255); // slider меняющий зелёную компоненту цвета
    Slider slider_color_b({400, 550}, {200, 8}, font, 0, 255); // slider меняющий голубую компоненту цвета
//-----------------------------------------------------------------------------------------------------------
//												BALL														
//-----------------------------------------------------------------------------------------------------------
    sf::CircleShape circle;
    sf::Color ball_color = sf::Color::White;
    circle.setFillColor(ball_color);
    circle.setRadius(50);
    circle.setOrigin({50, 50});
    circle.setPosition({400, 200});
    // std::cout << circle.getOrigin().x << " " << circle.getOrigin().y << std::endl; // Отладочный принт
    


    bool isMoving = false; // Флаг на переджвижение ползунка

//-----------------------------------------------------------------------------------------------------------
//										ОСНОВНОЙ ЦИКЛ ПРОГРАММЫ														
//-----------------------------------------------------------------------------------------------------------
    while(window.isOpen())
    {
        sf::Event event;
        while(window.pollEvent(event))
        {
            // Выход из приложение
            if(event.type == sf::Event::Closed                    || 
               sf::Keyboard::isKeyPressed(sf::Keyboard::Escape)   || 
              (sf::Keyboard::isKeyPressed(sf::Keyboard::LControl) && (sf::Keyboard::isKeyPressed(sf::Keyboard::W))))
                {
                    window.close();
                }
            
            if(event.type == sf::Event::MouseMoved) 
            {
                sf::Vector2f mousePosition = window.mapPixelToCoords({event.mouseMove.x, event.mouseMove.y});
                // std::cout << mousePosition.x << " " << mousePosition.y << std::endl; // Отладочный принт
                // Проверяем передвигли ли ползунок, и если да, то какой
                if(slider_size.isMoving)
                    slider_size.move(mousePosition);

                if(slider_color_r.isMoving)
                    slider_color_r.move(mousePosition);

                if(slider_color_g.isMoving)
                    slider_color_g.move(mousePosition);    

                if(slider_color_b.isMoving)
                    slider_color_b.move(mousePosition);                     
            }
            
            // Проверка на нажатие мыши
            if(event.type == sf::Event::MouseButtonPressed)
            {
                sf::Vector2f mousePosition = window.mapPixelToCoords({event.mouseButton.x, event.mouseButton.y});

                slider_size.pressed(mousePosition);
                slider_color_r.pressed(mousePosition);
                slider_color_g.pressed(mousePosition);
                slider_color_b.pressed(mousePosition);
            }

            // При отжатии кнопки мышки
            if(event.type == sf::Event::MouseButtonReleased)
            {
                slider_size.isMoving = false;
                slider_color_r.isMoving = false;
                slider_color_g.isMoving = false;
                slider_color_b.isMoving = false;
            }
        } 

        ball_color = {(sf::Uint8)slider_color_r.getCur(), (sf::Uint8)slider_color_g.getCur(), (sf::Uint8)slider_color_b.getCur()};
        circle.setFillColor(ball_color);
        circle.setRadius(slider_size.getCur());
        circle.setOrigin(circle.getRadius(), circle.getRadius());

        // Отрисовка всех объектов
        window.clear(sf::Color::Black);
        
        slider_size.draw(window);
        slider_color_r.draw(window);
        slider_color_g.draw(window);
        slider_color_b.draw(window);

        window.draw(circle);
        window.display();
    }


    return 0;
}