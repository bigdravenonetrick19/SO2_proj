#include <stdio.h>

#include "exploding_kittens.h"

Game joc_curent;
int clienti_conectati=0;

void amesteca_pachet() {
    for (int i = joc_curent.deck_size - 1; i > 0; i--) {
        int j = rand() % (i + 1);
        Card temp = joc_curent.deck[i];
        joc_curent.deck[i] = joc_curent.deck[j];
        joc_curent.deck[j] = temp;
    }
}

#include "exploding_kittens.h"

// Starea jocului global (o avem aici ca sa o poata accesa toate functiile)
Game joc;

// Functie simpla pentru a amesteca pachetul (algoritmul Fisher-Yates)
void amesteca() {
    for (int i = joc.deck_size - 1; i > 0; i--) {
        int j = rand() % (i + 1);
        Card temp = joc.deck[i];
        joc.deck[i] = joc.deck[j];
        joc.deck[j] = temp;
    }
}

// Pregatim jocul conform regulilor (pachetul complet)
void pregateste_joc() {
    joc.deck_size = 0;

    // 1. Punem toate cartile normale in pachet
    for (int i = 0; i < 4; i++) joc.deck[joc.deck_size++] = (Card){ATTACK, "Attack"};
    for (int i = 0; i < 4; i++) joc.deck[joc.deck_size++] = (Card){SKIP, "Skip"};
    for (int i = 0; i < 4; i++) joc.deck[joc.deck_size++] = (Card){FAVOR, "Favor"};
    for (int i = 0; i < 4; i++) joc.deck[joc.deck_size++] = (Card){SHUFFLE, "Shuffle"};
    for (int i = 0; i < 5; i++) joc.deck[joc.deck_size++] = (Card){SEE_THE_FUTURE, "See the Future"};
    for (int i = 0; i < 5; i++) joc.deck[joc.deck_size++] = (Card){NOPE, "Nope"};
    for (int i = 0; i < 4; i++) joc.deck[joc.deck_size++] = (Card){CAT_TACOCAT, "Tacocat"};
    for (int i = 0; i < 4; i++) joc.deck[joc.deck_size++] = (Card){CAT_CATTERMELLON, "Cattermellon"};
    for (int i = 0; i < 4; i++) joc.deck[joc.deck_size++] = (Card){CAT_POTATO, "Potato"};
    for (int i = 0; i < 4; i++) joc.deck[joc.deck_size++] = (Card){CAT_BEARD, "Beard"};
    for (int i = 0; i < 4; i++) joc.deck[joc.deck_size++] = (Card){CAT_RAINBOW, "Rainbow"};

    amesteca(); // Amestecam cartile normale

    // 2. Initializam jucatorii
    for (int p = 0; p < 2; p++) {
        joc.players[p].hand_size = 0;
        joc.players[p].is_alive = 1;
    }

int main(void)
{




    return 0;
}
