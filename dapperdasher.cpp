#include "raylib.h"


struct AnimData
{
    Rectangle rec;
    Vector2 pos;
    int frame;
    float UpdateTime;
    float RunningTime;
};

bool IsOnGround( AnimData Data , int WindowHeight)
{
    return Data.pos.y >= WindowHeight - Data.rec.height ;
}

AnimData UpdateAnimDAta( AnimData data , float DeltaTime , int MaxFrame)
{
    //Update running time 
    data.RunningTime += DeltaTime;
    if(data.RunningTime >= data.UpdateTime)
    {
        data.RunningTime = 0.0;
        //Update Animation Frame  
        data.rec.x = data.frame * data.rec.width;
        data.frame++;
        if(data.frame > MaxFrame)
            data.frame=0;
        }
        return data;
    }

bool collision{};


int main(){

    // Creating Array IN WINDOW DIMENSION!!!!
    int Windowdimensions[2];
    Windowdimensions[0]=1000;
    Windowdimensions[1]=600;

    InitWindow(Windowdimensions[0], Windowdimensions[1], "DAPPER-DASHER"); 
    SetTargetFPS(60);

    //NEBULA , THE ENEMY IN THE GAME!!!!
    Texture2D Nebula = LoadTexture("Textures/12_nebula_spritesheet.png");

    const int SizeOfNebula{10};
    //ARRAY FOR NEBULA!!
    AnimData Nebulae[SizeOfNebula]{ };

    for(int i = 0; i<SizeOfNebula; i++)
    {
        Nebulae[i].rec.height = Nebula.height/8;
        Nebulae[i].rec.width = Nebula.width/8;
        Nebulae[i].rec.y = 0;
        Nebulae[i].rec.x = 0;
        Nebulae[i].pos.y = Windowdimensions[1] - Nebula.height/8;
        Nebulae[i].frame = 0;
        Nebulae[i].RunningTime = 0.0; 
        Nebulae[i].UpdateTime = 1.0/16.0;

        Nebulae[i].pos.x = Windowdimensions[0] + i*300;
    }
    

    float finsihline{ Nebulae[SizeOfNebula - 1 ].pos.x};

    //Nebula velocity 
    int NebulaVel{-200};


    // SCARFY THE MAIN CHARACTER IN THE GAME!!!!!!
    Texture2D scarfy = LoadTexture("Textures/scarfy.png");
    AnimData scarfyData;
    scarfyData.rec.height = scarfy.height;
    scarfyData.rec.width = scarfy.width/6;
    scarfyData.rec.x = 0;
    scarfyData.rec.y = 0;
    scarfyData.pos.x = Windowdimensions[0]/2 - scarfyData.rec.width/2;
    scarfyData.pos.y = Windowdimensions[1] - scarfyData.rec.height;
    scarfyData.frame = 0;
    scarfyData.RunningTime = 0.0;
    scarfyData.UpdateTime = 1.0/12.0 ;
 
    // rectangle dimension 
    int velocity{0};
    // accelaration due to gravity
    int gravity{1000};  //(pixels/seconds)/seconds 
    
    bool IsInAir{};  // rectnagle is in air 
    
    int jumpvel{-600}; // jump velocity 

    //BACKGROUND 
    Texture2D Background = LoadTexture("Textures/far-buildings.png");
    float bgX{};

    Texture2D MidGround = LoadTexture("Textures/back-buildings.png");
    float mgX{};

    Texture2D ForeGround = LoadTexture("Textures/foreground.png");
    float fgX{};
    

    while (WindowShouldClose()==false){

        const float dT{GetFrameTime()};

        

        // start drawing 
        BeginDrawing();
        ClearBackground(WHITE);

        //Update X position for background 
        bgX -= 20 * dT;
        if( bgX <= -Background.width*4)
        {
            bgX = 0.0;
        }

        Vector2 bg1Pos;
        bg1Pos.x = bgX;
        bg1Pos.y = 0.0;
        //DRAW BACKGROUND 
        DrawTextureEx( Background , bg1Pos , 0.0 ,4.0 , WHITE );
        Vector2 bg2Pos;
        bg2Pos.x = bgX + Background.width*4;
        bg2Pos.y = 0.0;
        DrawTextureEx( Background , bg2Pos , 0.0 , 4.0 , WHITE);

        // draw midground
        Vector2 mg1Pos;
        mg1Pos.x = mgX;
        mg1Pos.y = 0.0;
        DrawTextureEx( MidGround , mg1Pos , 0.0 , 4.0 , WHITE);
        Vector2 mg2Pos;
        mg2Pos.x = mgX + MidGround.width*4;
        mg2Pos.y = 0.0;
        DrawTextureEx( MidGround , mg2Pos , 0.0 , 4.0 , WHITE);

        //Update position of midground 
        mgX -= 40 * dT;
        if( mgX <= -MidGround.width*4)
        {
            mgX = 0.0;
        }

        // draw the foreground 
        Vector2 fg1Pos;
        fg1Pos.x = fgX;
        fg1Pos.y = 0.0;
        DrawTextureEx( ForeGround , fg1Pos , 0.0 , 4.0 , WHITE);
        Vector2 fg2Pos;
        fg2Pos.x = fgX + ForeGround.width*4;
        fg2Pos.y = 0.0;
        DrawTextureEx( ForeGround , fg2Pos , 0.0 , 4.0 , WHITE);
        //Update position for foreground 
        fgX -= 80 * dT;
        if( fgX <= -ForeGround.width*4)
        {
            fgX = 0.0;
        }

        // scarfy animation update !!
        if(IsInAir==false)
        {
            scarfyData = UpdateAnimDAta( scarfyData , dT , 5);
        }

        // GROUND CHECK !!!!height
        if (IsOnGround(scarfyData , Windowdimensions[1])){
            velocity = 0;
            IsInAir = false;
        }
        else{
            velocity += gravity * dT;
            IsInAir = true;
        }


        if (IsKeyPressed(KEY_SPACE) && IsInAir==false){
            velocity += jumpvel;
        } 

        for( int i = 0; i <SizeOfNebula; i++ )
        {
            //Nebula animation update
            Nebulae[i].RunningTime += dT;
            if(Nebulae[i].RunningTime >= Nebulae[i].UpdateTime){
                Nebulae[i].RunningTime = i;
                Nebulae[i].rec.x = Nebulae[i].frame * Nebulae[i].rec.width;
                Nebulae[i].frame++;
                if(Nebulae[i].frame > 7){
                    Nebulae[i].frame = i;
                }
            }
        }

        for( int i = 0; i<SizeOfNebula; i++)
        {
            //Nebula moving (updating position of nebula)
            Nebulae[i].pos.x += NebulaVel * dT;
        }

        for(AnimData Nebula : Nebulae)
        {   float pad{50};
            Rectangle Nebrec{
                Nebula.pos.x + pad ,
                Nebula.pos.y + pad , 
                Nebula.rec.width - 2*pad ,
                Nebula.rec.height - 2*pad
            };
            Rectangle scarfyRec{
                scarfyData.pos.x  ,
                scarfyData.pos.y ,
                scarfyData.rec.width,
                scarfyData.rec.height 
            };
            if(CheckCollisionRecs(Nebrec , scarfyRec))
            {
                collision = true;
            }
        }


        //Update finish line            
        finsihline += NebulaVel * dT;
        if(collision)
        {
            //loose the game
            DrawText("GAME OVER", Windowdimensions[0]/3 , Windowdimensions[1]/2 , 40 , WHITE); 
        }
        else if( scarfyData.pos.x >= finsihline)
        {
            // win the game 
            DrawText("YOU WON THE GAME", Windowdimensions[0]/3 , Windowdimensions[1]/2 , 40 , WHITE);
        }
        else
        {
            //update scarfy position 
            scarfyData.pos.y += velocity * dT;
            // draw characters 
            for( int i = 0; i<SizeOfNebula; i++)
            {
                //CREATING NEBULA 
                DrawTextureRec( Nebula , Nebulae[i].rec ,Nebulae[i].pos , WHITE);
            }
            //CRETAING SCARFY THE MAIN CHARATER OF THE GAME (RUNNER)
            DrawTextureRec( scarfy , scarfyData.rec , scarfyData.pos , WHITE);
        }

        //stop drawing 
        EndDrawing();

    }

    UnloadTexture(scarfy);
    UnloadTexture(Nebula);
    UnloadTexture(Background);
    UnloadTexture(MidGround);
    UnloadTexture(ForeGround);
    CloseWindow();
}