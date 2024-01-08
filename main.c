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



void iniciaJogo(void){
    carregaTextJog();
    carregaTextObstaculos();
    criaPosicaoObstaculos();

    harry.score = 0;
    gameOver = FALSE;


}

void carregaTextJog(void){
    Image harryImage = LoadImage("sprites/harry-broomstick.png");
    harry.jogador = LoadTextureFromImage(harryImage);
    UnloadImage(harryImage);
    harry.posicao = (Vector2){POS_INIC_JOG_X, POS_INIC_JOG_Y};
    harry.areaJogador.height = 0.5 * (harry.jogador.height);
    harry.areaJogador.width = 0.5 * (harry.jogador.width);
    harry.areaJogador.x = harry.posicao.x;
    harry.areaJogador.y = harry.posicao.y;


}


void desenhaJogador(void){
    //DrawRectangleRec(harry.areaJogador,WHITE);
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
        torresPos[i].y = GetRandomValue(MIN_ALT_TORRE, MAX_ALT_TORRE);

        dementadorPos[i].x = 500 + 250*i;
        dementadorPos[i].y = GetRandomValue(0, 300);
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
           // printf("posicao torre draw %d: %d %d\n",i, listaTorres[i].posicao.x, listaTorres[i].posicao.y);
            DrawTextureEx(listaTorres[i].textura,listaTorres[i].posicao, 0, 0.6, WHITE);
            DrawTextureEx(listaDementadores[i].textura,listaDementadores[i].posicao, 0, 0.2, WHITE);
            //DrawRectangleRec(listaDementadores[i].recDementador, WHITE);

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

        //printf("area rec torre %d: %f %f %f %f\n",i, listaTorres[i].recTorre.height, listaTorres[i].recTorre.width, listaTorres[i].recTorre.x, listaTorres[i].recTorre.y);
        //printf("posicao torre %d: %f %f\n",i, listaTorres[i].posicao.x, listaTorres[i].posicao.y);
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

void desenhaJogo(void){
    background = LoadTexture("sprites/background.png");

    BeginDrawing();

    ClearBackground(RAYWHITE);

    if (!gameOver){
        DrawTexture(background, 0, 0, WHITE);
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
            if(harry.posicao.y = 0){
                harry.posicao.y = 0;
            }
            harry.posicao.y -= 10;
            harry.areaJogador.y = harry.posicao.y;

        } else if (harry.posicao.y >= 800){
                gameOver = TRUE;
            } else {
            harry.posicao.y += 3;
            harry.areaJogador.y = harry.posicao.y;
           // printf("\n\n***");
           // printJogador(harry);
            //printf("***\n\n");
            if(harry.rotationJogador >= 0 && harry.rotationJogador < 90){
                harry.rotationJogador += 0.5;
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

}

int main(void){

    //Inicializa��o da janela do jogo
    InitWindow(MAX_WIDTH, MAX_HEIGHT,"Flappy Harry");

    iniciaJogo();
    while(!WindowShouldClose()){

        atualizaJogo();

    }

    unloadGame();
    CloseWindow();


    return 0;
}


