#include <iostream>

using namespace std;

enum colors_t {
    green,
    blue,
    red,
    violet,
    yellow,
    white,
    black
};
typedef unsigned int val;

struct card_t {
    colors_t card_color;
    val card_value;  
};
struct  cards_t
{   
    int length = 0;
    card_t deck[];
};
struct  cauldron
{
    colors_t cauldron_color;
    cards_t cauldron_deck;
};


int main()
{
   /* "Trucizna game!\n";
     (1 <= k <= 6, 
     1 <= g <= 9,
     1<= gv <= 10,
     1 <= o <= 20;
    */

    
    unsigned int k, g, gv, o; // nums of...cauldrons |green card| value of green card| other color card(not green)
    cin >> k >> g >> gv >> o;
    //TO_DO 
    //check if values in rigth range

    //creating main deck
    unsigned int length =  g + k*o;
    cards_t main_deck;
    main_deck.length = length;
    main_deck.deck[length];
    // make and add green cards to a main deck
    for (int i = 0; i < g; i++)
    {
        card_t green_card = { green, gv };
        main_deck.deck[i] = green_card;
        main_deck.length++;
    }

}

