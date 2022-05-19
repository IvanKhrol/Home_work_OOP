#ifndef __AbstructSkillTree_hpp__
#define __AbstructSkillTree_hpp__

#include "HitNode.hpp"
#include "AccumulateNode.hpp"

class AbstructSkillTree {
public:
    std::shared_ptr<Node> root;
    sf::Text Title;
    std::string Name;

    AbstructSkillTree(std::shared_ptr<Node> new_root, const sf::Font &font, const std::string title, size_t max_skill_points, sf::Color textColor);
    void onMousePressed(sf::Vector2f mouseCoord, Node::MouseState state);
    void draw(sf::RenderWindow &window) const;
    void addChild(const std::shared_ptr<Node> &child);

    static inline const sf::Vector2f title_offset {-25, 50};
    static inline const size_t kCharacterSize = 16;

    size_t currPoints = 0;
    size_t maxPoints;
};


class WarriorSkillTree : public AbstructSkillTree {
public:
    WarriorSkillTree (sf::Vector2f pos, const sf::Font &font) : 
        AbstructSkillTree(std::shared_ptr<Node>{new SwordRectSkillNode{pos, font}}, font, std::string("Warrior\n"), 7, sf::Color {255, 0, 0}) {
            addChild(std::shared_ptr<Node>{new ShieldSkillNode({pos.x, pos.y - 100})});
            root->mChildren[0]->addChild(std::shared_ptr<Node>{new EarthquakeSkillNode({pos.x - 50, pos.y - 200})});
            root->mChildren[0]->addChild(std::shared_ptr<Node>{new SpikesSkillNode({pos.x + 50, pos.y - 200})});
            root->mChildren[0]->mChildren[0]->addChild(std::shared_ptr<Node>{new ClawsSkillNode({pos.x - 50, pos.y - 300})});
            root->mChildren[0]->mChildren[1]->addChild(std::shared_ptr<Node>{new SwordSkillNode({pos.x + 50, pos.y - 300})});
            root->unblock();
        }
};


class RogueSkillTree : public AbstructSkillTree {
public:
    RogueSkillTree (sf::Vector2f pos, const sf::Font &font) : 
        AbstructSkillTree(std::shared_ptr<Node>{new ChainRectSkillNode{pos, font}}, font, std::string("Rogue\n"), 10, sf::Color {0, 255, 0}) {
            addChild(std::shared_ptr<Node>{new HandSkillNode({pos.x, pos.y - 100})});
            root->mChildren[0]->addChild(std::shared_ptr<Node>{new ShurikenSkillNode({pos.x - 50, pos.y - 200})});
            root->mChildren[0]->addChild(std::shared_ptr<Node>{new SwordSkillNode({pos.x + 50, pos.y - 200})});
            root->mChildren[0]->mChildren[0]->addChild(std::shared_ptr<Node>{new BombSkillNode({pos.x - 50, pos.y - 300})});
            root->mChildren[0]->mChildren[1]->addChild(std::shared_ptr<Node>{new EarthquakeSkillNode({pos.x + 50, pos.y - 300})});
            root->unblock();
        }
};

class MageSkillTree : public AbstructSkillTree {
public:
    MageSkillTree (sf::Vector2f pos, const sf::Font &font) : 
        AbstructSkillTree(std::shared_ptr<Node>{new FreezeRectSkillNode{pos, font}}, font, std::string("Mage\n"), 10, sf::Color {0, 0, 255}) {
            addChild(std::shared_ptr<Node>{new LightningSkillNode({pos.x, pos.y - 100})});
            root->mChildren[0]->addChild(std::shared_ptr<Node>{new EyeSkillNode({pos.x - 50, pos.y - 200})});
            root->mChildren[0]->addChild(std::shared_ptr<Node>{new WindSkillNode({pos.x + 50, pos.y - 200})});
            root->mChildren[0]->mChildren[0]->addChild(std::shared_ptr<Node>{new HandSkillNode({pos.x - 50, pos.y - 300})});
            root->mChildren[0]->mChildren[1]->addChild(std::shared_ptr<Node>{new MeteoriteSkillNode({pos.x + 50, pos.y - 300})});
            root->unblock();
        }
};

#endif