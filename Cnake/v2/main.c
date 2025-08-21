/*
 *           +=====================================================================+
 *           |  ____                      __                    __  __      _      |
 *           | /\  _`\                   /\ \                  /\ \/\ \   /' \     |
 *           | \ \ \/\_\    ___      __  \ \ \/'\      __      \ \ \ \ \ /\_, \    |
 *           |  \ \ \/_/_ /' _ `\  /'__`\ \ \ , <    /'__`\     \ \ \ \ \\/_/\ \   |
 *           |   \ \ \L\ \/\ \/\ \/\ \L\.\_\ \ \\`\ /\  __/      \ \ \_/ \__\ \ \  |
 *           |    \ \____/\ \_\ \_\ \__/.\_\\ \_\ \_\ \____\      \ `\___/\_\\ \_\ |
 *           |     \/___/  \/_/\/_/\/__/\/_/ \/_/\/_/\/____/       `\/__/\/_/ \/_/ |
 *           +=====================================================================+  
 * 
 *           +==================================================+
 *           |                                                  |
 *           |     ██████╗███╗   ██╗ █████╗ ██╗  ██╗███████╗    |
 *           |    ██╔════╝████╗  ██║██╔══██╗██║ ██╔╝██╔════╝    |
 *           |    ██║     ██╔██╗ ██║███████║█████╔╝ █████╗      |
 *           |    ██║     ██║╚██╗██║██╔══██║██╔═██╗ ██╔══╝      |
 *           |    ╚██████╗██║ ╚████║██║  ██║██║  ██╗███████╗    |
 *           |    ╚═════╝╚═╝  ╚═══╝╚═╝  ╚═╝╚═╝  ╚═╝╚══════╝     |
 *           |                                                  |
 *           +==================================================+
 *
 *
 *
*/


/* -=- BIBLIOTHEQUE -=- */
#include <stdio.h>   // Entrer / Sortie terminal 
#include <stdlib.h>  // Malloc,calloc ...
#include <string.h>  // Gestion de string
#include <conio.h>   // Gestion des entrée en continue 
#include <time.h>    // Gestion de l'aleatoire
#include <unistd.h>  // Gestion du Sleep
#include <windows.h> // Gestion terminal

/* -=- DEFINITION DE VARIABLE -=- */
// Definit que les variable char* (Pointeur vers un caractere qui vas étre utilisée comme tableau de caractere) est une String 
typedef char* String;

// Définit un ensemble de variable utilise pour le jeu ...
struct PARAMETRE{
    int BoolAlive;          // Variable booléaine pour savoire si le joueur est en vie 
    String ReasonOfDeath;   // String qui vas étre utlisée pour savoir la raison de la mort

    /* POSTION JOUEUR */
    int Xposition;          // Position X de LA TÊTE du serpent 
    int Yposition;          // Position Y de LA TÊTE du serpent

    /* TABLEAU DE POSITION DE LA QUEUE
     *
     * Pointeur de pointeur d'interger utilisée comme un tableau de tableau d'entier pour la gestion des
     * coordonnée de la queue du serpent
     * Utilisation :
     *  +-------------------------------------------------------------------------------------------------+
     *  |   Index 0   |   Index 1   |   Index 2   |   Index 3   |   Index 4   |   Index x   |  Index Y*X  |
     *  |  0y  |  0x  |  1y  |  1x  |  2y  |  2x  |  3y  |  3x  |  4y  |  4x  |  xy  |  xx  | Y*Xy | Y*Xx |
     *  +-------------------------------------------------------------------------------------------------+
    */
    int** cnake;            

    /* POSTION PIECE */
    int Xcoin;
    int Ycoin;

    /* SCORE */
    int Score;

    /* ESPACE DE JEU 
     *
     * Pointeur de pointeur d'interger utilisée comme un tableau de tableau d'entier qui représente le plateau
     * du jeu
     * 
    */

    int** Tab;
};

// Définit des mouvement et des touches
typedef enum{
    HAUT = 'z',
    BAS = 's',
    GAUCHE = 'q',
    DROITE = 'd',
} Direction;

/* -=- DEFINITION DE CONSTANTE -=- */
const int X = 10; 
const int Y = 10;

/* -=- DEFINITION DES FONCTION -=- */

// Fonction setUp du serpent, du tableau ainsi que des variable utilisée lors du jeu
struct PARAMETRE SetUp();

// Fonction pour cachée le curseur dans le terminal
void HideCursor();

/* DISPLAY */
void DisplayGame(struct PARAMETRE Game);
void DisplayDebug(struct PARAMETRE Game);

/* REFRESH & MODIFICATION */
struct PARAMETRE refresh(struct PARAMETRE Game);
struct PARAMETRE refreshTail(struct PARAMETRE Game);
struct PARAMETRE InsertNewSize(struct PARAMETRE Game,int X,int Y);

/* COLORISATION */
void Color_printf_RED(String Element);
void Color_printf_GREEN(String Element);
void Color_printf_MAGENTA(String Element);

/*##################################################################################################################################################################################################*/

void main(){
    HideCursor(); // On cache le curseur

    char key; // Définition d'un char qui permettra de stockée le caractére entrée 
    char lastDirection = DROITE; // Définition d'un char qui est égal a la derniére direction choisi pour que le serpent puisse avancée tout seul
    struct PARAMETRE Game = SetUp(); // On setUp le serpent ET l'espace de jeu
    while(1){ // Boucle de jeu
        if(kbhit()){ // Si une touche est detecter 
            key = getch(); // La touche est = la variable de key
            
            // Si la touche est valide alors lastDirection est = key pour stocket la dernier direction
            if(key == HAUT || key == BAS || key == GAUCHE || key == DROITE){
                lastDirection = key;
            }else if(key == 27){
                break;
            }
        }

        // Direction selon la valeur de key
        switch(key){
            case HAUT:
                Game.Yposition --;
                Game = refresh(Game);
            break;

            case BAS:
                Game.Yposition ++;
                Game = refresh(Game);
            break;

            case GAUCHE:
                Game.Xposition --;
                Game = refresh(Game);
            break;

            case DROITE:
                Game.Xposition ++;
                Game = refresh(Game);
            break;
        }

        printf("\033[H"); // remet le curseur en haut à gauche pour eviter de clear tout le terminal 
        // DisplayDebug(Game); // Fonction DEBUG
        DisplayGame(Game); // Affichage  de la partie 
        if(Game.BoolAlive == 0){ // Si le joueur est toujour vivent = continuer 
            break;
        }
        Sleep(150); // Pause de 150ms
    }

    system("cls"); // Netoyage du terminal pour affichage final
    printf("\n\n\n");
    printf("Game over : %s\n",Game.ReasonOfDeath); // Affichage de la raison du game over 
    printf("            Score = %d\n",Game.Score); // Affichage du score 
    printf("\n\n\n");
    printf("PRESS ENTER > "); // Pause pour pouvoir voir le resultat
    String Buffer;
    fgets(Buffer,100,stdin);
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
    printf("Score [%d]\n\n",Game.Score);
    for(int i=0;i<Y;i++){
        for(int j=0;j<X;j++){
            if(Game.Tab[i][j] == 0){
                Color_printf_GREEN("[ ]");
            }else if(Game.Tab[i][j] == 1){
                Color_printf_RED("[#]");
            }else if(Game.Tab[i][j] == 2){
                Color_printf_MAGENTA("[@]");
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

    if(Game.Xposition < 0 || Game.Xposition >= X || Game.Yposition < 0 || Game.Yposition >= Y){
        Game.BoolAlive = 0;
        strcpy(Game.ReasonOfDeath,"Tu a toucher les bords ...\n");
        return Game;
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
                return Game;
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


void HideCursor() {
    HANDLE consoleHandle = GetStdHandle(STD_OUTPUT_HANDLE);
    CONSOLE_CURSOR_INFO info;
    info.dwSize = 100;
    info.bVisible = FALSE;  // FALSE = cache le curseur
    SetConsoleCursorInfo(consoleHandle, &info);
}

void Color_printf_RED(String Element){printf("\033[1;31m%s\033[0m",Element);}
void Color_printf_GREEN(String Element){printf("\033[1;32m%s\033[0m",Element);}
void Color_printf_MAGENTA(String Element){printf("\033[0;35m%s\033[0m",Element);}