#pragma once
#include <SFML/Graphics.hpp>
//#include <SFML/Audio.hpp>
#include <unordered_map>
#include <string>
#include <memory>

#include "Macros.h"


class ResourceManager {
public:
    static ResourceManager& getInstance();
    sf::Texture& getTexture(const std::string& name);
    sf::Font& getFont(const std::string& name);
    //sf::Music& getMusic(const std::string& name);
    std::vector<std::string> getTextFile(const std::string& name);
   // sf::SoundBuffer& getSound(const std::string& name);
    int getLevel() const;




    // מניעת העתקה
    ResourceManager(const ResourceManager&) = delete;
    ResourceManager& operator=(const ResourceManager&) = delete;

private:
    ResourceManager();


    void loadTexture(const std::string& name, const std::string& filename);
    void loadFont(const std::string& name, const std::string& filename);
    //void loadMusic(const std::string& name, const std::string& filename);
    void loadTextFile(const std::string& name, const std::string& filename);
    //void loadSound(const std::string& name, const std::string& filename);
    //void loadPlaylist();


    std::unordered_map<std::string, std::unique_ptr<sf::Texture>> m_textures;
    std::unordered_map<std::string, std::unique_ptr<sf::Font>> m_fonts;
    //std::unordered_map<std::string, std::unique_ptr<sf::Music>> m_music_files;
    std::unordered_map<std::string, std::string> m_text_files;
   // std::unordered_map<std::string, std::unique_ptr<sf::SoundBuffer>> m_Sound_files;

    int m_level = 0;

};



