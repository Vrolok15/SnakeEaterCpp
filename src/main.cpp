#include <raylib.h>
#include <iostream>

int main() 
{
    std::cout << "Starting the game..." << std::endl;
    InitWindow(750, 750, "SNAKE!");
    SetTargetFPS(60);
    
    while(WindowShouldClose() == false){
        BeginDrawing();
        
        EndDrawing();
    }

    CloseWindow();
    return 0;
}