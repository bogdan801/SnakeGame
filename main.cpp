#include <SFML/Graphics.hpp>
#include <iostream>
#include <cmath>
#include <Windows.h>
#include "game.h"
#include <vector>

int w = 24, h = 16;

sf::RenderWindow window(sf::VideoMode(w*22,h*22), "Snake");
void main() {
    //icon
    sf::Image icon;
    icon.loadFromFile("img/icon.png");
    window.setIcon(icon.getSize().x, icon.getSize().y, icon.getPixelsPtr());

    //textures
    sf::Texture whiteT, redT, greenT;
    sf::Sprite whiteS, redS, greenS;
    whiteT.loadFromFile("img/white.png");
    redT.loadFromFile("img/red.png");
    greenT.loadFromFile("img/green.png");
    whiteS.setTexture(whiteT);
    redS.setTexture(redT);
    greenS.setTexture(greenT);
    whiteS.setScale(0.1, 0.1);
    redS.setScale(0.1, 0.1);
    greenS.setScale(0.1, 0.1);

    game g(w, h);
    
    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed)
                window.close();
        }
        g.update(window, whiteS, redS, greenS);
        window.display();
    }
}