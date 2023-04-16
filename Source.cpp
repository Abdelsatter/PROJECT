#include<iostream>
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <SFML/Audio.hpp>
#include <SFML/Network.hpp>
#include <SFML/System.hpp>
using namespace std;
using namespace sf;

int main()
{
    RenderWindow window(VideoMode(700, 700), "Fireboy & Watergirl");
    window.setFramerateLimit(30);
    Texture player, menu;
    menu.loadFromFile("pngtree-game-menu-start-pause-and-options-button-glass-style-png-image_2996022.jpges ");

    int animation_indicator = 0;
    Clock  animation_clocl;

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

       
        
        window.clear();
        window.draw(p);
        window.display();

    }
    return 0;
}