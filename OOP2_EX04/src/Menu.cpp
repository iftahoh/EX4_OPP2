#include "Menu.h"
#include "ResourcesManager.h"
#include "Macros.h"
#include <iostream>

// ���� ������ �� ������
Menu::Menu() {
    auto& resourceManager = ResourceManager::getInstance();
    // ���� ������
    const float BUTTON_WIDTH = 200; // ���� ������
    const float BUTTON_HEIGHT = 50; // ���� ������
    const float BUTTON_SPACING = 100;  // ������ ��� ��������

    // ����� ����� X (�����)
    float buttonX = (WINDOW_WIDTH - BUTTON_WIDTH) / 2;

    // ����� ����� Y ������� (�����) + 2 �"� ����
    float totalHeight = (MenuButtonSize * BUTTON_HEIGHT) + (2 * (BUTTON_SPACING - BUTTON_HEIGHT));
    float startY = (WINDOW_HEIGHT - totalHeight) / 2;
    startY += 60; // ����� �-60 ������� (?2 �"� ���� ����������)

    // ����� ������ ������
    for (int index = 0; index < MenuButtonSize; index++) {
        sf::RectangleShape button;
        button.setSize(sf::Vector2f(BUTTON_WIDTH, BUTTON_HEIGHT));
        button.setPosition(buttonX, startY + index * BUTTON_SPACING);
        button.setTexture(&resourceManager.getTexture(RESOURCES_TEXTURE_NAME[index]));
        m_menuButtons.push_back(button);
    }

    // ��� ���� ���� ��� ����...
    // ����� ��� ������
    m_background.setSize(sf::Vector2f(WINDOW_WIDTH, WINDOW_HEIGHT));
    m_background.setTexture(&resourceManager.getTexture("background"));

    // ����� ��� ��� ������ �����
    m_infoBackground.setSize(sf::Vector2f(WINDOW_WIDTH * 0.8f, WINDOW_HEIGHT * 0.8f));
    m_infoBackground.setFillColor(sf::Color(0, 0, 0, 150));
    m_infoBackground.setPosition((WINDOW_WIDTH - m_infoBackground.getSize().x) / 2,
        (WINDOW_HEIGHT - m_infoBackground.getSize().y) / 3);

    // ����� ���� �����
    m_infoText.setFont(resourceManager.getFont("main_font"));
    m_infoText.setCharacterSize(20);
    m_infoText.setFillColor(sf::Color::White);
    m_infoText.setString(MenuInfo);

    // ������ ���� �����
    sf::FloatRect textBounds = m_infoText.getLocalBounds();
    m_infoText.setPosition((WINDOW_WIDTH - textBounds.width) / 2,
        (WINDOW_HEIGHT - textBounds.height) / 3);

    // ����� ����� ����
    m_backButton.setFont(resourceManager.getFont("main_font"));
    m_backButton.setCharacterSize(20);
    m_backButton.setString("Back to Menu (ESC)");
    m_backButton.setFillColor(sf::Color::Black);

    // ����� ����� �����
    sf::FloatRect backBounds = m_backButton.getLocalBounds();
    m_backButton.setPosition((WINDOW_WIDTH - backBounds.width) / 2,
        WINDOW_HEIGHT - backBounds.height - 50);


    //// ����� ������ ����
    //setMusic();
    //// ����� ����� �����
    //m_muteButton.setFont(resourceManager.getFont("main_font"));
    //m_muteButton.setString("M - Unmuted");
    //m_muteButton.setCharacterSize(20);
    //m_muteButton.setPosition(WINDOW_WIDTH - 150, 10);
    //m_muteButton.setFillColor(sf::Color::White);
}

// ������� ����� ������
void Menu::draw(sf::RenderWindow& window) {
    window.draw(m_background);

    if (!m_showingInfo) {
        for (auto& button : m_menuButtons) {
            window.draw(button);
        }
    }
    else {
        window.draw(m_infoBackground);  // ���� ��� ��� ������ �����
        window.draw(m_infoText);
        window.draw(m_backButton);


        // ����� ����� �����
        sf::Vector2i mousePos = sf::Mouse::getPosition(window);
        if (m_backButton.getGlobalBounds().contains(mousePos.x, mousePos.y)) {
            m_backButton.setFillColor(sf::Color(50, 50, 50));  // ���� ���� ������� ���
        }
        else {
            m_backButton.setFillColor(sf::Color::Black);  // ���� ����
        }
    }
    window.draw(m_muteButton);
}
// ������� ������ ������
void Menu::run_menu(sf::RenderWindow& window) {
    window.clear();
    draw(window);
    window.display();

    sf::Event event;
    while (window.isOpen()) {
        while (window.waitEvent(event)) {
            switch (event.type) {
            case sf::Event::Closed:
                window.close();
                break;
            case sf::Event::KeyPressed:
                if (event.key.code == sf::Keyboard::Escape && m_showingInfo) {
                    returnToMainMenu(window);
                }
                //if (event.key.code == sf::Keyboard::M) {
                //    m_isMuted = !m_isMuted;
                //    if (m_isMuted) {
                //        m_menuMusic->setVolume(0);
                //        m_muteButton.setString("M - Muted");

                //    }
                //    else {
                //        m_menuMusic->setVolume(100);
                //        m_muteButton.setString("M - Unmuted");
                //        window.draw(m_muteButton);
                //    }
                //    window.clear();
                //    draw(window);
                //    window.display();

               // }
                break;
            case sf::Event::MouseButtonPressed:
                handle_mouse_click(event.mouseButton, window);
                break;
            case sf::Event::MouseMoved:
                if (m_showingInfo) {
                    window.clear();
                    draw(window);
                    window.display();
                }
                break;
            default:
                break;


            }
            /*           if (m_stratGame == true) {
                           m_menuMusic->stop();
                           return;
                       }*/
        }

    }
}

// ������� ������ ������ ����� �����
void Menu::handle_mouse_click(sf::Event::MouseButtonEvent& event, sf::RenderWindow& window) {
    if (m_showingInfo) {
        if (m_backButton.getGlobalBounds().contains(event.x, event.y)) {
            returnToMainMenu(window);
            return;
        }
    }

    for (int index = 0; index < m_menuButtons.size(); index++) {
        if (m_menuButtons[index].getGlobalBounds().contains(event.x, event.y)) {
            std::cout << "Button " << RESOURCES_TEXTURE_NAME[index] << " clicked" << std::endl;
            if (index == 0) {
                m_stratGame = true;
                return;
            }
            if (index == 1) {
                m_showingInfo = true;
                window.clear();
                draw(window);
                window.display();
            }
            else if (index == 2) {
               // m_menuMusic->stop();  // ����� ������� ���� ������
                exit(0);
            }
        }
    }
}
// ������� ������ ������ ������ �����
void Menu::returnToMainMenu(sf::RenderWindow& window) {
    m_showingInfo = false;
    window.clear();
    draw(window);
    window.display();
}
//void Menu::setMusic()
//{
//    m_menuMusic = &ResourceManager::getInstance().getMusic("background_music");
//    m_menuMusic->setLoop(true);
//    m_menuMusic->setVolume(100.0f);
//    m_menuMusic->play();
//}
// ������� ������ ���� �� ������ �������� ������ ��� �� ������ ����
bool ::Menu::getStratGame() {
    return m_stratGame;
}
// ������� ������ ������
void Menu::resetMenu()
{
    m_stratGame = false;
    m_showingInfo = false;
    //m_menuMusic->play();
}



