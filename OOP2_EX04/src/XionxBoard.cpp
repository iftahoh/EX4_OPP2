#include <XionxBoard.h>

XonixBoard::XonixBoard(int w, int h, int cell_size)
    : width(w), height(h), cellSize(cell_size) {
    gridWidth = width / cellSize;
    gridHeight = height / cellSize;
    grid.resize(gridHeight, std::vector<CellType>(gridWidth, CellType::OPEN));
    initializeBoard();
}

void XonixBoard::initializeBoard() {
    // יצירת מסגרת סגורה בתחילת המשחק
    for (int y = 0; y < gridHeight; ++y) {
        for (int x = 0; x < gridWidth; ++x) {
            // גבולות המסך - תמיד סגורים
            if (x == 0 || x == gridWidth - 1 || y == 0 || y == gridHeight - 1) {
                grid[y][x] = CellType::BORDER;
            }
            // מסגרת התחלתית - כ-20% מהמסך
            else if (x < gridWidth * 0.2 || x > gridWidth * 0.8 ||
                y < gridHeight * 0.2 || y > gridHeight * 0.8) {
                grid[y][x] = CellType::CLOSED;
            }
            // השאר נשאר פתוח
            else {
                grid[y][x] = CellType::OPEN;
            }
        }
    }
}

void XonixBoard::draw(sf::RenderWindow& window) {
    sf::RectangleShape cell(sf::Vector2f(cellSize, cellSize));

    for (int y = 0; y < gridHeight; ++y) {
        for (int x = 0; x < gridWidth; ++x) {
            cell.setPosition(x * cellSize, y * cellSize);

            switch (grid[y][x]) {
            case CellType::OPEN:
                cell.setFillColor(sf::Color::Black);
                break;
            case CellType::CLOSED:
                cell.setFillColor(sf::Color::Green);
                break;
            case CellType::TRAIL:
                cell.setFillColor(sf::Color::Magenta);
                break;
            case CellType::BORDER:
                cell.setFillColor(sf::Color::Blue);
                break;
            }

            window.draw(cell);
        }
    }
}

CellType XonixBoard::getCellType(int x, int y) const {
    if (!isInBounds(x, y)) return CellType::BORDER;
    return grid[y][x];
}

void XonixBoard::setCellType(int x, int y, CellType type) {
    if (isInBounds(x, y)) {
        grid[y][x] = type;
    }
}

bool XonixBoard::isInBounds(int x, int y) const {
    return x >= 0 && x < gridWidth && y >= 0 && y < gridHeight;
}

bool XonixBoard::isValidMove(int x, int y) const {
    if (!isInBounds(x, y)) return false;
    CellType type = grid[y][x];
    return type == CellType::OPEN || type == CellType::CLOSED;
}

void XonixBoard::startTrail(int x, int y) {
    currentTrail.clear();
    currentTrail.push_back({ x, y });
    setCellType(x, y, CellType::TRAIL);
}

void XonixBoard::addToTrail(int x, int y) {
    currentTrail.push_back({ x, y });
    setCellType(x, y, CellType::TRAIL);
}

void XonixBoard::clearTrail() {
    // מחיקת הקו מהלוח
    for (const auto& pos : currentTrail) {
        setCellType(pos.x, pos.y, CellType::OPEN);
    }
    currentTrail.clear();
}

bool XonixBoard::isTrailComplete(int x, int y) {
    // בדיקה אם הגענו לשטח סגור
    return getCellType(x, y) == CellType::CLOSED;
}

void XonixBoard::closeArea() {
    if (currentTrail.empty()) return;

    // הפיכת הקו לחלק מהשטח הסגור
    for (const auto& pos : currentTrail) {
        setCellType(pos.x, pos.y, CellType::CLOSED);
    }

    // מציאת השטח שיש לסגור באמצעות Flood Fill
    // כאן נצטרך לממש את האלגוריתם
    // floodFill(/* פרמטרים מתאימים */);

    currentTrail.clear();
}

bool XonixBoard::checkTrailCollision(int x, int y) const {
    // בדיקה אם הנקודה נמצאת על הקו הנוכחי
    for (const auto& pos : currentTrail) {
        if (pos.x == x && pos.y == y) {
            return true;
        }
    }
    return false;
}

sf::Vector2i XonixBoard::pixelToGrid(int pixelX, int pixelY) const {
    return { pixelX / cellSize, pixelY / cellSize };
}

sf::Vector2i XonixBoard::gridToPixel(int gridX, int gridY) const {
    return { gridX * cellSize, gridY * cellSize };
}

float XonixBoard::calculateClosedPercentage() const {
    int totalCells = gridWidth * gridHeight;
    int closedCells = 0;

    for (int y = 0; y < gridHeight; ++y) {
        for (int x = 0; x < gridWidth; ++x) {
            if (grid[y][x] == CellType::CLOSED || grid[y][x] == CellType::BORDER) {
                closedCells++;
            }
        }
    }

    return (float)closedCells / totalCells * 100.0f;
}