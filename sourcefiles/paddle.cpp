#include "../headerfiles/paddle.hpp"
#include <iostream>
using namespace std;

/*
create a paddle function is use to create a paddle*/
void Paddle::Create_Paddle()
{
    sfml_paddle.setSize(sf::Vector2f(this->paddle_width, this->paddle_height));
    sfml_paddle.setPosition(this->paddle_position_X, this->paddle_position_Y);
    sfml_paddle.setFillColor(this->color);
}

void Paddle::draw(sf::RenderWindow &window)
{
    window.draw(sfml_paddle);
}
/*
this function is used to update the position of left paddle with w and s
*/
void Paddle::update_paddle_left()
{
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::W))
    {
        this->paddle_position_Y = this->paddle_position_Y - this->paddle_speed;
        sfml_paddle.setPosition(this->paddle_position_X, this->paddle_position_Y);
        // cout << "clicked on w " << endl;
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::S))
    {
        this->paddle_position_Y = this->paddle_position_Y + this->paddle_speed;
        // cout << "clicked on s " << endl;
        sfml_paddle.setPosition(this->paddle_position_X, this->paddle_position_Y);
    }
    Limit_paddle_movement();
}

/*
Update the position of right paddle with up and down key
*/
void Paddle::update_paddle_right()
{
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
    {
        this->paddle_position_Y = this->paddle_position_Y - this->paddle_speed;
        sfml_paddle.setPosition(this->paddle_position_X, this->paddle_position_Y);
        // cout << "clicked on up " << endl;
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
    {
        this->paddle_position_Y = this->paddle_position_Y + this->paddle_speed;
        // cout << "clicked on down " << endl;
        sfml_paddle.setPosition(this->paddle_position_X, this->paddle_position_Y);
    }
    Limit_paddle_movement();
}
/*
This function will control the paddle up and down movements
*/
void Paddle::Limit_paddle_movement()
{
    if (this->paddle_position_Y <= 0)
    {
        this->paddle_position_Y = 0;
    }
    if (this->paddle_position_Y + this->paddle_height >= sf::VideoMode::getDesktopMode().height)
    {
        this->paddle_position_Y = sf::VideoMode::getDesktopMode().height - this->paddle_height;
    }
}