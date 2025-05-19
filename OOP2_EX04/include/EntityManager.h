#pragma once
class EntityManager {
private:
    std::unique_ptr<Player> player;
    std::vector<std::unique_ptr<Enemy>> enemies;

public:
    EntityManager();
    ~EntityManager() = default;

    // ����� �����
    void createPlayer(sf::Vector2f startPos);
    Player* getPlayer() { return player.get(); }

    // ����� �������
    void addEnemy(sf::Vector2f startPos, sf::Vector2f velocity);
    void clearEnemies();
    const std::vector<std::unique_ptr<Enemy>>& getEnemies() const { return enemies; }

    // ����� ����� �� �������
    void updateAll(float deltaTime, XonixBoard& board);
    void drawAll(sf::RenderWindow& window);

    // ����� ���������
    bool checkPlayerEnemyCollisions();
    bool checkEnemyTrailCollisions();

    // ����� ������� ����� �� �����
    void resetAllPositions();
};