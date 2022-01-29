#include<stdio.h>
#include<stdlib.h>
#include<conio.h>
#include<time.h>
#include<Windows.h>
#include<string>
#define BHEIGHT 16
#define BWIDTH 10
int gameBoard[BHEIGHT][BWIDTH], pieceA[2],pieceB[2],pieceC[2],pieceD[2], numRows, bottomLocations[4][2], bottomRow, matrixMovementRotation[4][4], blockID, pointsOfMatrix[2][2];
bool gameState=true, collidedNextChance=false;

void init ();
void printGameboard ();
void spawnBlock();
void moveDirection(bool dir);
void renderBlocks(int val);
void checkLineComplete();
void rotateMatrix();
void getMatrix();
void updatePositions(int a, int b, int c, int d, int a2, int b2, int c2, int d2);
void checkGameOver();
void checkGameOver()
{
    for(int j=0; j!=BWIDTH; j++)
    {
        if(gameBoard[2][j]==1)
        {
            gameState=false;
            break;

        }
    }
}
void getMatrix()
{
    for(int i=pointsOfMatrix[0][1]; i<=pointsOfMatrix[1][1]; i++)
    {
        for(int j=pointsOfMatrix[0][0]; j<=pointsOfMatrix[1][0]; j++)
        {

            if(i>=0 && j>=0)
            {
                matrixMovementRotation[i-pointsOfMatrix[0][1]][j-pointsOfMatrix[0][0]]=gameBoard[i][j];

            }
            else
            {
                matrixMovementRotation[i-pointsOfMatrix[0][1]][j-pointsOfMatrix[0][0]]=7;
            }
        }
    }


}
void rotateMatrix()
{


    if(blockID!=0)
    {
        int extraVar, newMatrix[4][4];
        getMatrix();
        bool state=false;
        int counter=0;
        extraVar=newMatrix[0][0];
        newMatrix[0][0]=matrixMovementRotation[3][0];
        //newMatrix[0][0]=newMatrix[1][0];
        newMatrix[0][1]=matrixMovementRotation[2][0];
        newMatrix[0][2]=matrixMovementRotation[1][0];
        newMatrix[0][3]=matrixMovementRotation[0][0];
        newMatrix[1][3]=matrixMovementRotation[0][1];
        newMatrix[2][3]=matrixMovementRotation[0][2];
        newMatrix[3][3]=matrixMovementRotation[0][3];

        newMatrix[3][2]=matrixMovementRotation[1][3];
        newMatrix[3][1]=matrixMovementRotation[2][3];
        newMatrix[3][0]=matrixMovementRotation[3][3];
        newMatrix[2][0]=matrixMovementRotation[3][2];
        newMatrix[1][0]=matrixMovementRotation[3][1];
        newMatrix[1][1]=matrixMovementRotation[2][1];
        newMatrix[2][1]=matrixMovementRotation[2][2];
        newMatrix[2][2]=matrixMovementRotation[1][2];
        newMatrix[1][2]=matrixMovementRotation[1][1];
        for(int i=0; i!=4; i++)
        {
            for(int j=0; j!=4; j++)
            {
                if(newMatrix[i][j]+matrixMovementRotation[i][j]==9)
                {
                    state=true;
                    break;
                }

            }
            if(state)
            {
                break;
            }
        }
        if(!state)
        {
            bottomLocations[0][0]=-1;
            bottomLocations[0][1]=-1;
            bottomLocations[1][0]=-1;
            bottomLocations[1][1]=-1;
            bottomLocations[2][0]=-1;
            bottomLocations[2][1]=-1;
            bottomLocations[3][0]=-1;
            bottomLocations[3][1]=-1;

            for(int i=pointsOfMatrix[0][1]; i<=pointsOfMatrix[1][1]; i++)
            {
                for(int j=pointsOfMatrix[0][0]; j<=pointsOfMatrix[1][0]; j++)
                {
                    if(newMatrix[i-pointsOfMatrix[0][1]][j-pointsOfMatrix[0][0]]==2)
                    {
                        bottomLocations[j-pointsOfMatrix[0][0]][0]=j;
                        bottomLocations[j-pointsOfMatrix[0][0]][1]=i;
                        if(counter==0)
                        {
                            pieceA[0]=i;
                            pieceA[1]=j;
                        }
                        if(counter==1)
                        {
                            pieceB[0]=i;
                            pieceB[1]=j;
                        }
                        if(counter==2)
                        {
                            pieceC[0]=i;
                            pieceC[1]=j;
                        }
                        if(counter==3)
                        {
                            pieceD[0]=i;
                            pieceD[1]=j;
                        }
                        counter+=1;
                    }
                    if(newMatrix[i-pointsOfMatrix[0][1]][j-pointsOfMatrix[0][0]]!=7)
                    {
                        gameBoard[i][j]=newMatrix[i-pointsOfMatrix[0][1]][j-pointsOfMatrix[0][0]];
                    }
                    else
                    {
                        gameBoard[i][j]=0;
                    }
                }
            }
        }

    }
}
void updatePositions(int a, int b, int c, int d, int a2, int b2, int c2, int d2)
{
    pieceA[1]=a,pieceA[0]=a2;
    pieceB[1]=b,pieceB[0]=b2;
    pieceC[1]=c,pieceC[0]=c2;
    pieceD[1]=d,pieceD[0]=d2;

}
void moveDirection(bool dir)
{
    if(dir)
    {
        if(BWIDTH-1-pieceA[1] && BWIDTH-1-pieceB[1] && BWIDTH-1-pieceC[1] && BWIDTH-1-pieceD[1])
        {
            if(gameBoard[pieceA[0]][pieceA[1]+1]!=1 && gameBoard[pieceB[0]][pieceB[1]+1]!=1 && gameBoard[pieceC[0]][pieceC[1]+1]!=1 && gameBoard[pieceD[0]][pieceD[1]+1]!=1)
            {
                renderBlocks(0);
                pieceA[1]+=1;
                pieceB[1]+=1;
                pieceC[1]+=1;
                pieceD[1]+=1;
                for(int i=0; i!=4; i++)
                {
                    if (bottomLocations[i][0]!=-1)
                    {
                        bottomLocations[i][0]+=1;
                    }
                }
                pointsOfMatrix[0][0]+=1;
                pointsOfMatrix[1][0]+=1;
            }
        }

    }
    else
    {
        if(pieceA[1] && pieceB[1] && pieceC[1] && pieceD[1])
        {
            if(gameBoard[pieceA[0]][pieceA[1]-1]!=1 && gameBoard[pieceB[0]][pieceB[1]-1]!=1 && gameBoard[pieceC[0]][pieceC[1]-1]!=1 && gameBoard[pieceD[0]][pieceD[1]-1]!=1)
            {
                renderBlocks(0);
                pieceA[1]-=1;
                pieceB[1]-=1;
                pieceC[1]-=1;
                pieceD[1]-=1;
                for(int i=0; i!=4; i++)
                {
                    if (bottomLocations[i][0]!=-1)
                    {
                        bottomLocations[i][0]-=1;
                    }
                }
                pointsOfMatrix[0][0]-=1;
                pointsOfMatrix[1][0]-=1;
            }
        }
    }
}
void checkLineComplete()
{
    int top_row=0, i=BHEIGHT,pq;
    bool lineComplete=true, debug=false;
    while(i>=top_row)
    {
        i--;
        lineComplete=true;
        for(int j=0; j!=BWIDTH; j++)
        {
            pq=i;
            if(gameBoard[i][j]==0)
            {
                lineComplete=false;
                break;
            }
        }
        if(lineComplete)
        {
            top_row+=1;
            i=BHEIGHT;
            for(int i=pq; i!=0; i--)
            {
                for(int j=0; j!=BWIDTH; j++)
                {
                    if(gameBoard[i-1][j]!=2)
                    {
                        gameBoard[i][j]=gameBoard[i-1][j];
                    }
                }
            }
        }
    }
}
void init()
{
    for(int i=0; i!=BHEIGHT-1; i++)
    {
        for(int j=0; j!=BWIDTH; j++)
        {
            gameBoard[i][j]=0;
        }
    }
    for(int j=0; j!=BWIDTH; j++)
    {
        gameBoard[BHEIGHT-1][j]=1;
    }
}
void renderBlocks(int val)
{
    gameBoard[pieceA[0]][pieceA[1]]=val;
    gameBoard[pieceB[0]][pieceB[1]]=val;
    gameBoard[pieceC[0]][pieceC[1]]=val;
    gameBoard[pieceD[0]][pieceD[1]]=val;
}
void spawnBlock()
{
    srand(time(0));
    blockID=rand()%5;
    switch(blockID)
    {
    case 0:
        /*This case represents the square block*/
        pointsOfMatrix[0][0]=3, pointsOfMatrix[0][1]=-1;
        pointsOfMatrix[1][0]=6, pointsOfMatrix[1][1]=2;
        pieceA[1]=4,pieceA[0]=0;
        pieceB[1]=5,pieceB[0]=0;
        pieceC[1]=4,pieceC[0]=1;
        pieceD[1]=5,pieceD[0]=1;
        bottomRow=1;
        bottomLocations[0][0]=-1;
        bottomLocations[0][1]=-1;
        bottomLocations[1][0]=4;
        bottomLocations[1][1]=1;
        bottomLocations[2][0]=5;
        bottomLocations[2][1]=1;
        bottomLocations[3][0]=-1;
        bottomLocations[3][1]=-1;
        renderBlocks(2);
        break;
    case 1:
        pointsOfMatrix[0][0]=3, pointsOfMatrix[0][1]=-1;
        pointsOfMatrix[1][0]=6, pointsOfMatrix[1][1]=2;
        pieceA[1]=3,pieceA[0]=0;
        pieceB[1]=4,pieceB[0]=0;
        pieceC[1]=5,pieceC[0]=0;
        pieceD[1]=6,pieceD[0]=0;
        bottomRow=1;
        bottomLocations[0][0]=3;
        bottomLocations[0][1]=0;
        bottomLocations[1][0]=4;
        bottomLocations[1][1]=0;
        bottomLocations[2][0]=5;
        bottomLocations[2][1]=0;
        bottomLocations[3][0]=6;
        bottomLocations[3][1]=0;
        renderBlocks(2);
        break;
    case 2:
        pointsOfMatrix[0][0]=3, pointsOfMatrix[0][1]=-1;
        pointsOfMatrix[1][0]=6, pointsOfMatrix[1][1]=2;
        pieceA[1]=4,pieceA[0]=0;
        pieceB[1]=5,pieceB[0]=0;
        pieceC[1]=5,pieceC[0]=1;
        pieceD[1]=6,pieceD[0]=1;
        bottomRow=1;
        bottomLocations[0][0]=-1;
        bottomLocations[0][1]=-1;
        bottomLocations[1][0]=4;
        bottomLocations[1][1]=0;
        bottomLocations[2][0]=5;
        bottomLocations[2][1]=1;
        bottomLocations[3][0]=6;
        bottomLocations[3][1]=1;
        renderBlocks(2);
        break;
    case 3:
        pointsOfMatrix[0][0]=3, pointsOfMatrix[0][1]=-1;
        pointsOfMatrix[1][0]=6, pointsOfMatrix[1][1]=2;
        pieceA[1]=6,pieceA[0]=0;
        pieceB[1]=5,pieceB[0]=0;
        pieceC[1]=5,pieceC[0]=1;
        pieceD[1]=4,pieceD[0]=1;
        bottomRow=1;
        bottomLocations[0][0]=-1;
        bottomLocations[0][1]=-1;
        bottomLocations[1][0]=6;
        bottomLocations[1][1]=0;
        bottomLocations[2][0]=5;
        bottomLocations[2][1]=1;
        bottomLocations[3][0]=4;
        bottomLocations[3][1]=1;
        renderBlocks(2);
        break;
    case 4:
        pointsOfMatrix[0][0]=3, pointsOfMatrix[0][1]=-1;
        pointsOfMatrix[1][0]=6, pointsOfMatrix[1][1]=2;
        pieceA[1]=6,pieceA[0]=0;
        pieceB[1]=5,pieceB[0]=0;
        pieceC[1]=5,pieceC[0]=1;
        pieceD[1]=4,pieceD[0]=0;
        bottomRow=1;
        bottomLocations[0][0]=-1;
        bottomLocations[0][1]=-1;
        bottomLocations[1][0]=6;
        bottomLocations[1][1]=0;
        bottomLocations[2][0]=5;
        bottomLocations[2][1]=1;
        bottomLocations[3][0]=4;
        bottomLocations[3][1]=0;
        renderBlocks(2);
        break;

    }
}
bool calculateCollision()
{
    bool isCollisionDetected=false;
    for(int i=0; i!=4; i++)
    {
        if(bottomLocations[i][0]!=-1)
        {
            if(gameBoard[bottomLocations[i][1]+1][bottomLocations[i][0]]==1 || bottomLocations[i][1]>=BHEIGHT-1)
            {
                isCollisionDetected=true;
                break;
            }
        }
    }
    if(isCollisionDetected)
    {
        collidedNextChance=true;
    }
    return isCollisionDetected;
}
void moveDown()
{
    renderBlocks(0);
    for(int i=0; i!=4; i++)
    {
        if(bottomLocations[i][0]!=-1)
        {
            bottomLocations[i][1]+=1;
        }
    }
    pieceA[0]+=1;
    pieceB[0]+=1;
    pieceC[0]+=1;
    pieceD[0]+=1;
    pointsOfMatrix[0][1]+=1;
    pointsOfMatrix[1][1]+=1;
}
void printGameboard()
{
    printf("__________");
    for(int i=0; i!=BHEIGHT; i++)
    {
        for(int j=0; j!=BWIDTH; j++)
        {
            if(gameBoard[i][j]==2 || gameBoard[i][j]==1)
            {
                printf("O");
            }
            else
            {
                printf(" ");
            }

        }
        if(i!=BHEIGHT-1)
        {
            printf("|\n|");
        }
        else
        {
            printf("|\n");
        }

    }
    printf(" ¯¯¯¯¯¯¯¯¯¯");
}
int main()
{
    std::string anim1="Hey, there! Press any key to continue";
    char c=_getch();
    if(c!='N')
    {
        for(int i=0; i!=anim1.length(); i++)
        {
            printf("%c",anim1[i]);
            Sleep(100);
        }
        _getch();
        system("cls");
        FILE *fptr;
        fptr=fopen("final.txt", "r");
        c = fgetc(fptr);
        while (c != EOF)
        {
            printf ("%c", c);
            c = fgetc(fptr);
        }

        fclose(fptr);
        _getch();
        system("cls");
        anim1="@<aP-10 'g; [wgwefq. I think 51^9;  my systasd135em'dass been hackeasd. BEAT THIS BOSS AND HELP MEEE!";
        for(int i=0; i!=anim1.length(); i++)
        {
            printf("%c",anim1[i]);
            Sleep(100);
        }
        _getch();
    }
    init();
    spawnBlock();
    checkLineComplete();
    int x=0;
    bool keyWasPressed=false;
    while(gameState==true)
    {
        x=0;
        while(x<=500)
        {
            if(GetKeyState('A') & 0x8000)
            {
                /*Checks if key was being pressed even in the last frame*/
                checkGameOver();
                if(!keyWasPressed)
                {
                    keyWasPressed=true;
                    moveDirection(false);
                }

            }
            else if(GetKeyState('D') & 0x8000)
            {
                /*Checks if key was being pressed even in the last frame*/
                checkGameOver();
                if(!keyWasPressed)
                {
                    keyWasPressed=true;
                    moveDirection(true);
                }

            }
            else if(GetKeyState('S') & 0x8000)
            {
                /*Checks if key was being pressed even in the last frame*/
                if(!keyWasPressed)
                {
                    renderBlocks(2);
                    keyWasPressed=true;
                    bool zx=calculateCollision();
                    checkGameOver();
                    if(zx!=true)
                    {
                        moveDown();
                    }
                }

            }
            else if(GetKeyState('R') & 0x8000)
            {
                /*Checks if key was being pressed even in the last frame*/
                checkGameOver();
                if(!keyWasPressed)
                {
                    keyWasPressed=true;
                    rotateMatrix();
                }

            }
            else
            {
                /*Sets the variable false as the key was not pressed this time*/
                keyWasPressed=false;
            }
            x+=1;
            Sleep(1);
            if(x%17==0)
            {
                if(collidedNextChance)
                {
                    renderBlocks(1);
                    checkGameOver();
                    spawnBlock();
                    checkLineComplete();
                    collidedNextChance=false;
                }
                system("cls");
                renderBlocks(2);
                printGameboard();
            }
            if(x%40==0)
            {
                bool zx=calculateCollision();
                if(zx!=true)
                {
                    moveDown();
                }
            }
        }
        if(x<=500)
        {
            Sleep(501-x);
        }
        if(!gameState)
        {
            break;
        }
    }
    system("cls");
    printf("GAME OVER");
}
