#pragma once

class Player : public Entity {
private:
    sf::Vector2f startPosition;     // ����� ����� ����� �� �����
    bool isCreatingTrail;           // ��� ����� ���� �� ����
    std::vector<sf::Vector2i> trail; // ��� ������ ����
    sf::RectangleShape shape;       // ���� ������ �� �����

public:
    Player(sf::Vector2f startPos);

    // ����� ��������� �����������
    virtual void update(float deltaTime, const XonixBoard& board) override;
    virtual void draw(sf::RenderWindow& window) override;
    virtual void handleCollision(const XonixBoard& board) override;

    // �������� �������� �����
    void move(sf::Vector2f direction, const XonixBoard& board);
    void startTrail();
    void endTrail(XonixBoard& board);
    void resetPosition();
    void handleInput();

    // getters
    bool isInTrail() const { return isCreatingTrail; }
    const std::vector<sf::Vector2i>& getTrail() const { return trail; }
    sf::Vector2f getStartPosition() const { return startPosition; }

    // ������ ���
    bool isInClosedArea(const XonixBoard& board) const;
    bool canMoveTo(sf::Vector2f newPos, const XonixBoard& board) const;
};