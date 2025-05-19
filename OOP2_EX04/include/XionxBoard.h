#pragma once
#include <SFML/Graphics.hpp>
#include <vector>

class XonixBoard {
private:
    int width, height;  // גודל הלוח בפיקסלים
    int cellSize;       // גודל כל תא
    int gridWidth, gridHeight; // גודל הרשת

    // רשת המייצגת את מצב כל תא בלוח
    std::vector<std::vector<CellType>> grid;

    // נקודות הקו הנוכחי שהשחקן יוצר
    std::vector<sf::Vector2i> currentTrail;

public:
    XonixBoard(int w, int h, int cell_size);

    // פונקציות בסיסיות
    void initializeBoard();
    void draw(sf::RenderWindow& window);

    // ניהול התא
    CellType getCellType(int x, int y) const;
    void setCellType(int x, int y, CellType type);

    // ניהול הקו
    void startTrail(int x, int y);
    void addToTrail(int x, int y);
    void clearTrail();
    bool isTrailComplete(int x, int y);

    // סגירת שטח
    void closeArea();
    float calculateClosedPercentage() const;

    // בדיקות התנגשות
    bool isInBounds(int x, int y) const;
    bool isValidMove(int x, int y) const;
    bool checkTrailCollision(int x, int y) const;

    // אלגוריתם Flood Fill לסגירת השטח
    void floodFill(int startX, int startY, bool hasEnemies);

    // פונקציות עזר
    sf::Vector2i pixelToGrid(int pixelX, int pixelY) const;
    sf::Vector2i gridToPixel(int gridX, int gridY) const;

private:
    // פונקציות פרטיות לעיבוד השטח
    void markClosedArea(const std::vector<sf::Vector2i>& area);
    std::vector<sf::Vector2i> findEnclosedArea();
    bool areaContainsEnemies(const std::vector<sf::Vector2i>& area);
};