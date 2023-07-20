#ifndef BALL_HPP
#define BALL_HPP
#include <SFML/Graphics.hpp>
#include "paddle.hpp"

using namespace sf;

class Ball
{
public:
    int first_player_scores;
    int second_player_scores;
    float radius;
    float ball_position_X;
    float ball_position_Y;
    float speed_X;
    float speed_Y;
    // Vector2f position;
    Color color;

    CircleShape sfml_ball;

    /*
    @param radius position of ball along x axis
    @param y position of ball
    */
public:
    void Create_ball();
    void draw(sf::RenderWindow &window);
    // void update(float ball_position_x, float ball_position_y, float speed_, float speed_y);
    void update(float screen_width, float screen_height);

    void check_ball_paddle_collision(Ball &ball, Paddle &first_player, Paddle &second_player);

    void ResetBallAfterInning();
};

#endif // BALL_HPP
