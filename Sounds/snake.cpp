#include <raylib.h>
#include <iostream>
#include <deque>
#include <raymath.h>

using namespace std;

Color green = {173, 204, 96, 255};
Color darkGreen = {43, 51, 24, 255};

int cellSize = 30;
int cellCount = 25;

double lastUpdateTime = 0;

bool eventTriggered(double interval)
{
	double currentTime = GetTime();
	if (currentTime - lastUpdateTime >= interval)
	{
		lastUpdateTime = currentTime;
		return true;
	}
	return false;
}


class Snake
{
public :
	deque<Vector2>  body = { Vector2{6, 9}, Vector2{5, 9}, Vector2{4, 9} };
	Vector2 direction = { 1, 0 };

	void Draw()
	{
		for (unsigned int i = 0; i < body.size(); i++)
		{
			float x = body[i].x;
			float y = body[i].y;
			Rectangle segment = Rectangle{x * cellSize, y * cellSize, float(cellSize), float(cellSize)};
			DrawRectangleRounded(segment, 0.5, 6, darkGreen);
		}
	}

	void Update()
	{
		body.pop_back();
		body.push_front(Vector2Add(body[0], direction));
	}
};

class Food {

public:
	Vector2 position = { 5, 6 };
	Texture2D texture;

	Food()
	{
		Image image = LoadImage("Graphics/food.png");
		texture = LoadTextureFromImage(image);
		UnloadImage(image);
		position = GenerateRandomPos();
	}


	void Draw()
	{
		DrawTexture( texture ,position.x * cellSize, position.y * cellSize, darkGreen);
	}

	Vector2 GenerateRandomPos()
	{
		float x = GetRandomValue(0, cellCount - 1);
		float y = GetRandomValue(0, cellCount - 1);
		return Vector2{x, y};
	}

	
};

int main()
{
	cout << "Starting the game..." << endl;
	InitWindow(cellSize * cellCount, cellSize * cellCount, "Retro Snake");
	SetTargetFPS(60);

	Food food = Food();
	Snake snake = Snake();

	while(WindowShouldClose() == false)
	{
		BeginDrawing();

		if (eventTriggered(0.2))
		{
			snake.Update();
		}

		//snake.Update();

		// Drawing
		ClearBackground(green);
		food.Draw();
		snake.Draw();
	

		EndDrawing();
	}

	CloseWindow();
	return 0;

}
