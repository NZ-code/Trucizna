#include <iostream>
#define MAX_CARDS 174

#define MAX_PLAYERS 6
#define MIN_PLAYERS 2
#define MAX_OTHER 20
#define MIN_OTHER 1
#define MAX_G_VAL 10
#define MIN_G_VAL 1
#define MAX_GREEN 9
#define MIN_GREEN 1
#define MAX_CAULDRONS 6
#define MIN_CAULDRONS 1
#define MIN_O 1
using namespace std;

enum  colors_t {
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
struct  cauldron_t
{
    colors_t cauldron_color;
    cards_t cauldron_deck;
};
struct  cauldrons_t
{
    int length = 0;
    cauldron_t cauldrons_arr[MAX_CAULDRONS]{};
};
void show_card(card_t card) {
    cout << card.card_value << " ";
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
void add_card(cards_t* pdeck, card_t card) {
    pdeck->deck[pdeck->length] = card;
    pdeck->length++;
}
void add_cards(cards_t* main_deck, unsigned int len, unsigned int value, colors_t color) {
    // create and add green cards to a main deck
    for (int i = 0; i < int(len); i++) // amount of green cards
    {
        card_t card = { color, value };
        add_card(main_deck, card);
    }
}

void fill_deck(cards_t* main_deck, int k, int g, int gv, int o) {
    // adding green cards
    add_cards(main_deck, g, gv, green);


    int arr_values[MAX_OTHER];
    //adding other cards in main_deck
    for (int i = 0; i < int(o); i++) // nums of no-green cards
    {
        unsigned int card_value;
        cin >> card_value;
        arr_values[i] = card_value;

    }

    for (int j = 0; j < int(k); j++) //iterate by colors(int)
    {


        for (int i = 0; i < int(o); i++) // nums of no-green cards
        {
            unsigned int card_value = arr_values[i];
            add_cards(main_deck, 1, card_value, colors_t(j + 1));

        }
    }
}
struct  player_t
{   
    val id = 0;
    cards_t hand_cards;
    cards_t deck_cards;
};
struct  players_t
{
    int length = 0;
    player_t players_arr[MAX_PLAYERS]{};
};
void add_player(players_t* players,const player_t player) {
    players->players_arr[players->length] = player;
    players->length++;
}
void create_players(players_t *players, int n) {
    for (int i = 0; i < n; i++)
    {
        player_t pl;
        pl.id = i;
        add_player(players, pl);
       
    }
    players->length = n;
}

void show_players_decks(players_t players) {
    for (int i = 0; i < players.length; i++)
    {
        cout << i + 1 << " player hand cards: ";
        show_deck(players.players_arr[i].hand_cards);
        cout << endl;
        cout << i + 1 << " player deck cards: ";
        show_deck(players.players_arr[i].deck_cards);
        cout << endl;
    }
}
void add_cauldron(cauldrons_t *cauldrons, const cauldron_t cauldron) {
    cauldrons->cauldrons_arr[cauldrons->length] = cauldron;
    cauldrons->length++;
}
void create_cauldrons(cauldrons_t *cauldrons, int k) {
    for (int i = 0; i < k; i++)
    {
        cauldron_t cld;
        cld.cauldron_color = (colors_t)(k + 1);
        add_cauldron(cauldrons, cld);

    }
}
void show_cauldrons(cauldrons_t cauldrons) {
    for (int i = 0; i < int(cauldrons.length); i++)
    {
        cout << i + 1 << " pile cards:\n";
        show_deck(cauldrons.cauldrons_arr[i].cauldron_deck);
    }
}
int main()
{



    unsigned int n, k, g, gv, o; // nums of...players /cauldrons |green card| value of green card| other color card(not green)
    do {
        cin >>n>> k >> g >> gv >> o;
        if ((MIN_PLAYERS <= n && n <= MAX_PLAYERS)\
            &&(MIN_CAULDRONS <= k && k <= MAX_CAULDRONS)\
            && (MIN_GREEN <= g && g <= MAX_GREEN)\
            && (MIN_G_VAL <= gv && gv <= MAX_G_VAL)\
            && (MIN_OTHER <= o && o <= MAX_OTHER)) break;
        else {
            cout << "Looks like you entered wrong values";
        }
    } while (true);
    cards_t main_deck;
    fill_deck(&main_deck, k, g, gv, o);
    //players array
    players_t players;
    //create palyers
    create_players(&players, n);
    

    

    for (int i = 0; i < main_deck.length; i++)
    {
        add_card(&players.players_arr[i % n].hand_cards, main_deck.deck[i]);
    }
    
    
    
    
    cout << "active player = 1\nplayers number = " << n << endl;
    show_players_decks(players);

    cauldrons_t cauldrons;
    create_cauldrons(&cauldrons,k);
    show_cauldrons(cauldrons);
    
}
