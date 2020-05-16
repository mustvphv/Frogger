#include "game.h"
#include "driver.h"
#include <stdio.h>
#include <unistd.h>
#ifdef __EMSCRIPTEN__
#include <emscripten.h>
#endif
#include <SDL.h>
#include <SDL_image.h>
#include <SDL/SDL_mixer.h>


static int init(const Game* game);
static void menu(void(*callback_menu)(void*));
static void start(void(*callback)(void*));
static int touche_bouton(void);
static int get_move(void);
static void draw_bg(void);
static void draw_bg_menu(void);
static void draw_entity(int ent_id);
static void update(void);

Driver sdl_driver = {
    .game = NULL,
    .init = init,
    .menu = menu,
    .start = start,
    .touche_bouton = touche_bouton,
    .get_move = get_move,
    .draw_bg = draw_bg,
    .draw_bg_menu = draw_bg_menu,
    .draw_entity = draw_entity,
    .update = update,
};

#define GAME (sdl_driver.game)

static SDL_Window *win;
static SDL_Renderer *ren;
static SDL_Texture* tiles[NCell];
static const char* tiles_files[] = {"files/noir.png","files/violet.png","files/voiture.png","files/camion1.png","files/bleu.png","files/gazon.png","files/serpent.png","files/finbois.png","files/finbois.png", "files/transparent.png", "files/barrenouv.png", "files/frog200points1petit.png", "files/frog200points2petit.png", "files/frog200points3petit.png", "files/frog200points4petit.png", "files/frog200points1grand.png", "files/frog200points2grand.png", "files/frog200points3grand.png", "files/frog200points4grand.png", "files/frog200points5grand.png", "files/frog200points6grand.png", "files/H.png", "files/I.png", "files/G.png", "files/S.png", "files/C.png", "files/O.png", "files/R.png", "files/E.png", "files/2points.png", "files/0.png", "files/1.png", "files/2.png", "files/3.png", "files/4.png", "files/5.png", "files/6.png", "files/7.png", "files/8.png", "files/9.png", "files/fleur.png", "files/croco.png", "files/tortue.png", "files/tortue2.png", "files/N.png", "files/Iniveau.png", "files/V.png", "files/Eniveau.png", "files/A.png", "files/U.png", "files/J.png", "files/Z.png", "files/F.png", "files/P.png", "files/Y.png", /**/"files/tortuesouseau.png", "files/tortue3.png"};
static SDL_Texture* sprites[NSprite];
static const char* sprites_files[] = {"files/frog.png","files/camion.png"};
static SDL_Rect set[4];


enum { SZ = 32 };
enum { FPS = 15 };

static int load_sprites(void) {
    int i;
    SDL_Surface *png;
    for(i = 0; i < NSprite; ++i) {
        png = IMG_Load(sprites_files[i]);
        if (png == NULL){
            SDL_DestroyRenderer(ren);
            SDL_DestroyWindow(win);
            printf("Error: %s\n", SDL_GetError());
            SDL_Quit();
            return 1;
        }
        sprites[i] = SDL_CreateTextureFromSurface(ren, png);
        SDL_FreeSurface(png);
    }
    return 0;
}

static int load_tiles(void) {
    int i;
    SDL_Surface *png;
    for(i = 0; i < NCell; ++i) {
        png = IMG_Load(tiles_files[i]);
        if (png == NULL){
            SDL_DestroyRenderer(ren);
            SDL_DestroyWindow(win);
            printf("Error: %s\n", SDL_GetError());
            SDL_Quit();
            return 1;
        }
        tiles[i] = SDL_CreateTextureFromSurface(ren, png);
        SDL_FreeSurface(png);
    }
    return 0;
}

//fonction modifié par Mustapha Ilyès DAHMANI (pour la musique)
static int init(const Game* game) {
    int i;
    

    GAME = game;
    if (SDL_Init(SDL_INIT_VIDEO) != 0){
        printf("SDL_Init Error: %s\n",  SDL_GetError());
        return 1;
    }
    
    win = SDL_CreateWindow("Game", 0, 0, GAME->w * SZ, GAME->h * SZ, SDL_WINDOW_SHOWN);
    if (win == NULL) {
        printf("SDL_CreateWindow Error: %s\n", SDL_GetError());
        SDL_Quit();
        return 1;
    }
    
    ren = SDL_CreateRenderer(win, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
    if (ren == NULL){
        SDL_DestroyWindow(win);
        printf("SDL_CreateRenderer Error: %s\n", SDL_GetError());
        SDL_Quit();
        return 1;
    }

   SDL_Init(SDL_INIT_VIDEO);
   if(Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, MIX_DEFAULT_CHANNELS, 1024) == -1)
   {
      printf("%s", Mix_GetError());
   }
   Mix_VolumeMusic(MIX_MAX_VOLUME / 2);
   Mix_Music *musique;
   musique = Mix_LoadMUS("files/b.mp3");
   Mix_PlayMusic(musique, -1);
    
    if(load_tiles())
        return 1;
    
    if(load_sprites())
        return 1;
    
    return 0;
}

static void menu(void(*callback_menu)(void*)) {
    for(;;) {
        callback_menu(&sdl_driver);
    }
}

static int continuer=1;
static void start(void(*callback)(void*)) {
#ifdef __EMSCRIPTEN__
    emscripten_set_main_loop_arg(callback, &sdl_driver, FPS, 0);
#else
    for(;;) {
        callback(&sdl_driver);
        usleep(175000);
    }
#endif
}

//fonction faite par Mustapha Ilyès DAHMANI:
static int touche_bouton(void){
    SDL_PumpEvents();
    const Uint8 * state = SDL_GetKeyboardState(NULL);
        if (state[SDL_SCANCODE_P]){
            SDL_DestroyWindow(win);
            SDL_Quit();
            exit(1);
        }
        if (state[SDL_SCANCODE_SPACE])
            return 1;        
    return Nothing;
}

static int get_move(void) {
    SDL_PumpEvents();
    const Uint8 * state = SDL_GetKeyboardState(NULL);
        if (state[SDL_SCANCODE_P]){
            SDL_DestroyWindow(win);
            SDL_Quit();
            exit(1);
        }
        if (state[SDL_SCANCODE_W])
            return Up;
        if (state[SDL_SCANCODE_A])
            return Left;
        if (state[SDL_SCANCODE_S])
            return Down;
        if (state[SDL_SCANCODE_D])
            return Right;
        
    
    return Nothing;
}

static void draw_bg(void) {
    SDL_RenderClear(ren);
    int y, x;
    SDL_Rect dst = {.x = 0, .y = 0, .w = SZ, .h = SZ };
   
    for(y = 0; y < GAME->h; ++y) {
        for(x = 0; x < GAME->w; ++x) {
            dst.x = x * SZ;
            dst.y = y * SZ;
            int typecell = GAME->background[y * GAME->w + x];
            SDL_RenderCopy(ren, tiles[typecell], NULL, &dst);
        }
    }
}

//fonction faite par Mustapha Ilyès DAHMANI:
static void draw_bg_menu(void) {
    SDL_RenderClear(ren);
    int y, x;
    SDL_Rect dst = {.x = 0, .y = 0, .w = SZ, .h = SZ };
   
    for(y = 0; y < GAME->h; ++y) {
        for(x = 0; x < GAME->w; ++x) {
            dst.x = x * SZ;
            dst.y = y * SZ;
            int typecell = GAME->background[y * GAME->w + x];
            SDL_RenderCopy(ren, tiles[typecell], NULL, &dst);
        }
    }
}

int static deja_fait=0;
static void draw_bg_music(void) {
   SDL_Surface *ecran = NULL;
   if(deja_fait==0){
   SDL_Window* win = SDL_CreateWindow("L'équipe blanche a gagné", 0, 0, 900, 600,SDL_WINDOW_SHOWN);
   deja_fait=1;
   }
 
   SDL_Event event;
}

static int sp = 0;

//fonction faite par Pierre MARGALE:
static void draw_entity(int ent_id) {
    
    
    if(ent_id == 0){
    	set[0].x = 0, set[0].y = 0, set[0].w = SZ, set[0].h = SZ;
 	    set[1].x = SZ * GAME->entity[ent_id].x, set[1].y = SZ * GAME->entity[ent_id].y, set[1].w = SZ, set[1].h = SZ;
	    set[0].x = sp * 32;
        SDL_RenderCopy(ren, sprites[ent_id], &set[0], &set[1]);
    }
    else{
	    set[ent_id+1].x = 0, set[ent_id+1].y = 0, set[ent_id+1].w = 150, set[ent_id+1].h = SZ; 
	    set[ent_id+2].x = SZ * GAME->entity[ent_id].x, set[ent_id+2].y = SZ * GAME->entity[ent_id].y , set[ent_id+2].w = 150, set[ent_id+2].h = SZ;
        
        SDL_RenderCopy(ren, sprites[ent_id], &set[ent_id+1], &set[ent_id+2]);
    }
    sp = (sp + 1) %3;
}

static void update(void) {
    SDL_RenderPresent(ren);
}
