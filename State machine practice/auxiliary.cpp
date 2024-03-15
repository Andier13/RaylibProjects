#include "auxiliary.h"

float dt() {
    //return (!paused ? GetFrameTime() : 0);
    float result = GetFrameTime();
    float targetFPS = 60;
    return (result == 0 ? 1.f/ targetFPS : result);
}

/*float remainder(float x, float y) {
    return x - floor(x / y) * y;
}*/

float map(float value, float istart, float istop, float ostart, float ostop) {
    return ostart + (ostop - ostart) * ((value - istart) / (istop - istart));
}

void DrawLineExRound(Vector2 startPos, Vector2 endPos, float thick, Color color) {
    DrawLineEx(startPos, endPos, thick, color);
    DrawCircleV(startPos, thick / 2, color);
    DrawCircleV(endPos, thick / 2, color);
}

uint64_t timeSinceEpochMillisec() {
    using namespace std::chrono;
    return duration_cast<milliseconds>(system_clock::now().time_since_epoch()).count();
}

std::default_random_engine generator((unsigned)timeSinceEpochMillisec());
float random(float min, float max) {
    
    std::uniform_real_distribution<float> distribution(min, max);
    return distribution(generator);
}

float random(float max) {
    return random(0.0f, max);
}

bool probability(float chance) {
    return random(1) < chance;
}

bool probability_percent(float chance) {
    return random(1) < chance / 100;
}

Vector2 GetMouseV() {
    return { (float)GetMouseX(), (float)GetMouseY() };
}

Vector2 fromAngle(float angle) {
    return { cos(angle), sin(angle) };
}

Vector2 RandomVector2() {
    const float angle = random(2 * PI);
    return { cos(angle), sin(angle) };
}

Vector2 operator*(Vector2 v, float n) {
    return { v.x * n, v.y * n };
}

Vector2 operator*(Vector2 v1, Vector2 v2)
{
    return { v1.x * v2.x, v1.y * v2.y };
}

Vector2 operator*(float n, Vector2 v)
{
    return { v.x * n, v.y * n };
}

Vector2 operator/(Vector2 v, float n)
{
    return { v.x / n, v.y / n };
}

Vector2 operator+(Vector2 v1, Vector2 v2) {
    return { v1.x + v2.x, v1.y + v2.y };
}

Vector2 operator-(Vector2 v1, Vector2 v2) {
    return { v1.x - v2.x, v1.y - v2.y };
}

bool operator==(Vector2 v1, Vector2 v2)
{
    return v1.x == v2.x && v1.y == v2.y;
}

bool operator!=(Vector2 v1, Vector2 v2)
{
    return !(v1 == v2);
}

float dot(Vector2 v1, Vector2 v2) {
    return v1.x * v2.x + v1.y * v2.y;
}

float cross(Vector2 v1, Vector2 v2) {
    return v1.x * v2.y - v2.x * v1.y;
}

int orientare(Vector2 p0, Vector2 p1, Vector2 p2) {
    float val = cross(p1 - p0, p2 - p0);
    if (val > 0) //primul este in dreapta celui de-al doilea
        return 1;
    if (val < 0) //primul este in stanga celui de-al doilea
        return -1;
    return 0;
}

float mag(Vector2 v) {
    return sqrt(v.x * v.x + v.y * v.y);
}

float magSq(Vector2 v) {
    return v.x * v.x + v.y * v.y;
}

float direction(Vector2 v)
{
    return atan2f(v.y, v.x);
}

Vector2 norm(Vector2 v) {
    if (magSq(v) == 0)
        return v;
    float len = 1.0f / mag(v);
    return { v.x * len, v.y * len };
}

Vector2 fromTo(Vector2 a, Vector2 b)
{
    return b-a;
}

Vector2 Rotate(Vector2 v, float angle)
{
    return mag(v) * fromAngle(direction(v) + angle);
}

Rectangle rect(Vector2 pos, Vector2 dim) {
    return { pos.x, pos.y, dim.x, dim.y };
}

Rectangle rectFromCenter(Vector2 center, Vector2 dim)
{
    return { center.x - dim.x/2, center.y-dim.y/2, dim.x, dim.y };
}

Rectangle rectFromCenter(float centerx, float centery, float dimx, float dimy)
{
    return { centerx - dimx / 2, centery - dimy / 2, dimx, dimy };
}

Rectangle computerCoordsToMathCoords(Rectangle b)
{
    return {b.x, HEIGHT - b.y - b.height, b.width, b.height};
}

float area(Rectangle b) {
    return b.width * b.height;
}

float left(Rectangle b) {
    return b.x;
}

float right(Rectangle b) {
    return b.x + b.width;
}

float top(Rectangle b) {
    return b.y;
}

float bottom(Rectangle b) {
    return b.y + b.height;
}

float centerX(Rectangle b) {
    return b.x + b.width / 2;
}

float centerY(Rectangle b) {
    return b.y + b.height / 2;
}

Vector2 center(Rectangle b)
{
    return { centerX(b), centerY(b) };
}

bool isInsideRect(Vector2 v, Rectangle b) {
    return v.x >= left(b) && v.x <= right(b) &&
        v.y >= top(b) && v.y <= bottom(b);
}

bool isInsideCircle(Vector2 v, Vector2 pos, float r) {
    return magSq(v - pos) <= r * r;
}

bool isInsideCircle(Vector2 v, Circle c)
{
    Vector2 pos = { c.x, c.y };
    float r = c.r;
    return magSq(v - pos) <= r * r;
}

bool CheckCollisionCircles(Circle c1, Circle c2)
{
    return CheckCollisionCircles({ c1.x, c1.y }, c1.r, { c2.x, c2.y }, c2.r);
}

float lerp(float x, float y, float t) {

    return (1 - t) * x + t * y;
}

Vector2 lerp(Vector2 v1, Vector2 v2, float t) {
    return { lerp(v1.x, v2.x, t), lerp(v1.y, v2.y, t) };
}

float clamp(float value, float min, float max)
{
    if (value < min)
        return min;
    if (value > max)
        return max;
    return value;
}

float closestModValue(float value, float target, float mod)
{
    if (mod == 0)
        return target;
    float cx = target; //target
    cx = remainderf(cx, mod);
    float cy = value; //current
    cy = remainderf(cy, mod);
    cy = value - cy;
    float x1 = cy - TWO_PI + cx;
    float x2 = cy + cx;
    float x3 = cy + TWO_PI + cx;
    float dx1 = abs(x1 - value);
    float dx2 = abs(x2 - value);
    float dx3 = abs(x3 - value);
    float minx = (dx1 < dx2 ? x1 : x2);
    float mindx = (dx1 < dx2 ? dx1 : dx2);
    minx = (mindx < dx3 ? minx : x3);
    return minx;
}

void float_to_str(char s[], float x, unsigned digit, unsigned decimal) {
    char format[] = "%0.0f";
    format[1] += digit;
    format[3] += decimal;
    strcpy_s(s, 32, TextFormat(format, x));
}

/*template <class T>
void swap(T& a, T& b) {
    T aux = a;
    a = b;
    b = aux;
}*/

ColorHSB::operator Color()
{
   // return ColorFromHSV(h, s, b);
    Color HSB = { h, s, b, a };
    Color rgb = { 0, 0, 0, 0 };
    unsigned char region, p, q, t;
    unsigned int h, s, v, remainder;
    rgb.a = HSB.a;

    if (HSB.g == 0)
    {
        rgb.r = HSB.g;
        rgb.g = HSB.g;
        rgb.b = HSB.g;
        return rgb;
    }

    // converting to 16 bit to prevent overflow
    h = HSB.r;
    s = HSB.g;
    v = HSB.b;

    region = h / 43;
    remainder = (h - (region * 43)) * 6;

    p = (v * (255 - s)) >> 8;
    q = (v * (255 - ((s * remainder) >> 8))) >> 8;
    t = (v * (255 - ((s * (255 - remainder)) >> 8))) >> 8;

    switch (region)
    {
    case 0:
        rgb.r = v;
        rgb.g = t;
        rgb.b = p;
        break;
    case 1:
        rgb.r = q;
        rgb.g = v;
        rgb.b = p;
        break;
    case 2:
        rgb.r = p;
        rgb.g = v;
        rgb.b = t;
        break;
    case 3:
        rgb.r = p;
        rgb.g = q;
        rgb.b = v;
        break;
    case 4:
        rgb.r = t;
        rgb.g = p;
        rgb.b = v;
        break;
    default:
        rgb.r = v;
        rgb.g = p;
        rgb.b = q;
        break;
    }

    return rgb;
}

Circle::Circle() : x(0), y(0), r(0)
{
}

Circle::Circle(Vector2 center, float radius) :
    x(center.x), y(center.y), r(radius)
{
}

Circle::operator Rectangle()
{
    return { x - r, y - r, 2*r, 2*r };
}

Rectangle RectangleFrom(Alignment xAlign, Alignment yAlign, Vector2 origin, Vector2 dimensions)
{
    Rectangle res = {0, 0, dimensions.x, dimensions.y};

    switch (xAlign)
    {
    case Alignment::LEFT:
        res.x = origin.x;
        break;
    case Alignment::CENTER:
        res.x = origin.x - dimensions.x * 0.5f;
        break;
    case Alignment::RIGHT:
        res.x = origin.x - dimensions.x;
        break;
    default:
        break;
    }

    switch (yAlign)
    {
    case Alignment::TOP:
        res.y = origin.y;
        break;
    case Alignment::CENTER:
        res.y = origin.y - dimensions.y * 0.5f;
        break;
    case Alignment::BOTTOM:
        res.y = origin.y - dimensions.y;
        break;
    default:
        break;
    }

    return res;
}

void DrawTextFrom(Font font, const char* text, Alignment xAlign, Alignment yAlign, Vector2 origin, float fontSize, float spacing, Color tint)
{
    Vector2 dim = MeasureTextEx(font, text, fontSize, spacing);
    Rectangle box = RectangleFrom(xAlign, yAlign, origin, dim);
    DrawTextEx(font, text, { box.x, box.y }, fontSize, spacing, tint);
}

Vector2 GetRectangleAlignmentPoint(Rectangle box, Alignment xAlign, Alignment yAlign)
{
    Vector2 res = {};
    switch (xAlign)
    {
    case Alignment::LEFT:
        res.x = box.x;
        break;
    case Alignment::CENTER:
        res.x = box.x + box.width * 0.5f;
        break;
    case Alignment::RIGHT:
        res.x = box.x + box.width;
        break;
    default:
        break;
    }

    switch (yAlign)
    {
    case Alignment::TOP:
        res.y = box.y;
        break;
    case Alignment::CENTER:
        res.y = box.y + box.height * 0.5f;
        break;
    case Alignment::BOTTOM:
        res.y = box.y + box.height;
        break;
    default:
        break;
    }

    return res;
}
