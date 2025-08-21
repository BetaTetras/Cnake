#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <conio.h>
#include <time.h>


typedef char* String;

const int X = 5;
const int Y = 5;

struct PARAMETRE{
    int BoolAlive;
    String ReasonOfDeath;

    int Xposition;
    int Yposition;

    int** cnake;

    int Xcoin;
    int Ycoin;

    int Score;

    int** Tab;
};

typedef enum{
    HAUT = 'z',
    BAS = 's',
    GAUCHE = 'q',
    DROITE = 'd',
} Direction;

struct PARAMETRE SetUp();

void DisplayGame(struct PARAMETRE Game);
void DisplayDebug(struct PARAMETRE Game);

struct PARAMETRE refresh(struct PARAMETRE Game);
struct PARAMETRE refreshTail(struct PARAMETRE Game);
struct PARAMETRE InsertNewSize(struct PARAMETRE Game,int X,int Y);

void Color_printf_RED(String Element);
void Color_printf_GREEN(String Element);
void Color_printf_MAGENTA(String Element);

void main(){
    char key;
    struct PARAMETRE Game = SetUp();
    while(1){
        if(kbhit()){
            system("cls");
            key = getch();
            if(key == HAUT){
                Game.Yposition --;
                Game = refresh(Game);
            }else if(key == BAS){
                Game.Yposition ++;
                Game = refresh(Game);
            }else if(key == DROITE){
                Game.Xposition ++;
                Game = refresh(Game);
            }else if(key == GAUCHE){
                Game.Xposition --;
                Game = refresh(Game);
            }else if(key == 27){
                break;
            }
            DisplayDebug(Game);
            DisplayGame(Game);
            if(Game.BoolAlive == 0){
                break;
            }
        }
    }

    system("cls");
    printf("\n\n\n");
    printf("Game over : %s\n",Game.ReasonOfDeath);
    printf("            Score = %d\n",Game.Score);
    printf("\n\n\n");

}

struct PARAMETRE SetUp(){
    int** Tab = (int**)calloc(Y,sizeof(int*));
    int** TabTails = (int**)calloc(X*Y,sizeof(int*));
    
    for(int i=0;i<Y;i++){
        Tab[i] = (int*)calloc(X,sizeof(int));
    }

    for(int i=0;i<Y*X;i++){
        TabTails[i] = (int*)calloc(2,sizeof(int));
    }

    struct PARAMETRE Game;
    Game.BoolAlive = 1;
    Game.ReasonOfDeath = (String)calloc(100,sizeof(char));

    Game.Xposition = 0;
    Game.Yposition = 0;
    Game.Xcoin = X-1;
    Game.Ycoin = Y-1;

    Game.Score = 0;

    Game.Tab = Tab;
    Game.cnake = TabTails;
    
    Game.Tab[Game.Yposition][Game.Xposition] = 1;
    Game.Tab[Game.Ycoin][Game.Xcoin] = 2;
    
    return Game;
}

void DisplayGame(struct PARAMETRE Game){
    printf("\n\nScore [%d]\n",Game.Score);
    for(int i=0;i<Y;i++){
        for(int j=0;j<X;j++){
            if(Game.Tab[i][j] == 0){
                Color_printf_GREEN("[ ]");
            }else if(Game.Tab[i][j] == 1){
                Color_printf_RED("[#]");
            }else if(Game.Tab[i][j] == 2){
                Color_printf_MAGENTA("[x]");
            }else if(Game.Tab[i][j] == 3){
                Color_printf_RED("[x]");
            }
        }
        printf("\n");
    }
    printf("\n\n");
}

void DisplayDebug(struct PARAMETRE Game){
    printf("Position joueur [%d:%d]\n",Game.Yposition,Game.Xposition);
    printf("Position piece [%d:%d]\n",Game.Ycoin,Game.Xcoin);
    printf("Position queue : ");
    for(int i=0;i<Game.Score;i++){
        printf("[%d : %d]   ",Game.cnake[i][0],Game.cnake[i][1]);
    }
    printf("\n\n");
}

struct PARAMETRE refresh(struct PARAMETRE Game){
    srand(time(NULL));

    if(Game.Xposition < 0 ||Game.Xposition == X || Game.Yposition < 0 || Game.Yposition == Y){
        Game.BoolAlive = 0;
        strcpy(Game.ReasonOfDeath,"Tu a toucher les bords ...\n");
    }

    if(Game.Score > 0){
        Game = refreshTail(Game);
    }


    for(int i=0;i<Y;i++){
        for(int j=0;j<X;j++){
            Game.Tab[i][j] = 0;
        }
    }

    for(int i=0;i<Game.Score;i++){
        Game.Tab[Game.cnake[i][0]][Game.cnake[i][1]] = 3;
    }
    Game.Tab[Game.Yposition][Game.Xposition] = 1;

    if(Game.Xposition == Game.Xcoin && Game.Yposition == Game.Ycoin){
        Game = InsertNewSize(Game,Game.Xposition,Game.Yposition);
        Game.Score += 1;
        int BoolValide = 0;
        while(BoolValide == 0){
            Game.Xcoin = rand() % X;
            Game.Ycoin = rand() % Y;
            for(int i=0;i<Game.Score;i++){
                BoolValide = 1;
                if(Game.Xcoin == Game.cnake[i][1] && Game.Ycoin == Game.cnake[i][0]){
                    BoolValide = 0;
                    break;
                }
            }
        }
    }else{
        for(int i=1;i<Game.Score;i++){
            if(Game.cnake[0][0] == Game.cnake[i][0] && Game.cnake[0][1] == Game.cnake[i][1]){
                Game.BoolAlive = 0;
                strcpy(Game.ReasonOfDeath,"tu t'es manger la queue ...\n");
            }
        }
    }

    Game.Tab[Game.Ycoin][Game.Xcoin] = 2;

    return Game;
}

struct PARAMETRE InsertNewSize(struct PARAMETRE Game,int X,int Y){
    int* TabBuffer = (int*)calloc(2,sizeof(int));
    TabBuffer[0] = Y;
    TabBuffer[1] = X;

    int* BufferFirstElement = Game.cnake[0];

    for(int i = Game.Score;i != 0; i --){
        Game.cnake[i+1] = Game.cnake[i];
    }
    Game.cnake[1] = BufferFirstElement;
    Game.cnake[0] = TabBuffer;

    return Game;
}

struct PARAMETRE refreshTail(struct PARAMETRE Game){
    for(int i = Game.Score; i > 0; i--){
        Game.cnake[i][0] = Game.cnake[i-1][0];
        Game.cnake[i][1] = Game.cnake[i-1][1];
    }
    Game.cnake[0][0] = Game.Yposition;
    Game.cnake[0][1] = Game.Xposition;

    return Game;
}

void Color_printf_RED(String Element){printf("\033[1;31m%s\033[0m",Element);}
void Color_printf_GREEN(String Element){printf("\033[1;32m%s\033[0m",Element);}
void Color_printf_MAGENTA(String Element){printf("\033[0;35m%s\033[0m",Element);}