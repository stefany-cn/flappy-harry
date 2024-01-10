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

//oi! oi oi

typedef struct Torre_str {
    Rectangle recTorre;
    Texture2D textura;
    Vector2 posicao;
    int passou;

}TORRE;

typedef struct Dementador_str {
    Rectangle recDementador;
    Texture2D textura;
    Vector2 posicao;
    int passou;

}DEMENTADOR;

typedef struct Jogador_str {
    Rectangle areaJogador;
    Texture2D jogador;
    Vector2 posicao;
    float rotationJogador;
    char nomeJogador[30];
    int score;

}JOGADOR;

typedef struct Menu_str{
    Rectangle recMenu;
}MENU;

//Declara��o de vari�vel est�tica para poder usar em todas as fun��es mantendo o valor dela ao sair da fun��o
static Vector2 torresPos[MAX_QTD_TORRES] = {0};
static TORRE listaTorres[MAX_QTD_TORRES] = {0};
static DEMENTADOR listaDementadores[MAX_QTD_TORRES] = {0};
static Vector2 dementadorPos[MAX_QTD_TORRES] = {0};
static int gameOver = FALSE;
static int newRecord = 0;
static JOGADOR harry = {0};
static Texture2D background;
static Texture2D texturaTorres[4] = {0};
static Texture2D dementador;
static int menuOption = 0;
static char* menuOptions[3];
static Rectangle recMenuOptions[3];

int menuPrincipal(void) {
    int i = 0;
    char* menuOptions[] = {"Start Game", "Options", "Exit"};

    for (i = 0; i < 3; i++) {
       recMenuOptions[i] = {MAX_WIDTH / 2 - MeasureText(menuOptions[i], 20) / 2,
                              200 + i * 50 - 10, MeasureText(menuOptions[i], 20), 30};
    }
    if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON)) {
        int mouseX = GetMouseX();
        int mouseY = GetMouseY();
        for(i = 0; i < 3; i++){
            if (CheckCollisionPointRec((Vector2){mouseX, mouseY}, recMenuOptions[i])) {
               menuOption = i;
            }
        }
    }

    for (i = 0; i < 3; i++) {
        if (i == menuOption) {
            DrawText(menuOptions[i], MAX_WIDTH / 2 - MeasureText(menuOptions[i], 20) / 2, 200 + i * 50, 20, RED);
        } else {
            DrawText(menuOptions[i], MAX_WIDTH / 2 - MeasureText(menuOptions[i], 20) / 2, 200 + i * 50, 20, BLACK);
        }
    }
    return menuOption;
}
int carregaMenuPrincipal(void){
    int menuOption = 0;
    menuOption = menuPrincipal();

    return menuOption;
}
void iniciaJogo(void){
    int menuOption;
    menuOption = carregaMenuPrincipal();
    if (menuOption == 0){
        background = LoadTexture("sprites/background-min.png");
        carregaTextJog();
        carregaTextObstaculos();
        criaPosicaoObstaculos();
    }


    harry.score = 0;
    gameOver = FALSE;


}

void desenhaMenu(void){
    DrawRectangle(MAX_WIDTH/2, MAX_HEIGHT/2, 100, 50, WHITE);

}

void menuJogo(void){


}

void carregaTextJog(void){
    //Image harryImage = LoadImage("sprites/harry-broomstick.png");
    harry.jogador = LoadTexture("sprites/harry-broomstick.png");
    //UnloadImage(harryImage);
    harry.posicao = (Vector2){POS_INIC_JOG_X, POS_INIC_JOG_Y};
    harry.areaJogador.height = 0.5 * (harry.jogador.height);
    harry.areaJogador.width = 0.5 * (harry.jogador.width);
    harry.areaJogador.x = harry.posicao.x;
    harry.areaJogador.y = harry.posicao.y;


}


void desenhaJogador(void){
    DrawRectangleRec(harry.areaJogador,WHITE);
    DrawTexturePro(harry.jogador,
                   (Rectangle){0, 0, harry.jogador.width, harry.jogador.height},
                   (Rectangle){harry.posicao.x, harry.posicao.y, harry.jogador.width/2, harry.jogador.height/2},
                   (Vector2){0, 0},
                   harry.rotationJogador,
                   WHITE);

}
void carregaTextObstaculos(void){
    //Textura das torres

    Texture2D torrelufa = LoadTexture("sprites/torre-lufalufa.png");
    Texture2D torrecorvinal = LoadTexture("sprites/torre-corvinal.png");
    Texture2D torregrifinoria = LoadTexture("sprites/torre-grifinoria.png");
    Texture2D torresonserina = LoadTexture("sprites/torre-sonserina.png");
    texturaTorres[0] = torrelufa;
    texturaTorres[1] = torregrifinoria;
    texturaTorres[2] = torrecorvinal;
    texturaTorres[3] = torresonserina;

    //Textura dos dementadores
    dementador = LoadTexture("sprites/dementador.png");

}
void criaPosicaoObstaculos(void){
    int i = 0, j = 0;
    for (i = 0; i < MAX_QTD_TORRES; i++){
        //posi��o x =  come�a em 500px e a pr�xima torre vem 250px depois
        torresPos[i].x = 500 + 250*i;
        torresPos[i].y = GetRandomValue(450, 650);

        dementadorPos[i].x = 500 + 250*i;
        dementadorPos[i].y = 800 - listaTorres[i].recTorre.height - torresPos[i].y - 200;
    }
    for(i = 0, j = 0; i < MAX_QTD_TORRES; i++, j++){
        if(j > 3){
            j = 0;
        }
        listaTorres[i].textura = texturaTorres[j];
        listaTorres[i].posicao.x = torresPos[i].x;
        listaTorres[i].posicao.y = torresPos[i].y;
        listaTorres[i].recTorre.x = listaTorres[i].posicao.x;
        listaTorres[i].recTorre.y = torresPos[i].y;
        listaTorres[i].recTorre.height = listaTorres[i].textura.height;
        listaTorres[i].recTorre.width = listaTorres[i].textura.width;

        listaTorres[i].passou = FALSE;

        listaDementadores[i].textura = dementador;
        listaDementadores[i].posicao.x = dementadorPos[i].x;
        listaDementadores[i].posicao.y = dementadorPos[i].y;
        listaDementadores[i].recDementador.x = dementadorPos[i].x;
        listaDementadores[i].recDementador.y = dementadorPos[i].y;
        listaDementadores[i].recDementador.height = 0.2 *(listaDementadores[i].textura.height);
        listaDementadores[i].recDementador.width = 0.2 * (listaDementadores[i].textura.width);

        listaDementadores[i].passou = FALSE;
    }
}
void desenhaObstaculos(void){
    int i = 0;

    for(i = 0; i < MAX_QTD_TORRES; i++){
        DrawTextureEx(listaTorres[i].textura,listaTorres[i].posicao, 0, 0.6, WHITE);

        DrawTextureEx(listaDementadores[i].textura,listaDementadores[i].posicao, 0, 0.2, WHITE);
        DrawRectangleRec(listaDementadores[i].recDementador, WHITE);
    }
}

void atualizaPosObstaculos(void){
    int i = 0;
    for (i = 0; i < MAX_QTD_TORRES; i++){
            torresPos[i].x -= GetFrameTime() * 100;
            dementadorPos[i].x -= GetFrameTime() * 100;
        }
        for(i = 0; i < MAX_QTD_TORRES; i++){
            listaTorres[i].posicao.x = torresPos[i].x;
            listaTorres[i].recTorre.x = torresPos[i].x;

            listaDementadores[i].posicao.x = dementadorPos[i].x;
            listaDementadores[i].recDementador.x = dementadorPos[i].x;
        }

}
void checaColisao(void){
    int i = 0;
    for (i = 0; i < MAX_QTD_TORRES; i++){

        if (CheckCollisionRecs(harry.areaJogador, listaTorres[i].recTorre) || CheckCollisionRecs(harry.areaJogador, listaDementadores[i].recDementador)){

            gameOver = TRUE;
            printf("\n\n\nCOLISAO!\n\n\n");
        } else if ((torresPos[i].x < harry.posicao.x) && !listaTorres[i].passou && !gameOver){
            harry.score += 100;
            listaTorres[i].passou = TRUE;
            listaDementadores[i].passou = TRUE;
        }
        if(harry.score > newRecord){
            newRecord = harry.score;
        }
    }
}
void desenhaBackground(void){

    DrawTexture(background, 0, 0, RAYWHITE);
}
void desenhaJogo(void){


    BeginDrawing();

    ClearBackground(RAYWHITE);

    if (!gameOver){
        desenhaBackground();
        desenhaJogador();
        desenhaObstaculos();
    } else {
        DrawText("GAME OVER!", MAX_WIDTH/2 - MeasureText("GAME OVER!", 40)/2, MAX_HEIGHT/2 - 40, 40, BLACK);
    }
    DrawText(TextFormat("%04i", harry.score), 20, 20, 40, BLACK);

    EndDrawing();
}

void jogoPorFrame(void){
    if(!gameOver){
        atualizaPosObstaculos();
        if (IsKeyDown(KEY_SPACE) && !gameOver){
            harry.rotationJogador = 0;
            if (harry.posicao.y >= 780){
                harry.posicao.y = 780;
            }
            harry.posicao.y -= 1;
            harry.areaJogador.y = harry.posicao.y;

        } else if(harry.posicao.y <= 0){
                gameOver = TRUE;
        } else {
            harry.posicao.y += 1;
            harry.areaJogador.y = harry.posicao.y;
            if(harry.rotationJogador >= 0 && harry.rotationJogador < 90){
                harry.rotationJogador += 0.3;
            } else if (harry.rotationJogador = 90){
                harry.rotationJogador = 90;
            }
        }
        checaColisao();
    } else {
        if(IsKeyPressed(KEY_ENTER)){
            iniciaJogo();
            gameOver = FALSE;
        }
    }
}
void atualizaJogo(void){
    jogoPorFrame();
    desenhaJogo();
}
void unloadGame(void){
    UnloadTexture(background);
    UnloadTexture(harry.jogador);
    UnloadTexture(texturaTorres[0]);
    UnloadTexture(texturaTorres[1]);
    UnloadTexture(texturaTorres[2]);
    UnloadTexture(texturaTorres[3]);
    UnloadTexture(dementador);
}

int main(void){

    //Inicializa��o da janela do jogo
    InitWindow(MAX_WIDTH, MAX_HEIGHT,"Flappy Harry");
    SetTargetFPS(60);
    iniciaJogo();

    while(!WindowShouldClose()){

        atualizaJogo();

    }

    unloadGame();
    CloseWindow();


    return 0;
}


