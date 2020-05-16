#include "game.h"
#include "driver.h"
#include <ncurses.h>
#include <unistd.h>

static int init(const Game* game);
static void menu(void(*callback_menu)(void*));
static void start(void(*callback)(void*));
static int touche_bouton(void);
static int get_move(void);
static void draw_bg(void);
static void draw_bg_menu(void);
static void draw_entity(int ent_id);
static void update(void);

Driver ncurses_driver = {
    .game = NULL,
    .init = init,
    .menu = menu,
    .start = start,
    .touche_bouton = touche_bouton,
    .get_move = get_move,
    .draw_bg = draw_bg,
    .draw_bg_menu = draw_bg_menu,
    .draw_entity = draw_entity,
    .update = update
};

#define GAME (ncurses_driver.game)

static char tiles[NCell] = {',', '#', 'V','C','~','Y','F','I','O', ' ', '=', 'o', 'o', 'o', 'o', 'o', 'o','o', 'o', 'o', 'o', 'h', 'i', 'g', 's', 'c', 'o', 'r', 'e', ':', '0', '1', '2', '3', '4', '5', '6', '7', '8', '9', '?', '!', ':', '.', 'n', 'i', 'v', 'e', 'a', 'u', 'j', 'z', 'f', 'p', 'y', '+', ';'};
static const char* sprites[NSprite] = {"ooo@<<<@>>>@^^^@vvv@","===="};

enum { FPS = 15 };

static int init(const Game* game) {
    GAME = game;
    initscr();
    curs_set(0);
    noecho();
    halfdelay(1);
    return 0;
}

static void menu(void(*callback_menu)(void*)) {
    for(;;) {
        callback_menu(&ncurses_driver);
    }
}

static void start(void(*callback)(void*)) {
    for(;;) {
        callback(&ncurses_driver);
        usleep(90000);
    }
}

//fonction faite par Mustapha Ilyès DAHMANI:
static int touche_bouton(void){
    int car = getch();
    switch(car) {
        case ' ':
            return 1;
        default:
            break;
    }
    return 0;
}

//fonction faite par Pierre MARGALE:
static void vide_stdin(void){
    int c;
    while(c!=EOF){
        c=getch();
    }
}

static int get_move(void) {
    int car = getch();
    switch(car) {
        case 'z':
            vide_stdin();
            return Up;
        case 'q':
            vide_stdin();
            return Left;
        case 's':
            vide_stdin();
            return Down;
        case 'd':
            vide_stdin();
            return Right;
        default:
            break;
    }

    return Nothing;
}

static void draw_bg(void) {
    int y, x;
    for(y = 0; y < GAME->h; ++y) {
        for(x = 0; x < GAME->w; ++x) {
            int typecell = GAME->background[y * GAME->w + x];
            mvprintw(y, x, "%c", tiles[typecell]);
        }
    }
}

static void draw_bg_menu(void) {
    int y, x;
    for(y = 0; y < GAME->h; ++y) {
        for(x = 0; x < GAME->w; ++x) {
            int typecell = GAME->background[y * GAME->w + x];
            mvprintw(y, x, "%c", tiles[typecell]);
        }
    }
}

static void draw_entity(int ent_id) {
    static int anim = 0;
    mvprintw(GAME->entity[ent_id].y, GAME->entity[ent_id].x, "%c", sprites[ent_id][4 * GAME->entity[ent_id].dir + anim]);
    anim = (anim + 1) % 4;
}

static void update(void) {
    refresh();
}


