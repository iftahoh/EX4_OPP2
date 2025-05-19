#include <stdexcept>
#include <ResourcesManager.h>
#include <fstream>
#include <sstream>
#include <filesystem>
#include <iostream>

// פונקציה שמחזירה את המנהל היחיד של המשאבים
ResourceManager& ResourceManager::getInstance() {
    static ResourceManager instance;
    return instance;
}
// פונקציה שמטעינה תמונה
void ResourceManager::loadTexture(const std::string& name, const std::string& filename) {
    auto texture = std::make_unique<sf::Texture>();
    if (!texture->loadFromFile(filename + ".png")) {
        throw std::runtime_error("Failed to load texture: " + filename);
    }
    m_textures[name] = std::move(texture);
}
// פונקציה שמחזירה תמונה
sf::Texture& ResourceManager::getTexture(const std::string& name) {
    auto found = m_textures.find(name);
    if (found == m_textures.end()) {
        throw std::runtime_error("Texture not found: " + name);
    }
    return *found->second;
}
// פונקציה שמטעינה פונט
void ResourceManager::loadFont(const std::string& name, const std::string& filename) {
    auto font = std::make_unique<sf::Font>();
    if (!font->loadFromFile(filename)) {
        throw std::runtime_error("Failed to load font: " + filename);
    }
    m_fonts[name] = std::move(font);
}
// פונקציה שמחזירה פונט
sf::Font& ResourceManager::getFont(const std::string& name) {
    auto found = m_fonts.find(name);
    if (found == m_fonts.end()) {
        throw std::runtime_error("Font not found: " + name);
    }
    return *found->second;
}
// פונקציה שמטעינה קובץ קול
//void ResourceManager::loadMusic(const std::string& name, const std::string& filename) {
//    auto music = std::make_unique<sf::Music>();
//    if (!music->openFromFile(filename)) {
//        throw std::runtime_error("Failed to load music: " + filename);
//    }
//    m_music_files[name] = std::move(music);
//}
// פונקציה שמחזירה קובץ קול
//sf::Music& ResourceManager::getMusic(const std::string& name) {
//    auto found = m_music_files.find(name);
//    if (found == m_music_files.end()) {
//        throw std::runtime_error("Music not found: " + name);
//    }
//    return *found->second;
//}
// פונקציה שמטעינה קובץ טקסט
void ResourceManager::loadTextFile(const std::string& name, const std::string& filename)
{
    std::ifstream file(filename);
    if (!file.is_open()) {
        throw std::runtime_error("Failed to load text file: " + filename);
    }

    std::stringstream buffer;
    buffer << file.rdbuf();
    m_text_files[name] = buffer.str();
}
std::vector<std::string> ResourceManager::getTextFile(const std::string& name)
{
    auto found = m_text_files.find(name);
    if (found == m_text_files.end()) {
        throw std::runtime_error("Text file not found: " + name);
    }

    std::vector<std::string> lines;
    std::stringstream ss(found->second);
    std::string line;

    while (std::getline(ss, line)) {
        lines.push_back(line);
    }

    return lines;
}
// פונקציה שמטעינה קובץ קול
//void ResourceManager::loadSound(const std::string& name, const std::string& filename)
//{
//    auto buffer = std::make_unique<sf::SoundBuffer>();
//
//    // ניסיון לטעון את הקובץ
//    if (!buffer->loadFromFile(filename)) {
//        std::cout << "Failed to load sound: " << filename << std::endl;
//
//    }
//
//    // הוספה למפה
//    m_Sound_files[name] = std::move(buffer);
//
//}
//void ResourceManager::loadPlaylist()
//{
//    std::fstream file("Playlist.txt");
//    if (!file.is_open())
//    {
//        throw std::runtime_error("Failed to load text file: Playlist.txt");
//    }
//    std::string line;
//    while (std::getline(file, line))
//    {
//        m_level++;
//        loadTextFile(line, line + ".txt");
//    }
//}
// פונקציה שמחזירה קובץ קול
//sf::SoundBuffer& ResourceManager::getSound(const std::string& name)
//{
//    auto found = m_Sound_files.find(name);
//    if (found == m_Sound_files.end()) {
//        throw std::runtime_error("Sound not found: " + name);
//    }
//    return *found->second;
//
//}
int ResourceManager::getLevel() const
{
    return m_level;
}
// פונקציה בונה
ResourceManager::ResourceManager() {
    for (int index = 0; index < TEXTURE_PATH_SIZE; index++)
    {
        loadTexture(RESOURCES_TEXTURE_NAME[index], RESOURCES_TEXTURE_PATH[index]);
    }
    loadFont("main_font", "C:/Windows/Fonts/Arial.ttf");
 /*   loadPlaylist();

    loadFont("main_font", "C:/Windows/Fonts/Arial.ttf"); \
        loadMusic("background_music", "backGroundSound.ogg");
    loadMusic("level0", "level1Music.ogg");
    loadMusic("level1", "level2Music.ogg");
    loadMusic("level2", "level3Music.ogg");
    loadSound("explosion", "explosion.wav");
    loadSound("giftSound", "GiftSound.wav");
    loadSound("GuardSound", "GuardSound.wav");
    loadSound("timer", "TimerSound.wav");
    loadSound("win", "WinSound.wav");
    loadSound("loss", "LossSound.wav");
    */

};