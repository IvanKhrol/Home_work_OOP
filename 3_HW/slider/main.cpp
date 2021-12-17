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
    Slider slider; // наш slider
//-----------------------------------------------------------------------------------------------------------
//                                              ПОДКЛЮЧАЕМ ШРИФТ
//-----------------------------------------------------------------------------------------------------------
    sf::Font font;
    if(!font.loadFromFile("./consolas.ttf")) 
    {
        std::cout << "Can't load font" << std::endl;
    }
//-----------------------------------------------------------------------------------------------------------
//												TEKCT														
//-----------------------------------------------------------------------------------------------------------
    sf::Text text;
    text.setFont(font);
    text.setCharacterSize(slider.slide_rect.getSize().y * 0.6);
    text.setFillColor(sf::Color::White);
    text.setString(std::to_string(slider.getCur()));
    text.setPosition({slider.main_rect.getSize().x * 1.1 + slider.main_rect.getPosition().x, slider.slide_rect.getPosition().y});
//-----------------------------------------------------------------------------------------------------------
//-----------------------------------------------------------------------------------------------------------



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
                if(isMoving)
                {
                    if(mousePosition.x < slider.main_rect.getPosition().x + slider.main_rect.getSize().x  &&
                       mousePosition.x > slider.main_rect.getPosition().x - slider.slide_rect.getSize().x / 2)
                        {
                            slider.slide_rect.setPosition({mousePosition.x, slider.slide_rect.getPosition().y});
                            slider.setCur(slider.slide_rect.getPosition());
                            text.setString(std::to_string(slider.getCur()));
                        }
                }                
            }
            
            // Проверка на нажатие мыши
            if(event.type == sf::Event::MouseButtonPressed)
            {
                sf::Vector2f mousePosition = window.mapPixelToCoords({event.mouseButton.x, event.mouseButton.y});

                // Проверяем куда нажато
                if(isBelongs(slider.slide_rect.getPosition(), slider.slide_rect.getSize(), mousePosition))
                {
                    isMoving = true;
                }
                
                if(isBelongs(slider.main_rect.getPosition(), slider.main_rect.getSize(), mousePosition) && !isMoving)
                {
                    slider.slide_rect.setPosition({mousePosition.x, slider.slide_rect.getPosition().y});
                    slider.setCur(slider.slide_rect.getPosition());
                    text.setString(std::to_string(slider.getCur()));

                }
            }

            // При отжатии кнопки мышки
            if(event.type == sf::Event::MouseButtonReleased)
            {
                isMoving = false;
            }
        }



        // Отрисовка всех объектов
        window.clear(sf::Color::Black);
        
        // drawLine(window, {100, 100}, {300, 100}, sf::Color::Green);
        window.draw(slider.main_rect);
        window.draw(slider.slide_rect);
        window.draw(text);
        window.display();
    }


    return 0;
}