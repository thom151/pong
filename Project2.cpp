#include <SFML/Graphics.hpp>
#include "constants.h"
#include <iostream>
#include "players.h"
#include "ball.h"

void checkScore(Ball& ball, Player& player1, Player& player2);
int main()
{
    sf::RenderWindow window(sf::VideoMode(SCREEN_WIDTH, SCREEN_HEIGHT), "My window");

    sf::Font font;
    if (!font.loadFromFile("Tempter.otf")) {
        std::cerr << "Error loading font" << "\n\n";
        return -1;
    }

    sf::Text Player1Score;
    Player1Score.setFont(font);
    Player1Score.setString("0");
    Player1Score.setFillColor(sf::Color::White);
    Player1Score.setPosition(200 - 50, 30);
    Player1Score.setCharacterSize(100);


    sf::Text Player2Score;
    Player2Score.setFont(font);
    Player2Score.setString("0");
    Player2Score.setFillColor(sf::Color::White);
    Player2Score.setPosition(600 - 50, 30);
    Player2Score.setCharacterSize(100);

    Ball ball{};
    window.setFramerateLimit(60);
    sf::Vector2f rect1Pos((SCREEN_WIDTH/8)-(PLAYER_WIDTH/2), (SCREEN_HEIGHT/2)-(PLAYER_HEIGHT/2));
    sf::Vector2f rect2Pos((SCREEN_WIDTH - (SCREEN_WIDTH / 8)) - (PLAYER_WIDTH / 2), (SCREEN_HEIGHT / 2) - (PLAYER_HEIGHT / 2)); 
    Player player1{rect1Pos,Player1Score};
    Player player2{ rect2Pos, Player2Score };

    sf::VertexArray dashedLine(sf::Lines);

    for (float i{ 0 }; i < SCREEN_HEIGHT; i += DASHED_LINE_LENGTH + DASHED_LINE_GAP) {
        dashedLine.append(sf::Vertex(sf::Vector2f(SCREEN_WIDTH/2, i), sf::Color::White));
        dashedLine.append(sf::Vertex(sf::Vector2f(SCREEN_WIDTH / 2, i + DASHED_LINE_LENGTH), sf::Color::White));
    }

    sf::Clock clock;
    while (window.isOpen())
    {
        float dt = clock.restart().asSeconds();

        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();

        }


        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up)) {
            player1.moveUp(dt);
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down)) {
            player1.moveDown(dt);
        }

        window.clear(sf::Color::Black);
        ball.draw(window, dt);
        player1.collided(ball);
        player2.collided(ball);
        player2.aiMove(ball, dt);
        checkScore(ball, player1, player2);
        window.draw(Player1Score);
        window.draw(Player2Score);
        window.draw(dashedLine);
        player1.draw(window);
        player2.draw(window);
        window.display();
    }

    return 0;
}


void checkScore(Ball& ball, Player& playerLeft, Player& playerRight) {
    if (ball.outOfBounds()) {
		  if (ball.getBallX() < 10) {
            playerRight.score();
            playerLeft.minusLives();
            ball.reset();
            return;
           }

          if (ball.getBallX() > SCREEN_WIDTH - 10) {
              playerLeft.score();
              playerRight.minusLives();
              ball.reset();
              return;
        }

    }
  }

