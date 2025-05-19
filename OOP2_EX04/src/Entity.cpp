#pragma once
#include "Entity.h"

Entity::Entity(sf::Vector2f pos, sf::Vector2f vel, sf::Color col, float spd)
    : position(pos), velocity(vel), color(col), speed(spd) {
    size = sf::Vector2f(20.0f, 20.0f); // גודל ברירת מחדל
}

sf::FloatRect Entity::getBounds() const {
    return sf::FloatRect(position.x, position.y, size.x, size.y);
}

bool Entity::checkCollisionWith(const Entity& other) const {
    return getBounds().intersects(other.getBounds());
}

bool Entity::checkBoardCollision(const XonixBoard& board) const {
    // המרה למקום ברשת ובדיקה מול הלוח
    sf::Vector2i gridPos = board.pixelToGrid(static_cast<int>(position.x),
        static_cast<int>(position.y));
    CellType cellType = board.getCellType(gridPos.x, gridPos.y);
    return cellType == CellType::CLOSED || cellType == CellType::BORDER;
}