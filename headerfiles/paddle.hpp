#ifndef RECTANGLE_HPP
#define RECTANGLE_HPP

#include <SFML/Graphics.hpp>

using namespace sf;

class Paddle
{
public:
    float paddle_width;
    float paddle_height;
    float paddle_position_X;
    float paddle_position_Y;
    float paddle_speed;
    // sf::Vector2f position;
    sf::Color color;
    
    RectangleShape sfml_paddle;
    
public:
    void Create_Paddle();
    void draw(sf::RenderWindow &window);
    void update_paddle_left();
    void update_paddle_right();
    void Limit_paddle_movement();
    


};

#endif // RECTANGLE_HPP
