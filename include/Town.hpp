#pragma once
#include "Nodes/Node.hpp"
#include "GUI/text.hpp"
#include "AnimationManager.hpp"
#include "Train.hpp"
#include <SFML/Graphics.hpp>

class Town : public Node
{
public:
    sf::Shader post_fx_town_shader;

    Town(std::string _name, bool isItBig, sf::Vector2f position);
    void onReady();
    void Repair();
    void onUpdate(const sf::Time& delta);
    void onDraw() const;
private:
    bool repaired = false;
    std::string name;
    AnimationManager animationManager;
    sf::RectangleShape body;
    sf::RectangleShape collision;
    std::shared_ptr<engine::Text> text;
    EventListener<std::shared_ptr<Node>> el_train = EventListener<std::shared_ptr<Node>>([this](std::shared_ptr<Node> train) {
        if(!repaired){
            std::dynamic_pointer_cast<Train>(train)->speed -= 2;
            std::dynamic_pointer_cast<Train>(train)->turningRate += 5;
            std::dynamic_pointer_cast<Train>(train)->score += 500;
            std::dynamic_pointer_cast<Train>(train)->cities += 1;
            Repair();
            repaired = true;
        }
    });
};
