#include "raylib.h"
#include <iostream>
#include "rlgl.h"
#include "const.h"

using namespace std;


void updateIt() {

    if (it[1] >= high && dirdown[1]) {
        dirdown[1] = false;
        sp = -sp;
    }
    if (it[1] <= low && !dirdown[1]) {
        dirdown[1] = true;
        sp = -sp;
    }

    if (it[3] >= high && dirdown[2]) {
        dirdown[2] = false;
        sp2 = -sp2;
    }
    if (it[3] <= low && !dirdown[2]) {
        dirdown[2] = true;
        sp2 = -sp2;
    }

    it[1]+=sp;
    it[2] = high-it[1];
    it[3]+=sp2; 
    it[4] = high-it[3];


    //piston 1 
    if(dirdown[1]) angle[1] = (2.0f * PI * (it[1] - low) / (high - low))/2 - PI/2; 
    if(!dirdown[1]) angle[1] = 2*PI - (2.0f * PI * (it[1] - low) / (high - low))/2 - PI/2; 
    x[1] = radius * cos(angle[1]);
    y[1] = radius * sin(angle[1]);

    //piston 2
    if(!dirdown[1]) angle[2] = (2.0f * PI * (it[2] - low) / (high - low))/2 - PI/2; 
    if(dirdown[1]) angle[2] = 2*PI - (2.0f * PI * (it[2] - low) / (high - low))/2 - PI/2; 
    x[2] = radius * cos(angle[2]);
    y[2] = radius * sin(angle[2]);

    //piston 3
    if(dirdown[2]) angle[3] = (2.0f * PI * (it[3] - low) / (high - low))/2 - PI/2; 
    if(!dirdown[2]) angle[3] = 2*PI - (2.0f * PI * (it[3] - low) / (high - low))/2 - PI/2; 
    x[3] = radius * cos(angle[3]);
    y[3] = radius * sin(angle[3]);

    //piston 4
    if(!dirdown[2]) angle[4] = (2.0f * PI * (it[4] - low) / (high - low))/2 - PI/2; 
    if(dirdown[2]) angle[4] = 2*PI - (2.0f * PI * (it[4] - low) / (high - low))/2 - PI/2; 
    x[4] = radius * cos(angle[4]);
    y[4] = radius * sin(angle[4]);
}


int main()
{     
    dirdown[1] = true;
    dirdown[2] = true;
    cn[2] = 1;
    cn[4] = 1;
    SetTargetFPS(fps);
    InitWindow(screenWidth, screenHeight, "engine");
    
    it[3] = high/2;

    InitAudioDevice();
    Sound poop = LoadSound("phonk.wav");
    Sound poop2 = LoadSound("poop.wav");
    Sound poop3 = LoadSound("/crunch.wav");



    while (!WindowShouldClose())
    {   
        
        BeginDrawing();
        ClearBackground(LIGHTGRAY);

        rlSetLineWidth(10.0f);

        if(IsKeyPressed(KEY_SPACE))paused = !paused;
        if(IsKeyPressed(KEY_S))PlaySound(poop);
        if(!paused){
            updateIt();
            DrawText("|>",300,550,20,BLACK);
        } else {
            DrawText("||",300,550,20,BLACK);
        }

        //bg
        DrawRectangle(270,40,60,200,GRAY); //side view

        DrawRectangle(390,40,200,200,GRAY); //lateral view
        DrawText("lateral view",390,250,20,BLACK);



        // DrawLine(,x[1]+screenHeight/2,y[1]+screenWidth/2+100,BLACK); //spoke
        DrawCircle(screenWidth/2,screenHeight/2+100,60,GRAY);
        

        // Ignition
        DrawRectangle(35,85,220,60,GRAY);
        DrawText("top view/Ign seq",35,150,20,BLACK);

        if(it[1]<ign){
            DrawRectangle(50,100,30,30,DARKGRAY);
            DrawRectangle(screenHeight/2-15,50,30,5,ORANGE); //piston ig
            DrawRectangle(screenHeight/2+100,50,30,5,ORANGE); //piston
            DrawText("1",60,50,20,BLACK);
            if(it[1]==0){
                
                if(cn[1]==2&&!ignited[1]){
                     
                    cn[1]=0;
                }
                cn[1]++;
                PlaySound(poop);
                PlaySound(poop2);
                PlaySound(poop3);
            }
            
        }
        if(it[2]<ign){
            DrawRectangle(100,100,30,30,BLUE);
            DrawRectangle(screenHeight/2-15,50,30,5,ORANGE); //piston 2 ig
            DrawRectangle(screenHeight/2+150,50,30,5,ORANGE); // piston 2
            DrawText("2",110,50,20,BLACK);

            if(it[2]==0){
                if(cn[2]==2&&!ignited[2]){

                    cn[2]=0;
                }
                cn[2]++;
                PlaySound(poop);
                PlaySound(poop2);
                PlaySound(poop3);
            }

        }
        if(it[3]<ign){
            DrawRectangle(150,100,30,30,DARKGREEN);
            DrawRectangle(screenHeight/2-15,50,30,5,ORANGE); //piston 3 ig
            DrawRectangle(screenHeight/2+200,50,30,5,ORANGE); // piston 3
            DrawText("3",160,50,20,BLACK);

            if(it[3]==0){
                if(cn[3]==2&&!ignited[3]){

                    cn[3]=0;
                }
                cn[3]++;
                PlaySound(poop);
                PlaySound(poop2);
                PlaySound(poop3);
            }

        }
        if(it[4]<ign){
            DrawRectangle(200,100,30,30,VIOLET);
            DrawRectangle(screenHeight/2-15,50,30,5,ORANGE); //piston 4 ig
            DrawRectangle(screenHeight/2+250,50,30,5,ORANGE); // piston 4
            DrawText("4",210,50,20,BLACK);
            
            if(it[4]==0){
                if(cn[4]==2&&!ignited[4]){
                    
                    cn[4]=0;
                }
                cn[4]++;
                PlaySound(poop);
                PlaySound(poop2);
                PlaySound(poop3);
            }
            

        }


        //piston 1
        DrawRectangle(screenHeight/2-15,it[1]+50,30,30,DARKGRAY); //piston
        DrawLine(screenHeight/2,it[1]+75,x[1]+screenHeight/2,y[1]+screenWidth/2+100,DARKGRAY); //connecting rod 
        DrawLine(screenWidth/2,screenHeight/2+100,x[1]+screenHeight/2,y[1]+screenWidth/2+100,BLACK); //spoke
        DrawCircle(x[1]+screenHeight/2,y[1]+screenWidth/2+100,10,BLACK);


        // piston 2
        DrawRectangle(screenHeight/2 - 15, it[2] + 50, 30, 30, BLUE); // piston 2
        DrawLine(screenHeight/2, it[2] + 75, x[2] + screenHeight/2, y[2] + screenWidth/2 + 100, BLUE); //connecting rod 
        DrawLine(screenWidth/2, screenHeight/2 + 100, x[2] + screenHeight/2, y[2] + screenWidth/2 + 100, BLACK); //spoke 
        DrawCircle(x[2] + screenHeight/2, y[2] + screenWidth/2 + 100, 10, BLACK);


        // piston 3
        DrawRectangle(screenHeight/2 - 15, it[3] + 50, 30, 30, DARKGREEN); // piston 3
        DrawLine(screenHeight/2, it[3] + 75, x[3] + screenHeight/2, y[3] + screenWidth/2 + 100, DARKGREEN); //connecting rod 
        DrawLine(screenWidth/2, screenHeight/2 + 100, x[3] + screenHeight/2, y[3] + screenWidth/2 + 100, BLACK); //spoke 
        DrawCircle(x[3] + screenHeight/2, y[3] + screenWidth/2 + 100, 10, BLACK);
        

        
        // piston 4
        DrawRectangle(screenHeight/2 - 15, it[4] + 50, 30, 30, VIOLET); // piston 4
        DrawLine(screenHeight/2, it[4] + 75, x[4] + screenHeight/2, y[4] + screenWidth/2 + 100, VIOLET); //connecting rod 
        DrawLine(screenWidth/2, screenHeight/2 + 100, x[4] + screenHeight/2, y[4] + screenWidth/2 + 100, BLACK); //spoke 
        DrawCircle(x[4] + screenHeight/2, y[4] + screenWidth/2 + 100, 10, BLACK);
    

        //central axel
        DrawCircle(screenHeight/2,screenWidth/2+100,20,DARKGRAY); //central axel


        // lateral view
        DrawRectangle(screenHeight/2+100,it[1] + 50,30,30,DARKGRAY); //piston
        DrawRectangle(screenHeight/2+150,it[2] + 50,30,30, BLUE); // piston 2
        DrawRectangle(screenHeight/2+200,it[3] + 50,30,30, DARKGREEN); // piston 3
        DrawRectangle(screenHeight/2+250,it[4] + 50,30,30, VIOLET); // piston 4
        
        
        //RPM calc
        rpm = (fps*60.0f*abs(sp))/(2.0f*(high-low));
        // cout<<rpm<<endl;
        
        DrawText("BEENGINE SIM",100,550,20,BLACK);

        EndDrawing();

    }   

    UnloadSound(poop);
    CloseAudioDevice();
    
    CloseWindow();


    return 0;
}
