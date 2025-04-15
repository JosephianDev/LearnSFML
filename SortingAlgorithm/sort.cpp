#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <algorithm>
#include <chrono>
#include <random>
#include <sstream>
#include <string>
#include <vector>

#include "oth/drawText.cpp"
#include "oth/drawRect.cpp"

template <typename T>
void scambia(T &x, T &y) { // scambia
    T tmp = x;
    x = y;
    y = tmp;
}

template <typename T>
bool isSorted(std::vector<T> &v) {
    if(std::is_sorted(v.begin(), v.end())) return true;
    else return false;
}

struct SortResult {
    bool finalStatus;
    std::string sortTitle;
    unsigned NUM_SWAPS;
};

// compila i risultati
SortResult getResults(bool status, std::string sort_title, unsigned num_of_swaps){
    SortResult res;

    res.finalStatus = status;
    res.sortTitle = sort_title;
    res.NUM_SWAPS = num_of_swaps;

}
void notifyResult(SortResult ris){
    std::stringstream text;

    // compongo testo e messaggio di avviso
    text<<"Sorted = ";
    if(ris.finalStatus) text<<"correctly";
    else text<<"false";

    text<<"\nType of sort: "<<ris.sortTitle<<"\nNumber of swaps: "<<ris.NUM_SWAPS;
    MessageBox(0, text.str().c_str(), "Result of sorting", MB_OK | MB_ICONASTERISK);
}

struct Node {
    unsigned short int *cell;
    bool boolStatus;
};

template <typename T>
void bubble_sort(std::vector<T> &NUM, std::vector<Node> &cv) {
    unsigned int NUM_SWAPS=0;

    int n = NUM.size();
    unsigned sleepTime = (2500/n)*(n*0.2);

    // bubble sort
    int k = 0;

    while(!isSorted(NUM)) {
        if(k == n-1){
            while(NUM[n-2]==NUM[n-1]-1) n--;
            k = 0;
        }

        if(NUM[k] > NUM[k + 1]){
            cv.push_back({&NUM[k-1],false}); // tolgo il vecchio K
            cv.push_back({&NUM[k],true}); // evidenzio il nuovo K

            scambia(NUM[k],NUM[k+1]);
            NUM_SWAPS++;
        }

        sf::sleep(sf::milliseconds(sleepTime));
        cv.push_back({&NUM[n], true});

        k++;
    }

    cv.clear();

    notifyResult(getResults(true,"BubbleSort",NUM_SWAPS));
}

#ifndef ___CELLS_VISUALIZATION_TABLE_
#define ___CELLS_VISUALIZATION_TABLE_

class CellTable {
private:
    void resolve();//for thread

    std::vector<unsigned short int> NUMBERS;
    unsigned short CELL_NUM;

    float window_x_max=0,window_y_max=0;
public:
    std::vector<Node> CHECKED_STATUS; // indipendente da NUMBERS e contiene l'indirizzo delle celle con il valore dello status

    CellTable(unsigned NumCells)
        : sort_thread(&CellTable::resolve, this) 
    {
        srand(time(NULL));
        CELL_NUM = NumCells;

        //prepara vettore
        for(int i=0;i<CELL_NUM;i++) NUMBERS.push_back(i);
    }
    ~CellTable(){}

    // main functions
    void draw(sf::RenderWindow &i_window);
    void shuffle();
    sf::Thread sort_thread;

    //check function
    bool is_check_element(unsigned short value){
        bool res=false;
        for(int i=0;i<CHECKED_STATUS.size();i++){
            if(*CHECKED_STATUS[i].cell == value) res = CHECKED_STATUS[i].boolStatus;
        }
        return res;
    }
};

// disordina vettore
void CellTable::shuffle(){
    unsigned seed = std::chrono::system_clock::now().time_since_epoch().count();
    std::shuffle(NUMBERS.begin(), NUMBERS.end(), std::default_random_engine(seed));
}

// disegna
void CellTable::draw(sf::RenderWindow& i_window){
    window_x_max=i_window.getSize().x;
    window_y_max=i_window.getSize().y;

    sf::Color color(255,255,255);
    for(int i=0;i<CELL_NUM;i++){
        if(is_check_element(i)){//check -> red
            color.r = 255;
            color.g = 0;
            color.b = 0;
        }else{//not check -> white
            color.r = 255;
            color.g = 255;
            color.b = 255;
        }

        drawText(std::to_string(NUMBERS[i]+1),((window_x_max-10)/CELL_NUM)*i,50,window_x_max/(CELL_NUM*2),i_window,sf::Color::White);
        drawRect_r(((window_x_max) / CELL_NUM) * i, window_y_max - 20, (window_x_max / CELL_NUM) / 1, ( NUMBERS[i]  + 1) * (window_y_max / (CELL_NUM * 1.5)), i_window, color);
    }
    //CHECKED.clear();
}

// risolvi
void CellTable::resolve(){
    bubble_sort(NUMBERS,CHECKED_STATUS);
}

#endif //#!___CELLS_VISUALIZATION_TABLE_