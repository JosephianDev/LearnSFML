#include <SFML/Graphics.hpp>

#include <windows.h>

#include "oth/drawText.cpp"

//versione 2.0
#include "sort.cpp"

//valori
#define MAX_VALUE 1024
#define MIN_VALUE 5
#define DEFAULT_VALUE 128

//schermi
#define MAX_SCREEN_W 1920
#define MAX_SCREEN_H 1080

#define MIN_SCREEN_W 640
#define MIN_SCREEN_H 360

#define DEFAULT_SCREEN_W 1280
#define DEFAULT_SCREEN_H 720

int main(int argc, char** argv) {
    sf::RenderWindow window;
    setFontPath("oth\\consola.ttf");

    //prima volta
    bool primo_avvio=true;
    bool comandi=false;
    bool check=false;
    bool picktext=false;//inserimento testo
    sf::String sentence;

    //imposto il valore di argomento
    unsigned value,  screenW,screenH;
    if(argc>1){//maggiore di 1 argomento
        value = std::stoi(argv[1]);
        if(value > MAX_VALUE || value < MIN_VALUE) value = DEFAULT_VALUE;
        MessageBox(0, "Argomento accettato!", "SortingAlgorithm", MB_OK | MB_ICONASTERISK);

        if(argc>=3){//maggiore di 3 argomenti
            screenW = std::stoi(argv[2]), screenH = std::stoi(argv[3]);
            if((screenW<MIN_SCREEN_W && screenH<MIN_SCREEN_H) || (screenW>MAX_SCREEN_W && screenH>MAX_SCREEN_H)){screenW=DEFAULT_SCREEN_W;screenH=DEFAULT_SCREEN_H;}
        }else{//tra 3 e 1 argomento
            screenW=DEFAULT_SCREEN_W;screenH=DEFAULT_SCREEN_H;
        }
    }else{//non ci sono argomenti
        MessageBox(0, "Non ci sono argomenti validi.", "SortingAlgorithm", MB_OK | MB_ICONEXCLAMATION);
        value = DEFAULT_VALUE;
        screenW=DEFAULT_SCREEN_W;screenH=DEFAULT_SCREEN_H;
    }
    MessageBox(0, "R: risolvi (resolve)\nS: disordina (shuffle)", "SortingAlgorithm Comandi:", MB_OK | MB_ICONASTERISK);

    window.create(sf::VideoMode(screenW,screenH), "SFML PROJECT 1#",sf::Style::Titlebar | sf::Style::Close);

    CellTable* a = new CellTable(value);

    sf::Event event;
    while (window.isOpen()){

        //input
        while (window.pollEvent(event)){
            switch(event.type){
                case sf::Event::Closed:
                    a->sort_thread.terminate();
                    window.close();
                    break;
                case sf::Event::KeyPressed:
                    if(!primo_avvio)
                    switch(event.key.code){
                        case sf::Keyboard::S:
                            a->shuffle();
                            break;
                        case sf::Keyboard::R:
                            a->sort_thread.launch();
                            break;
                        case sf::Keyboard::H:
                            comandi=!comandi;
                            break;
                        case sf::Keyboard::L:
                            picktext=true;
                            break;
                        case sf::Keyboard::Enter:
                            if(picktext){
                                picktext=false;

                                delete a;
                                a = new CellTable(std::stoi(sentence.toAnsiString()));
                            }
                            break;
                    }
                    primo_avvio=false;
                    break;
                case sf::Event::TextEntered:
                    if(picktext){
                        if(event.text.unicode>=48 && event.text.unicode<=57) //default 32, 126
                            sentence+=static_cast<char>(event.text.unicode);
                        else if(event.text.unicode==8 && sentence.getSize()>0)
                            sentence.erase(sentence.getSize()-1,sentence.getSize());
                    }
                    break;
            }
        }

        //draw
        window.clear(sf::Color(0,0,0));

        drawText(("Sorting Algorithm: Num=" + std::to_string(value)).c_str(), 10, 0, 40, window, sf::Color::White);
        
        if(primo_avvio) drawText("Premi un tasto qualsiasi\nper visualizzare i valori dei vettori..", 0,window.getSize().y/2,50, window, sf::Color::White);
        else a->draw(window);

        if(comandi) drawText("Comandi:\nR: risolvi (resolve)\nS: disordina (shuffle)", window.getSize().x-200, 0, 10, window, sf::Color::White);

        window.display();
    }
    return 0;
}