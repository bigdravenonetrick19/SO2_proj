void amesteca_pachet(Game *joc) {
    for (int i = joc->deck_size - 1; i > 0; i--) {
        int j = rand() % (i + 1);
        Card temp = joc->deck[i];
        joc->deck[i] = joc->deck[j];
        joc->deck[j] = temp;
    }
}

// Functia care pregateste un joc nou
void pregateste_joc(Game *joc, int game_id) {
    joc->deck_size = 0;
    joc->game_id = game_id;

    // Adaugam cartile
    for (int i = 0; i < 4; i++) joc->deck[joc->deck_size++] = (Card){ATTACK, "Attack"};
    for (int i = 0; i < 4; i++) joc->deck[joc->deck_size++] = (Card){SKIP, "Skip"};
    for (int i = 0; i < 4; i++) joc->deck[joc->deck_size++] = (Card){FAVOR, "Favor"};
    for (int i = 0; i < 4; i++) joc->deck[joc->deck_size++] = (Card){SHUFFLE, "Shuffle"};
    for (int i = 0; i < 5; i++) joc->deck[joc->deck_size++] = (Card){SEE_THE_FUTURE, "See the Future"};
    for (int i = 0; i < 5; i++) joc->deck[joc->deck_size++] = (Card){NOPE, "Nope"};
    
    // Cele 5 tipuri de pisici
    for (int i = 0; i < 4; i++) joc->deck[joc->deck_size++] = (Card){CAT_TACOCAT, "Tacocat"};
    for (int i = 0; i < 4; i++) joc->deck[joc->deck_size++] = (Card){CAT_CATTERMELLON, "Cattermellon"};
    for (int i = 0; i < 4; i++) joc->deck[joc->deck_size++] = (Card){CAT_POTATO, "Potato"};
    for (int i = 0; i < 4; i++) joc->deck[joc->deck_size++] = (Card){CAT_BEARD, "Beard"};
    for (int i = 0; i < 4; i++) joc->deck[joc->deck_size++] = (Card){CAT_RAINBOW, "Rainbow"};

    amesteca_pachet(joc);

    for (int p = 0; p < 2; p++) {
        joc->players[p].hand_size = 0;
        joc->players[p].is_alive = 1;
        joc->players[p].hand[joc->players[p].hand_size++] = (Card){DEFUSE, "Defuse"}; // Defuse initial
    }
    for (int i = 0; i < 4; i++) joc->deck[joc->deck_size++] = (Card){DEFUSE, "Defuse"};

    amesteca_pachet(joc);

    for (int p = 0; p < 2; p++) {
        for (int i = 0; i < 4; i++) {
            joc->players[p].hand[joc->players[p].hand_size++] = joc->deck[--joc->deck_size];
        }
    }

    joc->deck[joc->deck_size++] = (Card){EXPLODING_KITTEN, "Exploding Kitten"};
    amesteca_pachet(joc);

    joc->current_turn = 0;
    joc->game_running = 1;
}
