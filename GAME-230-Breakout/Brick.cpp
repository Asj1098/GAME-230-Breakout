#include "Brick.h"

Brick::Brick(sf::Vector2f _size, sf::Vector2f _position)
{
    shape.setSize(_size);
    shape.setPosition(_position);
    original_position = _position;
    center = sf::Vector2f(_position.x + _size.x / 2, _position.y + _size.y / 2);
    size = _size;
    is_enabled = false;
}

void Brick::Enable()
{
    is_enabled = true;
}

void Brick::Disable()
{
    is_enabled = false;
}

void Brick::SetPosition(sf::Vector2f _position)
{
    shape.setPosition(_position);
    original_position = _position;
    center = sf::Vector2f(_position.x + size.x / 2, _position.y + size.y / 2);
}