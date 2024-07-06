#include "player.h"
#include "debug.h"
#include "raylib.h"
#include "raymath.h"

#define PLAYER_SPEED 250

void PlayerUpdate(Player *player)
{
    float frameTime = GetFrameTime();

    int xIn = (int)IsKeyDown(KEY_RIGHT) - (int)IsKeyDown(KEY_LEFT);
    player->rotation += (xIn * PLAYER_ROT_SPEED * frameTime);

    int yIn = (int)IsKeyDown(KEY_UP) - (int)IsKeyDown(KEY_DOWN);
    if (yIn > 0)
    {
        Vector2 facingDirection =
            Vector2Rotate((Vector2){0, 1}, player->rotation);
        player->velocity = Vector2Add(
            player->velocity,
            Vector2Scale(facingDirection, PLAYER_ACCELERATION * frameTime));
        float mag = Vector2Length(player->velocity);
        if (mag > PLAYER_SPEED)
        {
            player->velocity = Vector2Scale(player->velocity, PLAYER_SPEED / mag);
        }
    }

    player->position =
        Vector2Add(player->position, Vector2Scale(player->velocity, frameTime));

    SetPlayerInfo(player->position, player->velocity, player->rotation);
}

void PlayerDraw(Player player)
{
    DrawPoly(player.position, 3, 32, player.rotation, RAYWHITE);
}