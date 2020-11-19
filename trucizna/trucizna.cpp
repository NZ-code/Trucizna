#include <iostream>
#define MAX_CARDS 174

#define MAX_OTHER 20
#define MIN_OTHER 1
#define MAX_G_VAL 10
#define MIN_G_VAL 1
#define MAX_GREEN 9
#define MIN_GREEN 1
#define MAX_CAULDRONS 6
#define MIN_CAULDRONS 1
#define MAX_PLAYER 6
#define MIN_PLAYER 2
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
struct  cauldron
{
    colors_t cauldron_color;
    cards_t cauldron_deck;
};
struct player_t {
    val name =0;
    cards_t hand_cards;
    cards_t deck_cards;
};
struct players_t{
    player_t all[MAX_PLAYER];
    val length = 0;
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
void show_player(player_t player) {
    cout << "player " << player.name;
    cout << " hand cards:";
    for (int i = 0; i < player.hand_cards.length; i++)
    {
        show_deck(player.hand_cards);
    }
    cout << "\n";
    cout << "player " << player.name;
    cout << " deck cards:";
    cout << "\n";
}
void show_players(players_t players) {
    for (int i = 0; i < int(players.length) ; i++)
    {
        show_player(players.all[i]);
    }
}
void add_cards(cards_t* main_deck, unsigned int len, unsigned int value, colors_t color) {
    // create and add green cards to a main deck
    for (int i = 0; i < int(len); i++) // amount of green cards
    {
        card_t card = { color, value };
        main_deck->deck[main_deck->length] = card;
        main_deck->length++;
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

void transfer_cars(cards_t* deck1, cards_t* deck2, int num) {

}

void create_players(players_t* players, int num) {
    for (int i = 0; i < num; i++) // creating players
    {
        player_t player;
        player.name = i + 1;
        players->all[i] = player;
    }
}

int main()
{
    unsigned int n,k, g, gv, o; // nums of...cauldrons |green card| value of green card| other color card(not green)
    do {
        cin >>n>> k >> g >> gv >> o;
        if ((MIN_PLAYER <= n && n <= MAX_PLAYER)
            &&(MIN_CAULDRONS <= k && k <= MAX_CAULDRONS)\
            && (MIN_GREEN <= g && g <= MAX_GREEN)\
            && (MIN_G_VAL <= gv && gv <= MAX_G_VAL)\
            && (MIN_OTHER <= o && o <= MAX_OTHER)
            ) break;
        else {
            cout << "Looks like you entered wrong values";
        }
    } while (true);
    cards_t main_deck;
    fill_deck(&main_deck, k, g, gv, o);
    
    cout << "active player = 1\n";
    cout << "players number = "<<n<<"\n";

    players_t players;
    create_players(&players,n);
    show_players(players);

    //TO_DO 
    // THINCK ABOUT NEW WAY OF COLLECTING CARDS 
    // MAY BE STACK OR VECTOR

}

