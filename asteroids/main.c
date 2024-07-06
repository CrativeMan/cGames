#include <stdlib.h>
#include <time.h>

#include "asteroid.h"
#include "raylib.h"
#include "raymath.h"

const int screenWidth = 600;
const int screenHeight = 600;
const Vector2 screenCenter = {screenWidth / 2, screenHeight / 2};
#define NEARBLACK                                                              \
    CLITERAL(Color)                                                            \
    {                                                                          \
        15, 15, 15, 255                                                        \
    }

#define MAX_ASTEROIDS 64
#define ASTEROID_RANDOM_ANGLE 30 * DEG2RAD
#define ASTEROID_DELAY 0.25f

static AsteroidSize _sizes[] = {ASTEROID_SMALL, ASTEROID_MEDIUM,
                                ASTEROID_LARGE};
static Asteroid _asteroids[MAX_ASTEROIDS] = {0};
static float _lastAsteroidCreationTime = -1.0f;

// DEBUG
bool _showAngleCone = true;
bool _showAsteroidCount = true;
Vector2 line0[2];
Vector2 line1[2];
//

void UpdateDrawFrame(void);
void AddAsteroid(Vector2 position, AsteroidSize size);
Vector2 GetNextAsteroidPosition(void);

int main()
{
    srand(time(0));

    InitWindow(screenWidth, screenHeight, "Asteroids");

    while (!WindowShouldClose())
    {
        UpdateDrawFrame();
    }

    CloseWindow();
    return 0;
}

void UpdateDrawFrame(void)
{
    float frametime = GetFrameTime();
    float time = GetTime();

    for (int i = 0; i < MAX_ASTEROIDS; i++)
    {
        AsteroidUpdate(_asteroids + i, frametime, time);
    }

    if (GetTime() > _lastAsteroidCreationTime + ASTEROID_DELAY)
    {
        AsteroidSize nextSize = _sizes[GetRandomValue(0, 3)];
        AddAsteroid(GetNextAsteroidPosition(), nextSize);
        _lastAsteroidCreationTime = time;
    }

    BeginDrawing();

    ClearBackground(NEARBLACK);
    for (int i = 0; i < MAX_ASTEROIDS; i++)
    {
        AsteroidDraw(_asteroids[i]);
    }

    if (_showAngleCone)
    {
        DrawLineV(line0[0], line0[1], RED);
        DrawLineV(line1[0], line1[1], BLUE);
    }

    if (_showAsteroidCount)
    {
        int count = 0;
        for (int i = 0; i < MAX_ASTEROIDS; i++) {
            if (_asteroids[i].active)
            {
                count++;
            }
        }

        DrawRectangle(10, 10, 100, 30, Fade(BLACK, 0.6f));
        DrawText(TextFormat("ASTEROIDS: %d", count), 20, 20, 20, WHITE);
    }
    
    EndDrawing();
}

void AddAsteroid(Vector2 position, AsteroidSize size)
{
    bool created = false;
    Vector2 velocity = Vector2Subtract(screenCenter, position);
    velocity =
        Vector2Scale(Vector2Normalize(velocity),
                     GetRandomValue(ASTEROID_SPEED_MIN, ASTEROID_SPEED_MAX));

    if (_showAngleCone)
    {
        line0[0] = position;
        line1[0] = position;

        line0[1] =
            Vector2Add(position, Vector2Rotate(Vector2Scale(velocity, 10),
                                               -ASTEROID_RANDOM_ANGLE));
        line1[1] =
            Vector2Add(position, Vector2Rotate(Vector2Scale(velocity, 10),
                                               ASTEROID_RANDOM_ANGLE));
    }

    velocity = Vector2Rotate(
        velocity,
        (float)(GetRandomValue(-ASTEROID_RANDOM_ANGLE, ASTEROID_RANDOM_ANGLE)));

    for (int i = 0; i < MAX_ASTEROIDS; i++)
    {
        if (_asteroids[i].active)
        {
            continue;
        }

        _asteroids[i] = CreateAsteroid(position, velocity, size);
        created = true;
        break;
    }

    if (!created)
    {
        TraceLog(LOG_ERROR, "Failed to create an Asteroid because there was no "
                            "inactive spots in the array!");
    }
}

Vector2 GetNextAsteroidPosition(void)
{
    int padding = 128;
    Vector2 result = {-128, -128};

    if (GetRandomValue(0, 1))
    {
        if (GetRandomValue(0, 1))
        {
            result.y = screenWidth + padding;
        }
        result.x = GetRandomValue(-padding, screenWidth + padding);
    }
    else
    {
        if (GetRandomValue(0, 1))
        {
            result.x = screenHeight + padding;
        }
        result.y = GetRandomValue(-padding, screenWidth + padding);
    }

    return result;
}