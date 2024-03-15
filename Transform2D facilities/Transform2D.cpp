#include "Transform2D.h"

Vector2 Transform2D::GetGlobalPostion()
{
    //Vector2 scaled = position * scale;
    //return origin + Rotate(scaled, rotation);
    return *this * position;
}

float Transform2D::GetScaledRotation()
{
    return direction(fromAngle(rotation) * scale);
}

Transform2D operator*(Transform2D t1, Transform2D t2)
{
    Transform2D result = {};
    //result.origin = t2.GetGlobalPostion();
    result.origin = t2 * t2.position;
    result.scale = t1.scale * t2.scale;
    result.rotation = t1.rotation + t2.rotation;
    result.position = t1.position;
    return result;
}

Vector2 operator*(Transform2D t, Vector2 v)
{
    return t.origin + Rotate(v, t.rotation) * t.scale;
}
