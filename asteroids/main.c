#include <stdlib.h>
#include <time.h>

#include "raylib.h"

#include "constants.h"
#include "debug.h"
#include "game_asteroids.h"
#include "player.h"

static Player _player;

void UpdateDrawFrame(void);

int main()
{
    srand(time(0));

    InitWindow(SCREEN_WIDTH, SCREEN_HEIGHT, "Asteroids");

    _player =
        (Player){.position = SCREEN_CENTER, .rotation = 180, .velocity = {0}};

    while (!WindowShouldClose())
    {
        UpdateDrawFrame();
    }

    CloseWindow();
    return 0;
}

void UpdateDrawFrame(void)
{

    int activeAsteroids = UpdateAsteroids();
    PlayerUpdate(&_player);

    BeginDrawing();

    ClearBackground(NEARBLACK);

    DrawAsteroids();
    PlayerDraw(_player);
    ShowDebugVisualisations(activeAsteroids);

    EndDrawing();
}
