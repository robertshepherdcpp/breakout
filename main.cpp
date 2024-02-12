#include<SFML/Graphics.hpp>

#include<iostream>

auto main() -> int
{
    /*
    std::vector<sf::CircleShape> circles{};
    */

    sf::RenderWindow window(sf::VideoMode(1000, 700), "Bouncing Balls SFML App");
    window.setFramerateLimit(60);

    sf::RectangleShape paddle(sf::Vector2f(100, 20));
    paddle.setPosition(sf::Vector2f(450, 660));

    sf::CircleShape ball(5);
    ball.setPosition(sf::Vector2f(500, 350));

    sf::Vector2f ball_velocity(3.f, 3.f);

    sf::RectangleShape target(sf::Vector2f(40, 10));
    std::vector<sf::RectangleShape> targets{};

    int score = 0;
    int amount_killed = 0;
    bool isDone = false;
    bool has_reset = false;


    for (int y = 100; y < 300; y += 50)
    {
        for (int x = 200; x < 800; x += 50)
        {
            auto copy_sprite = target;
            copy_sprite.setPosition(sf::Vector2f(float(x), float(y)));
            targets.push_back(copy_sprite);
        }
    }

    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed)
                window.close();

            if (event.type == sf::Event::KeyPressed)
            {
                if (event.key.code == sf::Keyboard::A)
                {
                    if (paddle.getPosition().x > 0)

                        for (int i = 0; i < 30; i++)
                        {
                            paddle.move(sf::Vector2f(-1, 0));
                        }
                }
            }
            if (event.key.code == sf::Keyboard::D)
            {
                if (paddle.getPosition().x < (1000 - paddle.getGlobalBounds().width))
                {
                    for (int i = 0; i < 30; i++)
                    {
                        paddle.move(sf::Vector2f(1, 0));
                    }
                }
            }
        }

        ball.move(ball_velocity);

        if (ball.getPosition().x < 0 || ball.getPosition().x >(1000 - ball.getGlobalBounds().width))
        {
            ball_velocity.x = -ball_velocity.x;
        }
        if (ball.getPosition().y < 0)
        {
            ball_velocity.y = -ball_velocity.y;
        }
        if (ball.getPosition().y > (700 - ball.getGlobalBounds().height))
        {
            score -= 1;
            ball.setPosition(500, 350);
        }
        if (paddle.getGlobalBounds().intersects(ball.getGlobalBounds()))
        {
            //ball_velocity.x = -ball_velocity.x;
            ball_velocity.y = -ball_velocity.y;
        }

        for (int i = 0; i < targets.size(); i++)
        {
            if (targets[i].getGlobalBounds().intersects(ball.getGlobalBounds()))
            {
                ball_velocity.y = -ball_velocity.y;
                targets[i].setPosition(-100, -100);
                score += 1;
                amount_killed += 1;
                std::cout << "Score: " << score << "\n";
            }
        }

        if (amount_killed >= 48 && !isDone)
        {
            isDone = true;
        }
        if (isDone)
        {
            paddle.setPosition(ball.getPosition().x, paddle.getPosition().y);
            if (!has_reset)
            {
                std::vector<sf::RectangleShape> new_targets{};
                for (int y = 100; y < 300; y += 50)
                {
                    for (int x = 200; x < 800; x += 50)
                    {
                        auto copy_sprite = target;
                        copy_sprite.setPosition(sf::Vector2f(float(x), float(y)));
                        new_targets.push_back(copy_sprite);
                    }
                }
                has_reset = true;
                targets = new_targets;
            }

        }

        /*
        sf::CircleShape copy_circle = ball;
        copy_circle.setFillColor(sf::Color(sf::Uint8(100), sf::Uint8(100), sf::Uint8(100)));
        circles.push_back(copy_circle);
        */

        window.clear();
        window.draw(paddle);

        for (const auto& i : targets)
        {
            window.draw(i);
        }

        /*
        for (const auto& x : circles)
        {
            window.draw(x);
        }
        */
        window.draw(ball);
        window.display();
    }
    return 0;
}