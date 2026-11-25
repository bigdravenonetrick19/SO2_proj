#include <string.h>
#include <locale.h>
#include <ncurses.h>
#include "gui.h"

enum { C_DEFAULT = 1, C_BOMB, C_DEFUSE, C_ACTION, C_NOPE, C_CAT, C_TITLE, C_OK };

static short card_color(CardType t) {
    switch (t) {
        case EXPLODING_KITTEN: return C_BOMB;
        case DEFUSE:           return C_DEFUSE;
        case NOPE:             return C_NOPE;
        case ATTACK: case SKIP: case FAVOR:
        case SHUFFLE: case SEE_THE_FUTURE: return C_ACTION;
        default:               return C_CAT;
    }
}

void gui_init(void) {
    setlocale(LC_ALL, "");
    initscr();
    cbreak();
    noecho();
    keypad(stdscr, TRUE);
    curs_set(0);
    if (has_colors()) {
        start_color();
        use_default_colors();
        init_pair(C_DEFAULT, -1, -1);
        init_pair(C_BOMB,   COLOR_WHITE,  COLOR_RED);
        init_pair(C_DEFUSE, COLOR_BLACK,  COLOR_GREEN);
        init_pair(C_ACTION, COLOR_BLACK,  COLOR_CYAN);
        init_pair(C_NOPE,   COLOR_WHITE,  COLOR_MAGENTA);
        init_pair(C_CAT,    COLOR_BLACK,  COLOR_YELLOW);
        init_pair(C_TITLE,  COLOR_YELLOW, -1);
        init_pair(C_OK,     COLOR_GREEN,  -1);
    }
}

void gui_end(void) { endwin(); }

/* Deseneaza o carte (latime 14, inaltime 5) la (y,x) */
static void draw_card(int y, int x, const Card *c, int selected) {
    short col = card_color(c->type);
    attron(COLOR_PAIR(col));
    if (selected) attron(A_REVERSE | A_BOLD);
    for (int r = 0; r < 5; r++) mvhline(y + r, x, ' ', 14);
    mvaddch(y, x, ACS_ULCORNER);     mvhline(y, x + 1, ACS_HLINE, 12);   mvaddch(y, x + 13, ACS_URCORNER);
    mvaddch(y + 4, x, ACS_LLCORNER); mvhline(y + 4, x + 1, ACS_HLINE, 12); mvaddch(y + 4, x + 13, ACS_LRCORNER);
    for (int r = 1; r < 4; r++) { mvaddch(y + r, x, ACS_VLINE); mvaddch(y + r, x + 13, ACS_VLINE); }
    /* Imparte numele pe maxim 3 randuri de cate 12 caractere (word wrap) */
    char lines[3][13];
    int n = 0, cur = 0;
    lines[0][0] = '\0';
    const char *p = c->name;
    while (*p && n < 3) {
        while (*p == ' ') p++;
        if (!*p) break;
        const char *w = p;
        while (*p && *p != ' ') p++;
        int wl = (int)(p - w);
        if (wl > 12) wl = 12;
        if (cur > 0 && cur + 1 + wl > 12) {       /* nu mai incape: rand nou */
            n++;
            cur = 0;
            if (n >= 3) break;
        }
        if (cur == 0) lines[n][0] = '\0';
        else lines[n][cur++] = ' ';
        memcpy(lines[n] + cur, w, wl);
        cur += wl;
        lines[n][cur] = '\0';
    }
    int total = (n < 3 && cur > 0) ? n + 1 : n;
    if (total > 3) total = 3;
    int start = y + 1 + (3 - total + 1) / 2;
    for (int i = 0; i < total; i++) {
        int len = (int)strlen(lines[i]);
        mvprintw(start + i, x + 1 + (12 - len) / 2, "%s", lines[i]);
    }
    if (selected) attroff(A_REVERSE | A_BOLD);
    attroff(COLOR_PAIR(col));
}

static void draw_back(int y, int x) {
    attron(COLOR_PAIR(C_DEFAULT));
    for (int r = 0; r < 5; r++) mvprintw(y + r, x, r == 0 || r == 4 ? "+------------+" : "|////////////|");
    attroff(COLOR_PAIR(C_DEFAULT));
}

void gui_draw(const GameView *v, int selected) {
    int H, W;
    getmaxyx(stdscr, H, W);
    erase();

    if (H < 24 || W < 80) {
        mvprintw(0, 0, "Terminal prea mic (minim 80x24).");
        refresh();
        return;
    }

    /* Titlu */
    attron(COLOR_PAIR(C_TITLE) | A_BOLD);
    mvprintw(0, (W - 22) / 2, "=== PISICILE EXPLOZIVE ===");
    attroff(COLOR_PAIR(C_TITLE) | A_BOLD);

    /* Adversar */
    mvprintw(2, 2, "Adversar: %s  (%d carti)", v->opp_name, v->opp_hand_size);
    int shown = v->opp_hand_size < 8 ? v->opp_hand_size : 8;
    for (int i = 0; i < shown; i++) draw_back(3, 2 + i * 6 > W - 16 ? W - 16 : 2 + i * 6);

    /* Centru: pachet + discard */
    int cy = 9;
    draw_back(cy, W / 2 - 17);
    mvprintw(cy + 5, W / 2 - 17, "Pachet: %d", v->deck_size);
    if (v->has_discard) draw_card(cy, W / 2 + 3, &v->discard_top, 0);
    else mvprintw(cy + 2, W / 2 + 3, "(discard gol)");
    mvprintw(cy + 5, W / 2 + 3, "Discard");

    /* Randul cui e */
    if (v->my_turn) {
        attron(COLOR_PAIR(C_OK) | A_BOLD);
        mvprintw(cy + 2, 2, ">> RANDUL TAU <<");
        attroff(COLOR_PAIR(C_OK) | A_BOLD);
    } else {
        mvprintw(cy + 2, 2, "Asteapta randul lui %s...", v->opp_name);
    }

    /* Log */
    int ly = cy + 7 > H - 12 ? H - 12 : cy + 7;
    mvprintw(ly - 1, 2, "Evenimente:");
    for (int i = 0; i < LOG_LINES && ly + i < H - 8; i++)
        mvprintw(ly + i, 4, "%.*s", W - 6, v->log[i]);

    /* Mana mea */
    int hy = H - 8;
    mvprintw(hy, 2, "Mana ta: %s", v->my_name);
    int per_row = (W - 2) / 15;
    int first = 0;
    if (selected >= per_row) first = selected - per_row + 1;   /* scroll orizontal */
    for (int i = first; i < v->hand_size && (i - first) < per_row; i++)
        draw_card(hy + 1, 2 + (i - first) * 15, &v->hand[i], i == selected);

    mvprintw(H - 1, 0, " <- -> alege | ENTER joaca | D trage | Q iesire ");
    refresh();
}

int gui_handle_key(const GameView *v, int *selected) {
    int ch = getch();
    switch (ch) {
        case KEY_LEFT:  if (*selected > 0) (*selected)--; return -1;
        case KEY_RIGHT: if (*selected < v->hand_size - 1) (*selected)++; return -1;
        case '\n': case KEY_ENTER:
            return (v->my_turn && v->hand_size > 0) ? *selected : -1;
        case 'd': case 'D': return v->my_turn ? -2 : -1;
        case 'q': case 'Q': return -3;
        default: return -1;
    }
}

#ifdef GUI_DEMO
/* Demo cu date false: gcc -DGUI_DEMO gui.c -o gui_demo -lncurses */
int main(void) {
    GameView v = {0};
    strcpy(v.my_name, "Ana");
    strcpy(v.opp_name, "Bogdan");
    Card c[] = {
        {DEFUSE, "Defuse"}, {ATTACK, "Attack"}, {SKIP, "Skip"}, {NOPE, "Nope"},
        {CAT_TACOCAT, "Tacocat"}, {SEE_THE_FUTURE, "See the Future"}, {EXPLODING_KITTEN, "Exploding Kitten"}
    };
    for (int i = 0; i < 7; i++) v.hand[v.hand_size++] = c[i];
    v.opp_hand_size = 5;
    v.deck_size = 33;
    v.my_turn = 1;
    v.has_discard = 1;
    v.discard_top = (Card){SHUFFLE, "Shuffle"};
    strcpy(v.log[0], "Bogdan a jucat Shuffle.");
    strcpy(v.log[1], "Ai tras o carte: Tacocat.");

    gui_init();
    int sel = 0, r;
    do {
        gui_draw(&v, sel);
        r = gui_handle_key(&v, &sel);
        if (r >= 0) snprintf(v.log[2], LOG_LEN, "Ai jucat: %s", v.hand[r].name);
    } while (r != -3);
    gui_end();
    return 0;
}
#endif
