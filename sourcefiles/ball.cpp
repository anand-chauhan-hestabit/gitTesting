
#include "../headerfiles/ball.hpp"
#include "../headerfiles/paddle.hpp"
#include <unistd.h>
#include <ctime>

#include <iostream>
using namespace std;

void Ball::Create_ball()
{
    sfml_ball.setRadius(this->radius);
    sfml_ball.setPosition(this->ball_position_X, this->ball_position_Y);
    sfml_ball.setFillColor(this->color);
}

void Ball::draw(sf::RenderWindow &window)
{
    window.draw(this->sfml_ball);
}

void Ball::update(float screen_width, float screen_height)
{
    // Update ball position
    ball_position_X += speed_X;
    ball_position_Y += speed_Y;
    sfml_ball.setPosition(ball_position_X, ball_position_Y);
    // cout<<endl<<"Current speed of ball speed_x and speed_y "<<speed_X<<speed_Y<<endl;

    // Check for collisions with window borders
    if (ball_position_Y - radius <= 0 || ball_position_Y >= screen_height)
    {
        speed_Y *= -1;
    }

    if (ball_position_X + radius >= screen_width)
    {
        first_player_scores++;

        ResetBallAfterInning();
    }
    if (ball_position_X - radius * 0 <= 0)
    {
        second_player_scores++;

        ResetBallAfterInning();
    }
   
}

void Ball::check_ball_paddle_collision(Ball &ball, Paddle &first_player, Paddle &second_player)
{
    if (ball.sfml_ball.getGlobalBounds().intersects(first_player.sfml_paddle.getGlobalBounds()))
    {
        // Collision detected!
        first_player.sfml_paddle.setFillColor(sf::Color::Green);
        ball.speed_X *= -1;
    }
    if (ball.sfml_ball.getGlobalBounds().intersects(second_player.sfml_paddle.getGlobalBounds()))
    {
        // Collision detected!
        second_player.sfml_paddle.setFillColor(sf::Color::Red);
        ball.speed_X *= -1;
    }
}

void Ball::ResetBallAfterInning()
{

    // Reset the ball position and speed after the timer finishes
    ball_position_X = sf::VideoMode::getDesktopMode().width / 2;
    ball_position_Y = sf::VideoMode::getDesktopMode().height / 2;
    // int speed_choices[2] = {-1, 1};
    // speed_X *= speed_choices[rand()%2];
    // speed_Y = speed_choices[rand()%2];
}