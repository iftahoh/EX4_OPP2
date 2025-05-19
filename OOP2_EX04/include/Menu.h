// Menu.h
#pragma once
#include <SFML/Graphics.hpp>
#include <vector>
#include <SFML/Audio.hpp>
#include "ResourcesManager.h"

class Menu {
public:
    Menu();
    void draw(sf::RenderWindow& window);
    void run_menu(sf::RenderWindow& window);
    void handle_mouse_click(sf::Event::MouseButtonEvent& event, sf::RenderWindow& window);
    bool getStratGame();
    void resetMenu();

private:
    std::vector<sf::RectangleShape> m_menuButtons;
    sf::RectangleShape m_background;
    sf::Text m_infoText;
    sf::Text m_backButton;
    //sf::Music* m_menuMusic;
    sf::RectangleShape m_infoBackground;
    bool m_showingInfo = false;
    bool m_stratGame = false;
    sf::Text m_muteButton;
    bool m_isMuted = false;

    void returnToMainMenu(sf::RenderWindow& window);
    //void setMusic();
};
