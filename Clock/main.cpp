#include <SFML\Graphics.hpp>

#include "oth/drawText.cpp"
#include "Clock.cpp"

#include "oth/drawRect.cpp"

#define DEFAULT_SCREEN_W 1280
#define DEFAULT_SCREEN_H 720

int main(int argc, char **argv) {
    sf::RenderWindow window;
    
    window.create(sf::VideoMode(DEFAULT_SCREEN_W,DEFAULT_SCREEN_H),"SFML PROJECT 2# - Clock",sf::Style::Titlebar | sf::Style::Close);

    unsigned radius=window.getSize().x/2-window.getSize().y/2;
    Clock c(radius,sf::Vector2f(window.getSize().x/2,window.getSize().y/2),true);

    sf::Event event;
    while (window.isOpen()){
        while (window.pollEvent(event)){
            switch(event.type){
                case sf::Event::Closed:
                    window.close();
                    break;
                case sf::Event::KeyPressed:
                    switch(event.key.code){
                        case sf::Keyboard::Escape:
                            window.close();
                            break;
                    }
                    break;
            }
        }

        c.update();

        //draw
        window.clear(sf::Color(0,0,0));

        c.draw(window);


        window.display();
    }

    return 0;
}
