#include <string>
#include <iostream>
#include <fstream>

#include <raylib.h> // version 5.5
#include "game.h"
#include "gmath.h"
#include "gdraw.h"

void game(int fps, int screenWidth, int screenHeight)
{
    typedef struct Player {
        Vector2 position;
        float speed;
        float size;
    } Player;

    InitWindow(screenWidth, screenHeight, "Game title");
    SetTargetFPS(fps);
    ToggleFullscreen(); // Needs proper mechanic

    float deltaTime;
    
    std::ifstream file("resources/map/map.txt");

    Texture2D stoneTexture[] = {LoadTexture("resources/textures/stone/stone1.png"),
                                LoadTexture("resources/textures/stone/stone2.png"),
                                LoadTexture("resources/textures/stone/stone3.png")};
    
    Player player = { 0 }; //Initializing all variables
    player.position.x = 100.0f;
    player.position.y = 100.0f;

    const float moveSpeed = 60.0f;
    Vector2 direction = { 0 };

    // Camera variables
    Camera2D camera = { 0 };
    camera.target = (Vector2){player.position.x, player.position.y};
    camera.offset = (Vector2){screenWidth / 2.0f, screenHeight / 2.0f};
    camera.zoom = 2.0f;

    while (!WindowShouldClose()) 
    {
        deltaTime = GetFrameTime();

        // Functionality
        if (IsKeyDown(KEY_RIGHT)) direction.x = 1.0f;
        if (IsKeyDown(KEY_LEFT)) direction.x = -1.0f;
        
        if (IsKeyDown(KEY_UP)) direction.y = -1.0f;
        if (IsKeyDown(KEY_DOWN)) direction.y = 1.0f;

        // Vector normalization
        direction = NormalizeVector2(&direction);

        player.position.x += direction.x * moveSpeed * deltaTime;
        player.position.y += direction.y * moveSpeed * deltaTime;
        
        direction = {0, 0}; // zeroing direction

        // Camera follows player
        camera.target = (Vector2){ player.position.x + 25.0f, player.position.y + 25.0f};

        // Rendering
        BeginDrawing();
            ClearBackground(RAYWHITE); //Needs to be before BeginMode2D
            BeginMode2D(camera);

                DrawRectangle(player.position.x, player.position.y, 32, 32, RED);

                DrawBorders(&file, stoneTexture);

                DrawRectangle(550, 550, 32, 32, BLUE); // TEST OBJECT

            EndMode2D();
        EndDrawing();

    }
    file.close();
    
    for (unsigned int i = 0; i < sizeof(stoneTexture)/sizeof(Texture2D); i++) 
    {
        UnloadTexture(stoneTexture[i]);
    }
    //UnloadTexture(stoneTexture);

    CloseWindow();
}
