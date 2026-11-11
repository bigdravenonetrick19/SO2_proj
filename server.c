#include <stdio.h>

#include "exploding_kittens.h"

#include "exploding_kittens.h"

// Avem un singur joc global pentru a simplifica lucrurile
Game joc;

// Functie simpla pentru a amesteca pachetul de carti (algoritmul Fisher-Yates)
void amesteca_pachet() {
    for (int i = joc.deck_size - 1; i > 0; i--) {
        int j = rand() % (i + 1);
        Card temp = joc.deck[i];
        joc.deck[i] = joc.deck[j];
        joc.deck[j] = temp;
    }
}

// Aceasta functie creeaza pachetul complet si il imparte jucatorilor
void pregateste_joc() {
    joc.deck_size = 0;
    joc.game_id = 1; // Il setam ca sa nu fie variabila moarta

    // 1. Adaugam toate cartile normale in pachet
    for (int i = 0; i < 4; i++) joc.deck[joc.deck_size++] = (Card){ATTACK, "Attack"};
    for (int i = 0; i < 4; i++) joc.deck[joc.deck_size++] = (Card){SKIP, "Skip"};
    for (int i = 0; i < 4; i++) joc.deck[joc.deck_size++] = (Card){FAVOR, "Favor"};
    for (int i = 0; i < 4; i++) joc.deck[joc.deck_size++] = (Card){SHUFFLE, "Shuffle"};
    for (int i = 0; i < 5; i++) joc.deck[joc.deck_size++] = (Card){SEE_THE_FUTURE, "See the Future"};
    for (int i = 0; i < 5; i++) joc.deck[joc.deck_size++] = (Card){NOPE, "Nope"};

    // Cele 5 tipuri de pisici
    for (int i = 0; i < 4; i++) joc.deck[joc.deck_size++] = (Card){CAT_TACOCAT, "Tacocat"};
    for (int i = 0; i < 4; i++) joc.deck[joc.deck_size++] = (Card){CAT_CATTERMELLON, "Cattermellon"};
    for (int i = 0; i < 4; i++) joc.deck[joc.deck_size++] = (Card){CAT_POTATO, "Potato"};
    for (int i = 0; i < 4; i++) joc.deck[joc.deck_size++] = (Card){CAT_BEARD, "Beard"};
    for (int i = 0; i < 4; i++) joc.deck[joc.deck_size++] = (Card){CAT_RAINBOW, "Rainbow"};

    // 2. Amestecam pachetul
    amesteca_pachet();

    // 3. Initializam jucatorii
    for (int p = 0; p < 2; p++) {
        joc.players[p].hand_size = 0;
        joc.players[p].is_alive = 1;
    }

    // 4. Le dam cate un Defuse fiecaruia
    for (int p = 0; p < 2; p++) {
        joc.players[p].hand[joc.players[p].hand_size++] = (Card){DEFUSE, "Defuse"};
    }
    // Punem restul de 4 Defuse in pachet
    for (int i = 0; i < 4; i++) {
        joc.deck[joc.deck_size++] = (Card){DEFUSE, "Defuse"};
    }

    // 5. Amestecam iar
    amesteca_pachet();

    // 6. Impartim cate 4 carti fiecarui jucator
    for (int p = 0; p < 2; p++) {
        for (int i = 0; i < 4; i++) {
            joc.players[p].hand[joc.players[p].hand_size++] = joc.deck[--joc.deck_size];
        }
    }

    // 7. Punem o singura pisica exploziva in pachet (pentru 2 jucatori)
    joc.deck[joc.deck_size++] = (Card){EXPLODING_KITTEN, "Exploding Kitten"};

    // 8. Ultima amestecare
    amesteca_pachet();

    // Setam randul primului jucator
    joc.current_turn = 0;
    joc.game_running = 1;
}

int main(void)
{




    return 0;
}
