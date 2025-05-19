#pragma once

class Enemy : public Entity {
private:
    sf::CircleShape shape;          // צורת העיגול של האויב
    sf::Vector2f startPosition;     // נקודת התחלה
    bool isInOpenArea;              // האם האויב בשטח פתוח

public:
    Enemy(sf::Vector2f startPos, sf::Vector2f initialVelocity);

    // יישום הפונקציות הוירטואליות
    virtual void update(float deltaTime, const XonixBoard& board) override;
    virtual void draw(sf::RenderWindow& window) override;
    virtual void handleCollision(const XonixBoard& board) override;

    // פונקציות ייחודיות לאויב
    void bounceOffWall(sf::Vector2f normal);
    void resetPosition();
    bool checkTrailCollision(const Player& player) const;

    // getters
    sf::Vector2f getStartPosition() const { return startPosition; }
    bool getIsInOpenArea() const { return isInOpenArea; }
};