#pragma once
#include <Player.h>

Player::Player(sf::Vector2f startPos)
    : Entity(startPos, sf::Vector2f(0, 0), sf::Color::Yellow, 100.0f),
    startPosition(startPos), isCreatingTrail(false) {

    shape.setSize(size);
    shape.setFillColor(color);
    shape.setPosition(position);
}

void Player::update(float deltaTime, const XonixBoard& board) {
    handleInput();

    // עדכון מיקום הריבוע הגרפי
    shape.setPosition(position);

    // בדיקת מעבר בין שטח פתוח לסגור
    sf::Vector2i gridPos = board.pixelToGrid(static_cast<int>(position.x),
        static_cast<int>(position.y));
    bool inClosedArea = (board.getCellType(gridPos.x, gridPos.y) == CellType::CLOSED);

    if (!isCreatingTrail && !inClosedArea) {
        // התחלת יצירת קו
        startTrail();
    }
    else if (isCreatingTrail && inClosedArea) {
        // סיום יצירת קו
        endTrail(const_cast<XonixBoard&>(board));
    }
}

void Player::draw(sf::RenderWindow& window) {
    window.draw(shape);
}

void Player::handleCollision(const XonixBoard& board) {
    // בדיקת התנגשות עם הקו שהשחקן עצמו יוצר
    if (isCreatingTrail) {
        sf::Vector2i gridPos = board.pixelToGrid(static_cast<int>(position.x),
            static_cast<int>(position.y));
        if (board.checkTrailCollision(gridPos.x, gridPos.y)) {
            // התנגשות עם עצמו - פסילה
            resetPosition();
        }
    }
}

void Player::move(sf::Vector2f direction, const XonixBoard& board) {
    sf::Vector2f newPos = position + direction * speed;

    if (canMoveTo(newPos, board)) {
        position = newPos;

        // הוספה לקו אם יוצרים אחד
        if (isCreatingTrail) {
            sf::Vector2i gridPos = board.pixelToGrid(static_cast<int>(position.x),
                static_cast<int>(position.y));
            trail.push_back(gridPos);
        }
    }
}

void Player::startTrail() {
    if (!isCreatingTrail) {
        isCreatingTrail = true;
        trail.clear();
        sf::Vector2i gridPos = board.pixelToGrid(static_cast<int>(position.x),
            static_cast<int>(position.y));
        trail.push_back(gridPos);
    }
}

void Player::endTrail(XonixBoard& board) {
    if (isCreatingTrail) {
        // הפיכת הקו לשטח סגור
        for (const auto& pos : trail) {
            board.setCellType(pos.x, pos.y, CellType::CLOSED);
        }

        // סגירת השטח
        board.closeArea();

        // איפוס מצב הקו
        isCreatingTrail = false;
        trail.clear();
    }
}

void Player::resetTrail() {
    isCreatingTrail = false;
    trail.clear();
}

void Player::handleInput() {
    // הטיפול בקלט יתבצע במחלקת המשחק הראשית
    // כאן רק נעדכן את המהירות על סמך הקלט שנקבל
}

bool Player::isInClosedArea(const XonixBoard& board) const {
    sf::Vector2i gridPos = board.pixelToGrid(static_cast<int>(position.x),
        static_cast<int>(position.y));
    CellType cellType = board.getCellType(gridPos.x, gridPos.y);
    return cellType == CellType::CLOSED;
}

// Enemy - פונקציות נוספות
void Enemy::pauseMovement() {
    // שמירת המהירות הנוכחית ועצירה
    // ניתן להוסיף שדה savedVelocity למחלקה
    velocity = sf::Vector2f(0, 0);
}

void Enemy::resumeMovement() {
    // שחזור המהירות - זה דורש שמירה מוקדמת של המהירות
    // לצורך הדוגמה, נשתמש במהירות ברירת מחדל
    if (velocity.x == 0 && velocity.y == 0) {
        velocity = sf::Vector2f(50.0f, 50.0f);
    }
}

bool Enemy::checkTrailCollision(const Player& player) const {
    if (!player.isInTrail()) return false;

    const auto& trail = player.getTrail();
    // נזדקק לקבל הפניה ללוח כדי לבצע את ההמרה
    // לכן נעביר את הבדיקה למחלקת ה-EntityManager

    // בינתיים, בדיקה פשוטה על סמך מיקום
    sf::FloatRect enemyBounds = getBounds();
    sf::Vector2f playerPos = player.getPosition();
    sf::FloatRect playerBounds(playerPos.x, playerPos.y, 20, 20);

    return enemyBounds.intersects(playerBounds);
}

bool Player::canMoveTo(sf::Vector2f newPos, const XonixBoard& board) const {
    sf::Vector2i gridPos = board.pixelToGrid(static_cast<int>(newPos.x),
        static_cast<int>(newPos.y));
    CellType cellType = board.getCellType(gridPos.x, gridPos.y);

    // השחקן יכול לנוע בשטח פתוח או סגור, אבל לא דרך גבולות
    return cellType != CellType::BORDER;
}