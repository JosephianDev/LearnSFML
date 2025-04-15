#include <SFML/Graphics.hpp>
#include <cmath>
#include <ctime>
#include <vector>

#include "oth/drawText.cpp"

#define PIGRECO 3.14159
float deg2rad(float deg){
    return (deg*PIGRECO)/180;
}
float rad2deg(float rad){
    return (rad*180)/PIGRECO;
}

#ifndef __CLOCK_HPP_CLASS_
#define __CLOCK_HPP_CLASS_

#define MAX_LANCETTE 3

class Clock {
    private:
        unsigned RADIUS;
        unsigned short NUM_LANCETTE;
        sf::Vector2f pos;
        sf::RectangleShape LANCETTE[MAX_LANCETTE];
        sf::CircleShape CLOCK,centro;
        bool CIFRE_SU_OROLOGIO;

        void crea_orologio();
    public:
        Clock(unsigned radius,sf::Vector2f position, bool numeri_su_orologio){
            //imposto le lancette
            NUM_LANCETTE=3;

            //imposto il raggio e la posizione dell'orologio
            RADIUS=radius;
            pos=position;
            //imposto i numeri sul quadrante dell'orologio (1-12)
            CIFRE_SU_OROLOGIO=numeri_su_orologio;
            setFontPath("oth\\consola.ttf");
            //creo orologio
            crea_orologio();
        }

        void setNumLancetta(unsigned short numLancette){
            NUM_LANCETTE=numLancette;
        }

        //disegna
        void draw(sf::RenderWindow& i_window){
            i_window.draw(CLOCK);
            for(int i=0;i<NUM_LANCETTE;i++) i_window.draw(LANCETTE[i]);
            i_window.draw(centro);
            
            //numeri sull'orologio
            int adder1=0;
            if(CIFRE_SU_OROLOGIO) for(int i=0;i<12;i++){
                if(i==9) adder1=12;
                drawText(std::to_string(((i+3)%12)+adder1),(pos.x-17)-(cos(deg2rad(180+(360/12)*i))*(RADIUS+20)),(pos.y-17)+(sin(deg2rad((360/12)*i))*(RADIUS+20)),25,i_window,sf::Color::Magenta);
                adder1=0;// nn ho trovato una soluzione nello shifting delle cifre allora ho scritto i numeri a partire da 3 e utilizzando una variabile per la parte dove diviene 0

                drawText(std::to_string(((i+3)%12)*5),(pos.x-17)-(cos(deg2rad(180+(360/12)*i))*(RADIUS+50)),(pos.y-17)+(sin(deg2rad((360/12)*i))*(RADIUS+50)),12,i_window,sf::Color::Magenta);
            } 
        }

        //accendi
        void update(){
            std::time_t t = std::time(0); // get time now
            std::tm *now = std::localtime(&t);
            
            LANCETTE[0].setRotation(180+(360/12)*(now->tm_hour%12));
            LANCETTE[1].setRotation(180+(360/60)*(now->tm_min));
            LANCETTE[2].setRotation(180+(360/60)*(now->tm_sec));
        }
};

void Clock::crea_orologio(){
    //creo l'orologio
    CLOCK.setRadius(RADIUS);
    CLOCK.setPosition(pos);
    CLOCK.setOrigin(sf::Vector2f(RADIUS, RADIUS));
    CLOCK.setFillColor(sf::Color::White);

    //creo il centro
    centro.setRadius(5);
    centro.setPosition(pos);
    centro.setOrigin(sf::Vector2f(5,5));
    centro.setFillColor(sf::Color::Black);

    //creo le lancette
    sf::RectangleShape* temp;
    for(int i=0;i<NUM_LANCETTE;i++){
        temp=new sf::RectangleShape;
        temp->setPosition(pos);
        temp->setSize(sf::Vector2f(10,(RADIUS/(NUM_LANCETTE+0.5f))*(i+1)));
        switch(i){
            case 0:
                temp->setFillColor(sf::Color(0, 255, 0));
                break;
            case 1:
                temp->setFillColor(sf::Color(0, 0, 255));
                break;
            case 2:
                temp->setFillColor(sf::Color(255, 0, 0));
                break;
        }
        temp->setOrigin(sf::Vector2f(temp->getSize().x/2,0));
        LANCETTE[i]=*temp;
        delete temp;
    }
    
}

#endif //#!__CLOCK_HPP_CLASS_
