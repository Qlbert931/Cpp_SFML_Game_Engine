#include <SFML/Graphics.hpp>
#include "Standard/math.hpp"
#include "engine.hpp"
#include "Loaders/TextureLoaderPrototypeFactory.hpp"
#include "TestAnimatedCircle.hpp"
#include "MusicSystem.hpp"
#include "SoundSystem.hpp"
#include "Nodes/Node.hpp"
#include "Layers.hpp"
#include "Track.hpp"
#include "GUI/GUI.hpp"
#include "test/SpriteNode.hpp"
#include "Standard/line.hpp"
#include "Train.hpp"
#include "Town.hpp"
#include <memory>
#include "GUI/text.hpp"
#include "Loaders/ResourceLoader.hpp"
#include "Nodes/Grid.hpp"

class game : public engine::engineer{
    using animation_map = std::unordered_map<std::string,AtlasManager::animation>;
    public:
    void onStart() override
    {
        TextureLoaderPrototypeFactory::getInstance("res/textures/");
        musicSystem = MusicSystem::getInstance("res/musics/");
        soundSystem = SoundSystem::getInstance("res/sounds/");
        musicSystem->playMusic("GamePlayMusic.wav");
        soundSystem->playSound("dead.wav");
        soundSystem->setVolume("dead.wav", 100.0f);
        soundSystem->playSound("punch.wav");
        spriteNode = Node::create<SpriteNode>();
        warszawa = Node::create<Town>("Warszawa", true, sf::Vector2f(500.0f, 500.0f));
        berlin = Node::create<Town>("Berlin", false, sf::Vector2f(600.0f, 500.0f));
        train = Node::create<Train>();
        animation_map m;
        m["test"] = {1.f,{0,0},4};
        atlasManager = new AtlasManager("indoors.png",{16,16},m);

        grid = Node::create<Grid>(engine::Vec2i(5,5), std::string("indoors.png"), engine::Vec2i(16,16));
        grid->scale({5.f,5.f});
        grid->loadTileDataFromFile("");
    }
    void update(const sf::Time& delta) override
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
            if (event.type == sf::Event::MouseButtonPressed)
            { 

            }
            
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space))
            {
                warszawa->Repair();
            }
            if (event.type == sf::Event::MouseButtonPressed) {
                //pl.append_vertex(sf::Vertex({(float)event.mouseButton.x,(float)event.mouseButton.y}, sf::Color(255,0,0,255)));
            }
        }
        spriteNode->update(delta);
        warszawa->update(delta);
        berlin->update(delta);
        train->update(delta);
        atlasManager->update(delta);
    }
    void draw() override
    {
        /*sf::VertexArray triangle(sf::Quads, 4);
        // 35 x 30
        // define the position of the triangle's points
        sf::Vector2f a(10.f, 10.f), b(200.f, 10.f), c(200.f, 200.f), d(10.f, 200.f);

        triangle[0].position = a;
        triangle[1].position = b;
        triangle[2].position = c;
        triangle[3].position = d;

        // define the color of the triangle's points
        auto[x,y,z,w] = atlasManager->get_texture_coords_at(atlasManager->get_frame("test"));
        triangle[0].texCoords = x;
        triangle[1].texCoords = y;
        triangle[2].texCoords = z;
        triangle[3].texCoords = w;

        sf::RenderStates state;

        state.texture = atlasManager->get_texture().get();

        (*layers)[1]->draw(triangle,state);*/
        grid->draw();
        //(*layers)[1]->draw(triangle);
        

        spriteNode->draw();
        warszawa->draw();
        berlin->draw();
        train->draw();
        auto l = (*layers)[0];
        pl.draw(*l, sf::RenderStates());
        if(colorIDMap->get_hovered_object())
            std::cout << "hover!\n";
        std::string t("dwaijidja");
        std::shared_ptr<engine::Text> eng_text = engine::Text::create<engine::Text>(t);
        eng_text->draw();
    }
    private:
    // systems
    MusicSystem* musicSystem;
    SoundSystem* soundSystem;
    std::shared_ptr<Train> train;
    std::shared_ptr<SpriteNode> spriteNode;
    std::shared_ptr<Town> warszawa;
    std::shared_ptr<Town> berlin;
    engine::PolyLine pl = engine::PolyLine(sf::Vertex({100,100}, sf::Color(255,0,0,255)), 20); 

    AtlasManager* atlasManager;
    std::shared_ptr<Grid> grid;
};

int main()
{
    game test;
    test.start();
    return 0;
}