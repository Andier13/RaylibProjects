#version 400

//#extension GL_ARB_gpu_shader_fp64 : enable

// Input vertex attributes (from vertex shader)
in vec2 fragTexCoord;
in vec4 fragColor;

// Output fragment color
out vec4 finalColor;

uniform vec2 screen_dim;
uniform vec2 origin;
uniform float scale;
//uniform float time;


// Convert Hue Saturation Value (HSV) color into RGB
vec3 Hsv2rgb(vec3 c)
{
    vec4 K = vec4(1.0, 2.0 / 3.0, 1.0 / 3.0, 3.0);
    vec3 p = abs(fract(c.xxx + K.xyz) * 6.0 - K.www);
    return c.z * mix(K.xxx, clamp(p - K.xxx, 0.0, 1.0), c.y);
}

float dist(vec2 a, vec2 b){
    return sqrt((b.x-a.x)*(b.x-a.x) + (b.y-a.y)*(b.y-a.y));
}

float map(float value, float istart, float istop, float ostart, float ostop) {
    return ostart + (ostop - ostart) * ((value - istart) / (istop - istart));
}

void main()
{
    vec2 uv = fragTexCoord;
    float ratio = screen_dim.x/screen_dim.y;

    vec2 uvo;
    uvo.x = map(origin.x, 0, screen_dim.x, 0, 1);
    uvo.y = map(origin.y, 0, screen_dim.y, 0, 1);

    uvo.y = map(uvo.y, 1, 0, -2, 2);
    uvo.x = map(uvo.x, 0, 1, -2*ratio, 2*ratio);

    uv.y = map(uv.y, 1, 0, -scale, scale);
    uv.x = map(uv.x, 0, 1, -scale*ratio, scale*ratio);

    uv -= uvo;
    ;
    vec2 c = uv;
    vec2 z = vec2(0, 0);             
    vec2 z2 = vec2(0, 0);
    int iteration;
    int maxIteration = 1000;
    float maxValue = 3;
    for (iteration = 0; iteration < maxIteration && z2.x + z2.y < maxValue * maxValue; iteration++)
    {
            z.y = 2 * z.x * z.y + c.y;
            z.x = z2.x - z2.y + c.x;
            z2.x = z.x * z.x;
            z2.y = z.y * z.y;
    }
              
        
    if (iteration==maxIteration)
        finalColor = vec4(vec3(1, 0, 0), 1);
    else
    {
        float t = map(iteration, 0, 50, 0, 1);

        vec3 start = vec3(0, 0, 0);
        vec3 finish = vec3(1, 1, 1);
        vec3 col = start*(1-t) + finish*t;
        finalColor = vec4(col, 1);
    }
}