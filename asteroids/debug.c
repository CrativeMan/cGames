#include "debug.h"
#include "raymath.h"
#include "constants.h"

static bool _showAngleCone = true;
static bool _showAsteroidCount = true;
static bool _showPlayerInformation = true;
static Vector2 line0[2] = {0};
static Vector2 line1[2] = {0};

static Vector2 _playerPosition = {0};
static Vector2 _playerVelocity = {0};
static float _playerRotation = 180;

void ShowDebugVisualisations(int aseroidcount)
{
    if (_showAngleCone)
    {
        DrawLineV(line0[0], line0[1], RED);
        DrawLineV(line1[0], line1[1], BLUE);
    }

    if (_showAsteroidCount)
    {
        DrawRectangle(10, 10, 100, 30, Fade(BLACK, 0.6f));
        DrawText(TextFormat("ASTEROIDS: %d", aseroidcount), 20, 20, 20, WHITE);
    }
}

void SetLastCone(Vector2 position, Vector2 velocity)
{
    line0[0] = position;

    line0[1] = Vector2Add(position, Vector2Rotate(Vector2Scale(velocity, 10),
                                                  -ASTEROID_RANDOM_ANGLE));

    line1[0] = position;
    line1[1] = Vector2Add(position, Vector2Rotate(Vector2Scale(velocity, 10),
                                                  ASTEROID_RANDOM_ANGLE));
}

void SetPlayerInfo(Vector2 position, Vector2 velocity, float rotation)
{
    _playerPosition = position;
    _playerVelocity = velocity;
    _playerRotation = rotation;
}