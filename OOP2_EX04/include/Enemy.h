#pragma once

class Enemy : public Entity {
private:
    sf::CircleShape shape;          // ���� ������ �� �����
    sf::Vector2f startPosition;     // ����� �����
    bool isInOpenArea;              // ��� ����� ���� ����

public:
    Enemy(sf::Vector2f startPos, sf::Vector2f initialVelocity);

    // ����� ��������� �����������
    virtual void update(float deltaTime, const XonixBoard& board) override;
    virtual void draw(sf::RenderWindow& window) override;
    virtual void handleCollision(const XonixBoard& board) override;

    // �������� �������� �����
    void bounceOffWall(sf::Vector2f normal);
    void resetPosition();
    bool checkTrailCollision(const Player& player) const;

    // getters
    sf::Vector2f getStartPosition() const { return startPosition; }
    bool getIsInOpenArea() const { return isInOpenArea; }
};