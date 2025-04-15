#include <SFML\Graphics.hpp>
#include <string>

#ifndef __DRAW_TEXT
#define __DRAW_TEXT

std::string FONTPATH = "";

void setFontPath(std::string FontPath){
    FONTPATH = FontPath;
}

//funzione con posizioni assolute
void drawText(std::string Text, float POS_X, float POS_Y, unsigned Dim, sf::RenderWindow &window, sf::Color crl) {
    sf::Text t;
    sf::Font f;

    if(f.loadFromFile(FONTPATH)) t.setFont(f);

    t.setString(Text);
    
    t.setFillColor(crl);
    
    if(Dim>40) Dim=40;
    t.setCharacterSize(Dim);

    t.setPosition(sf::Vector2f(POS_X, POS_Y));

    window.draw(t);
}
//funzione con posizioni relative
void drawText_r(std::string Text, unsigned Dim, sf::RenderWindow &window, sf::Color crl, bool alignment_x, bool alignment_y) {
    sf::Text t;
    sf::Font f;

    if(f.loadFromFile(FONTPATH)) t.setFont(f);

    t.setString(Text);
    
    t.setFillColor(crl);
    
    if(Dim>40) Dim=40;
    t.setCharacterSize(Dim);

    if(alignment_x) t.setPosition(sf::Vector2f( ( window.getSize().x/2 ) - ( t.getCharacterSize() * Text.size()-1 ),t.getPosition().y));
    else t.setPosition(sf::Vector2f(0,t.getPosition().y));

    if(alignment_y) t.setPosition(sf::Vector2f(t.getPosition().x,(window.getSize().y/2)-t.getCharacterSize()));
    else t.setPosition(sf::Vector2f(t.getPosition().x,0));

    t.setPosition(sf::Vector2f(t.getPosition().x + 10, t.getPosition().y + 10));//aggiungo i bordi

    window.draw(t);
}

#endif