#include <raylib.h>
#include <iostream>

Color green = {173, 204, 96, 255};
Color darkGreen = {43, 51, 24, 255};

int cellSize = 32;
int cellCount = 24;

class Food{

    public:
        Vector2 position;
        Texture2D texture;

        Food()
        {
            Image image = LoadImage("graphics/food.png");
            texture = LoadTextureFromImage(image);
            UnloadImage(image);
            position = GenerateRandomPos();
        }

        ~Food()
        {
            UnloadTexture(texture);
        }

        void Draw()
        {
            DrawTexture(texture, position.x * cellSize, position.y * cellSize, WHITE);
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
    std::cout << "Starting the game..." << std::endl;
    InitWindow(cellSize * cellCount, cellSize * cellCount, "SNAKE!");
    SetTargetFPS(60);

    Food food = Food();
    Food food2 = Food();
    Food food3 = Food();

    while(WindowShouldClose() == false){
        BeginDrawing();
        
        //Drawing
        ClearBackground(green);
        food.Draw();
        food2.Draw();
        food3.Draw();

        EndDrawing();
    }

    CloseWindow();
    return 0;
}