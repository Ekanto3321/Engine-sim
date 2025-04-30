#include<math.h>

int fps = 75;
int screenWidth = 600;
int screenHeight = 600;
float sp = 5;
float sp2 = sp;
int it[10] = {0}; //iterator variable
int low = 0;
int high =  150;
int radius = high/2;
bool dirdown[10] = {true};
float angle[10];
bool paused = false;
int dst = 0;
float x[10];
float y[10];
int ign = 16;
bool ignited[5] = {false};
int cn[10] = {1}; 
int rpm;
int frCnt=0;