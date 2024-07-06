#ifndef DEBUG_H_
#define DEBUG_H_

#include "raylib.h"

/// @brief Call from within a BeginDrawing2D!
void ShowDebugVisualisations(int aseroidcount);

void SetLastCone(Vector2 position, Vector2 velocity);

void SetPlayerInfo(Vector2 position, Vector2 velocity, float rotation);

#endif