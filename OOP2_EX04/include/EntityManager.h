#pragma once
class EntityManager {
private:
    std::unique_ptr<Player> player;
    std::vector<std::unique_ptr<Enemy>> enemies;

public:
    EntityManager();
    ~EntityManager() = default;

    // ניהול השחקן
    void createPlayer(sf::Vector2f startPos);
    Player* getPlayer() { return player.get(); }

    // ניהול האויבים
    void addEnemy(sf::Vector2f startPos, sf::Vector2f velocity);
    void clearEnemies();
    const std::vector<std::unique_ptr<Enemy>>& getEnemies() const { return enemies; }

    // עדכון וציור כל הישויות
    void updateAll(float deltaTime, XonixBoard& board);
    void drawAll(sf::RenderWindow& window);

    // בדיקת התנגשויות
    bool checkPlayerEnemyCollisions();
    bool checkEnemyTrailCollisions();

    // איפוס מיקומים במקרה של פסילה
    void resetAllPositions();
};