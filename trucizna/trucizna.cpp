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
#define COLOR_LENGTH 14

using namespace std;


int is_green(char *napis) {
    char napis2[] = "green\0";
    int flag = 1;
    for (int i = 0; napis[i]!='\0'; i++)
    {
        if (napis[i] != napis2[i]) {
            flag = 0;
        }
    }
    return flag;
}

int main()
{   
    int nums_players;
    if (scanf("active player = 1\nplayers number = %d\n", &nums_players)) {
        int cauldrons[MAX_CAULDRONS] = {};
        int id;
        int gc = 0;
        int gv = 0;
        for (int i = 0; i < nums_players; i++)
        {
            if (scanf("%d player hand cards:", &id)) {
                char c = getchar();

                while (c != '\n' && c != EOF) {
                    char tmp = c;
                    int num=0;
                    char color[COLOR_LENGTH] = {};
                    c = getchar();
                    if (isdigit(c)) {
                        int digit1 = c-'0';
                        c = getchar();
                        if (isdigit(c)) {
                            int digit2 = c -'0';
                            num = digit1 * 10 + digit2;
                        }
                        else {
                            num = digit1;
                        }
                        
                    }
                    c = getchar();
                    if (isalpha(c)) {
                        
                        for (int i = 0;isalpha(c); i++)
                        {
                            color[i] = c;
                            c = getchar();
                        }
                        if (is_green(color)) {
                            gc++;
                            if (gv == 0) {
                                gv = num;
                            }
                            else {
                                if (gv != num) {
                                    num = -1;
                                }
                            }
                        }
                    }
                   
                }
            }
            if (scanf("%d player deck cards:", &id)) {
                char c = getchar();

                while (c != '\n' && c != EOF) {
                    char tmp = c;
                    int num = 0;
                    char color[COLOR_LENGTH] = {};
                    c = getchar();
                    if (isdigit(c)) {
                        int digit1 = c - '0';
                        c = getchar();
                        if (isdigit(c)) {
                            int digit2 = c - '0';
                            num = digit1 * 10 + digit2;
                        }
                        else {
                            num = digit1;
                        }

                    }
                    c = getchar();
                    if (isalpha(c)) {

                        for (int i = 0; isalpha(c); i++)
                        {
                            color[i] = c;
                            c = getchar();
                        }
                        if (is_green(color)) {
                            gc++;
                            if (gv == 0) {
                                gv = num;
                            }
                            else {
                                if (gv != num) {
                                    gv = -1;
                                }
                                
                            }
                        }
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
                int num = 0;
                char color[COLOR_LENGTH] = {};
                c = getchar();
                if (isdigit(c)) {
                    int digit1 = c - '0';
                    c = getchar();
                    if (isdigit(c)) {
                        int digit2 = c - '0';
                        num = digit1 * 10 + digit2;
                    }
                    else {
                        num = digit1;
                    }

                }
                c = getchar();
                if (isalpha(c)) {

                    for (int i = 0; isalpha(c); i++)
                    {
                        color[i] = c;
                        c = getchar();
                    }
                    if (is_green(color)) {
                        gc++;
                        if (gv == 0) {
                            gv = num;
                        }
                        else {
                            if (gv != num) {
                                gv = -1;
                            }

                        }
                    }
                }

                if (c == EOF) break;
            }
            if (c == EOF) break;
        }     
        if (gv == 0) {
            printf("Green cards does not exist");
        }
        else if (gv == -1) {
            printf("Different green cards values occurred");
        }
        else {
            printf("Found %d green cards, all with %d value", gc, gv);
        }
        
    }
    
    
       /*
       active player = 1
       players number = 3
       1 player hand cards: 4 green 4 green 1 blue 
       1 player deck cards:
       */
}
