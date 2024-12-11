#include <raylib.h>
#include <iostream>
#include <deque>
#include <raymath.h>

Color green = {173, 204, 96, 255};
Color darkGreen = {43, 51, 24, 255};

int cellSize = 32;
int cellCount = 24;

double lastUpdateTime = 0;

bool eventTriggered(double interval){
    double currentTime = GetTime();
    if (currentTime - lastUpdateTime >= interval){
        lastUpdateTime = currentTime;
        return true;
    }
    return false;
}

bool elementInDeque(Vector2 element, std::deque<Vector2> deque){
    for(unsigned int i = 0; i < deque.size(); i++){
            if(Vector2Equals(deque[i], element)){
                return true;
            }
    }
    return false;
}

class Snake
{
    public:
        Texture2D headTexture, bodyTexture;
        std::deque<Vector2> body = {Vector2{6,9}, Vector2{5,9}, Vector2{4,9}};
        Vector2 direction = Vector2{1,0};

        Snake()
        {
            Image imageHead = LoadImage("graphics/SnakeHead.png");
            Image imageBody = LoadImage("graphics/SnakeBody.png");
            headTexture = LoadTextureFromImage(imageHead);
            bodyTexture = LoadTextureFromImage(imageBody);
            UnloadImage(imageHead);
            UnloadImage(imageBody);
        }

        ~Snake()
        {
            UnloadTexture(headTexture);
            UnloadTexture(bodyTexture);
        }

        void Draw(){
            for(unsigned int i = 0; i < body.size(); i++){
                float x = body[i].x;
                float y = body[i].y;
                if(i == 0){
                    DrawTexture(headTexture, x * cellSize, y * cellSize, WHITE);
                }
                else{
                    DrawTexture(bodyTexture, x * cellSize, y * cellSize, WHITE);
                }
            }
        }

        void Update(){
            body.pop_back();
            body.push_front(body[0] + direction);
        }
};

class Food
{

    public:
        Vector2 position;
        Texture2D texture;

        Food(std::deque<Vector2> snakeBody)
        {
            Image image = LoadImage("graphics/food.png");
            texture = LoadTextureFromImage(image);
            UnloadImage(image);
            position = GenerateRandomPos(snakeBody);
        }

        ~Food()
        {
            UnloadTexture(texture);
        }

        void Draw()
        {
            DrawTexture(texture, position.x * cellSize, position.y * cellSize, WHITE);
        }

        Vector2 generateRandomCell(){
            float x = GetRandomValue(0, cellCount - 1);
            float y = GetRandomValue(0, cellCount - 1);
            return Vector2{x, y};
        }

        Vector2 GenerateRandomPos(std::deque<Vector2> snakeBody)
        {
            Vector2 position = generateRandomCell();
            while (elementInDeque(position, snakeBody)){
                position = generateRandomCell();
            }
            return position;
        }

};

class Game{
    public:
        Snake snake = Snake();
        Food food = Food(snake.body);

        void Draw(){
            food.Draw();
            snake.Draw();
        }

        void Update(){
            snake.Update();
            CheckCollisionWithFood();
        }

        void CheckCollisionWithFood(){
            if(Vector2Equals(snake.body[0], food.position)){
                food.position = food.GenerateRandomPos(snake.body);
            }
        }
};

int main() 
{
    std::cout << "Starting the game..." << std::endl;
    InitWindow(cellSize * cellCount, cellSize * cellCount, "SNAKE!");
    SetTargetFPS(60);

    Game game = Game();

    while(WindowShouldClose() == false){
        BeginDrawing();

        if(eventTriggered(0.2)){
            game.Update();
        }

        if((IsKeyPressed(KEY_UP) || IsKeyPressed(KEY_W)) && game.snake.direction.y != 1){
            game.snake.direction = {0, -1};
        }
        else if((IsKeyPressed(KEY_RIGHT)|| IsKeyPressed(KEY_D)) && game.snake.direction.x != -1){
            game.snake.direction = {1, 0};
        }
        else if((IsKeyPressed(KEY_DOWN)|| IsKeyPressed(KEY_S)) && game.snake.direction.y != -1){
            game.snake.direction = {0, 1};
        }
        else if((IsKeyPressed(KEY_LEFT)|| IsKeyPressed(KEY_A)) && game.snake.direction.x != 1){
            game.snake.direction = {-1, 0};
        }
        
        //Drawing
        ClearBackground(green);
        game.Draw();

        EndDrawing();
    }

    CloseWindow();
    return 0;
}