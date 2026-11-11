//
// Created by ubuntu on 11/11/26.


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
#include <ncurses.h> // Pentru GUI

#define PORT 8080
#define MAX_CLIENTS 10
#define MAX_NAME_LEN 32
#define MAX_CARDS 108

// Tipurile de cărți din joc
typedef enum {
    EXPLODING_KITTEN,
    DEFUSE,
    ATTACK,
    SKIP,
    FAVOR,
    SHUFFLE,
    SEE_THE_FUTURE,
    NOPE,
    CAT_TACOCAT,
    CAT_CATTERMELLON,
    CAT_POTATO,
    CAT_BEARD,
    CAT_RAINBOW,
    UNKNOWN_CARD
} CardType;

// Structura unei cărți
typedef struct {
    CardType type;
    char name[30];
} Card;

// Starea unui jucător
typedef struct {
    int socket_fd;
    char name[MAX_NAME_LEN];
    int id;             // 0 sau 1 (jucătorul 1 sau 2)
    Card hand[20];      // Mâna jucătorului (max 20 cărți)
    int hand_size;
    int is_alive;       // 1 dacă e în viață, 0 dacă a explodat
} Player;

// Starea unui joc (gestionat de server)
typedef struct {
    int game_id;
    Player players[2];
    Card deck[MAX_CARDS];
    int deck_size;
    int current_turn;   // 0 sau 1
    int game_running;
} Game;

// Comenzile trimise între client și server
typedef enum {
    CMD_JOIN,
    CMD_START_GAME,
    CMD_PLAY_CARD,
    CMD_DRAW_CARD,
    CMD_UPDATE_STATE,
    CMD_GAME_OVER,
    CMD_WAITING,
    CMD_ERROR
} CommandType;

// Structura unui mesaj schimbat între client și server
typedef struct {
    CommandType cmd;
    int card_index; // Folosit când jucătorul joacă o carte
    char message[256];
    Game current_game_state; // Trimitem starea jocului către client
} Message;

#endif