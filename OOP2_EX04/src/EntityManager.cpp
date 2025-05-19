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
    // הסרת אויבים שסומנו להשמדה (אם נוסיף מנגנון כזה)
    enemies.erase(
        std::remove_if(enemies.begin(), enemies.end(),
            [](const std::unique_ptr<Enemy>& enemy) {
                return enemy == nullptr; // או תנאי אחר להשמדה
            }),
        enemies.end()
    );
}

void EntityManager::updateAll(float deltaTime, XonixBoard& board) {
    // עדכון השחקן
    if (player) {
        player->update(deltaTime, board);
    }

    // עדכון כל האויבים
    for (auto& enemy : enemies) {
        if (enemy) {
            enemy->update(deltaTime, board);
        }
    }

    // בדיקת התנגשויות אחרי העדכון
    if (checkPlayerEnemyCollisions() || checkEnemyTrailCollisions()) {
        // פסילה - איפוס מיקומים
        resetAllPositions();
        // ניקוי הקו של השחקן
        if (player && player->isInTrail()) {
            player->resetTrail();
        }
    }
}

void EntityManager::drawAll(sf::RenderWindow& window) {
    // ציור כל האויבים
    for (const auto& enemy : enemies) {
        if (enemy) {
            enemy->draw(window);
        }
    }

    // ציור השחקן אחרון (כדי שיהיה מעל האויבים)
    if (player) {
        player->draw(window);
    }
}

bool EntityManager::checkPlayerEnemyCollisions() {
    if (!player) return false;

    // בדיקת התנגשות בין השחקן לכל אויב
    for (const auto& enemy : enemies) {
        if (enemy && player->checkCollisionWith(*enemy)) {
            return true;
        }
    }
    return false;
}

bool EntityManager::checkEnemyTrailCollisions() {
    if (!player || !player->isInTrail()) return false;

    // בדיקת התנגשות בין אויב לקו של השחקן
    for (const auto& enemy : enemies) {
        if (enemy && enemy->checkTrailCollision(*player)) {
            return true;
        }
    }
    return false;
}

void EntityManager::resetAllPositions() {
    // איפוס מיקום השחקן
    if (player) {
        player->resetPosition();
    }

    // איפוס מיקום כל האויבים
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

    // קריאת השורה הראשונה (הגדרות כלליות)
    if (std::getline(file, line) && levelNumber == 0) {
        // שורה ראשונה מכילה גודל מסך ומספר חיים
        // נעבד אותה במקום אחר
        return;
    }

    // חיפוש השלב הרצוי
    while (std::getline(file, line) && currentLevel < levelNumber) {
        currentLevel++;
    }

    if (currentLevel != levelNumber) {
        throw std::runtime_error("Level " + std::to_string(levelNumber) + " not found");
    }

    // עיבוד שורת השלב
    std::istringstream iss(line);
    float requiredPercentage;
    int enemyCount;

    if (!(iss >> requiredPercentage >> enemyCount)) {
        throw std::runtime_error("Invalid level format in line: " + line);
    }

    // ניקוי אויבים קיימים
    clearEnemies();

    // יצירת אויבים חדשים במיקומים רנדומליים
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_real_distribution<float> xDist(100.0f, 700.0f);
    std::uniform_real_distribution<float> yDist(100.0f, 500.0f);
    std::uniform_real_distribution<float> velDist(-100.0f, 100.0f);

    for (int i = 0; i < enemyCount; ++i) {
        sf::Vector2f startPos(xDist(gen), yDist(gen));
        sf::Vector2f velocity(velDist(gen), velDist(gen));

        // ודא שהמהירות לא אפס
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

// פונקציות עזר נוספות
void EntityManager::setPlayerPosition(sf::Vector2f position) {
    if (player) {
        player->setPosition(position);
    }
}

void EntityManager::pauseAllEntities() {
    // עצירת תנועה זמנית (למשל בזמן pause)
    if (player) {
        player->setVelocity(sf::Vector2f(0, 0));
    }

    for (auto& enemy : enemies) {
        if (enemy) {
            // שמירת המהירות הנוכחית ועצירה זמנית
            enemy->pauseMovement();
        }
    }
}

void EntityManager::resumeAllEntities() {
    // חידוש תנועה
    for (auto& enemy : enemies) {
        if (enemy) {
            enemy->resumeMovement();
        }
    }
}

// פונקציה לדיבוג - הדפסת מידע על כל הישויות
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