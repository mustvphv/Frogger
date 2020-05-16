typedef struct Game Game;
typedef struct Driver Driver;
typedef struct Entity Entity;

struct Entity {
    int x;
    int y;
    int id;
    int dir;
};

struct Game {
    int h;
    int w;
    unsigned char* background;
    Entity* entity;
};


enum {
    Noir,
    Violet,
    Cars,
    Camion,
    Water,
    Gazon,
    Serpent,
    Finbois,
    Finbois2,
    Transparent,
    Barre2Progression,
    FrogGagnant1Petit,
    FrogGagnant2Petit,
    FrogGagnant3Petit,
    FrogGagnant4Petit,
    FrogGagnant1Grand,
    FrogGagnant2Grand,
    FrogGagnant3Grand,
    FrogGagnant4Grand,
    FrogGagnant5Grand,
    FrogGagnant6Grand,
    H,
    I,
    G,
    S,
    C,
    O,
    R,
    E,
    DeuxPoints,
    Zero,
    Un,
    Deux,
    Trois,
    Quatre,
    Cinq,
    Six,
    Sept,
    Huit,
    Neuf,
    Fleur,
    Croco,
    Tortue,
    Tortue2,
    N,
    Iniveau,
    V,
    Eniveau,
    A,
    U,
    J,
    Z,
    F,
    P,
    Y,
    Tortuesouseau,
    Tortue3,
    NCell
};

enum {
    Frog,
    Car,
    NSprite
};

enum {
    Nothing, Left, Right, Up, Down
};

void init_game(const Driver*);


