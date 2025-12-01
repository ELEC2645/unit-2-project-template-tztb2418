#include <stdio.h>
#include <unistd.h>
#include <math.h>

#define PI 3.14159265358979323846

//  ---  Function header  ---  //
void clear_screen(void);
void move_cursor(int x, int y);
void draw_sin(int width, int height, int offset, const char* mark);
void draw_crosshairs(int height, int width);


int main() {
    
    int width = 128, height = 26;       // width and height of frame
    
    for(int i=0; i<200; i++){
        clear_screen();
        printf("\n\n");                     // spacing for tideness

        draw_crosshairs(width, height);
            
        draw_sin(width, height, i, "o");
            
        fflush(stdout);  // Force output
        usleep(100000);  // 100ms delay
        
    
        move_cursor(0,height);              // returning cursor to end point
        printf("\n\n\n");
    }

    return 0;
}

//  ---   Functions def  ---   //

void clear_screen(void) {
    printf("\033[2J");    // clear output
    printf("\033[H");     // move cursor to home position
}

void move_cursor(int x, int y) {
    printf("\033[%d;%dH", y, x);    // move curcor to x,y location
}

void draw_sin(int width, int height, int offset, const char* mark){
    
    // float for sine calculation
    float zeroy = (float)(height/2) + 1;
    float flwi = (float)width;
    float flhi = (float)height;
    float radwi = 2*PI/flwi;
    float radhi = flhi/(2*PI);

    // draw sine wave
    float fx = 0.0;
    float fy = 0.0;
    int y = 0;
    for(int i = 0; i < width; i++) {
        fx = (float)(i + offset) *  radwi;
        fy = sin(fx) * (flhi / 2.4) + zeroy;
        y = (int)round(fy);
        move_cursor(i,y);
        printf("%s",mark);
    }
}

void draw_crosshairs(int width, int height){

    for(int j=0; j<=height; j++){
            move_cursor(width/2, j);
            printf("|");
        }

        for(int j=0; j<=width; j++){

            if(j == width/2){
                move_cursor(j, height/2);
                printf("+");
            }
            else{
                move_cursor(j, height/2);
                printf("-");
            }
        }
}