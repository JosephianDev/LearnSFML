#include <SFML\Graphics.hpp>

#ifndef __DRAW_RECT
#define __DRAW_RECT

//funzione classica
void drawRect(float POS_X, float POS_Y, float Dim_X, float Dim_Y, sf::RenderWindow &window, sf::Color crl) {
    sf::RectangleShape* r = new sf::RectangleShape;

    r->setFillColor(crl);

    r->setSize(sf::Vector2f(Dim_X, Dim_Y));
    r->setPosition(sf::Vector2f(POS_X, POS_Y));

    window.draw(*r);

    delete r;
}
//funzione con punto origine opposto
void drawRect_r(float POS_X, float POS_Y, float Dim_X, float Dim_Y, sf::RenderWindow &window, sf::Color crl) {
    sf::RectangleShape* r=new sf::RectangleShape;

    r->setFillColor(crl);

    r->setSize(sf::Vector2f(Dim_X, Dim_Y));
    r->setPosition(sf::Vector2f(POS_X, POS_Y));

    // punto origine opposto
    r->setOrigin(0, r->getSize().y);

    window.draw(*r);

    delete r;
}

#endif