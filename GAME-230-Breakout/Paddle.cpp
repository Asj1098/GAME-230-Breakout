#include "Paddle.h"

Paddle::Paddle(sf::Vector2f _size = sf::Vector2f(50.0f, 10.0f), sf::Vector2f initial_position = sf::Vector2f(575.0f, 875.0f), float _speed = 5.0f, int _hit_dir = -1, sf::Color _color = sf::Color::Red)
{
    shape.setSize(_size);
    shape.setPosition(initial_position);
    shape.setFillColor(_color);
    speed = _speed;
    hit_dir = _hit_dir;
    reset_position = initial_position;
}

void Paddle::UpdatePosition(float delta_time, int horizontal_direction, float x_bounds)
{
    sf::Vector2f position = shape.getPosition();

    if (position.x + shape.getSize().x >= x_bounds && horizontal_direction == 1)
        horizontal_direction = 0;
    if (position.x <= 0.0f && horizontal_direction == -1)
        horizontal_direction = 0;

    position.x += horizontal_direction * speed * delta_time;
    shape.setPosition(position);
}

void Paddle::SetPaddleSpeed(float _speed)
{
    speed = _speed;
}

void Paddle::Reset()
{
    shape.setPosition(reset_position);
}