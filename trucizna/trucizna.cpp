#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>  
#include <stdlib.h>   
#include <time.h> 
#include<iostream>
#define MAX_CARDS 174
#define MAX_PLAYERS 6
#define MIN_PLAYERS 1
#define MAX_OTHER 20
#define MIN_OTHER 1
#define MAX_G_VAL 10
#define MIN_G_VAL 1
#define MAX_GREEN 9
#define MIN_GREEN 1
#define MAX_CAULDRONS 7
#define MIN_CAULDRONS 1
#define MIN_O 1
#define COLOR_L 14
using namespace std;



enum  colors_t {
    green = -1,
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
    colors_t cauldron_color = green;
    cards_t cauldron_deck{};
};
struct  cauldrons_t
{
    int length = 0;
    cauldron_t cauldrons_arr[MAX_CAULDRONS]{};
};
struct  player_t
{
    val id = 0;
    cards_t hand_cards{};
    cards_t deck_cards{};
};
struct  players_t
{
    int length = 0;
    player_t players_arr[MAX_PLAYERS]{};
};
void show_card(card_t card, FILE *statusFile) {
    printf("%d ", card.card_value);
    fprintf(statusFile,"%d ", card.card_value);
    switch (card.card_color) {
    case green:
        printf("green");
        fprintf(statusFile,"green");
        break;
    case blue:
        printf("blue");
        fprintf(statusFile,"blue");
        break;
    case red:
        printf("red");
        fprintf(statusFile, "red");
        break;
    case violet:
        printf("violet");
        fprintf(statusFile, "violet");
        break;
    case yellow:
        printf("yellow");
        fprintf(statusFile, "yellow");
        break;
    case white:
        printf("white");
        fprintf(statusFile, "white");
        break;
    case black:
        printf("black");
        fprintf(statusFile, "black");
        break;
    default:
        printf("Something wrong with color!!!");
        fprintf(statusFile, "Something wrong with color!!!");
        break;
    }
    printf(" ");
    fprintf(statusFile, " ");
}
void show_deck(cards_t deck, FILE* statusFile) {
    for (int i = 0; i < deck.length; i++)
    {
        show_card(deck.deck[i],statusFile);
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

void fill_deck(cards_t* main_deck, int k, int g, int gv, int o, FILE* startFile) {
    // adding green cards
    add_cards(main_deck, g, gv, green);


    int arr_values[MAX_OTHER];
    //adding other cards in main_deck
    for (int i = 0; i < int(o); i++) // nums of no-green cards
    {
        unsigned int card_value;
        fscanf(startFile,"%d ",&card_value);
        arr_values[i] = card_value;

    }

    for (int j = 0; j < int(k); j++) //iterate by colors(int)
    {
        for (int i = 0; i < int(o); i++) // nums of no-green cards
        {
            unsigned int card_value = arr_values[i];
            add_cards(main_deck, 1, card_value, colors_t(j));
        }
    }
}

void add_player(players_t* players, const player_t player) {
    players->players_arr[players->length] = player;
    players->length++;
}
void create_players(players_t* players, int n) {
    for (int i = 0; i < n; i++)
    {
        player_t pl;
        pl.id = i;
        add_player(players, pl);

    }
    players->length = n;
}

void show_players_decks(players_t *players, FILE* statusFile) {
    for (int i = 0; i < players->length; i++)
    {
        printf("%d player hand cards: ", i + 1);
        fprintf(statusFile, "%d player hand cards: ", i + 1);

        show_deck(players->players_arr[i].hand_cards, statusFile);

        printf("\n");
        fprintf(statusFile, "\n");

        printf("%d player deck cards: ", i + 1);
        fprintf(statusFile, "%d player deck cards: ", i + 1);

        show_deck(players->players_arr[i].deck_cards, statusFile);
        printf("\n");
        fprintf(statusFile, "\n");

    }

}
void print_players_state(players_t players) {
    for (int i = 0; i < players.length; i++)
    {
        printf("%d player has %d cards on hand\n", i + 1, players.players_arr[i].hand_cards.length);
        printf("%d player has %d cards in front of him\n", i + 1, players.players_arr[i].deck_cards.length);
    }

}
void print_cauldrons_state(cauldrons_t cauldrons) {
    for (int i = 0; i < cauldrons.length; i++)
    {
        printf("there are %d cards on %d pile\n", cauldrons.cauldrons_arr[i].cauldron_deck.length, i + 1);
    }
}
void add_cauldron(cauldrons_t* cauldrons, const cauldron_t cauldron) {
    cauldrons->cauldrons_arr[cauldrons->length] = cauldron;
    cauldrons->length++;
}
void create_cauldrons(cauldrons_t* cauldrons, int k) {
    for (int i = 0; i < k; i++)
    {
        cauldron_t cld;
        cld.cauldron_color = (colors_t)(k + 1);
        add_cauldron(cauldrons, cld);

    }
}
void show_cauldrons(cauldrons_t *cauldrons, FILE* statusFile) {
    for (int i = 0; i < int(cauldrons->length); i++)
    {

        printf("%d pile cards:",i+1);
        fprintf(statusFile,"%d pile cards:",i+1);
        show_deck(cauldrons->cauldrons_arr[i].cauldron_deck,statusFile);
        printf("\n");
        fprintf(statusFile, "\n");
    }
}
void print_header(int n,int active_player, FILE* statusFile, int exp) {
    // TO FILE
    fprintf(statusFile, "active player = %d\nplayers number = %d\nexplosion threshold = %d\n", active_player, n, exp);
    // TO CMD
    printf("active player = %d\nplayers number = %d\nexplosion threshold = %d\n", active_player, n, exp);
}
void create_game_objects(cards_t * main_deck, players_t *players ,cauldrons_t * cauldrons, int k, int g, int gv, int o, int n) {
    
    create_players(players, n);
    create_cauldrons(cauldrons, k);
}
void give_cards_to_players(players_t* players, cards_t * main_deck,int n) {
    for (int i = 0; i < main_deck->length; i++)
    {
        add_card(&players->players_arr[i % n].hand_cards, main_deck->deck[i]);
    }
}

// MADE THIS BY PLAYER 1
void swap_cards(cards_t *deck,int i, int j) {
    card_t temp = deck->deck[i];
    deck->deck[i] = deck->deck[j];
    deck->deck[j] = temp;
}
void shuffle_deck(cards_t *deck) {
    for (int i = 0; i < deck->length ; i++)
    {
        int random_index = rand() % deck->length;
        swap_cards(deck, i, random_index);
    }
}
void generate_game() {
    FILE* startFile;
    startFile = fopen("start_input.txt", "r");
    // PARSING GIVING VALUES
    unsigned int n, k, g, gv, o; // nums of...players /cauldrons |green card| value of green card| other color card(not green)
    do {
        //cin >> n >> k >> g >> gv >> o;
        if (fscanf(startFile, "%d %d %d %d %d", &n, &k, &g, &gv, &o) == 5) {
            if ((MIN_PLAYERS <= n && n <= MAX_PLAYERS)\
                && (MIN_CAULDRONS <= k && k <= MAX_CAULDRONS)\
                && (MIN_GREEN <= g && g <= MAX_GREEN)\
                && (MIN_G_VAL <= gv && gv <= MAX_G_VAL)\
                && (MIN_OTHER <= o && o <= MAX_OTHER)) break;
            else {
                printf("Looks like you entered wrong values");
            }

        }
        else {
            printf("Something wrong with start_input file");
        }


    } while (true);
    //CONFIGURATION FILE
    FILE* configFile;
    configFile = fopen("config.txt", "r");
    int active_player;
    int exp;
    fscanf(configFile, "active player = %d\n", &active_player);
    fscanf(configFile, "explosion threshold = %d\n", &exp);
    fclose(configFile);

    // CREATE GAME OBJECTS

    cards_t main_deck;
    players_t players;
    cauldrons_t cauldrons;
    fill_deck(&main_deck, k, g, gv, o, startFile);

    shuffle_deck(&main_deck);

    fclose(startFile);
    create_game_objects(&main_deck, &players, &cauldrons, k, g, gv, o, n);
    // GIVING CARDS TO PLAYERS
    give_cards_to_players(&players, &main_deck, n);


    FILE* statusFile;
    statusFile = fopen("game_status.txt", "w");
    // HEADER
    print_header(n, active_player, statusFile, exp);
    // GAME_STATE
    show_players_decks(&players, statusFile);
    show_cauldrons(&cauldrons, statusFile);
    fclose(statusFile);
}
//  GETTING CURRENT STATE FUNCTIONS

int checkcolor(char color[]) {
    
    if (!strncmp(color, "blue", 4)) return 0;
    else if (!strncmp(color, "red", 3)) return 1;
    else if (!strncmp(color, "violet", 6)) return 2;
    else if (!strncmp(color, "yellow", 6)) return 3;
    else if (!strncmp(color, "white", 5)) return 4;
    else if (!strncmp(color, "black", 5)) return 5;
    else {
        return -1;
    }
}
char count_cards(cards_t* cards, FILE* statusFile) {
    char c;
    c = (char)fgetc(statusFile);
    while (c != '\n' && c != EOF) {

        card_t card;
        if (!isdigit(c)) {
            c = (char)fgetc(statusFile);
        }

        if (c == '\n') break;

        if (isdigit(c)) {
            int digit1 = c - '0';
            c = (char)fgetc(statusFile);
            if (isdigit(c)) {
                int digit2 = c - '0';
                card.card_value = digit1 * 10 + digit2;
                c = (char)fgetc(statusFile);
            }
            else {
                card.card_value = digit1;
            }
        }
        char color[COLOR_L] = {};
        if (!isalpha(c)) {
            c = (char)fgetc(statusFile);
            
            int pos = 0;
            while (isalpha(c) && c != EOF) {
                color[pos] = c;
                pos++;
                c = (char)fgetc(statusFile);
            }
        }
        card.card_color = (colors_t)checkcolor(color);
        cards->deck[cards->length] = card;
        cards->length++;
        if (isspace(c) && c != '\n') {
            c = (char)fgetc(statusFile);
        }
        if (c == EOF) break;
    }
    return c;
}
void count_players_cards(players_t* players, int nums_players, FILE* statusFile) {
    int id;
    for (int i = 0; i < nums_players; i++)
    {
        if (fscanf(statusFile,"%d player hand cards:", &id)) {
            count_cards(&(players->players_arr[i]).hand_cards, statusFile);
        }
        if (fscanf(statusFile,"%d player deck cards:", &id)) {
            count_cards(&(players->players_arr[i]).deck_cards, statusFile);
        }
    }
    
}
int count_cauldrons(cauldrons_t* cauldrons, FILE* statusFile,int cauldrons_colors[]) {
    int id_p;
    for (int i = 0; fscanf(statusFile, "%d  pile cards:", &id_p) != 0; i++) {
        char c;
        c = count_cards(&(cauldrons->cauldrons_arr[i]).cauldron_deck, statusFile);

                     //NO COLOR DETERMINATE FOR CAULDRON
        if((colors_t)cauldrons_colors[i] != -2){
            cauldrons->cauldrons_arr[i].cauldron_color = (colors_t)cauldrons_colors[i];
        }
        
        if (c == EOF) break;
    }
    cauldrons->length = id_p;
    return id_p;
}
int get_nums_cards(player_t player) {
    int number_of_cards = 0;
    for (int j = 0; j < player.hand_cards.length; j++)
    {
        //cout << "Color:" << deck.deck[j].color << " VALUE:" << deck.deck[j].card_value << endl;   
        number_of_cards++;
    }
    return number_of_cards;
}
int is_explode(cauldron_t cauldron, int exp) {
    cards_t deck = cauldron.cauldron_deck;
    int sum = 0;
    for (int j = 0; j < cauldron.cauldron_deck.length; j++)
    {
        //cout << "Color:" << deck.deck[j].color << " VALUE:" << deck.deck[j].card_value << endl;
        int color = deck.deck[j].card_color;

        sum += deck.deck[j].card_value;


    }
    if (sum > exp) {
        
        return 1;
    }
    return 0;
}
int is_different_colors(cauldron_t cauldron) {
    cards_t deck = cauldron.cauldron_deck;
    int color_basic = -1;
    for (int j = 0; j < cauldron.cauldron_deck.length; j++)
    {
        //cout << "Color:" << deck.deck[j].color << " VALUE:" << deck.deck[j].card_value << endl;
        int color = deck.deck[j].card_color;
        if (color != -1) { // not green
            if (color_basic != -1 && color_basic != color) {
                return 1;
            }
            else {
                color_basic = color;
            }
        }

    }
    return 0;
}
int check_cards(cauldrons_t cauldrons, players_t players, int exp, int active, int cauldrons_color[]) {
    int num_flag = 1;
    int hand_cards_num[MAX_PLAYERS] = {};
    // adding nums of cards to a hand_cards_num array
    for (int i = 0; i < players.length; i++)
    {
        player_t player = players.players_arr[i];
        hand_cards_num[i] = get_nums_cards(player);
    }
    // check for proper cards nums in hand_cards array
    for (int i = 0; i < players.length; i++)
    {
        player_t player = players.players_arr[i];
        int cnum = hand_cards_num[i];  // current number of cards 
        int anum = hand_cards_num[active - 1]; // active player number of cards
        if (abs(cnum - anum) > 1) {
            num_flag = 0;
        }
    }

    if (!num_flag) {
        printf("The number of players cards on hand is wrong\n");
    }
    int diff_flag = 0;
    for (int i = 0; i < cauldrons.length; i++)
    {

        cauldron_t cauldron = cauldrons.cauldrons_arr[i];

        if (is_different_colors(cauldron) && diff_flag == 0) {
            diff_flag = is_different_colors(cauldron);
        }

        if (is_different_colors(cauldron)) {
            printf("Two different colors were found on the %d pile\n", i + 1);
            
        }
    }
    int exp_flag = 0;
    for (int i = 0; i < cauldrons.length; i++)
    {

        cauldron_t cauldron = cauldrons.cauldrons_arr[i];
        exp_flag = is_explode(cauldron, exp);
        if (exp_flag) {
            printf("Pile number %d should explode earlier\n", i + 1);
        }
    }
    if (!exp_flag && !diff_flag && num_flag) {
        return 1;
    }
    else {
        return 0;
    }

}

// MAKING MOVE FUNCTIONS
void delete_first_cards(player_t* player) {

    for (int i = 0; i < player->hand_cards.length; i++)
    {
        player->hand_cards.deck[i] = player->hand_cards.deck[i + 1];
    }
    player->hand_cards.length--;
}
card_t get_first_card(player_t* player) {
    card_t card;
    card = player->hand_cards.deck[0];

    return card;
}
int find_cauldron(card_t card, cauldrons_t *cauldrons, int cauldrons_colors[]) {
    colors_t color = card.card_color;
    
    if (color == -1) {
        int colors_number = cauldrons->length;
        return rand() % colors_number;
    }

    // ITERATING OVER CAULDRONS WITH COLOR
    for (int i = 0; i < cauldrons->length; i++)
    {
        cauldron_t* cauldron = &(cauldrons->cauldrons_arr[i]);
        
        if (color == cauldron->cauldron_color) {
                return i;
        }

    }

    for (int i = 0; i < cauldrons->length; i++)
    {
        cauldron_t* cauldron = &(cauldrons->cauldrons_arr[i]);

        if (cauldron->cauldron_color == green) {
            cauldron->cauldron_color = color;
            cauldrons_colors[i] = color;
            return i;
        }
    }

    return -1;
}
int sum_of_cauldron(cauldron_t * cauldron) {
    int sum = 0;
    for (int i = 0; i < cauldron->cauldron_deck.length; i++)
    {
        sum += cauldron->cauldron_deck.deck[i].card_value;
    }
    return sum;
}
int find_min_cauldron(card_t card, cauldrons_t* cauldrons, int cauldrons_colors[]) {
    colors_t color = card.card_color;

    // check if card is green 
    if (color == -1) {

        int index_of_cauldron = 0;
        int sum = 100000;

        for (int i = 0; i < cauldrons->length; i++)
        {
            cauldron_t* cauldron = &(cauldrons->cauldrons_arr[i]);
            if (sum > sum_of_cauldron(cauldron)) {
                sum = sum_of_cauldron(cauldron);
                index_of_cauldron = i;

            }
        }
        return index_of_cauldron;

    }

    // ITERATING OVER CAULDRONS WITH COLOR
    for (int i = 0; i < cauldrons->length; i++)
    {
        cauldron_t* cauldron = &(cauldrons->cauldrons_arr[i]);

        if (color == cauldron->cauldron_color) {
            return i;
        }

    }
    // ITERATING OVER EMPTY 
    for (int i = 0; i < cauldrons->length; i++)
    {
        cauldron_t* cauldron = &(cauldrons->cauldrons_arr[i]);

        if (cauldron->cauldron_color == green && cauldron->cauldron_deck.length == 0) {
            cauldron->cauldron_color = color;
            cauldrons_colors[i] = color;
            return i;
        }
    }
    // ITERATING OVER GREEN CAULDRONS WITH MIN SUM OF CARDS
    int index_of_cauldron = 0;
    int sum = 100000;

    for (int i = 0; i < cauldrons->length; i++)
    {
        cauldron_t* cauldron = &(cauldrons->cauldrons_arr[i]);
        if (cauldron->cauldron_color == green) {
            if (sum > sum_of_cauldron(cauldron)) {
                sum = sum_of_cauldron(cauldron);
                index_of_cauldron = i;
                
            }
           
        }
    }
    cauldrons->cauldrons_arr[index_of_cauldron].cauldron_color = color;
    cauldrons_colors[index_of_cauldron] = color;
    return index_of_cauldron;


    
}
void delete_all_cards(cauldron_t* cauldron) {
    for (int i = 0; i < cauldron->cauldron_deck.length; i++)
    {
        cauldron->cauldron_deck.deck[i].card_value = 0;
    }
    cauldron->cauldron_deck.length = 0;

}
void move_exploded_cards(cauldron_t* cauldron, player_t* player) {
    for (int i = 0; i < cauldron->cauldron_deck.length; i++)
    {
        card_t card = cauldron->cauldron_deck.deck[i];
        add_card(&player->deck_cards, card);
    }
    delete_all_cards(cauldron);
}

card_t get_min_card(player_t* player,int * ind) {
    card_t card;
    int index = 0;
    for (int i = 1; i < player->hand_cards.length; i++)
    {
        if (player->hand_cards.deck[i].card_value < player->hand_cards.deck[index].card_value) {
            index = i;
        }
    }
    card = player->hand_cards.deck[index];
    *ind = index;
    return card;
}
card_t get_max_card(player_t* player, int* ind) {
    card_t card;
    int index = 0;
    for (int i = 1; i < player->hand_cards.length; i++)
    {
        if (player->hand_cards.deck[i].card_value > player->hand_cards.deck[index].card_value) {
            index = i;
        }
    }
    card = player->hand_cards.deck[index];
    *ind = index;
    return card;
}


void delete_index_card(player_t* player,int index) {

    for (int i = index; i < player->hand_cards.length; i++)
    {
        player->hand_cards.deck[i] = player->hand_cards.deck[i + 1];
    }
    player->hand_cards.length--;
}

int will_explode(cauldrons_t *cauldrons, card_t card, int cauldron_id,int exp) {
    int sum = 0;
    cauldron_t cauldron = cauldrons->cauldrons_arr[cauldron_id];
    for (int i = 0; i < cauldron.cauldron_deck.length; i++)
    {
        sum += cauldron.cauldron_deck.deck[i].card_value;
    }
    sum += card.card_value;
    if (sum > exp) {
        return 1;
    }
    else {
        return 0;
    }


}

int find_opt_card(player_t* active_player, cauldrons_t* cauldrons, int cauldrons_colors[],int exp, int * cauldron_id) {

    int sums_of_cauldrons[MAX_CAULDRONS] = {};
    for (int i = 0; i < cauldrons->length; i++)
    {
        sums_of_cauldrons[i] = sum_of_cauldron(&cauldrons->cauldrons_arr[i]);
    }


    int card_index = -1;
    int difference = exp;
    *cauldron_id = -1;
    
    for (int i = 0; i < active_player->hand_cards.length; i++)
    {
        card_t card = active_player->hand_cards.deck[i];
        int cauldron_value_max = exp - card.card_value;
        for (int j = 0; j < cauldrons->length; j++)
        {
            if (sums_of_cauldrons[j] <= cauldron_value_max && cauldrons_colors[j] == card.card_color) {
                if (cauldron_value_max - sums_of_cauldrons[j] <= difference) {
                    card_index = i;
                    *cauldron_id = j;
                    difference = cauldron_value_max - sums_of_cauldrons[j];
                }
            }
        }

    }
    return card_index;
}
void move_card(cauldrons_t* cauldrons, players_t* players, int active, int exp,int cauldrons_colors[], int cauldrons_color[], int mode) {
    player_t* active_player = &(players->players_arr[active - 1]);
    card_t card;
    int cauldron_id;
    if (mode == 0) {
        card = get_first_card(active_player);
        delete_first_cards(active_player);
        cauldron_id = find_cauldron(card, cauldrons, cauldrons_colors);
    }
    else if(mode == 1){
        int* index;
        int standart_index = 0;
        index = &standart_index;

        card = get_min_card(active_player,index);
        delete_index_card(active_player, *index);
        cauldron_id = find_min_cauldron(card, cauldrons, cauldrons_colors);
        
    }
    else if (mode == 2) {
        int* index;
        int standart_index = 0;
        index = &standart_index;

        card = get_min_card(active_player, index);
        cauldron_id = find_min_cauldron(card, cauldrons, cauldrons_colors);
        if (will_explode(cauldrons, card, cauldron_id, exp)) {
            card = get_max_card(active_player, index);
            delete_index_card(active_player, *index);
            cauldron_id = find_min_cauldron(card, cauldrons, cauldrons_colors);
        }
        else {
            delete_index_card(active_player, *index);
        }
    }
    else if (mode == 3) {
        // FULL ARRAY WITH SUM OF CAULDRONS CARDS
        
        
        int card_index = find_opt_card(active_player, cauldrons, cauldrons_colors, exp, &cauldron_id);

        if (card_index != -1) {
            card = active_player->hand_cards.deck[card_index];
            delete_index_card(active_player, card_index);
        }
        else {
            move_card(cauldrons, players, active, exp, cauldrons_color, cauldrons_color, 2);
            return;
        }
    }
    else if (mode == 4) {
        // FULL ARRAY WITH SUM OF CAULDRONS CARDS


        int card_index = find_opt_card(active_player, cauldrons, cauldrons_colors, exp, &cauldron_id);

        if (card_index != -1) {
            card = active_player->hand_cards.deck[card_index];
            delete_index_card(active_player, card_index);

        }
        else {
            // GETTING MAX COLORs in players deck cards and cauldrons
            int colors_arr[MAX_CAULDRONS] = {};
            for (int i = 0; i < cauldrons->length; i++)
            {
                cauldron_t cauldron = cauldrons->cauldrons_arr[i];
                for (int i = 0; i < cauldron.cauldron_deck.length; i++)
                {
                    card_t ccard = cauldron.cauldron_deck.deck[i];
                    if (ccard.card_color != green) {
                        colors_arr[ccard.card_color]++;
                    }
                }
            }
            for (int i = 0; i < active_player->deck_cards.length; i++)
            {
                card_t card = active_player->deck_cards.deck[i];
                if (card.card_color != green) {
                    colors_arr[card.card_color]++;
                }
            }

            // FIND MAX COLOR IN YOUR DECK

            int max_sum = colors_arr[0];
            int max_color_index = 0;
            for (int i = 1; i < cauldrons->length-1; i++)
            {
                if (max_sum < colors_arr[i]) {
                    max_color_index = i;
                    max_sum = colors_arr[i];
                }
            }
            // finding this color card in your deck

            for (int i = 0; i < active_player->hand_cards.length; i++)
            {
                card_t card = active_player->hand_cards.deck[i];
                if (card.card_color == max_color_index) {
                    card_index = i;
                    break;
                }
            }
            if (card_index != -1) {
                
                // finding cauldron by color
                cauldron_id = -1;
                for (int i = 0; i < cauldrons->length; i++)
                {
                    if (cauldrons->cauldrons_arr[i].cauldron_color == max_color_index) {
                        cauldron_id = i;
                    }
                }
                if (cauldron_id == -1) {

                    for (int i = 0; i < cauldrons->length; i++)
                    {
                        if (cauldrons->cauldrons_arr[i].cauldron_color == green) {
                            cauldron_id = i;
                        }
                    }

                }
                card = active_player->hand_cards.deck[card_index];
                delete_index_card(active_player, card_index);

            }
            else {
                move_card(cauldrons, players, active, exp, cauldrons_color, cauldrons_color, 2);
                return;
            }

        }
    }
   


    add_card(&cauldrons->cauldrons_arr[cauldron_id].cauldron_deck, card);

    int exp_flag = is_explode(cauldrons->cauldrons_arr[cauldron_id], exp);

    if (exp_flag) {
        printf("\n\n\t\t\t\t!!!!!!!!BOOOOOOM!!!!!!!!!!! \n\n");
        cauldrons_color[cauldron_id] = -1;
        move_exploded_cards(&cauldrons->cauldrons_arr[cauldron_id], active_player);
    }
}
void print_color(int color) {

    switch (color) {
    case green:
        printf("green");
        break;
    case blue:
        printf("blue");
        break;
    case red:
        printf("red");
        break;
    case violet:
        printf("violet");
        break;
    case yellow:
        printf("yellow");
        break;
    case white:
        printf("white");
        break;
    case black:
        printf("black");
        break;
    default:
        printf("Something wrong with color!!!");
        break;
    }
}
void end_game(players_t players, int players_colors[][MAX_PLAYERS], int players_resist[], int results[]) {


    // full the players-colors array 

    for (int i = 0; i < players.length; i++)
    {
        //i - index of player
        cards_t deck = players.players_arr[i].deck_cards;
        for (int j = 0; j < deck.length; j++)
        {
            card_t card = deck.deck[j];
            int ci = card.card_color; // ci - color index
            if (ci != -1) {
                players_colors[ci][i]++;
            }


        }
    }
    // finding player resistance to color

    for (int i = 0; i < MAX_CAULDRONS; i++)
    {
        int index_max = 0;
        int max_val = players_colors[i][0];
        for (int j = 1; j < MAX_PLAYERS; j++)
        {
            if (players_colors[i][j] > max_val) {
                index_max = j;
                max_val = players_colors[i][j];
            }
            else if (players_colors[i][j] == max_val) {
                index_max = -1;
            }
        }
        if (index_max != -1) {
            printf("\n\t\t\t\tNa kolor ");
            print_color(i);
            players_resist[i] = index_max; // for i color index_max = index player
            printf(" odporny jest gracz% d\n", index_max + 1);
        }
        else {
            players_resist[i] = -2;
        }

    }

    // counting
    int result[MAX_PLAYERS] = {};
    for (int i = 0; i < players.length; i++)
    {
        //i - index of player
        cards_t deck = players.players_arr[i].deck_cards;
        for (int j = 0; j < deck.length; j++)
        {
            card_t card = deck.deck[j];
            int ci = card.card_color; // ci - color index
            if (ci != -1) {
                if (i != players_resist[ci]) {
                    result[i]++;
                }
            }
            else {
                result[i] += 2;
            }
        }
    }
    for (int i = 0; i < players.length; i++)
    {
        printf("\n\t\t\t\tWynik gracza %d = %d\n", i + 1, result[i]);
        //results[i] += result[i];
    }

    // FIND WINNER 

    int index_of_winner = 0;
    int winner_result = result[0];
    for (int i = 1; i < players.length; i++)
    {
        if (result[i] <= winner_result) {
            if (result[i] != winner_result) {
                index_of_winner = i;
                winner_result = result[i];
            }
            else {
                index_of_winner = -1;
            }
        }
    }
    if (index_of_winner != -1) {
        results[index_of_winner]++;
        printf("Wygral gracz %d\n", index_of_winner + 1);
    }
    else {
        printf("REMIS\n");
    }
    
}
int is_end(players_t players) {
    for (int i = 0; i < players.length; i++)
    {
        if (players.players_arr[i].hand_cards.length) return 0;
        
    }
    return 1;
}
void wait_for(double s)
{
    clock_t start = clock();
    while ((clock() - start) / CLOCKS_PER_SEC < s);
}
int main(int argc, char* argv[])
{   

    int results[MAX_PLAYERS] = {};
    int rounds = 5;
    // 0 - 8 % win  agaings mode 3
    // 1 - 9 % win  agaings mode 3
    // 2 - 33 % win  agaings mode 3
    int players_game_modes[MAX_PLAYERS] = { 0, 3 };
    // ROUNDS
    for (int r = 0; r < rounds; r++)
    {

        int my_id = 1;
        // READING FROM CMD
        if (argc != 1) {
            char number = *argv[1];
            int num = number - '0';
            my_id = num;
        }
        printf("\t\t\t\t\t\YOU ARE PLAYER %d\n", my_id);
        srand(time(NULL));
        // IF YOU ARE FIRST PLAER YOU GENERATE MAIN DECK
        if (my_id == 1) {
            printf("\n\t\t\t\tGENERATING GAME FROM start_input.txt\n\n");
            generate_game();
        }

        // GAME PROCESS
        int gameover = 0;

        //STORING CAULDRONS_COLORS  
        int cauldrons_color[MAX_CAULDRONS] = {};
        for (int i = 0; i < MAX_CAULDRONS; i++)
        {
            cauldrons_color[i] = -1;
        }
        while (!gameover) {

            // WAITING FOR ANOTHER PLAYER (CMD)
            wait_for(0);
            FILE* statusFile;
            statusFile = fopen("game_status.txt", "r");

            // CHECK IS GAME_STATUS_OK  
            printf("\nChecking game status...\n");

            int nums_players;
            int active_player;
            int exp;
           
            
            // GET CURRENT GAME FROM FILE  game_status.txt
            players_t players;
            cauldrons_t cauldrons;
            if (fscanf(statusFile, "active player = %d\nplayers number = %d\nexplosion threshold = %d", &active_player, &nums_players, &exp)) {

                create_players(&players, nums_players);
                count_players_cards(&players, nums_players, statusFile);
                count_cauldrons(&cauldrons, statusFile,cauldrons_color);
                print_players_state(players);
                print_cauldrons_state(cauldrons);
                if (check_cards(cauldrons, players, exp, active_player, cauldrons_color)) {
                    printf("Current state of the game is ok\n");
                }
                else {
                    break;
                }
            }
            fclose(statusFile);

            if (is_end(players)) {
                gameover = 1;
                int players_colors[MAX_CAULDRONS][MAX_PLAYERS] = { 0 };
                int players_resist[MAX_CAULDRONS] = { 0 };
                printf("\n\t\t\t\tEND GAME\n");
                end_game(players, players_colors, players_resist, results);
                break;

            }
            // IF YOU WANT TO SHOW THE PROGRAM IN CONSOLE UNCOMMENT THIS LINE    
            //if (active_player != my_id) break;

            // SIMPLE MOVE or NOT SIMPLE MOVE :-) 

            int mode = players_game_modes[active_player - 1];
            /*
            if (active_player == 1) {
                mode = 1; // player 1
            }
            else {
                mode = 3;  // player 2 
            }
            */
            
            
            move_card(&cauldrons, &players, active_player, exp,cauldrons_color, cauldrons_color, mode); /// 0 - default mode
            printf("\n\t\t\t\tPLAYER %d MADE  MOVE\n", active_player);
            // CHANGING ACTIVE PLAYER
            if ((active_player + 1) > nums_players) {
                active_player = (active_player + 1) % nums_players;
            }
            else {
                active_player = active_player + 1;
            }

            // STATUS FILE UPDATE
            statusFile = fopen("game_status.txt", "w");
            // HEADER
            print_header(nums_players, active_player, statusFile, exp);
            // GAME_STATE
            show_players_decks(&players, statusFile);
            show_cauldrons(&cauldrons, statusFile);
            fclose(statusFile);
            
        }
        printf("\n\n\n\n\n\n\n\n\n\n\n\n\n");
    }


    //TEST OF PLAYERS RESULT
    for (int i = 0; i < MAX_PLAYERS; i++)
    {   
        if (results[i] != 0) {
            printf("Result of player %d is : %d win from %d rounds (%d%%)\n", i+1, results[i],rounds,int(100*float(results[i])/rounds));
        }
    }
