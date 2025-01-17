#include <SFML/Graphics.hpp>

#include "constants.h"
#include "ball.h"
#ifndef PLAYERS_HPP
#define PLAYERS_HPP

float calculateBallTargetY(Ball& ball, float playerXpos);
class Player {
private:
    int m_points{};
    sf::Vector2f m_position{};
    sf::RectangleShape m_rectangle{};
    int m_lives{};
    sf::Text& m_score;

public:
    Player(sf::Vector2f position, sf::Text& player_score)
        :m_position{ position }, m_points{ 0 }, m_lives{5}, m_score{player_score}
    {
        m_rectangle.setPosition(m_position);
        m_rectangle.setSize(sf::Vector2f(PLAYER_WIDTH, PLAYER_HEIGHT));
        m_rectangle.setFillColor(sf::Color::White);
        std::cout << "Player created" << "\n";
    }

    void moveUp(float dt) {
		this->m_position.y -= PLAYER_SPEED * dt;
        m_rectangle.setPosition(m_position);

        if (m_position.y < 0) {
            m_position.y = 0;
        }
    }

    void moveDown(float dt) {
         this->m_position.y += PLAYER_SPEED * dt;
        m_rectangle.setPosition(m_position);

        if (m_position.y > (SCREEN_HEIGHT)-PLAYER_HEIGHT) {
            m_position.y = SCREEN_HEIGHT - PLAYER_HEIGHT;
        }

    }
    float getPlayerPosX() {
        return m_position.x;
   }
    void score() {
        m_points++;
        m_score.setString(std::to_string(m_points));
        std::cout << m_points << "\n\n";
    }

    void minusLives() {
        m_lives--;
        std::cout << m_lives << "\n\n";
    }

    void draw(sf::RenderWindow& window) {
        window.draw(this->m_rectangle);
    }

 
     void collided(Ball& ball) {
         if (m_rectangle.getGlobalBounds().intersects(ball.getGlobalBounds()))
             ball.reverseXDir();
    }


     void aiMove(Ball& ball, float dt) {
         float targetY = calculateBallTargetY(ball, m_position.x);

         float paddleCenterY = m_position.y + PLAYER_HEIGHT / 2;

         if (paddleCenterY < targetY - 10) {
             moveDown(dt);
         }
         else if (paddleCenterY > targetY + 10) {
             moveUp(dt);
         }
     }

};



float calculateBallTargetY(Ball& ball, float playerXpos) {
    float dx = ball.getBallDirectionX();
    float dy = ball.getBallDirectionY();

    float slope = dy / dx;

    float yIntercept = ball.getBallY() - (slope * ball.getBallX());

    float targetY = slope * playerXpos + yIntercept;
    while (targetY < 0 || targetY > SCREEN_HEIGHT) {
        if (targetY < 0) {
            targetY = -targetY; // Reflect off the top wall
        }
        else if (targetY > SCREEN_HEIGHT) {
            targetY = 2 * SCREEN_HEIGHT - targetY; // Reflect off the bottom wall
        }
    }

    return targetY;
}


#endif