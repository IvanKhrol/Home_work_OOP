#ifndef __Node_hpp__
#define __Node_hpp__

#include "sfLine.hpp"

class Node {
public:
  enum class State { Blocked = 0, Unblocked, Activated };
  enum class MouseState { LeftButton = 0, RightButton, ErrorButton };

  Node(sf::Vector2f &position);
  sf::Vector2f getPosition();

  void onMousePressed(sf::Vector2f mouseCoords, MouseState state);
  void addChild(const std::shared_ptr<Node> &child);

  void block();
  void unblock();

  virtual void leftMouseButtonPressed(sf::Vector2f mouseCoords);
  virtual void rightMouseButtonPressed(sf::Vector2f mouseCoords);
  virtual bool collisionTest(sf::Vector2f mouseCoords) const = 0;
  virtual void draw(sf::RenderWindow &window) const = 0;
  virtual size_t getNodeStatus() const = 0;

  std::vector<std::shared_ptr<Node>> mChildren{};

protected:
  sf::Vector2f mPosition{0, 0};
  State mState = State::Blocked;


  inline static sf::Color sBlockedColor{40, 40, 40};
  inline static sf::Color sUnlockedColor{80, 80, 40};
  inline static sf::Color sActivatedColor{160, 160, 40};
};

#endif