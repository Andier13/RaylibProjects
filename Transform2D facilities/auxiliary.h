#pragma once

#include "raylib.h"
#include <iostream>
#include <fstream>
#include <cmath>
#include <cstring>
#include <ctime>
#include <cstdio>
#include <random>
#include <string>
#include <vector>
#include <chrono>

#define WIDTH  (float)GetScreenWidth()
#define HEIGHT (float)GetScreenHeight()

const float HALF_PI = PI / 2;
const float TWO_PI = 2 * PI;

typedef struct Circle {
    float x, y, r;

    Circle();
    Circle(Vector2 center, float radius);
    operator Rectangle();
} Circle;

//int paused = 0;

float dt();
//float remainder(float x, float y);
float map(float value, float istart, float istop, float ostart, float ostop);
void DrawLineExRound(Vector2 startPos, Vector2 endPos, float thick, Color color);
template <class T>
//unsigned len(T v[]) {
//    return sizeof(v) / sizeof(v[0]);
//}
uint64_t timeSinceEpochMillisec();
float random(float min, float max);
float random(float max);
bool probability(float chance);
bool probability_percent(float chance);
Vector2 GetMouseV();
Vector2 fromAngle(float angle);
Vector2 RandomVector2();
Vector2 operator*(Vector2 v, float n);
Vector2 operator*(Vector2 v1, Vector2 v2);
Vector2 operator*(float n, Vector2 v);
Vector2 operator/(Vector2 v, float n);
Vector2 operator+(Vector2 v1, Vector2 v2);
Vector2 operator-(Vector2 v1, Vector2 v2);
bool operator==(Vector2 v1, Vector2 v2);
bool operator!=(Vector2 v1, Vector2 v2);
float dot(Vector2 v1, Vector2 v2);
float cross(Vector2 v1, Vector2 v2);
int orientare(Vector2 p0, Vector2 p1, Vector2 p2); //p0 = origin of both vectors, p1 and p2 are the two endpoints
float mag(Vector2 v);
float magSq(Vector2 v);
float direction(Vector2 v);
Vector2 norm(Vector2 v);
Vector2 fromTo(Vector2 a, Vector2 b);
Vector2 Rotate(Vector2 v, float angle);
Rectangle rect(Vector2 pos, Vector2 dim);
Rectangle rectFromCenter(Vector2 center, Vector2 dim);
Rectangle rectFromCenter(float centerx, float centery, float dimx, float dimy);
Rectangle computerCoordsToMathCoords(Rectangle b);
float area(Rectangle b);
float left(Rectangle b);
float right(Rectangle b);
float top(Rectangle b);
float bottom(Rectangle b);
float centerX(Rectangle b);
float centerY(Rectangle b);
Vector2 center(Rectangle b);
bool isInsideRect(Vector2 v, Rectangle b);
bool isInsideCircle(Vector2 v, Vector2 pos, float r);
bool isInsideCircle(Vector2 v, Circle c);
bool CheckCollisionCircles(Circle c1, Circle c2);
float lerp(float x, float y, float t);
Vector2 lerp(Vector2 v1, Vector2 v2, float t);
float clamp(float value, float min, float max);
//finds closest target to the value in mod space
float closestModValue(float value, float target, float mod);
void float_to_str(char s[], float x, unsigned digit, unsigned decimal);

typedef struct ColorHSB {
    unsigned char h;        // Color hue value
    unsigned char s;        // Color saturation value
    unsigned char b;        // Color brightness value (or v - value) 
    unsigned char a;        // Color alpha value (or transparency/opaqueness)

    operator Color();
} ColorHSB;

/*template<class T>
inline void DeleteAll(std::vector<T*> v, bool(*filter)(T*))
{
    for (int i = v.size() - 1; i >= 0; i--)
        if (filter(v[i]))
        {
            delete v[i];
            for (int j = i + 1; j < v.size(); j++)
                v[j - 1] = v[j];
            v.pop_back();
        }
}*/

enum Alignment
{
    LEFT,
    CENTER,
    RIGHT,
    TOP,
    BOTTOM
};

Rectangle RectangleFrom(Alignment xAlign, Alignment yAlign, Vector2 origin, Vector2 dimensions);
void DrawTextFrom(Font font, const char* text, Alignment xAlign, Alignment yAlign, Vector2 origin, float fontSize, float spacing, Color tint);
Vector2 GetRectangleAlignmentPoint(Rectangle box, Alignment xAlign, Alignment yAlign);
