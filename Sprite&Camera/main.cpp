#include <SFML\Graphics.hpp>
/***
 * 
 * THIS ARE TRY SNIPPETS FOR ANOTHER GAMES
 * 
 ***/

int main(){
    bool menu=false;
    float FPS=60.0f;

    sf::VideoMode VIDEOMODE(1280, 720);
    sf::RenderWindow window(VIDEOMODE, "TRY GAME", sf::Style::Titlebar | sf::Style::Close);
    sf::View view(sf::Vector2f(0.0f,0.0f),sf::Vector2f(1280.0f,720.0f));

    ///background
    sf::RectangleShape bg(sf::Vector2f(3000, 3000));
    sf::Texture bgt;
    bgt.loadFromFile("res/pack.png");
    bgt.setRepeated(true);
    bg.setTexture(&bgt);
    sf::Vector2u ts_bg = bgt.getSize();
    ts_bg.x /= 16;
    ts_bg.y /= 16;
    bg.setTextureRect(sf::IntRect(ts_bg.x * 0, ts_bg.y * 2, ts_bg.x, ts_bg.y));

    //player
    sf::RectangleShape player(sf::Vector2f(160,160));
    
    //texture
    sf::Texture ptexture;
    ptexture.loadFromFile("res/pack.png");

    //load and crop textures
    player.setTexture(&ptexture);
    sf::Vector2u textureSize = ptexture.getSize();
    textureSize.x /= 16;
    textureSize.y /= 16;

    player.setTextureRect(sf::IntRect(textureSize.x * 0, textureSize.y * 1, textureSize.x, textureSize.y));

    //timing
    bool redraw = true;
    sf::Clock clock;

    sf::Event evento;
    while (window.isOpen()){

        if(clock.getElapsedTime().asSeconds() >= 1.0f / FPS) {
            redraw = true; // pronti per ridisegnare

            // funzioni di aggiornamento...
            // PROVA-------------------------------------------------------------------------------------------------------------------------

            // movement
            if(sf::Keyboard::isKeyPressed(sf::Keyboard::Key::W)) player.move(0.0f, -5.0f);
            if(sf::Keyboard::isKeyPressed(sf::Keyboard::Key::A)) player.move(-5.0f, 0.0f);
            if(sf::Keyboard::isKeyPressed(sf::Keyboard::Key::S)) player.move(0.0f, 5.0f);
            if(sf::Keyboard::isKeyPressed(sf::Keyboard::Key::D)) player.move(5.0f, 0.0f);

            // aggiornamento schermo
            view.setCenter(player.getPosition().x + (player.getSize().x / 2), player.getPosition().y + (player.getSize().y / 2));
            window.setView(view);
            //PROVA-------------------------------------------------------------------------------------------------------------------------

            clock.restart();
        } else { // Interrompi fino al prossimo sessantesimo (1/60) di secondo
            sf::Time sleepTime = sf::seconds((1.0f / FPS) - clock.getElapsedTime().asSeconds());
            sleep(sleepTime);
        }

        //input
        while (window.pollEvent(evento))
        {
            switch (evento.type){
                case sf::Event::Closed:
                    window.close();
                    break;
                case sf::Event::KeyReleased:
                    switch(evento.key.code){
                        case sf::Keyboard::Escape:
                            menu=!menu;
                            break;
                    }
                    break;
                case sf::Event::MouseWheelMoved:
                    if(evento.mouseWheel.delta!=0)
                        if(evento.mouseWheel.delta > 0) view.zoom(0.5f);
                        else view.zoom(1.5f);
                    break;
            }
        }

        //draw
        if(redraw){
            redraw=false;

            window.clear(sf::Color(0,0,0));

            if(menu){

            }else{ // sta in gioco
                window.draw(bg);
                window.draw(player);
            }

            window.display();
        }
    }

    return 0;
}