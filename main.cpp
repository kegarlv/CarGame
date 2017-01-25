#include <bits/stdc++.h>

#include <SFML/Graphics.hpp>
#include <SFML/Main.hpp>
#include <SFML/Window.hpp>

#include "Level.h"


using namespace std;

int main(int argc, char* argv[]) {

    Level level("untitled.tmx");

    sf::View view;
    view.reset(sf::FloatRect(0.0f, 0.0f, 800,600));
    view.setViewport(sf::FloatRect(0.0f, 0.0f, 2.0f, 2.0f));

    sf::RenderWindow App(sf::VideoMode(800,600), "Box2D Car game");
    while (App.isOpen()) {
        sf::Event Event;
        while (App.pollEvent(Event)) {
            if (Event.type == sf::Event::Closed)
                App.close();
        }

        App.clear(sf::Color(0,0,0));
        level.draw(App,view);

        App.display();
    }

}
