#include "game_asteroids.h"
#include "raymath.h"

#include "constants.h"
#include "debug.h"

static AsteroidSize _sizes[] = {ASTEROID_SMALL, ASTEROID_MEDIUM,
                                ASTEROID_LARGE};
static Asteroid _asteroids[MAX_ASTEROIDS] = {0};
static float _lastAsteroidCreationTime = -1.0f;

void AddAsteroid(Vector2 position, AsteroidSize size)
{
    bool created = false;

    Vector2 velocity = Vector2Subtract(SCREEN_CENTER, position);
    velocity =
        Vector2Scale(Vector2Normalize(velocity),
                     GetRandomValue(ASTEROID_SPEED_MIN, ASTEROID_SPEED_MAX));

    SetLastCone(position, velocity);

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
    Vector2 result = {-padding, -padding};

    if (GetRandomValue(0, 1))
    {
        if (GetRandomValue(0, 1))
        {
            result.y = SCREEN_HEIGHT + padding;
        }
        result.x = GetRandomValue(-padding, SCREEN_WIDTH + padding);
    }
    else
    {
        if (GetRandomValue(0, 1))
        {
            result.x = SCREEN_WIDTH + padding;
        }
        result.y = GetRandomValue(-padding, SCREEN_HEIGHT + padding);
    }

    return result;
}

int UpdateAsteroids()
{
    int activeAsteroids = 0;

    float frametime = GetFrameTime();
    float time = GetTime();

    for (int i = 0; i < MAX_ASTEROIDS; i++)
    {
        if (AsteroidUpdate(_asteroids + i, frametime, time))
        {
            activeAsteroids++;
        }
    }

    if (time > _lastAsteroidCreationTime + ASTEROID_DELAY)
    {
        AsteroidSize nextSize = _sizes[GetRandomValue(0, 3)];
        AddAsteroid(GetNextAsteroidPosition(), nextSize);
        _lastAsteroidCreationTime = time;
    }

    return activeAsteroids;
}

void DrawAsteroids()
{
    for (int i = 0; i < MAX_ASTEROIDS; i++)
    {
        AsteroidDraw(_asteroids[i]);
    }
}