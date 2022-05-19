#include "../include/Node.hpp"

Node::Node(sf::Vector2f &position) : mPosition{position} {}

void Node::addChild(const std::shared_ptr<Node> &child) {
  mChildren.push_back(child);
}

sf::Vector2f Node::getPosition() { return mPosition; }

void Node::unblock() { mState = State::Unblocked; }

void Node::block() {
  mState = State::Blocked;
  for (const auto &child : mChildren)
    child->block();
}

void Node::onMousePressed(sf::Vector2f mouseCoords, Node::MouseState state) {
  switch (state) {
  case Node::MouseState::LeftButton:
    leftMouseButtonPressed(mouseCoords);
    break;
  case Node::MouseState::RightButton:
    rightMouseButtonPressed(mouseCoords);
    break;
  default:
    break;
  }
}

void Node::leftMouseButtonPressed(sf::Vector2f mouseCoords) {
  if (mState == State::Blocked)
    return;

  if (collisionTest(mouseCoords)) {
    if (mState == State::Unblocked) {
      mState = State::Activated;
      for (const auto &child : mChildren)
        child->unblock();
    }

    else if (mState == State::Activated) {
      mState = State::Unblocked;
      for (const auto &child : mChildren)
        child->block();
    }
  }

  for (const auto &child : mChildren) {
    child->leftMouseButtonPressed(mouseCoords);
  }
}

void Node::rightMouseButtonPressed(sf::Vector2f mouseCoords) {
  if (mState == State::Blocked)
    return;

  if (collisionTest(mouseCoords)) {
    if (mState == State::Activated) {
      mState = State::Unblocked;
      for (const auto &child : mChildren)
        child->block();
    }
  }

  for (const auto &child : mChildren) {
    child->rightMouseButtonPressed(mouseCoords);
  }
}