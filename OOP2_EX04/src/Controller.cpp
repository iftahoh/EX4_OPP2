#include "Controller.h"
#include <iostream>
// ���� ���
Controller::Controller()
{
}
// ������� ����� �����
void Controller::run()
{
    m_window.create(sf::VideoMode(WINDOW_WIDTH, WINDOW_HEIGHT), "BomberMan");
    m_window.setView(sf::View(sf::FloatRect(0, 0, 1260, 720)));
    m_window.setFramerateLimit(60);

    while (m_window.isOpen()) {
        m_menu.resetMenu();  // ����� ������
        m_menu.run_menu(m_window);

        if (!m_window.isOpen()) break;

        /*if (m_menu.getStratGame()) {
            m_game.resetGame();  // ����� ������� ���� ���
            m_game.run(m_window);

            if (m_game.isGameOver() || m_game.shouldReturnToMenu()) {
                continue;
            }
        }*/
    }
}