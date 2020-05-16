typedef struct Driver Driver;

struct Driver {
    const Game* game;
    int (*init)(const Game* game);
    void (*menu)(void(*callback_menu)(void*));
    void (*start)(void(*callback)(void*));
    int (*touche_bouton)(void);
    int (*get_move)(void);
    void (*draw_bg)(void);
    void (*draw_bg_menu)(void);
    void (*draw_bg_music)(void);
    void (*draw_entity)(int ent_id);
    void (*update)(void);
};
