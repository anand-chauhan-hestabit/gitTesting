#ifndef MAIN_SCREEN_HPP
#define MAIN_SCREEN_HPP

#include <SFML/Graphics.hpp>
#include "ball.hpp"
#include "paddle.hpp"
// #include "socketClient.hpp"
// #include "socketServer.hpp"
#include "../sockets/main.hpp"

#include <iostream>
using namespace std;

using namespace sf;

Color Green{38, 185, 154, 255};
Color Light_Green{129, 204, 184, 255};
Color Yellow{243, 213, 91, 255};
Color Dark_Green{20, 160, 133, 255};

class Game : public sockets
{
public:
    Game()
    {

        unsigned short framerate = 100.0f;
        unsigned short screen_width = sf::VideoMode::getDesktopMode().width;
        unsigned short screen_height = sf::VideoMode::getDesktopMode().height;
        cout << screen_height << "width" << screen_width;
        screen_width = screen_width - 140;
        screen_height = screen_height - 115;

        sf::RenderWindow window;

        window.create(sf::VideoMode(screen_width, screen_height), "Paddle Game");
        window.setFramerateLimit(framerate);
        // window.clear(sf::Color::Blue);

        sf::Font font;
        if (!font.loadFromFile("arial_narrow.ttf"))
        {
            std::cout << "Failed to load font." << std::endl;
        }

        Ball middlecircle;
        middlecircle.radius = 150.0f;
        middlecircle.ball_position_X = screen_width / 2 - middlecircle.radius; // sf::Vector2f(screen_width / 2, screen_height / 2);
        middlecircle.ball_position_Y = screen_height / 2 - middlecircle.radius;
        middlecircle.color = Light_Green;

        middlecircle.Create_ball();

        Paddle middleLine;
        middleLine.paddle_height = sf::VideoMode::getDesktopMode().height;
        middleLine.paddle_width = 2.0f;
        middleLine.color = sf::Color::White;
        middleLine.paddle_position_X = screen_width / 2; // sf::Vector2f(screen_width * 0 + first_player.width, (screen_height / 2) - first_player.height);
        middleLine.paddle_position_Y = screen_height * 0;
        middleLine.Create_Paddle();

        Ball ball;
        ball.radius = 25.f;
        ball.ball_position_X = screen_width / 2; // sf::Vector2f(screen_width / 2, screen_height / 2);
        ball.ball_position_Y = screen_height / 2;
        ball.speed_X = 5.0f;
        ball.speed_Y = 5.0f;
        ball.color = sf::Color::Yellow;
        ball.Create_ball();

        ball.first_player_scores = 0;
        ball.second_player_scores = 0;

        Paddle first_player;
        first_player.paddle_width = 25.0f;
        first_player.paddle_height = 120.0f;
        first_player.color = sf::Color::White;
        first_player.paddle_position_X = screen_width * 0 + first_player.paddle_width - 15; // sf::Vector2f(screen_width * 0 + first_player.width, (screen_height / 2) - first_player.height);
        first_player.paddle_position_Y = (screen_height / 2) - first_player.paddle_height;
        first_player.paddle_speed = 10.0f;
        first_player.Create_Paddle();

        Paddle second_player;
        second_player.paddle_width = 25.0f;
        second_player.paddle_height = 120.0f;
        second_player.color = sf::Color::White;
        second_player.paddle_position_X = sf::VideoMode::getDesktopMode().width - second_player.paddle_width * 5; // sf::Vector2f(screen_width - second_player.width * 5 - 5, (screen_height / 2) - second_player.height);
        second_player.paddle_position_Y = (screen_height / 2) - second_player.paddle_height;
        second_player.paddle_speed = 10.0f;
        second_player.Create_Paddle();

        struct GameData
        {
            float ball_position_x;
            float ball_position_y;
            float left_paddle_position_x;
            float left_paddle_position_y;
            float right_paddle_position_x;
            float right_paddle_position_y;
            int left_score;
            int right_score;
        };

        // Assume you have the game data stored in a GameData struct
        GameData gameData;
        sf::Packet packetToSend;
        sf::Packet packetToreceive;

        while (window.isOpen())
        {
            gameData.ball_position_x = ball.ball_position_X;
            gameData.ball_position_y = ball.ball_position_Y;
            gameData.left_paddle_position_x = first_player.paddle_position_X;
            gameData.left_paddle_position_y = first_player.paddle_position_Y;
            gameData.right_paddle_position_x = second_player.paddle_position_X;
            gameData.right_paddle_position_y = second_player.paddle_position_Y;
            gameData.left_score = ball.first_player_scores;
            gameData.right_score = ball.second_player_scores;

            sf::Event event;
            while (window.pollEvent(event))
            {
                if (event.type == sf::Event::Closed)
                    window.close();
            }

            if (sockets::choice == 1)
            {

                packetToSend << ball.first_player_scores;
                // packetToSend << gameData.right_paddle_position_y;

                server.sendGameData(packetToSend);
            }
            if (sockets::choice == 2)
            {
                GameData gameDataupdate;
                client.receiveGameData(packetToreceive);
                if (packetToreceive >> ball.second_player_scores)
                {
                    // Process the received game data as needed
                    // For example, update the game state based on the data
                    // ...
                    // ball.ball_position_X = gameDataupdate.ball_position_x;
                    ball.second_player_scores = ball.second_player_scores;
                    // second_player.paddle_position_Y = gameDataupdate.right_paddle_position_y;
                }
            }

            ball.update(screen_width, screen_height);
            first_player.update_paddle_left();
            second_player.update_paddle_right();

            /*Show the first player_score on main screen*/
            sf::Text firstPlayerScoreText(std::to_string(ball.first_player_scores), font, 80);
            firstPlayerScoreText.setPosition(screen_width / 4 - 20, 20);
            firstPlayerScoreText.setFillColor(sf::Color::White);
            /*Show the first second_player on main screen*/

            sf::Text secondPlayerScoreText(std::to_string(ball.second_player_scores), font, 80);
            secondPlayerScoreText.setPosition(screen_width / 1.25 - 20, 20);
            secondPlayerScoreText.setFillColor(sf::Color::White);
            window.draw(secondPlayerScoreText);

            // this functions will Check for collision with paddles
            ball.check_ball_paddle_collision(ball, first_player, second_player);

            window.clear(Dark_Green);

            middlecircle.draw(window);
            middleLine.draw(window);
            ball.draw(window);
            first_player.draw(window);
            second_player.draw(window);
            window.draw(firstPlayerScoreText);
            window.draw(secondPlayerScoreText);

            window.display();
        }
    }
};

#endif // MAIN_SCREEN_HPP
