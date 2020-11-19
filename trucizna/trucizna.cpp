#include <iostream>
#define MAX_CARDS 174
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
    card_t deck[MAX_CARDS]{};
};
struct  cauldron
{
    colors_t cauldron_color;
    cards_t cauldron_deck;
};
void show_card(card_t card) {
    cout << card.card_value<<" ";
    switch (card.card_color) {
    case green:
        cout << "green";
        break;
    case blue:
        cout << "blue";
        break;
    case red:
        cout << "red";
        break;
    case violet:
        cout << "violet";
        break;
    case yellow:
        cout << "yellow";
        break;
    case white:
        cout << "white";
        break;
    case black:
        cout << "black";
        break;
    default:
        cout << "Something erong with color!!!";
        break;
    }
    cout << " ";
}
void show_deck(cards_t deck) {
    for (int i = 0; i < deck.length; i++)
    {
        show_card(deck.deck[i]);
    }
}
void add_gcards(cards_t *main_deck, unsigned int g, unsigned int gv) {
    // create and add green cards to a main deck
    for (int i = 0; i < int(g); i++) // amount of green cards
    {
        card_t green_card = { green, gv }; //gv - green card value
        main_deck->deck[i] = green_card;
        main_deck->length++;
    }
}
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

    add_gcards(&main_deck, g, gv);
    show_deck(main_deck);

    //adding other cards in main_deck
    
}

