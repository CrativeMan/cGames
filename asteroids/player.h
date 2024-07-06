#ifndef PLAYER_H_
#define PLAYER_H_

#include "raylib.h"

#define PLAYER_ROT_SPEED 360
#define PLAYER_ACCELERATION 200

typedef struct Player
{
    Vector2 position;
    Vector2 velocity;
    float rotation;
} Player;

void PlayerUpdate(Player *player);
void PlayerDraw(Player player);

#endif