#include <SFML/Graphics.hpp>
#include "constants.h"
#include <iostream>

#ifndef BALL_HPP
#define BALL_HPP
#include <random>

class Ball {
private:
    sf::Vector2f m_position{};
    sf::RectangleShape m_ball{};
    float m_ball_speed{};
    sf::Vector2f m_direction{};


public:
    Ball( float speed = 300.0f)
       :m_ball_speed{ speed }
    { 
        std::random_device rd;
        std::mt19937 gen(rd());

        std::uniform_real_distribution<float> distY(50.0f, SCREEN_WIDTH - 50.0f);

        std::uniform_int_distribution<> direction(-1, 1);
         
        float dx = direction(gen) * m_ball_speed;
        float dy = direction(gen) * m_ball_speed;

        std::cout << dx << "\n";
        if (dx == 0) {
            std::cout << "dx is 0";
            dx = m_ball_speed;
        }
            
        if (dy == 0) dy = m_ball_speed;
        m_direction.x = dx;
        m_direction.y = dy;
    
       
        m_position.x = SCREEN_WIDTH / 2;
        m_position.y = distY(gen);
        m_ball.setPosition(m_position);




        m_ball.setSize(sf::Vector2f(BALL_SIZE, BALL_SIZE));
        m_ball.setFillColor(sf::Color::White);
        std::cout << "Ball created" << "\n";
    }

    void draw(sf::RenderWindow& window, float dt) {
        m_position.x += m_direction.x * dt;
        m_position.y += m_direction.y * dt;

        if (m_position.y <= 0 || m_position.y >= SCREEN_HEIGHT - BALL_SIZE * 2) {
            m_direction.y = -m_direction.y;
        }
		  

        m_ball.setPosition(m_position);
        window.draw(this->m_ball);
    }


  
    bool outOfBounds() {
        if (m_position.x <= 0 || m_position.x >= SCREEN_WIDTH - BALL_SIZE * 2) {

            return true;
        }
            return false;

    }

    void reverseXDir() {
        m_direction.x = -m_direction.x; 
		 std::random_device rd;
        std::mt19937 gen(rd());
        std::uniform_real_distribution<float> direction(-1.0f, 1.0f);

         
        float dx = direction(gen) * m_ball_speed;
        float dy = direction(gen) * m_ball_speed;

        std::cout << dx << "\n";
        if (dx == 0) {
            std::cout << "dx is 0";
            dx = m_ball_speed;
        }
            
        if (dy == 0) dy = m_ball_speed;
        m_direction.y = dy;
    }






	   void setPosition(float x, float y) {
       m_position.x = x;            
       m_position.y = y;
       m_ball.setPosition(m_position); 
   }


    sf::FloatRect getGlobalBounds() const {
        return m_ball.getGlobalBounds();
    }
    

   sf::Vector2f getPosition() const {
       return m_position;
   }


    float getBallX() {
        return m_position.x;
    }

    float getBallY() {
        return m_position.y;
    }

    float getBallDirectionX() {
        return m_direction.x;

    }

    float getBallDirectionY() {
        return m_direction.y;
    }

    void reset() {
         std::random_device rd;
        std::mt19937 gen(rd());

        std::uniform_real_distribution<float> distY(50.0f, SCREEN_WIDTH - 50.0f);

        std::uniform_int_distribution<> direction(-1, 1);
         
        float dx = direction(gen) * m_ball_speed;
        float dy = direction(gen) * m_ball_speed;

        if (dx == 0) {
            dx = m_ball_speed;
        }
            
        if (dy == 0) dy = m_ball_speed;
        m_direction.x = dx;
        m_direction.y = dy;
    
       
        m_position.x = SCREEN_WIDTH / 2;
        m_position.y = distY(gen);
        m_ball.setPosition(m_position);

    }
};




#endif