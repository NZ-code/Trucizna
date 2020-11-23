#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include<stdio.h>
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




int main()
{   
    int nums_players;
    scanf("active player = 1\nplayers number = %d\n", &nums_players);
    
    int hand_cards[MAX_PLAYERS] = {};
    int deck_cards[MAX_PLAYERS] = {};

    
    
    for (int i = 0; i < nums_players; i++)
    {
        int id;
        int num;
        char word[12];
        scanf("%d player hand cards:", &id);
        int hand_cnt = 0;
        int deck_cnt = 0;
        char c;
        c = getchar();
        while (c != '\n' && scanf("%d %s", &num, word) == 2) {
            hand_cnt++;
            c = getchar();
            
        }
        hand_cards[i] = hand_cnt;
        
       
        scanf("%d player deck cards:", &id);
        
        c = getchar();
        while (c!='\n' && scanf("%d %s", &num, word) == 2) {
            deck_cnt++;
            c = getchar();
        }
        deck_cards[i] = deck_cnt;
    }
    for (int i = 0; i < nums_players; i++)
    {
        printf("%d player has %d cards on hand\n", i+1, hand_cards[i]);
        printf("%d player has %d cards in front of him\n", i+1, deck_cards[i]);
    }
}
/*
active player = 1
players number = 3
1 player hand cards: 4 green 4 green 4 green 1 blue 2 blue 4 blue 5 blue 7 blue 1 red 2 red 5 red 7 red 1 violet 2 violet 4 violet 5 violet 7 violet
1 player deck cards:
*/