#include "../include/HitNode.hpp"

HitNode::HitNode(sf::Vector2f position) : Node{position} {}

void HitNode::loadTexture() {
  sf::String texturePath = getIconPath();
  if (!mTexture.loadFromFile(texturePath)) {
    std::cout << "Error! Can't load file " << texturePath.toAnsiString()
              << std::endl;
    std::exit(1);
  }
  mSprite.setTexture(mTexture);
  mSprite.setOrigin({mRadius, mRadius});
  mSprite.setPosition(mPosition);
}

sf::Color HitNode::getCurrentColor() const {
  if (mState == State::Unblocked)
    return sUnlockedColor;
  else if (mState == State::Activated)
    return sActivatedColor;
  return sBlockedColor;
}

void HitNode::draw(sf::RenderWindow &window) const {
  for (const auto &el : mChildren) {
    sfLine connectionLine{mPosition, el->getPosition(), getCurrentColor(), 2};
    connectionLine.draw(window);
    el->draw(window);
  }

  static sf::CircleShape shape(mRadius);
  shape.setOrigin({mRadius, mRadius});
  shape.setFillColor(getCurrentColor());
  shape.setPosition(mPosition);
  window.draw(shape);

  window.draw(mSprite);
}

bool HitNode::collisionTest(sf::Vector2f mouseCoords) const {
  sf::Vector2f d = mPosition - mouseCoords;
  return d.x * d.x + d.y * d.y < mRadius * mRadius;
}

size_t HitNode::getNodeStatus() const {
  size_t sum = 0;
  for (auto &child: mChildren) {
    sum += child->getNodeStatus();
  }
  return (mState == State::Activated) ? sum + 1 : sum ;
}

std::shared_ptr<Node> createSkillTree() {
  std::shared_ptr<Node> root{new LightningSkillNode({400, 500})};
  std::shared_ptr<Node> a{new ShurikenSkillNode({200, 400})};
  std::shared_ptr<Node> b{new BombSkillNode({400, 400})};
  std::shared_ptr<Node> c{new EyeSkillNode({600, 400})};
  root->addChild(a);
  root->addChild(b);
  root->addChild(c);

  a->addChild(std::shared_ptr<Node>{new ShieldSkillNode({100, 200})});
  a->addChild(std::shared_ptr<Node>{new SwordSkillNode({200, 200})});
  a->addChild(std::shared_ptr<Node>{new EarthquakeSkillNode({300, 200})});

  b->addChild(std::shared_ptr<Node>{new HandSkillNode({400, 200})});
  b->addChild(std::shared_ptr<Node>{new MeteoriteSkillNode({500, 200})});
  std::shared_ptr<Node> e{new BombSkillNode({600, 200})};
  b->addChild(e);
  e->addChild(std::shared_ptr<Node>{new WindSkillNode({500, 100})});
  e->addChild(std::shared_ptr<Node>{new SwordSkillNode({600, 100})});
  c->addChild(std::shared_ptr<Node>{new EyeSkillNode({700, 200})});
  std::shared_ptr<Node> f{new FireballSkillNode({100, 700})};
  a->addChild(f);

  return root;
}