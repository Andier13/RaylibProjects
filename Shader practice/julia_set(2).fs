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
uniform int maxIteration;
//uniform double time;

double map(double value, double istart, double istop, double ostart, double ostop) {
    return ostart + (ostop - ostart) * ((value - istart) / (istop - istart));
}

vec3 Hsv2rgb(vec3 c)
{
    vec4 K = vec4(1.0, 2.0 / 3.0, 1.0 / 3.0, 3.0);
    vec3 p = abs(fract(c.xxx + K.xyz) * 6.0 - K.www);
    return c.z * mix(K.xxx, clamp(p - K.xxx, 0.0, 1.0), c.y);
}

void main()
{
    dvec2 uv = fragTexCoord;
    double ratio = screen_dim.x/screen_dim.y;

    dvec2 uvo;
    uvo.x = map(origin.x, 0, screen_dim.x, 0, 1);
    uvo.y = map(origin.y, 0, screen_dim.y, 0, 1);

    uvo.y = map(uvo.y, 1, 0, -2, 2);
    uvo.x = map(uvo.x, 0, 1, -2*ratio, 2*ratio);

    uv.y = map(uv.y, 1, 0, -scale, scale);
    uv.x = map(uv.x, 0, 1, -scale*ratio, scale*ratio);

    uv -= uvo;
    ;
    dvec2 c = uv;
    dvec2 z = dvec2(0, 0);             
    dvec2 z2 = dvec2(0, 0);
    int iteration;
    //int maxIteration = 200;
    double maxValue = 3;
    for (iteration = 0; iteration < maxIteration && z2.x + z2.y < maxValue * maxValue; iteration++)
    {
            z.y = 2 * z.x * z.y + c.y;
            z.x = z2.x - z2.y + c.x;
            z2.x = z.x * z.x;
            z2.y = z.y * z.y;
    }
              
        
    if (iteration==maxIteration)
        finalColor = vec4(vec3(0, 0, 0), 1);
    else
    {
        float t = float(map(iteration, 0, 50, 0, 1));

        vec3 start = vec3(0, 0, 0);
        vec3 finish = vec3(1, 1, 1);
        //vec3 col = start*(1-t) + finish*t;
        vec3 col = Hsv2rgb(vec3(t+0.1, 1, 1));
        finalColor = vec4(col, 1);
    }
}