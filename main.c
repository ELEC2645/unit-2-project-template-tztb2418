#include <stdio.h>
#include <unistd.h>
#include <math.h>

#define PI 3.14159265358979323846

//  ---  Function header  ---  //
void clear_screen(void);
void move_cursor(int x, int y);
void draw_sin(int offset);
void draw_crosshairs(void);
void animate_sin(void);
void get_amp_freq(void);

char main_menu(void);

//  ---  Global varibles  ---  //

int width = 128, height = 28;       // width and height of frame, height must be even
int time = 200;

int amplitude;
int frequency;
float amp;
float freq;

const char mark = 'o';

int main() {

    if(main_menu() == "Sine"){
        get_amp_freq();
        animate_sin(); 
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

void draw_sin(int offset){
    
    // float for sine calculation
    float zeroy = (float)(height/2) +1;
    float flwi = (float)width;
    float flhi = (float)height * amp / 2.0;
    float radwi = 2*PI/flwi;
    float radhi = flhi/(2*PI);

    // draw sine wave
    float fx = 0.0;
    float fy = 0.0;
    int y = 0;
    for(int i = 0; i < width; i++) {
        fx = (float)(i + offset) *  radwi;
        fy = sin(fx * freq) * flhi + zeroy;
        y = (int)round(fy);
        move_cursor(i,y);
        printf("%c",mark);
    }
}

void draw_crosshairs(void){

    for(int j=0; j<=height + 1; j++){
            move_cursor(width/2, j);
            printf("|");
        }

        for(int j=0; j<=width; j++){

            if(j == width/2){
                move_cursor(j, (height/2) + 1);
                printf("+");
            }
            else{
                move_cursor(j, (height/2) + 1);
                printf("-");
            }
        }
}

void animate_sin(void){

      for(int i=0; i<time; i++){
        
        clear_screen();
        printf("\n\n");                     // spacing for tideness
        draw_crosshairs();
        draw_sin(i);
        printf("\n\n");                   // spacing for tideness
        
        fflush(stdout);  // Force output
        usleep(100000);  // 100ms delay
        move_cursor(0,height);              // returning cursor to start point
        
    }
    move_cursor(0,height+2);  // moving cursor to end point
}

void get_amp_freq(void){

    printf("\nInput a amplitude between 1 and 100: ");
    scanf("%d", &amplitude);
    printf("Input an frequency between 1 and 6: ");
    scanf("%d", &frequency);

    amp = (float)amplitude/ 100.0;
    freq = (float)frequency;
}

char main_menu(void){
    printf("  SIGNAL GENERATOR");
    printf("\n    MAIN MENU:");
    Printf("\n1. input Sine for sinusoidal wave form");
    char str[];
    scanf("%s", str);
    return str;
}