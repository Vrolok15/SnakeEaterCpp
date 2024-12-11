#include <raylib.h>
#include <iostream>

Color green = {173, 204, 96, 255};
Color darkGreen = {43, 51, 24, 255};

int cellSize = 30;
int cellCount = 25;

class Food{

    public:
        Vector2 position = {5, 6};

        void Draw()
        {
            DrawCircle(position.x * cellSize, position.y * cellSize, cellSize / 2, darkGreen);
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