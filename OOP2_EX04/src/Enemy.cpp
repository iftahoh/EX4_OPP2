#pragma once
#include "Enemy.h"

Enemy::Enemy(sf::Vector2f startPos, sf::Vector2f initialVelocity)
    : Entity(startPos, initialVelocity, sf::Color::White, 50.0f),
    startPosition(startPos), isInOpenArea(true) {

    shape.setRadius(size.x / 2);
    shape.setFillColor(color);
    shape.setPosition(position);
}

void Enemy::update(float deltaTime, const XonixBoard& board) {
    // �����
    position += velocity * deltaTime;

    // ����� ������� �� �����
    handleCollision(board);

    // ����� ����� ������ �����
    shape.setPosition(position);
}

void Enemy::draw(sf::RenderWindow& window) {
    window.draw(shape);
}

void Enemy::handleCollision(const XonixBoard& board) {
    sf::Vector2i gridPos = board.pixelToGrid(static_cast<int>(position.x),
        static_cast<int>(position.y));
    CellType cellType = board.getCellType(gridPos.x, gridPos.y);

    if (cellType == CellType::CLOSED || cellType == CellType::BORDER) {
        // ������� �� ��� - ����� �����
        // ��� ����� ���� �� ������ ���� ����� ������ ��������
        bounceOffWall(sf::Vector2f(1.0f, 1.0f)); // �� ���� ������
        isInOpenArea = false;
    }
    else {
        isInOpenArea = true;
    }
}

void Enemy::bounceOffWall(sf::Vector2f normal) {
    // ����� ����� �����
    velocity -= 2.0f * (velocity.x * normal.x + velocity.y * normal.y) * normal;
}

void Enemy::resetPosition() {
    position = startPosition;
    shape.setPosition(position);
}