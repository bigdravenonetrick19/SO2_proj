#ifndef GUI_H
#define GUI_H

#include "exploding_kittens.h"

#define LOG_LINES 8
#define LOG_LEN   80

/* Ce vede clientul: NU contine mana adversarului, nici pachetul.
 * Serverul trimite doar aceasta structura (cu campuri de dimensiune fixa). */
typedef struct {
    char my_name[MAX_NAME_LEN];
    char opp_name[MAX_NAME_LEN];
    Card hand[20];
    int  hand_size;
    int  opp_hand_size;
    int  deck_size;
    int  my_turn;                 /* 1 daca e randul meu */
    int  has_discard;             /* 1 daca exista carte in discard */
    Card discard_top;
    char log[LOG_LINES][LOG_LEN]; /* ultimele evenimente */
} GameView;

void gui_init(void);
void gui_end(void);
void gui_draw(const GameView *v, int selected);
/* Citeste o tasta si intoarce: >=0 = indexul cartii jucate,
 * -1 = nimic, -2 = trage carte, -3 = iesire */
int  gui_handle_key(const GameView *v, int *selected);

#endif
