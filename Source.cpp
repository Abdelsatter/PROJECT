#include<iostream>
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <SFML/Audio.hpp>
#include <SFML/System.hpp>
using namespace std;
using namespace sf;
int main()
{
    RenderWindow window(VideoMode(1280, 720), "Fireboy & Watergirl");
    window.setFramerateLimit(60);
    Texture F, W;
    F.loadFromFile("Fireboy.png");
    W.loadFromFile("water_girl.png");


    RectangleShape rectangleDown(Vector2f(1280, 10));
    rectangleDown.setPosition(0, 710);
    rectangleDown.setFillColor(Color::Red);

    RectangleShape rectangleUp(Vector2f(1280, 10));
    rectangleUp.setPosition(0, 0);
    rectangleUp.setFillColor(Color::Red);

    RectangleShape rectangleLeft(Vector2f(10, 720));
    rectangleLeft.setPosition(0, 0);
    rectangleLeft.setFillColor(Color::Red);

    RectangleShape rectangleRight(Vector2f(10, 720));
    rectangleRight.setPosition(1270, 0);
    rectangleRight.setFillColor(Color::Red);

    Sprite FireBoy, WaterGirl;
    FireBoy.setTexture(F);
    WaterGirl.setTexture(W);


    FireBoy.setPosition(450, 450);
    FireBoy.setOrigin(FireBoy.getLocalBounds().width / 124, FireBoy.getLocalBounds().height / 2);
    WaterGirl.setPosition(350, 350);
    WaterGirl.setOrigin(WaterGirl.getLocalBounds().width / 106, WaterGirl.getLocalBounds().height / 2);




    int cf = 0, cw = 0;
    int cf2 = 17, cw2 = 6;
    double Vf = 0, Vw = 0;

    bool co = true, co2 = true, groundedF = false, groundedW = false;


    Clock clock;

    while (window.isOpen())
    {
        Event event;
        while (window.pollEvent(event))
        {
            if (event.type == Event::Closed)
            {
                window.close();
            }
        }

        RectangleShape hitpoxf(Vector2f(60, 100));
        hitpoxf.setOrigin(30, 35);
        hitpoxf.setPosition(FireBoy.getPosition().x, FireBoy.getPosition().y);

        RectangleShape hitpoxw(Vector2f(60, 90));
        hitpoxw.setOrigin(30, 35);
        hitpoxw.setFillColor(Color::Blue);
        hitpoxw.setPosition(WaterGirl.getPosition().x, WaterGirl.getPosition().y);

        if (rectangleDown.getGlobalBounds().intersects(hitpoxw.getGlobalBounds()))
        {
            groundedF = true;
            Vw = 0;
            if (Keyboard::isKeyPressed(Keyboard::Key::Up))
            {
                Vw = 7;
            }
        }
        else
        {
            groundedW = false;
            Vw -= 0.2;
        }
        if (rectangleDown.getGlobalBounds().intersects(hitpoxf.getGlobalBounds()))
        {
            groundedF = true;
            Vf = 0;
            if (Keyboard::isKeyPressed(Keyboard::Key::W))
            {
                Vf = 7;
            }
        }
        else
        {
            groundedF = false;
            Vf -= 0.2;
        }

        FireBoy.setTextureRect(IntRect(118 * cf, 0, 118, 130));
        WaterGirl.setTextureRect(IntRect(118 * cw, 0, 118, 130));
        if (co)
        {
            if (clock.getElapsedTime().asSeconds() >= 0.05)
            {
                cf++; cf %= 17;
                cw++; cw %= 6;
                clock.restart();
            }
        }

        if (Keyboard::isKeyPressed(Keyboard::Key::Right) && Keyboard::isKeyPressed(Keyboard::Key::Left))
        {
            co2 = false;
        }
        else { co2 = true; }

        if (Keyboard::isKeyPressed(Keyboard::Key::D) && Keyboard::isKeyPressed(Keyboard::Key::A)) 
        { co2 = false;
        }
        else { co2 = true; }


        if (co2)
        {

            if (Keyboard::isKeyPressed(Keyboard::Key::A))
            {
                co = false;
                FireBoy.setTextureRect(IntRect(118 * cf2, 0, 118, 130));
                cf2++;
                if (cf2 > 27)cf2 -= 11;
                FireBoy.setScale(-1, 1);
                FireBoy.move(-5.f, 0.f);

            }
            else
            {
                co = true;
            }
            if (Keyboard::isKeyPressed(Keyboard::Key::D))
            {
                co = false;
                FireBoy.setTextureRect(IntRect(118 * cf2, 0, 118, 130));
                cf2++;
                if (cf2 > 27)cf2 -= 11;
                FireBoy.setScale(1, 1);

                FireBoy.move(5.f, 0.f);

            }
            else
            {
                co = true;
            }
            if (Keyboard::isKeyPressed(Keyboard::Key::Left))
            {
                co = false;
                WaterGirl.setTextureRect(IntRect(118 * cw2, 0, 118, 130));
                cw2++;
                if (cw2 > 15)cw2 -= 10;
                WaterGirl.setScale(-1, 1);
                WaterGirl.move(-5.f, 0.f);

            }
            else
            {
                co = true;
            }
            if (Keyboard::isKeyPressed(Keyboard::Key::Right))
            {
                co = false;
                WaterGirl.setTextureRect(IntRect(118 * cw2, 0, 118, 130));
                cw2++;
                if (cw2 > 15)cw2 -= 11;
                WaterGirl.setScale(1, 1);
                WaterGirl.move(5.f, 0.f);

            }
            else
            {
                co = true;
            }
            
        }



        window.clear();
        /*window.draw(hitpoxf);
        window.draw(hitpoxw);*/
        window.draw(FireBoy);
        window.draw(WaterGirl);
        window.draw(rectangleUp);
        window.draw(rectangleDown);
        window.draw(rectangleLeft);
        window.draw(rectangleRight);

        FireBoy.move(0, -Vf);
        WaterGirl.move(0, -Vw);

        window.display();

    }
    return 0;
}