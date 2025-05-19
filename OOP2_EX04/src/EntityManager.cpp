#pragma once
#include "EntityManager.h"

EntityManager::EntityManager() : player(nullptr) {
}

void EntityManager::createPlayer(sf::Vector2f startPos) {
    player = std::make_unique<Player>(startPos);
}

void EntityManager::addEnemy(sf::Vector2f startPos, sf::Vector2f velocity) {
    enemies.push_back(std::make_unique<Enemy>(startPos, velocity));
}

void EntityManager::clearEnemies() {
    enemies.clear();
}

void EntityManager::removeDestroyedEnemies() {
    // ���� ������ ������ ������ (�� ����� ������ ���)
    enemies.erase(
        std::remove_if(enemies.begin(), enemies.end(),
            [](const std::unique_ptr<Enemy>& enemy) {
                return enemy == nullptr; // �� ���� ��� ������
            }),
        enemies.end()
    );
}

void EntityManager::updateAll(float deltaTime, XonixBoard& board) {
    // ����� �����
    if (player) {
        player->update(deltaTime, board);
    }

    // ����� �� �������
    for (auto& enemy : enemies) {
        if (enemy) {
            enemy->update(deltaTime, board);
        }
    }

    // ����� ��������� ���� ������
    if (checkPlayerEnemyCollisions() || checkEnemyTrailCollisions()) {
        // ����� - ����� �������
        resetAllPositions();
        // ����� ��� �� �����
        if (player && player->isInTrail()) {
            player->resetTrail();
        }
    }
}

void EntityManager::drawAll(sf::RenderWindow& window) {
    // ���� �� �������
    for (const auto& enemy : enemies) {
        if (enemy) {
            enemy->draw(window);
        }
    }

    // ���� ����� ����� (��� ����� ��� �������)
    if (player) {
        player->draw(window);
    }
}

bool EntityManager::checkPlayerEnemyCollisions() {
    if (!player) return false;

    // ����� ������� ��� ����� ��� ����
    for (const auto& enemy : enemies) {
        if (enemy && player->checkCollisionWith(*enemy)) {
            return true;
        }
    }
    return false;
}

bool EntityManager::checkEnemyTrailCollisions() {
    if (!player || !player->isInTrail()) return false;

    // ����� ������� ��� ���� ��� �� �����
    for (const auto& enemy : enemies) {
        if (enemy && enemy->checkTrailCollision(*player)) {
            return true;
        }
    }
    return false;
}

void EntityManager::resetAllPositions() {
    // ����� ����� �����
    if (player) {
        player->resetPosition();
    }

    // ����� ����� �� �������
    for (auto& enemy : enemies) {
        if (enemy) {
            enemy->resetPosition();
        }
    }
}

void EntityManager::loadLevelFromFile(const std::string& filename, int levelNumber) {
    std::ifstream file(filename);
    if (!file.is_open()) {
        throw std::runtime_error("Cannot open level file: " + filename);
    }

    std::string line;
    int currentLevel = 0;

    // ����� ����� ������� (������ ������)
    if (std::getline(file, line) && levelNumber == 0) {
        // ���� ������ ����� ���� ��� ����� ����
        // ���� ���� ����� ���
        return;
    }

    // ����� ���� �����
    while (std::getline(file, line) && currentLevel < levelNumber) {
        currentLevel++;
    }

    if (currentLevel != levelNumber) {
        throw std::runtime_error("Level " + std::to_string(levelNumber) + " not found");
    }

    // ����� ���� ����
    std::istringstream iss(line);
    float requiredPercentage;
    int enemyCount;

    if (!(iss >> requiredPercentage >> enemyCount)) {
        throw std::runtime_error("Invalid level format in line: " + line);
    }

    // ����� ������ ������
    clearEnemies();

    // ����� ������ ����� �������� ���������
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_real_distribution<float> xDist(100.0f, 700.0f);
    std::uniform_real_distribution<float> yDist(100.0f, 500.0f);
    std::uniform_real_distribution<float> velDist(-100.0f, 100.0f);

    for (int i = 0; i < enemyCount; ++i) {
        sf::Vector2f startPos(xDist(gen), yDist(gen));
        sf::Vector2f velocity(velDist(gen), velDist(gen));

        // ��� �������� �� ���
        if (std::abs(velocity.x) < 10.0f) velocity.x = 50.0f;
        if (std::abs(velocity.y) < 10.0f) velocity.y = 50.0f;

        addEnemy(startPos, velocity);
    }

    file.close();
}

bool EntityManager::isPlayerInTrail() const {
    return player && player->isInTrail();
}

sf::Vector2f EntityManager::getPlayerPosition() const {
    if (player) {
        return player->getPosition();
    }
    return sf::Vector2f(0, 0);
}

// �������� ��� ������
void EntityManager::setPlayerPosition(sf::Vector2f position) {
    if (player) {
        player->setPosition(position);
    }
}

void EntityManager::pauseAllEntities() {
    // ����� ����� ����� (���� ���� pause)
    if (player) {
        player->setVelocity(sf::Vector2f(0, 0));
    }

    for (auto& enemy : enemies) {
        if (enemy) {
            // ����� ������� ������� ������ �����
            enemy->pauseMovement();
        }
    }
}

void EntityManager::resumeAllEntities() {
    // ����� �����
    for (auto& enemy : enemies) {
        if (enemy) {
            enemy->resumeMovement();
        }
    }
}

// ������� ������ - ����� ���� �� �� �������
void EntityManager::printDebugInfo() const {
    std::cout << "=== Entity Manager Debug Info ===" << std::endl;

    if (player) {
        sf::Vector2f pos = player->getPosition();
        std::cout << "Player: Position(" << pos.x << ", " << pos.y << ")";
        std::cout << " InTrail: " << (player->isInTrail() ? "Yes" : "No") << std::endl;
    }
    else {
        std::cout << "Player: None" << std::endl;
    }

    std::cout << "Enemies: " << enemies.size() << std::endl;
    for (size_t i = 0; i < enemies.size(); ++i) {
        if (enemies[i]) {
            sf::Vector2f pos = enemies[i]->getPosition();
            sf::Vector2f vel = enemies[i]->getVelocity();
            std::cout << "  Enemy " << i << ": Position(" << pos.x << ", " << pos.y << ")";
            std::cout << " Velocity(" << vel.x << ", " << vel.y << ")" << std::endl;
        }
    }
    std::cout << "=================================" << std::endl;
}