#include "ball.hpp"
//===========================================================================================================

int main()
{
    sf::ContextSettings settings;
    settings.antialiasingLevel = 8;
    sf::RenderWindow window(sf::VideoMode(800, 600), "Select, Move, Delete!", sf::Style::Default, settings);
    window.setFramerateLimit(60);


    // Создаём связный список из шариков
    // Связный список -- потому что нам нужно будет постоянно удалять и добавлять в этот список
    std::list<Ball> balls;
    balls.push_back(Ball({200, 200}, 26));
    balls.push_back(Ball({400, 300}, 20));
    balls.push_back(Ball({500, 100}, 16));
    balls.push_back(Ball({200, 400}, 18));
    balls.push_back(Ball({350, 150}, 22));
    balls.push_back(Ball({750, 400}, 21));

    // Создаём прямоугольник выделения
    // Обратите внимание на четвёртый параметр sf::Color(150, 150, 240, 50)
    // Это alpha - прозрачность      0 = полностью прозрачный     255 = непрозрачный
    sf::RectangleShape selectionRect;
    selectionRect.setFillColor(sf::Color(150, 150, 240, 50));
    selectionRect.setOutlineColor(sf::Color(200, 200, 255));
    selectionRect.setOutlineThickness(1);

    // Специальная переменная, которая будет показывать, что мы находимся в режиме выделения
    bool isSelecting = false;

    while(window.isOpen()) 
    {
        sf::Event event;
        while(window.pollEvent(event)) 
        {
            if(event.type == sf::Event::Closed || (sf::Keyboard::isKeyPressed(sf::Keyboard::W) && sf::Keyboard::isKeyPressed(sf::Keyboard::LControl))) 
            {
                window.close();
            }
            
            if(event.type == sf::Event::MouseMoved) 
            {
                sf::Vector2f mousePosition = window.mapPixelToCoords({event.mouseMove.x, event.mouseMove.y});
                
                // Если мы находимся в режиме выделения, то меняем прямоугольник выделения
                if(isSelecting) 
                {
                    selectionRect.setSize(mousePosition - selectionRect.getPosition());
                }
            }

            if(event.type == sf::Event::MouseButtonPressed) 
            {
                sf::Vector2f mousePosition = window.mapPixelToCoords({event.mouseButton.x, event.mouseButton.y});
                if(event.mouseButton.button == sf::Mouse::Left) 
                {
                    // Если не зажат левый Ctrl, то все выделения снимаются
                    if(!sf::Keyboard::isKeyPressed(sf::Keyboard::LControl)) 
                    {
                        for(Ball& b : balls)
                        {
                            b.isChoosen = false;
                        }
                    } 
                    // Проверяем попал ли курсор в какой-нибудь шарик, если попал - выделяем
                    for(Ball& b : balls) 
                    {
                        if(distance(mousePosition, b.getPosition()) < b.getRadius()) 
                        {
                            b.isChoosen = true;
                            break;
                        }
                    }
                    // ЛКМ + левый Alt - добавляем новый случайный шарик
                    if(sf::Keyboard::isKeyPressed(sf::Keyboard::LAlt))
                    {
                        balls.push_back(Ball(mousePosition, 5 + rand() % 40));
                    }
                    // Задаём новое положения прямоугольника выделения
                    isSelecting = true;
                    selectionRect.setPosition(mousePosition);
                    selectionRect.setSize({0, 0});
                }
            }
            // При отпускании кнопки мыши выходим из режима выделения
            if(event.type == sf::Event::MouseButtonReleased) 
            {
                isSelecting = false;
            }
            // Random color
            if(sf::Keyboard::isKeyPressed(sf::Keyboard::Space))
            {
                int  i = 0;
                for(Ball& b : balls)
                {
                    ++i;
                    if(b.isChoosen)
                    {
                        b.setColor({(unsigned char)(rand() % 256), (unsigned char)(rand() % 256), (unsigned char)(rand() % 256)});
                    }
                }
            }
        }

        window.clear(sf::Color::Black);
        // Рисуем все шарики
        for(Ball& b : balls) 
        {
            b.draw(window);
        }
        // Рисуем прямоугольник выделения
        if(isSelecting) 
        {
            window.draw(selectionRect);
        }
        window.display();
    }

    return 0;
}