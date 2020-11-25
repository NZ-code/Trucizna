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


int is_green(char *napis) {

}

int main()
{   
    int nums_players;
    if (scanf("active player = 1\nplayers number = %d\n", &nums_players)) {
        int hand_cards[MAX_PLAYERS] = {};
        int deck_cards[MAX_PLAYERS] = {};
        int cauldrons[MAX_CAULDRONS] = {};
        int id;
        for (int i = 0; i < nums_players; i++)
        {
            if (scanf("%d player hand cards:", &id)) {
                char c = getchar();
                while (c != '\n' && c != EOF) {
                    char tmp = c;
                    c = getchar();
                    if (isdigit(c) && !isdigit(tmp)) {
                        hand_cards[i] += 1;
                    }
                }
            }
            if (scanf("%d player deck cards:", &id)) {
                char c = getchar();
                while (c != '\n' && c != EOF) {
                    char tmp = c;
                    c = getchar();
                    if (isdigit(c) && !isdigit(tmp)) {
                        deck_cards[i] += 1;
                    }
                }
            }
        }
        int id_p;
        int cauldrons_cnt=0;

        for (int i = 0; scanf("%d  pile cards:", &id_p) != 0; i++) {
            cauldrons_cnt++;
            char c = getchar();
            while (c != '\n') {
                char tmp = c;
                c = getchar();
                if (isdigit(c) && !isdigit(tmp)) {
                    cauldrons[i] += 1;
                }
                if (c == EOF) break;
            }
            if (c == EOF) break;
        }



        for (int i = 0; i < nums_players; i++)
        {
            printf("%d player has %d cards on hand\n", i + 1, hand_cards[i]);
            printf("%d player has %d cards in front of him\n", i + 1, deck_cards[i]);
           
        }
        for (int i = 0; i < cauldrons_cnt; i++)
        {
            printf("there are %d cards on %d pile\n",cauldrons[i],i+1);
        }
        
    }
    
    
        
}
