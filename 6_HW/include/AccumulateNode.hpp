#ifndef __AccumulateNode_hpp__
#define __AccumulateNode_hpp__

#include "Node.hpp"

class AccumulateNode : public Node {
public:
  size_t maxLevel = 0;
  size_t currentLevel = 0;
  sf::Text subTitle;
  sf::Texture mTexture;
  sf::Sprite mSprite;

  AccumulateNode(sf::Vector2f &position, const sf::Font &font,
                 size_t max_level);

  void leftMouseButtonPressed(sf::Vector2f mouseCoords) override;
  void rightMouseButtonPressed(sf::Vector2f mouseCoords) override;
  bool collisionTest(sf::Vector2f mouseCoords) const override;
  void draw(sf::RenderWindow &window) const override;
  size_t getNodeStatus() const override;

  virtual sf::String getIconPath() const = 0;

  void loadTexture();
  sf::Color getCurrentColor() const;

  inline static const size_t kCharacterSize = 16;
  inline static const size_t width = 64;
  inline static const size_t height = 80;
  inline static const size_t subtitle_offset = 20;
};

class SwordRectSkillNode : public AccumulateNode {
public:
  inline static const size_t mxlvl = 4;

  SwordRectSkillNode(sf::Vector2f position, const sf::Font &font)
      : AccumulateNode{position, font, mxlvl} {
    loadTexture();
  }

  sf::String getIconPath() const override {
    return sf::String{"../src/icons/icon_rect_sword.png"};
  }
};

class FreezeRectSkillNode : public AccumulateNode {
public:
  inline static const size_t mxlvl = 7;

  FreezeRectSkillNode(sf::Vector2f position, const sf::Font &font)
      : AccumulateNode{position, font, mxlvl} {
    loadTexture();
  }

  sf::String getIconPath() const override {
    return sf::String{"../src/icons/icon_rect_freeze.png"};
  }
};

class ChainRectSkillNode : public AccumulateNode {
public:
  inline static const size_t mxlvl = 6;

  ChainRectSkillNode(sf::Vector2f position, const sf::Font &font)
      : AccumulateNode{position, font, mxlvl} {
    loadTexture();
  }

  sf::String getIconPath() const override {
    return sf::String{"../src/icons/icon_rect_chain.png"};
  }
};

std::shared_ptr<Node> anotherTree(const sf::Font &font);

#endif