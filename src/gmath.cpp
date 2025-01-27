#include <cmath>

#include <raylib.h> // version 5.5
#include "gmath.h"

Vector2 NormalizeVector2(Vector2* v)
{
    float magnitude = sqrtf(v->x * v->x + v->y * v->y);
    if (magnitude != 0) {
        v->x /= magnitude; // Normalize x-component
        v->y /= magnitude; // Normalize y-componentf
    }
    return *v;
}
