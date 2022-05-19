#include "../include/AbstructSkillTree.hpp"

int main() {
  sf::ContextSettings settings;
  settings.antialiasingLevel = 8;
  sf::RenderWindow window(sf::VideoMode(800, 800), "Skill Tree",
                          sf::Style::Close, settings);
  window.setFramerateLimit(60);

  sf::Font font;
  if (!font.loadFromFile("../src/consolas.ttf")) {
    std::cout << "Can't load font" << std::endl;
  }

  MageSkillTree mage_tree {{200, 500}, font};
  WarriorSkillTree war_tree {{400, 500}, font};
  RogueSkillTree rog_tree {{600, 500}, font};

  while (window.isOpen()) {
    sf::Event event;
    while (window.pollEvent(event)) {
      if (event.type == sf::Event::Closed)
        window.close();
      if (event.type == sf::Event::MouseButtonPressed) {
        sf::Vector2f mouseCoords =
            window.mapPixelToCoords({event.mouseButton.x, event.mouseButton.y});
        if (event.mouseButton.button == sf::Mouse::Left) {
          mage_tree.onMousePressed(mouseCoords, Node::MouseState::LeftButton);
          war_tree.onMousePressed(mouseCoords, Node::MouseState::LeftButton);
          rog_tree.onMousePressed(mouseCoords, Node::MouseState::LeftButton);
        }
        if (event.mouseButton.button == sf::Mouse::Right) {
          mage_tree.onMousePressed(mouseCoords, Node::MouseState::RightButton);
          war_tree.onMousePressed(mouseCoords, Node::MouseState::RightButton);
          rog_tree.onMousePressed(mouseCoords, Node::MouseState::RightButton);
        }
      }
      if (event.type == sf::Event::KeyPressed) {
        if(event.key.code == sf::Keyboard::Escape) {
            window.close();
        }
      }
    }

    window.clear(sf::Color::Black);
    mage_tree.draw(window);
    war_tree.draw(window);
    rog_tree.draw(window);
    window.display();
  }

  return 0;
}