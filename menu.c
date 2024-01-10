#include "raylib.h"
#include <time.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define MAX_WIDTH 1200
#define MAX_HEIGHT 800
#define MAX_ALT_TORRE 650
#define MIN_ALT_TORRE 450
#define MAX_ALT_DEM 300
#define MIN_ALT_DEM 10
#define MAX_QTD_TORRES 200
#define POS_INIC_JOG_X 150
#define POS_INIC_JOG_Y 400
#define TRUE 1
#define FALSE 0

#include <raylib.h>

int main() {
    // Initialization
    const int screenWidth = 800;
    const int screenHeight = 600;

    InitWindow(screenWidth, screenHeight, "Game Main Menu");

    SetTargetFPS(60);

    // Main menu variables
    int menuOption = 0;
    const char* menuOptions[] = {"Start Game", "Options", "Exit"};

    while (!WindowShouldClose()) {
        // Update
        // TODO: Add any game logic or input handling here

        // Check for mouse click on menu options
        if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON)) {
            int mouseX = GetMouseX();
            int mouseY = GetMouseY();

            for (int i = 0; i < 3; i++) {
                Rectangle optionRect = {screenWidth / 2 - MeasureText(menuOptions[i], 20) / 2,
                                        200 + i * 50 - 10, MeasureText(menuOptions[i], 20), 30};

                if (CheckCollisionPointRec((Vector2){mouseX, mouseY}, optionRect)) {
                    // Mouse click detected on this option
                    menuOption = i;

                    // TODO: Add logic specific to the selected menu option
                }
            }
        }

        // Draw
        BeginDrawing();

        ClearBackground(RAYWHITE);

        // Draw main menu options
        for (int i = 0; i < 3; i++) {
            if (i == menuOption) {
                DrawText(menuOptions[i], screenWidth / 2 - MeasureText(menuOptions[i], 20) / 2, 200 + i * 50, 20, RED);
            } else {
                DrawText(menuOptions[i], screenWidth / 2 - MeasureText(menuOptions[i], 20) / 2, 200 + i * 50, 20, BLACK);
            }
        }

        EndDrawing();
    }

    // De-Initialization
    CloseWindow();

    return 0;
}
