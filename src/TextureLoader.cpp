#include"TextureLoader.hpp"
#include<SFML/Graphics/Texture.hpp>
#include<string>
#include<iostream>
#include<filesystem>

std::string TextureLoader::fileFormat = ".png";

void TextureLoader::loadTextures(){
    for(const auto &entry: std::filesystem::directory_iterator(directoryPath)){
        sf::Texture texture;
        if(!texture.loadFromFile(entry.path().string())){
            std::cerr<<"Error while loading audio!"<<std::endl;
            continue;
        };
        std::string str = entry.path().string();
        str.erase(0,directoryPath.length()+1);
        textures.insert({str,std::make_shared<sf::Texture>(texture)});
        //std::cout << "Loaded Texture with id: " << str << std::endl;
    }
}

std::shared_ptr<sf::Texture> TextureLoader::returnTexture(std::string _fileName){
    return textures.at(_fileName + fileFormat);
}

int TextureLoader::getAmountOfTextures()
{
    return textures.size();
}

bool TextureLoader::checkIfThereIs(std::string fileName)
{
    //std::cout << "wants to check " << fileName + fileFormat << " for " << directoryPath << " and count = " << textures.count(fileName + fileFormat) << std::endl;
    return textures.count(fileName + fileFormat);
}