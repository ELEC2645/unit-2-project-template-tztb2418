#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <math.h>

#define PI 3.14159265358979323846

//  ---  Function headers  ---  //

// Operational
void clear_screen(void);
void move_cursor(int x, int y);
void draw_sin(int offset);
void draw_crosshairs(void);
void animate_sin(void);
// User input
int user_input(char *sel_buf, size_t sel_buf_sz);
void flush_input_buffer(void);
void get_amp(void);
void get_freq(void);
// print/ disply
void print_home_screen(void);
void print_main_menu(void);
void print_main_menu(void);
void soz(void);
// Program navigation
void main_menu(void);
void select_menu_item(char *sel_buf);

// ---  Constants  ---  //

const int width = 128; 
const int height = 28;       // width and height of frame, height must be even
const int time = 200;

float widthf = (float)width;
float heightf = (float)height;

const char mark = 'o';

//  ---  Global varibles  ---  //

float amp;
float freq;
// string input buffers
char sel_buf[20];
char amp_buf[4];
char freq_buf[5];
char *endptr;

int main() {

    print_home_screen();
    if(user_input(sel_buf, sizeof(sel_buf))){
       exit; 
    };
    if(strcmp(sel_buf, "m") == 0){
        main_menu(); 
    }
    else {
        exit;
    }
    
    return 0;
}

//  ---   Functions def  ---   //

// Operational - (sine)

void clear_screen(void) {
    printf("\033[2J");    // clear output
    printf("\033[H");     // move cursor to home position
}

void move_cursor(int x, int y) {
    printf("\033[%d;%dH", y, x);    // move curcor to x,y location
}

void draw_sin(int offset){
    
    // float for sine calculation
    float zeroy = heightf / 2.0;
    float flhi = (heightf / 2.0) * amp;
    float per = widthf / freq;

    // draw sine wave
    for(int i = 0; i < width; i++) {
        float fx = (float)(i + offset);
        float xrad = (2.0 * PI * freq * fx) / widthf;
        float sinval = sin(xrad);
        float fy = zeroy - (sinval * flhi);
        int y = (int)round(fy);
        // boundary checking
        if (y < 1) y = 1;
        if (y > height) y = height;

        move_cursor(i + 1, y);
        printf("%c", mark);
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

// User input

int user_input(char *sel_buf, size_t sel_buf_sz) {
    if (sel_buf == NULL || sel_buf_sz == 0) {
        printf("Invalid Buffer");
        return -1;
    }
    if (!fgets(sel_buf, (int)sel_buf_sz, stdin)) {
        flush_input_buffer();
        printf("fgets Fault");
        return -1;
    }

    // If no newline found, input exceeded buffer; flush leftover
    if (strchr(sel_buf, '\n') == NULL) {
        flush_input_buffer();
    }

    // Strip newline
    sel_buf[strcspn(sel_buf, "\n")] = '\0';

    if (sel_buf[0] == '\0') {
        // empty select word not allowed
        return -1;
    }

    return 0;
}

void flush_input_buffer(void) {
    int ch;
    while ((ch = getchar()) != '\n' && ch != EOF) { /* discard */ }
}

void get_amp(void){
    printf("\nPlease enter a amplitude between 1 and 100:");
    user_input(amp_buf, sizeof(amp_buf));
    amp = strtof(amp_buf, &endptr);
}

void get_freq(void){
    printf("\nPlease enter a frequency between 1 and 8:");
    user_input(freq_buf, sizeof(amp_buf));
    freq = strtof(freq_buf, &endptr);
}

// print/ disply

void print_home_screen(void){
    printf("\n------------- Wave Form Generator -------------\n");
    printf("Welcome, this is a waveform animation generator."); 
    printf("\nPlease enter m to view the Wave Form Menu:");
}

void print_main_menu(void) {
    printf("\n--------- Wave Form Menu ---------\n");
    printf("|\tSine\t\t\t|\n");
    printf("|\tSquare\t\t\t|\n");
    printf("|\tSaw Tooth\t\t|\n");
    printf("|\tInverse Saw\t\t|\n");
    printf("|\tTriangle\t\t|\n");
    printf("|\t\t\t\t|\n");
    printf("|\tExit\t\t\t|\n");
    printf("---------------------------------\n");
    printf("\nPlease enter selection here:");
}

void soz(void){
    printf("\nSorry, this waveform is yet to be developed.");
    printf("\nPlease enter m for Wave Form Menu");
}

// Program navigation

void main_menu() {
    print_main_menu();
    if(!user_input(sel_buf, sizeof(sel_buf))){
        get_amp();
        get_freq();
        select_menu_item(sel_buf);
    }
    
}

void select_menu_item(char *sel_buf) {

    if(strcmp(sel_buf, "sine") == 0) {
        animate_sin();  
    }
    else if(strcmp(sel_buf, "square") == 0) {
        soz();
    }
    else if(strcmp(sel_buf, "saw tooth") == 0) {
        soz();
    }
    else if(strcmp(sel_buf, "inverse saw tooth") == 0) {
        soz();
    }
    else if(strcmp(sel_buf, "triangle") == 0) {
        soz();
    }
    else if(strcmp(sel_buf, "exit") == 0){
        exit;
    }
    else {
        printf("Invalid input: %s\n", sel_buf);
    }
}