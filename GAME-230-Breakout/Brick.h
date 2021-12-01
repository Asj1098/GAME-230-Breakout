#pragma once
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <SFML/Audio.hpp>
#include <SFML/Network.hpp>
#include <SFML/System.hpp>
#include <SFML/OpenGL.hpp>
#include <SFML/Main.hpp>

class Brick
{
public:
	sf::RectangleShape shape;
	sf::Vector2f original_position;
	sf::Vector2f center;
	sf::Vector2f size;
	bool is_enabled = false;

	Brick(sf::Vector2f _size, sf::Vector2f _position);
	void Enable();
	void Disable();
	void SetPosition(sf::Vector2f _position);
};
