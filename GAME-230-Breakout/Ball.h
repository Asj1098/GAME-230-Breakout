#pragma once
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <SFML/Audio.hpp>
#include <SFML/Network.hpp>
#include <SFML/System.hpp>
#include <SFML/OpenGL.hpp>
#include <SFML/Main.hpp>

class Ball
{
private:
	const float max_speed = 1000.0f;

public:
	sf::CircleShape shape;
	float speed;

	sf::Vector2f velocity;
	Ball(float _radius, sf::Vector2f _initial_Position, sf::Color _color);
	void ApplyVelocity(float _speed, sf::Vector2f _direction);
	void ApplyCollisionVelocity(sf::Vector2f direction, float speed_increment);
	int UpdatePosition(float delta_time, sf::Vector2u window_size);
	void Reset(sf::Vector2f position);
	void Reflect(int directionX, int directionY);
};
