#ifndef EXPLODING_KITTENS_H
#define EXPLODING_KITTENS_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <pthread.h>
/* ncurses NU se include aici: doar clientul (gui.c) il foloseste */

#define PORT 8080
#define MAX_NAME_LEN 32
#define MAX_CARDS 56   /* pachetul oficial are 56 de carti */

typedef enum {
    EXPLODING_KITTEN, DEFUSE, ATTACK, SKIP, FAVOR, SHUFFLE, SEE_THE_FUTURE, NOPE,
    CAT_TACOCAT, CAT_CATTERMELLON, CAT_POTATO, CAT_BEARD, CAT_RAINBOW, UNKNOWN_CARD
} CardType;

typedef struct {
    CardType type;
    char name[30];
} Card;

typedef struct {
    int socket_fd;
    char name[MAX_NAME_LEN];
    int id;
    Card hand[20];
    int hand_size;
    int is_alive;
} Player;

typedef struct {
    int game_id;
    Player players[2];
    Card deck[MAX_CARDS];
    int deck_size;
    int current_turn;
    int game_running;
    int attack_turns;   /* ture ramase de jucat dupa un Attack */
} Game;

typedef enum {
    CMD_JOIN, CMD_WAITING, CMD_START_GAME, CMD_PLAY_CARD, CMD_DRAW_CARD,
    CMD_UPDATE_STATE, CMD_GAME_OVER, CMD_ERROR
} CommandType;

#endif
