#include "world.hpp"
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>

int main() {
  sf::ContextSettings settings;
  settings.antialiasingLevel = 8.0;
  sf::RenderWindow window(sf::VideoMode(1200, 900), "Player states",
                          sf::Style::Close, settings);
  window.setVerticalSyncEnabled(true);
  window.setFramerateLimit(60);

  double time = 0;
  double dt = 1.0 / 60;

  World world;
  world.addBlock({-500, 770, 20000, 400});
  world.addBlock({-400, 100, 700, 300});
  world.addBlock({600, 500, 300, 120});
  world.addBlock({800, 0, 400, 200});
  world.addBlock({-100, -700, 400, 100});
  world.addBlock({700, -700, 400, 100});
  world.addBlock({1500, -700, 400, 100});
  world.addBlock({1100, -300, 400, 100});

  world.addBlock({1100, 400, 400, 400});

  world.addBlock({1900, -100, 200, 800});

  world.addBlock({3000, 500, 1000, 200});

  while (window.isOpen()) {
    sf::Event event;
    while (window.pollEvent(event)) {
      if (event.type == sf::Event::Closed ||
          (event.type == sf::Event::KeyPressed &&
           event.key.code == sf::Keyboard::Escape))
        window.close();
      world.handleEvents(event);
    }
    window.clear(sf::Color::Black);
    world.update(dt);
    world.draw(window);

    window.display();

    time += dt;
  }

  return 0;
}