#include <stdio.h>
#include <windows.h>
#include <conio.h>
#include <time.h>
#include <stdbool.h>
#include <unistd.h>
#include <string.h>
#define HEIGHT 30
#define WIDTH 70
#define PIPEHEIGHT 5
#define PIPEWIDTH 5

void setConsoleSize(int height, int width) {
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    COORD size = {width, height};
    SetConsoleScreenBufferSize(hConsole, size);
    SMALL_RECT rect = {0, 0, width - 1, height - 1};
    SetConsoleWindowInfo(hConsole, TRUE, &rect);
}


typedef struct {
    int x;
    int y;
} Bird;
typedef struct {
    float vel;
    float grav;
    float jumpP;
} Psx;

typedef struct{
    int x;
    int y;
} Pipe;

char scene[HEIGHT][WIDTH+1];
Bird bird = {10, 5 };
Psx psx = {0,0.5,-2};
Pipe pipe = {WIDTH, 10};

void piperender(){
    for(int i = 0; i < HEIGHT; i++){
        if(i >= pipe.y && i <= pipe.y){
            i += PIPEHEIGHT;
        }
        else {
            for(int j = 0; j <= PIPEHEIGHT; j++){
                if(j == 0) scene[i][pipe.x] = '|';
                else if(j == PIPEHEIGHT) scene[i][pipe.x + PIPEWIDTH] = '|';
                else continue;
            }
        }
    }
    pipe.x--;
}

void clearscene(){
    for(int i = 0; i < HEIGHT; i++){
        for(int j = 0; j < WIDTH; j++)
            scene[i][j] = ' ';
        scene[i][WIDTH] = '\0';
    }
}
void updatePhys(bool isjump){
    if(isjump){
        psx.vel = psx.jumpP;
    }
    else{
        psx.vel += psx.grav;
    }
    bird.y += (int)psx.vel;
}
void render(){
    piperender();
    scene[bird.y][bird.x] = '@';
    for(int i = 0; i < HEIGHT; i++)
            puts(scene[i]);
}

int main(){
    setConsoleSize(HEIGHT, WIDTH);
    char key;
    pipe.y = 10/*rand() % 21 + 5*/;
    do{
        clearscene();
        if (_kbhit()) {
            key = _getch();
            if (key == 'w') {
                updatePhys(true);
            }
        }
        else{
            updatePhys(false);
        }
        render();
        Sleep(33);
        system("cls");
    }while(1);

    return 0;
}