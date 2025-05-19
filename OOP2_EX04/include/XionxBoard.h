#pragma once
#include <SFML/Graphics.hpp>
#include <vector>

class XonixBoard {
private:
    int width, height;  // ���� ���� ��������
    int cellSize;       // ���� �� ��
    int gridWidth, gridHeight; // ���� ����

    // ��� ������� �� ��� �� �� ����
    std::vector<std::vector<CellType>> grid;

    // ������ ��� ������ ������ ����
    std::vector<sf::Vector2i> currentTrail;

public:
    XonixBoard(int w, int h, int cell_size);

    // �������� �������
    void initializeBoard();
    void draw(sf::RenderWindow& window);

    // ����� ���
    CellType getCellType(int x, int y) const;
    void setCellType(int x, int y, CellType type);

    // ����� ���
    void startTrail(int x, int y);
    void addToTrail(int x, int y);
    void clearTrail();
    bool isTrailComplete(int x, int y);

    // ����� ���
    void closeArea();
    float calculateClosedPercentage() const;

    // ������ �������
    bool isInBounds(int x, int y) const;
    bool isValidMove(int x, int y) const;
    bool checkTrailCollision(int x, int y) const;

    // �������� Flood Fill ������ ����
    void floodFill(int startX, int startY, bool hasEnemies);

    // �������� ���
    sf::Vector2i pixelToGrid(int pixelX, int pixelY) const;
    sf::Vector2i gridToPixel(int gridX, int gridY) const;

private:
    // �������� ������ ������ ����
    void markClosedArea(const std::vector<sf::Vector2i>& area);
    std::vector<sf::Vector2i> findEnclosedArea();
    bool areaContainsEnemies(const std::vector<sf::Vector2i>& area);
};