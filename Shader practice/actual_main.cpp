#include "actual_main.h"

//#if defined(PLATFORM_DESKTOP)
//#define GLSL_VERSION            330
//#else   // PLATFORM_RPI, PLATFORM_ANDROID, PLATFORM_WEB
//#define GLSL_VERSION            100
//#endif

Shader shader;
RenderTexture2D target;
Vector2 origin, startPress, prevOrigin;
float scale = 2;
int maxIteration = 200;

template <class T>
void setShaderValue(Shader shader, int type, const char* name, const T& value) {
	// type name syntax UNIFORM_SHADER_<TYPE>
	SetShaderValue(shader, GetShaderLocation(shader, name), &value, type);
}

void setup()
{
	InitWindow(1200, 900, "Title");
	SetTargetFPS(60);

	//shader = LoadShader("vertex.vs", "julia_set(2).fs");
	shader = LoadShader(nullptr, "julia_set(2).fs");
	target = LoadRenderTexture(WIDTH, HEIGHT);

	Vector2 screen = {WIDTH, HEIGHT};
	setShaderValue(shader, SHADER_UNIFORM_VEC2, "screen_dim", screen);
	setShaderValue(shader, SHADER_UNIFORM_FLOAT, "scale", scale);

	origin = { WIDTH / 2, HEIGHT / 2 };
}

void update()
{
	//setShaderValue(shader, SHADER_UNIFORM_FLOAT, "time", (float)GetTime());

	//BeginTextureMode(target);
	//ClearBackground(BLACK);
	//DrawRectangle(0, 0, GetScreenWidth(), GetScreenHeight(), BLACK);
	//EndTextureMode();

	if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT))
	{
		startPress = GetMousePosition();
	}

	if (IsMouseButtonDown(MOUSE_BUTTON_LEFT))
	{
		origin = prevOrigin - (startPress - GetMousePosition())*scale/2;
	}

	if (IsMouseButtonUp(MOUSE_BUTTON_LEFT))
	{
		prevOrigin = origin;
	}


	Vector2 v = GetMouseWheelMoveV();


	if (v.y != 0)
	{
		float factor = std::pow(0.9, v.y);
		scale *= factor;
		Vector2 scaleOrigin = { WIDTH / 2, HEIGHT / 2 };
		Vector2 shift = (1 - factor) * scaleOrigin;
		//origin = origin + shift;
	}

	if (IsKeyPressed(KEY_UP))
		maxIteration += 10;
	if (IsKeyPressed(KEY_DOWN))
		maxIteration -= 10;

	setShaderValue(shader, SHADER_UNIFORM_FLOAT, "scale", scale);
	setShaderValue(shader, SHADER_UNIFORM_VEC2, "origin", origin);
	setShaderValue(shader, SHADER_UNIFORM_INT, "maxIteration", maxIteration);
}

void draw()
{
	ClearBackground(BLACK);


	BeginShaderMode(shader);
	DrawTextureEx(target.texture, { 0.0f, 0.0f }, 0.0f, 1.0f, WHITE);
	EndShaderMode();
	DrawFPS(0, 0);

	//DrawCircleV(startPress, 10, BLUE);
	//DrawCircleV(origin, 10, MAGENTA);
	//DrawCircleV(fromTo(GetMousePosition(), startPress), 10, RED);
}

void trash()
{
	UnloadShader(shader);
	UnloadRenderTexture(target);
}