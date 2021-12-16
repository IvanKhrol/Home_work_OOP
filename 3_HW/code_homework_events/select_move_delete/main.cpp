#include "ball.hpp"
#include "../context_menu/context_menu.hpp"
//===========================================================================================================


int main()
{
    sf::ContextSettings settings;
    settings.antialiasingLevel = 8;
    sf::RenderWindow window(sf::VideoMode(800, 600), "Select, Move, Delete!", sf::Style::Default, settings);
    window.setFramerateLimit(60);
//-----------------------------------------------------------------------------------------------------------
//												ПОДКЛЮЧАЕМ КОНТЕКСТНОЕ МЕНЮ														
//-----------------------------------------------------------------------------------------------------------
    sf::Font font;
    if(!font.loadFromFile("../context_menu/consolas.ttf")) 
    {
        std::cout << "Can't load button font" << std::endl;
    }
//-----------------------------------------------------------------------------------------------------------
    std::vector<sf::String> contextMenuStrings {"Delete", "Create", "Random Color", "Increase", "Decrease"};
    ContextMenu contextMenu(window, font);
    for(const auto& el : contextMenuStrings) 
        contextMenu.addButton(el);
//-----------------------------------------------------------------------------------------------------------


    // Создаём связный список из шариков
    // Связный список -- потому что нам нужно будет постоянно удалять и добавлять в этот список
    std::list<Ball> balls;
    balls.push_back(Ball({200, 200}, 26));
    balls.push_back(Ball({400, 300}, 20));
    balls.push_back(Ball({500, 100}, 16));
    balls.push_back(Ball({200, 400}, 18));
    balls.push_back(Ball({350, 150}, 22));
    balls.push_back(Ball({750, 400}, 21));

    // Буффер для копировния и вставки шариков
    std::list<Ball> buffer;
    // Создаём прямоугольник выделения
    // Обратите внимание на четвёртый параметр sf::Color(150, 150, 240, 50)
    // Это alpha - прозрачность      0 = полностью прозрачный     255 = непрозрачный
    sf::RectangleShape selectionRect;
    selectionRect.setFillColor(sf::Color(150, 150, 240, 50));
    selectionRect.setOutlineColor(sf::Color(200, 200, 255));
    selectionRect.setOutlineThickness(1);

    // Специальная переменная, которая будет показывать, что мы находимся в режиме выделения
    bool isSelecting = false;
    bool isMoving = false;

    sf::Vector2f last_mouse_position = {-1, -1};
    sf::Vector2f toCreate = {-1, -1};

    while(window.isOpen()) 
    {
        sf::Event event;
        while(window.pollEvent(event)) 
        {
            if(event.type == sf::Event::Closed) 
            {
                window.close();
            }

            // Работа с контекстным меню
            int result_menu = contextMenu.handleEvent(event);
            if (event.type == sf::Event::MouseButtonPressed && event.mouseButton.button == sf::Mouse::Right)
                toCreate = window.mapPixelToCoords({event.mouseButton.x, event.mouseButton.y}) ;
            switch(result_menu)
            {
                // DELETE
                case 0  :
                {
                    auto it = balls.begin();
                    auto tmp = it;
                    while(it != balls.end())
                    {
                        if(it->isChoosen)
                        {
                            tmp = std::next(it);
                            balls.erase(it);
                            it = tmp;
                        }else
                            ++it;
                    }  
                    break;
                }
                // CREATE
                case 1 : {balls.push_back(Ball(toCreate, 5 + rand() % 40)); break;}
                // Random Color
                case 2 : 
                {
                    for(Ball& b : balls)
                        if(b.isChoosen)
                            b.setColor({(unsigned char)(rand() % 256), (unsigned char)(rand() % 256), (unsigned char)(rand() % 256)});
                    break;
                }
                // Increase
                case 3 : 
                {
                    for(Ball& b : balls)
                        if(b.isChoosen)
                            b.setRadius(b.getRadius() * 1.25);
                    break;
                }
                // Decrease
                case 4 :
                {
                    for(Ball& b : balls)
                        if(b.isChoosen)
                            b.setRadius(b.getRadius() * 0.75);
                    break;
                }
                // default : std::cout << "ERROR::main:: Unknown context menu button" << std::endl; break;
            }

            if(event.type == sf::Event::MouseMoved) 
            {
                sf::Vector2f mousePosition = window.mapPixelToCoords({event.mouseMove.x, event.mouseMove.y});
                // Если мы находимся в режиме выделения, то меняем прямоугольник выделения
                if(isSelecting) 
                {
                    selectionRect.setSize(mousePosition - selectionRect.getPosition());
                }
                if(isMoving)
                {
                    for(Ball& b : balls)
                    {
                        if(b.isChoosen)
                        {
                            b.setPosition(b.getPosition() + mousePosition - last_mouse_position);
                            // std::cout << (b.getPosition() + mousePosition).x  << " " << (b.getPosition() + mousePosition).y << std::endl;
                        }
                    }
                    // std::cout << std::endl;
                    last_mouse_position = mousePosition;
                }
                    
            }

            if(event.type == sf::Event::MouseButtonPressed) 
            {
                sf::Vector2f mousePosition = window.mapPixelToCoords({event.mouseButton.x, event.mouseButton.y});
                if(event.mouseButton.button == sf::Mouse::Left) 
                {
                    last_mouse_position = mousePosition;
                    // Если не зажат левый Ctrl, то все выделения снимаются
                    if(!sf::Keyboard::isKeyPressed(sf::Keyboard::LControl)) 
                    {
                        for(Ball& b : balls)
                        {
                            if (b.isChoosen && distance(mousePosition, b.getPosition()) < b.getRadius()) 
                            { 
                                isMoving = true; 
                                break; 
                            }
                        }

                        if(!isMoving)
                            for(Ball& b : balls)
                                b.isChoosen = false;
                    } 
                    // Проверяем попал ли курсор в какой-нибудь шарик, если попал - выделяем
                    for(Ball& b : balls) 
                    {
                        if(distance(mousePosition, b.getPosition()) < b.getRadius()) 
                        {
                            isMoving = true;
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
                    if(!isMoving) 
                        isSelecting = true;
                    selectionRect.setPosition(mousePosition);
                    selectionRect.setSize({0, 0});
                }
                last_mouse_position = mousePosition;
            }
            // При отпускании кнопки мыши выходим из режима выделения и выделяем нужные шарики
            if(event.type == sf::Event::MouseButtonReleased) 
            {
                for(Ball& b : balls)
                {
                    if(isBelongs(selectionRect.getPosition(), selectionRect.getSize(), b.getPosition()))
                        b.isChoosen = true;
                }
                isSelecting = false;
                isMoving = false;
            }
            // Random color
            if(sf::Keyboard::isKeyPressed(sf::Keyboard::Space))
            {
                int  i = 0;
                for(Ball& b : balls)
                {
                    if(b.isChoosen)
                    {
                        b.setColor({(unsigned char)(rand() % 256), (unsigned char)(rand() % 256), (unsigned char)(rand() % 256)});
                    }
                }
            }
            
            // ALL WITH LCTRL
            if(sf::Keyboard::isKeyPressed(sf::Keyboard::LControl))
            {
                // Выделить се шарики
                if(event.type == sf::Event::KeyReleased && event.key.code == sf::Keyboard::A)
                    for(Ball& b : balls)
                        b.isChoosen = true;

                // Закрыть приложение
                if(event.type == sf::Event::KeyReleased && event.key.code == sf::Keyboard::W)
                    window.close();

                // COPY
                if(event.type == sf::Event::KeyReleased && event.key.code == sf::Keyboard::C)
                {
                    buffer.clear();
                    for(Ball& b : balls)
                        if(b.isChoosen)
                            buffer.push_back(b);
                }
                
                // CUT
                if(event.type == sf::Event::KeyReleased && event.key.code == sf::Keyboard::X)
                {
                    buffer.clear();
                    
                    for(Ball& b : balls)
                        if(b.isChoosen)
                            buffer.push_back(b);

                    auto it = balls.begin(), tmp = it;
                    while(it != balls.end()) 
                    {
                        if(it->isChoosen) 
                        {
                            tmp = std::next(it);
                            balls.erase(it);
                            it = tmp;
                        } else ++it;
                    }
                    continue;
                }

                // PUT
                if(event.type == sf::Event::KeyReleased && event.key.code == sf::Keyboard::V)
                {
                    for(Ball& b : balls)
                        b.isChoosen = false;
                    for(Ball& b : buffer) 
                        balls.push_back(b);
                }
                
            }
            // DELETE
            if(sf::Keyboard::isKeyPressed(sf::Keyboard::Delete))
            {
                auto it = balls.begin();
                auto tmp = it;
                while(it != balls.end())
                {
                    if(it->isChoosen)
                    {
                        tmp = std::next(it);
                        balls.erase(it);
                        it = tmp;
                    }else
                        ++it;
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
        contextMenu.draw();
        window.display();
    }

    return 0;
}
