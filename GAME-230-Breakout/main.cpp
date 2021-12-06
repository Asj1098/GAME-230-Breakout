#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <SFML/Audio.hpp>
#include <SFML/Network.hpp>
#include <SFML/System.hpp>
#include <SFML/OpenGL.hpp>
#include <SFML/Main.hpp>
#include<iostream>
#include <vector>

#include "Ball.h"
#include "Paddle.h"
#include "Brick.h"

void SetPattern(std::vector<Brick>& bricks, sf::Vector2f brick_size, int sequence)
{
    if (sequence == 0)
    {
        float x = 300.0f;
        float y = 200.0f;
        for (int i = 0; i < 5; i++)
        {
            bricks[i].SetPosition(sf::Vector2f(x, y));
            x += brick_size.x;
            bricks[i].is_enabled = true;
        }
        y += brick_size.y;
        x = 300.0f - brick_size.x/2;
        for (int i = 5; i < 11; i++)
        {
            bricks[i].SetPosition(sf::Vector2f(x, y));
            x += brick_size.x;
            bricks[i].is_enabled = true;
        }
        y += brick_size.y;
        x = 300.0f;
        for (int i = 11; i < 16; i++)
        {
            bricks[i].SetPosition(sf::Vector2f(x, y));
            x += brick_size.x;
            bricks[i].is_enabled = true;
        }
    }
    else if(sequence == 1)
    {
        float x = 250.0f;
        float y = 200.0f;
        for (int i = 0; i < 6; i++)
        {
            bricks[i].SetPosition(sf::Vector2f(x, y));
            x += brick_size.x;
            bricks[i].is_enabled = true;
        }
        y += brick_size.y;
        x = 250.0f + brick_size.x;
        for (int i = 6; i < 10; i++)
        {
            bricks[i].SetPosition(sf::Vector2f(x, y));
            x += brick_size.x;
            bricks[i].is_enabled = true;
        }
        y += brick_size.y;
        x = 250.0f;
        for (int i = 10; i < 16; i++)
        {
            bricks[i].SetPosition(sf::Vector2f(x, y));
            x += brick_size.x;
            bricks[i].is_enabled = true;
        }
    }
    else
    {
        float x = 240.0f;
        float y = 100.0f;
        for (int i = 0; i < 6; i++)
        {
            bricks[i].SetPosition(sf::Vector2f(x, y));
            x += brick_size.x;
            bricks[i].is_enabled = true;
        }
        y += brick_size.y;
        x = 300.0f;
        for (int i = 6; i < 11; i++)
        {
            bricks[i].SetPosition(sf::Vector2f(x, y));
            x += brick_size.x;
            bricks[i].is_enabled = true;
        }
        y += brick_size.y;
        x = 420.0f;
        for (int i = 11; i < 14; i++)
        {
            bricks[i].SetPosition(sf::Vector2f(x, y));
            x += brick_size.x;
            bricks[i].is_enabled = true;
        }
        y += brick_size.y;
        x = 480.0f;
        for (int i = 14; i < 16; i++)
        {
            bricks[i].SetPosition(sf::Vector2f(x, y));
            x += brick_size.x;
            bricks[i].is_enabled = true;
        }
    }
}

int main()
{
    sf::RenderWindow window(sf::VideoMode(1200, 900), "Pong");

    //set up V-Sync
    window.setVerticalSyncEnabled(true);

    //Clock to count the time taken for a frame
    sf::Clock clock;

    //Paddle Setup
    sf::Texture paddle_texture;
    if (!paddle_texture.loadFromFile("Resources/Paddle.png"))
    {
        return EXIT_FAILURE;
    }
    float _paddle_speed = 800.0f;
    float _paddle_offset_y = 20.0f;
    sf::Vector2f _paddle_size = sf::Vector2f(150.0f, 40.0f);
    Paddle paddle(_paddle_size, sf::Vector2f(window.getSize().x/2 - _paddle_size.x/2, window.getSize().y - _paddle_size.y - _paddle_offset_y), _paddle_speed, -1, sf::Color::White);
    paddle.shape.setTexture(&paddle_texture);

    //Ball Setup
    float _ball_radius = 15.0f;
    Ball ball(_ball_radius, sf::Vector2f(paddle.shape.getPosition().x + _paddle_size.x/2 - _ball_radius, paddle.shape.getPosition().y - 2 * _ball_radius), sf::Color::Red);
    float _initial_ball_speed = 500.0f;
    bool is_ball_attached = true;

    //Mouse
    sf::Vector2i prev_mouse_position = sf::Mouse::getPosition();

    //Load Font
    sf::Font font;
    if (!font.loadFromFile("Resources/Roboto-Regular.ttf"))
    {
        std::cout << "Font not loaded\n";
        return EXIT_FAILURE;
    }

    //Load Sounds
    sf::SoundBuffer break_buffer;
    if (!break_buffer.loadFromFile("Resources/Explosion_01.wav"))
        return EXIT_FAILURE;
    sf::Sound break_sound;
    break_sound.setBuffer(break_buffer);

    sf::SoundBuffer paddle_buffer;
    if (!paddle_buffer.loadFromFile("Resources/Hit_03.wav"))
        return EXIT_FAILURE;

    sf::Sound paddle_sound;
    paddle_sound.setBuffer(paddle_buffer);

    sf::SoundBuffer wall_buffer;
    if (!wall_buffer.loadFromFile("Resources/Hit_02.wav"))
        return EXIT_FAILURE;

    sf::Sound wall_sound;
    wall_sound.setBuffer(wall_buffer);
    
    sf::SoundBuffer life_buffer;
    if (!life_buffer.loadFromFile("Resources/Hero_Death_00.wav"))
        return EXIT_FAILURE;

    sf::Sound life_sound;
    life_sound.setBuffer(life_buffer);

    sf::SoundBuffer win_buffer;
    if (!win_buffer.loadFromFile("Resources/Jingle_Achievement_00.wav"))
        return EXIT_FAILURE;

    sf::Sound win_sound;
    win_sound.setBuffer(win_buffer);

    sf::SoundBuffer lose_buffer;
    if (!lose_buffer.loadFromFile("Resources/Jingle_Lose_00.wav"))
        return EXIT_FAILURE;

    sf::Sound lose_sound;
    lose_sound.setBuffer(lose_buffer);

    sf::Music music_buffer;
    //Credits: opengameart.org/content/space-boss-battle-theme
    if (!music_buffer.openFromFile("Resources/OrbitalColossus.wav"))
        return EXIT_FAILURE;
    music_buffer.setVolume(50.0f);

    //Setup Score Text
    sf::Text score_text;
    score_text.setFont(font);
    score_text.setString("0");
    score_text.setCharacterSize(100.0f);
    score_text.setFillColor(sf::Color::White);
    score_text.setPosition(sf::Vector2f(window.getSize().x / 2 - 25.0f, window.getSize().y * 0.75f - 50.0f));

    //Load Textures
    sf::Texture textures[4];
    if (!textures[0].loadFromFile("Resources/BrickY.png"))
    {
        return EXIT_FAILURE;
    }
    if (!textures[1].loadFromFile("Resources/BrickB.png"))
    {
        return EXIT_FAILURE;
    }
    if (!textures[2].loadFromFile("Resources/BrickR.png"))
    {
        return EXIT_FAILURE;
    }
    if (!textures[3].loadFromFile("Resources/BrickG.png"))
    {
        return EXIT_FAILURE;
    }
    
    //Bricks
    std::vector<Brick> bricks;
    sf::Vector2f brick_size = sf::Vector2f(120.0f, 50.0f);
    for (int i = 0; i < 16; i++)
    {
        Brick b(brick_size, sf::Vector2f(450.0f, 450.0f));
        b.shape.setTexture(&textures[i % 4]);
        bricks.push_back(b);
    }

    //Health UI;
    std::vector<sf::RectangleShape> hearts;
    sf::Texture heart_texture;
    if (!heart_texture.loadFromFile("Resources/Heart.png"))
    {
        return EXIT_FAILURE;
    }
    for (int i = 0; i < 3; i++)
    {
        sf::RectangleShape h;
        float heart_length = 50.0f;
        h.setSize(sf::Vector2f(heart_length, heart_length));
        h.setTexture(&heart_texture);
        h.setPosition(sf::Vector2f(50.0f + 1.5 * i * heart_length, 50.0f));

        hearts.push_back(h);
    }

    //Game Text
    sf::Text game_text;
    game_text.setFont(font);
    game_text.setCharacterSize(70.0f);
    game_text.setString("Hit Enter to Start");
    game_text.setFillColor(sf::Color::Magenta);
    game_text.setPosition(sf::Vector2f(350.0f, window.getSize().y * 0.5f));

    //Game Stats
    bool game_started = false;
    int score = 0;
    int pattern_sequence_number = 0;
    int health = 3;

    RESTART:
    game_started = false;
    score = 0;
    health = 3;
    pattern_sequence_number = 0;
    music_buffer.stop();
    music_buffer.setLoop(true);
    _initial_ball_speed = 500.0f;

    NEXT_LEVEL:
    SetPattern(bricks, brick_size, pattern_sequence_number);
    is_ball_attached = true;
    paddle.Reset();
    ball.Reset(sf::Vector2f(paddle.shape.getPosition().x + _paddle_size.x / 2 - 2 * _ball_radius, paddle.shape.getPosition().y - 2 * _ball_radius));

    while (window.isOpen())
    {
        //Update clock
        float delta_time = clock.getElapsedTime().asSeconds();
        clock.restart();

        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
        }

        if (!game_started)
        {
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Enter))
            {
                game_started = true;
                score_text.setFillColor(sf::Color::White);
                score_text.setPosition(sf::Vector2f(window.getSize().x / 2 - 25.0f, window.getSize().y * 0.75f - 50.0f));
                music_buffer.play();
                continue;
            }

            window.clear();
            window.draw(score_text);
            window.draw(game_text);
            window.draw(paddle.shape);
            window.draw(ball.shape);
            //Bricks
            for (int i = 0; i < bricks.size(); i++)
                if (bricks[i].is_enabled)
                    window.draw(bricks[i].shape);
            window.display();
            continue;
        }

        //Input
        {
            int _horizontal_direction = 0;

            //Mouse
            sf::Vector2i curr_mouse_position = sf::Mouse::getPosition();
            float delta_mouse_x = curr_mouse_position.x - prev_mouse_position.x;

            if(delta_mouse_x > 0)
                _horizontal_direction = 1.5f;
            if (delta_mouse_x < 0)
                _horizontal_direction = -1.5f;

            prev_mouse_position = curr_mouse_position;

            //Keyboard takes priority over mouse
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Left))
                _horizontal_direction = -1;
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Right))
                _horizontal_direction = 1;

            paddle.UpdatePosition(delta_time, _horizontal_direction, window.getSize().x);
            if (is_ball_attached)
            {
                ball.Reset(sf::Vector2f(paddle.shape.getPosition().x + _paddle_size.x / 2 - 2 * _ball_radius, paddle.shape.getPosition().y - 2 * _ball_radius));
                if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Space) || sf::Mouse::isButtonPressed(sf::Mouse::Left))
                {
                    ball.ApplyVelocity(_initial_ball_speed, sf::Vector2f(-0.4f, -1.0f));
                    paddle_sound.play();
                    is_ball_attached = false;
                }
            }
        }

        //Ball Interaction
        if(!is_ball_attached)
        {
            if (paddle.shape.getGlobalBounds().intersects(ball.shape.getGlobalBounds()))
            {
                float xmultiplier = (ball.shape.getPosition().x + ball.shape.getRadius()) - (paddle.shape.getPosition().x + paddle.shape.getSize().x / 2);
                ball.ApplyCollisionVelocity(sf::Vector2f(xmultiplier / 50, -1), 0.0f);
                paddle_sound.play();
            }

            bool all_bricks_broken = true;
            for (int i = 0; i < bricks.size(); i++)
            {
                if (bricks[i].is_enabled)
                {
                    all_bricks_broken = false;
                    sf::Vector2f ball_center = sf::Vector2f(ball.shape.getPosition().x + ball.shape.getRadius(), ball.shape.getPosition().y + ball.shape.getRadius());
                    if (bricks[i].shape.getGlobalBounds().intersects(ball.shape.getGlobalBounds()))
                    {
                        bricks[i].is_enabled = false;
                        break_sound.play();
                        score++;
                        score_text.setString(std::to_string(i + 1));
                        if ((ball_center.x >= bricks[i].original_position.x) && (ball_center.x <= bricks[i].original_position.x + bricks[i].shape.getSize().x))
                        {
                            if (ball_center.y > bricks[i].center.y)
                            {
                                ball.Reflect(0, 1);
                                ball.shape.setFillColor(sf::Color::Blue);
                            }
                            else
                            {
                                ball.Reflect(0, -1);
                                ball.shape.setFillColor(sf::Color::Yellow);
                            }
                        }
                        else
                        {
                            if (ball_center.x < bricks[i].center.x)
                            {
                                ball.Reflect(-1, 0);
                                ball.shape.setFillColor(sf::Color::Green);
                            }
                            else
                            {
                                ball.Reflect(1, 0);
                                ball.shape.setFillColor(sf::Color::Magenta);
                            }
                        }
                    }
                }
            }

            if (all_bricks_broken)
            {
                pattern_sequence_number = (pattern_sequence_number + 1)%3;
                _initial_ball_speed += 200.0f;
                win_sound.play();
                goto NEXT_LEVEL;
            }
        }

        if (ball.shape.getPosition().y > window.getSize().y + 10.0f)
        {
            health--;
            is_ball_attached = true;
            ball.Reset(sf::Vector2f(paddle.shape.getPosition().x + _paddle_size.x / 2 - 2 * _ball_radius, paddle.shape.getPosition().y - 2 * _ball_radius));
            if (health == 0)
            {
                music_buffer.stop();
                score_text.setPosition(sf::Vector2f(200.0f, window.getSize().y * 0.75f - 50.0f));
                score_text.setString("Previous Score: " + std::to_string(score));
                score_text.setFillColor(sf::Color::Red);
                lose_sound.play();
                goto RESTART;
            }
            else
                life_sound.play();
        }


        if (ball.UpdatePosition(delta_time, window.getSize()))
        {
            wall_sound.play();
        }
        score_text.setString(std::to_string(score));

        window.clear();
        window.draw(score_text);
        window.draw(paddle.shape);
        window.draw(ball.shape);
        //Bricks
        for (int i = 0; i < bricks.size(); i++)
            if(bricks[i].is_enabled)
                window.draw(bricks[i].shape);
        //Health
        for (int i = 0; i < health; i++)
            window.draw(hearts[i]);
        window.display();
    }

    return 0;
}
