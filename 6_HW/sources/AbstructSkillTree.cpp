#include "../include/AbstructSkillTree.hpp"

AbstructSkillTree::AbstructSkillTree(std::shared_ptr<Node> new_root, const sf::Font &font, const std::string s_title, size_t max_skill_points, sf::Color textColor) {
    maxPoints = max_skill_points;
    Name = s_title;
    currPoints = 0;

    std::string title = Name + std::to_string(currPoints) + "/" + std::to_string(maxPoints);
    Title.setFont(font);
    Title.setCharacterSize(kCharacterSize);
    Title.setFillColor(textColor);
    Title.setOrigin({(float)title.length(), 0});
    Title.setPosition(new_root->getPosition() + title_offset);
    Title.setString(title);

    root = new_root;
}

void AbstructSkillTree::onMousePressed(sf::Vector2f mouseCoord, Node::MouseState state) {
    switch(state) {
        case Node::MouseState::LeftButton: {
            if (currPoints != maxPoints)
                root->leftMouseButtonPressed(mouseCoord);
            currPoints = root->getNodeStatus();
            Title.setString(Name + std::to_string(currPoints) + "/" + std::to_string(maxPoints));
            break;
        }
        case Node::MouseState::RightButton: {
            root->rightMouseButtonPressed(mouseCoord);
            currPoints = root->getNodeStatus();
            Title.setString(Name + std::to_string(currPoints) + "/" + std::to_string(maxPoints));
            break;
        }
    }
}

void AbstructSkillTree::draw(sf::RenderWindow &window) const {
    root->draw(window);
    window.draw(Title);
}

void AbstructSkillTree::addChild(const std::shared_ptr<Node> &child) {
    root->addChild(child);
}