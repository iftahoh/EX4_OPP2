#pragma once

class Player : public Entity {
private:
    sf::Vector2f startPosition;     // נקודת התחלה למקרה של פסילה
    bool isCreatingTrail;           // האם השחקן יוצר קו כרגע
    std::vector<sf::Vector2i> trail; // הקו שהשחקן יוצר
    sf::RectangleShape shape;       // צורת הריבוע של השחקן

public:
    Player(sf::Vector2f startPos);

    // יישום הפונקציות הוירטואליות
    virtual void update(float deltaTime, const XonixBoard& board) override;
    virtual void draw(sf::RenderWindow& window) override;
    virtual void handleCollision(const XonixBoard& board) override;

    // פונקציות ייחודיות לשחקן
    void move(sf::Vector2f direction, const XonixBoard& board);
    void startTrail();
    void endTrail(XonixBoard& board);
    void resetPosition();
    void handleInput();

    // getters
    bool isInTrail() const { return isCreatingTrail; }
    const std::vector<sf::Vector2i>& getTrail() const { return trail; }
    sf::Vector2f getStartPosition() const { return startPosition; }

    // בדיקות מצב
    bool isInClosedArea(const XonixBoard& board) const;
    bool canMoveTo(sf::Vector2f newPos, const XonixBoard& board) const;
};