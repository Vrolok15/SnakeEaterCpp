#include <raylib.h>
#include <iostream>

Color green = {173, 204, 96, 255};
Color darkGreen = {43, 51, 24, 255};

int cellSize = 32;
int cellCount = 24;

class Food{

    public:
        Vector2 position = {5, 6};
        Texture2D texture;

        Food()
        {
            Image image = LoadImage("graphics/food.png");
            texture = LoadTextureFromImage(image);
            UnloadImage(image);
        }

        ~Food()
        {
            UnloadTexture(texture);
        }

        void Draw()
        {
            DrawTexture(texture, position.x * cellSize, position.y * cellSize, WHITE);
        }

};

int main() 
{
    std::cout << "Starting the game..." << std::endl;
    InitWindow(cellSize * cellCount, cellSize * cellCount, "SNAKE!");
    SetTargetFPS(60);

    Food food = Food();

    while(WindowShouldClose() == false){
        BeginDrawing();
        
        //Drawing
        ClearBackground(green);
        food.Draw();

        EndDrawing();
    }

    CloseWindow();
    return 0;
}