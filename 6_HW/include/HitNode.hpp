#ifndef __HitNode_hpp__
#define __HitNode_hpp__

/* Icons from Ken111:
 * https://www.flaticon.com/ru/packs/game-skill?k=1650700359068 */

#include "Node.hpp"

class HitNode : public Node {
public:
  HitNode(sf::Vector2f position);
  sf::Color getCurrentColor() const;

  void loadTexture();
  void draw(sf::RenderWindow &window) const;

  bool collisionTest(sf::Vector2f mouseCoords) const override;
  size_t getNodeStatus() const override;

  virtual sf::String getIconPath() = 0;

private:
  sf::Texture mTexture;
  sf::Sprite mSprite;

  float mRadius = 24;
  bool mIsActivated = false;
};

std::shared_ptr<Node> createSkillTree();

class BombSkillNode : public HitNode {
public:
  BombSkillNode(sf::Vector2f position) : HitNode{position} { loadTexture(); }

  sf::String getIconPath() override {
    return sf::String{"../src/icons/icon_bomb.png"};
  }
};

class SpikesSkillNode : public HitNode {
public:
  SpikesSkillNode(sf::Vector2f position) : HitNode{position} { loadTexture(); }

  sf::String getIconPath() override {
    return sf::String{"../src/icons/icon_spikes.png"};
  }
};

class LightningSkillNode : public HitNode {
public:
  LightningSkillNode(sf::Vector2f position) : HitNode{position} {
    loadTexture();
  }

  sf::String getIconPath() override {
    return sf::String{"../src/icons/icon_lightning.png"};
  }
};

class EyeSkillNode : public HitNode {
public:
  EyeSkillNode(sf::Vector2f position) : HitNode{position} { loadTexture(); }

  sf::String getIconPath() override {
    return sf::String{"../src/icons/icon_eye.png"};
  }
};

class ClawsSkillNode : public HitNode {
public:
  ClawsSkillNode(sf::Vector2f position) : HitNode{position} { loadTexture(); }

  sf::String getIconPath() override {
    return sf::String{"../src/icons/icon_claws.png"};
  }
};

class ShieldSkillNode : public HitNode {
public:
  ShieldSkillNode(sf::Vector2f position) : HitNode{position} { loadTexture(); }

  sf::String getIconPath() override {
    return sf::String{"../src/icons/icon_shield.png"};
  }
};

class SwordSkillNode : public HitNode {
public:
  SwordSkillNode(sf::Vector2f position) : HitNode{position} { loadTexture(); }

  sf::String getIconPath() override {
    return sf::String{"../src/icons/icon_sword.png"};
  }
};

class ShurikenSkillNode : public HitNode {
public:
  ShurikenSkillNode(sf::Vector2f position) : HitNode{position} {
    loadTexture();
  }

  sf::String getIconPath() override {
    return sf::String{"../src/icons/icon_shuriken.png"};
  }
};

class WindSkillNode : public HitNode {
public:
  WindSkillNode(sf::Vector2f position) : HitNode{position} { loadTexture(); }

  sf::String getIconPath() override {
    return sf::String{"../src/icons/icon_shuriken.png"};
  }
};

class MeteoriteSkillNode : public HitNode {
public:
  MeteoriteSkillNode(sf::Vector2f position) : HitNode{position} {
    loadTexture();
  }

  sf::String getIconPath() override {
    return sf::String{"../src/icons/icon_meteorite.png"};
  }
};

class HandSkillNode : public HitNode {
public:
  HandSkillNode(sf::Vector2f position) : HitNode{position} { loadTexture(); }

  sf::String getIconPath() override {
    return sf::String{"../src/icons/icon_hand.png"};
  }
};

class EarthquakeSkillNode : public HitNode {
public:
  EarthquakeSkillNode(sf::Vector2f position) : HitNode{position} {
    loadTexture();
  }

  sf::String getIconPath() override {
    return sf::String{"../src/icons/icon_earthquake.png"};
  }
};

class FireballSkillNode : public HitNode {
public:
  FireballSkillNode(sf::Vector2f position) : HitNode(position) {
    loadTexture();
  }

  sf::String getIconPath() override {
    return sf::String{"../src/icons/icon_fireball.png"};
  }
};

#endif