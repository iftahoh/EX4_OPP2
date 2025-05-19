#pragma once
#include "SFML/Graphics.hpp"
#include "StatiicObject/StaticObject.h"
#include "MovingObjects/Player.h"
#include "MovingObjects/Guard.h"
#include "Macros.h"
#include "WinScreen.h"
#include "LossScreen.h"
#include <LossScreen.h>

class GameManager
{
public:
    //-------------- Public Functions --------------
    GameManager();
    void run(sf::RenderWindow& window);
    bool isGameOver() const { return m_player.getLife() <= 0; }
    void resetGame();
    bool shouldReturnToMenu() const { return m_returnToMenu; }
    static GameManager& getInstance();
    //bool isMusicPlaying();

private:
    //-------------- Private Functions --------------
    //void startMusic(sf::Music* music, const int level);
    //void changeMusic(bool what);
    void updateStatics(const sf::Time& deltaTime);
    //void placeBomb();
    void processEvents(sf::RenderWindow& window);
    void update(float deltaTime);
    void loadLevel(sf::RenderWindow& window, int level);
    void render(sf::RenderWindow& window);
    void handleCollisions();
    //void removeRandomGuard();
    //void addGift(int giftType, sf::Vector2f Pos);
    //-------------- Members --------------
    std::vector<std::unique_ptr<StaticObject>> m_staticObjects;
    Player m_player;
    std::vector<Guard> m_guards;
    sf::Time m_elapsedTime;
    sf::Text m_infoText;
    sf::Text m_muteText;  // טקסט חדש להצגת סטטוס ההשתקה
    //bool m_myMusic = true;
    //sf::Music* m_music = nullptr;
    int m_level = 1;
    bool m_returnToMenu = false;
    bool m_isPaused = false; // משתנה חדש לסימון חזרה לתפריט
    //int m_rocksDestroyed = 0;  // מונה לסלעים שהתפוצצו
    const float TIME_LIMIT = 180.f;  // 3 דקות בשניות
    bool m_hasTimeLimit = false;     // האם השלב הנוכחי מוגבל בזמן
    sf::Time m_freezeTime = sf::Time::Zero;
    //WinScreen m_winScreen;
   // LossScreen m_lossScreen;

};