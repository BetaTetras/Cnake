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
 *           +=======================================================================+
 *           |                                                                       |
 *           |    ██████╗███╗   ██╗ █████╗ ██╗  ██╗███████╗    ██╗   ██╗  ██████╗    |
 *           |   ██╔════╝████╗  ██║██╔══██╗██║ ██╔╝██╔════╝    ██║   ██║  ╚════██╗   |
 *           |   ██║     ██╔██╗ ██║███████║█████╔╝ █████╗      ██║   ██║   █████╔╝   |
 *           |   ██║     ██║╚██╗██║██╔══██║██╔═██╗ ██╔══╝      ╚██╗ ██╔╝   ╚═══██╗   |
 *           |   ╚██████╗██║ ╚████║██║  ██║██║  ██╗███████╗     ╚████╔╝██╗██████╔╝   | 
 *           |   ╚═════╝╚═╝  ╚═══╝╚═╝  ╚═╝╚═╝  ╚═╝╚══════╝      ╚═══╝ ╚═╝╚═════╝     |
 *           |                                                                       |
 *           +=======================================================================+
 * 
 *        +==============================================+
 *        |                                              |
 *        |    .o88b. d8b   db  .d8b.  db   dD d88888b   |
 *        |   d8P  Y8 888o  88 d8' `8b 88 ,8P' 88'       |
 *        |   8P      88V8o 88 88ooo88 88,8P   88ooooo   |
 *        |   8b      88 V8o88 88~~~88 88`8b   88~~~~~   |
 *        |   Y8b  d8 88  V888 88   88 88 `88. 88.       |
 *        |    `Y88P' VP   V8P YP   YP YP   YD Y88888P   |
 *        |                                              |
 *        +==============================================+                                                         
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
#include <wchar.h>   // ACII étendu

/* -=- DEFINITION DE VARIABLE -=- */
// Definit que les variable char* (Pointeur vers un caractere qui vas étre utilisée comme tableau de caractere) est une String 
typedef char* String;
typedef wchar_t* WString;

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
     * ╔═════════════╦═════════════╦═════════════╦═════════════╦═════════════╦═════════════╦═════════════╗
     * ║   INDEX 0   ║   INDEX 1   ║   INDEX 2   ║   INDEX 3   ║   INDEX 4   ║   INDEX X   ║  INDEX Y*N  ║
     * ╠══════╦══════╬══════╦══════╬══════╦══════╬══════╦══════╬══════╦══════╬══════╦══════╬══════╦══════╣
     * ║  0y  ║  0x  ║  0y  ║  0x  ║  0y  ║  0x  ║  0y  ║  0x  ║  0y  ║  0x  ║  0y  ║  0x  ║  0y  ║  0x  ║
     * ╚══════╩══════╩══════╩══════╩══════╩══════╩══════╩══════╩══════╩══════╩══════╩══════╩══════╩══════╝
     * 
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

/* -=- UI -=- */
void Game();
void Information();
void EasterEggs();

/* -=- DEFINITION DE CONSTANTE -=- */
const int X = 5; 
const int Y = 5;

/* -=- DEFINITION DES FONCTION -=- */

// Fonction setUp du serpent, du tableau ainsi que des variable utilisée lors du jeu
struct PARAMETRE SetUp();

// Fonction pour cachée le curseur dans le terminal
void HideCursor();
void gotoxy(int x, int y);

/* DISPLAY */
void DisplayGame(struct PARAMETRE Game);
void DisplayDebug(struct PARAMETRE Game);

int TerminalUi(int Ystart,int n,...);

/* REFRESH & MODIFICATION */
struct PARAMETRE refresh(struct PARAMETRE Game);
struct PARAMETRE refreshTail(struct PARAMETRE Game);
struct PARAMETRE InsertNewSize(struct PARAMETRE Game,int X,int Y);

/* COLORISATION */
void printf_RED(String Text,...);
void printf_GREEN(String Text,...);
void printf_BLUE(String Text,...);

void printf_MAGENTA(String Text,...);

/*##################################################################################################################################################################################################*/

int main(){
    HideCursor(); // On cache le curseur
    int choix;

    while(1){
        system("cls");
        printf_GREEN("        +==============================================+\n");
        printf_GREEN("        |                                              |\n");
        printf_GREEN("        |    .o88b. d8b   db  .d8b.  db   dD d88888b   |\n");
        printf_GREEN("        |   d8P  Y8 888o  88 d8' `8b 88 ,8P' 88'       |\n");
        printf_GREEN("        |   8P      88V8o 88 88ooo88 88,8P   88ooooo   |\n");
        printf_GREEN("        |   8b      88 V8o88 88~~~88 88`8b   88~~~~~   |\n");
        printf_GREEN("        |   Y8b  d8 88  V888 88   88 88 `88. 88.       |\n");
        printf_GREEN("        |    `Y88P' VP   V8P YP   YP YP   YD Y88888P   |\n");
        printf_GREEN("        |                                              |\n");
        printf_GREEN("        +==============================================+");
        printf("\n\n");
        printf_GREEN("-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-\n");
        choix = TerminalUi(13,3,"Jouer","Information","Quitter");

        switch (choix)
        {
        case 1:
            Game();
        break;
        
        case 2:
            Information();
        break;

        case 3:
            return 0;
        break;
        }
    }

}

void Information(){
    system("cls");

    printf_GREEN("-=-=-=-=-=-=-=-=-=-=-=-=-=- INFORMATION -=-=-=-=-=-=-=-=-=-=-=-=-=-\n\n");
    printf_GREEN("Cnake est un mini-jeu programmee en C par Gregoire GIBRAT!\n\n");
    printf_GREEN("Version Cnake : ");printf_RED("v3\n\n");
    printf_GREEN("Code source : ");printf_RED("????????????????\n\n");
    printf_GREEN("-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-\n\n");
    printf_RED("PRESS ENTER > ");
    String Buffer = (String)calloc(10,sizeof(char));
    fgets(Buffer,100,stdin);
    if(strcmp(Buffer,"Snake!") == 0){
        EasterEggs();
    }
    free(Buffer);
}

void EasterEggs(){
    system("cls");
    printf_GREEN("Dit bonjour a Miia !\n\n");

    printf_RED("    --..,_                     _,.--.              \n");
    printf_RED("       `'.'.                .'`__ o  `;__.         \n");
    printf_RED("          '.'.            .'.'`  '---'`  `         \n");
    printf_RED("            '.`'--....--'`.'                       \n");
    printf_RED("              `'--....--'`                         \n\n\n");
    printf_GREEN("PRESS ENTER > ");
    String Buffer = (String)calloc(10,sizeof(char));
    fgets(Buffer,100,stdin);
    free(Buffer);

}

// ##############################################################################################################################################################################################

void Game(){
    system("cls");
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
        Sleep(250); // Pause de 150ms
    }

    system("cls"); // Netoyage du terminal pour affichage final
    printf("\n\n\n");
    printf("Game over : %s\n",Game.ReasonOfDeath); // Affichage de la raison du game over 
    printf("            Score = %d\n",Game.Score); // Affichage du score 
    printf("\n\n\n");
    printf("PRESS ENTER > "); // Pause pour pouvoir voir le resultat
    String Buffer = (String)calloc(10,sizeof(char));
    fgets(Buffer,100,stdin);
    free(Buffer);
}

struct PARAMETRE SetUp(){

    // SetUp de l'espace de jeu
    int** Tab = (int**)calloc(Y,sizeof(int*));
    int** TabTails = (int**)calloc(X*Y,sizeof(int*));
    
    // Affectation de tout les colonne
    for(int i=0;i<Y;i++){
        Tab[i] = (int*)calloc(X,sizeof(int));
    }

    // SetUp de la queue du sepent 
    for(int i=0;i<Y*X;i++){
        TabTails[i] = (int*)calloc(2,sizeof(int));
    }

    // Def des variable de base des paramétre de jeu
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
    
    // Définition de la position de base du joueur et des piece
    Game.Tab[Game.Yposition][Game.Xposition] = 1;
    Game.Tab[Game.Ycoin][Game.Xcoin] = 2;
    
    return Game;
}

/* AFFICHAGE DE LA ZONE DE JEU */
void DisplayGame(struct PARAMETRE Game){
    // Affiche le score
    printf("Score [%d]\n\n",Game.Score);
    // Pour tout les colonne ...
    for(int i=0;i<Y;i++){
        // Pour chaque élément d'une ligne ...
        for(int j=0;j<X;j++){
            if(Game.Tab[i][j] == 0){       // Vide = 0
                printf_GREEN("[ ]");
            }else if(Game.Tab[i][j] == 1){ // Position joueur = 1
                printf_RED("[#]");
            }else if(Game.Tab[i][j] == 2){ // Position piéce = 2
                printf_MAGENTA("[@]");
            }else if(Game.Tab[i][j] == 3){ // Position queue serpent = 3
                printf_RED("[x]");
            }
        }
        printf("\n");
    }
    printf("\n\n");
}

/* FONCTION DEBUG D'AFFICHAGE D'INFORMATION */
void DisplayDebug(struct PARAMETRE Game){
    // Fonction DEBUG pour avoir des info suplémentaire
    printf("Position joueur [%d:%d]\n",Game.Yposition,Game.Xposition);
    printf("Position piece [%d:%d]\n",Game.Ycoin,Game.Xcoin);
    printf("Position queue : ");
    for(int i=0;i<Game.Score;i++){
        printf("[%d : %d]   ",Game.cnake[i][0],Game.cnake[i][1]);
    }
    printf("\n\n");
}

/* FONCTION DE RAFRAICHISSEMENT DU GAMPLAY */
struct PARAMETRE refresh(struct PARAMETRE Game){
    srand(time(NULL));

    if(Game.Xposition < 0 || Game.Xposition >= X || Game.Yposition < 0 || Game.Yposition >= Y){ // Si la tête du joueur depasse la zone du jeu alors GAME OVER
        Game.BoolAlive = 0;
        strcpy(Game.ReasonOfDeath,"Tu a toucher les bords ...\n");
        return Game;
    }

    
    if(Game.Score > 0){ // Si le score est supérieure a 0 (donc que le joueur a récupérer au moins une piéce)
        // On refresh la queu du serpent
        Game = refreshTail(Game);
    }

    // Réinitialisation de la zone de jeu
    for(int i=0;i<Y;i++){
        for(int j=0;j<X;j++){
            Game.Tab[i][j] = 0;
        }
    }

    // Positionnement de la queue du serpent 
    for(int i=0;i<Game.Score;i++){
        Game.Tab[Game.cnake[i][0]][Game.cnake[i][1]] = 3;
    }
    // Positionnement du joueur 
    Game.Tab[Game.Yposition][Game.Xposition] = 1;

    if(Game.Xposition == Game.Xcoin && Game.Yposition == Game.Ycoin){ // Si la position du joueur est = a la position de la piéce alors ...
        // On ajoute une valeur au tableau de la queue du seprent 
        Game = InsertNewSize(Game,Game.Xposition,Game.Yposition);
        // On ajoute 1 au score 
        Game.Score += 1;
        
        // Replacage de la piece dans l'espace de jeu
        int BoolValide = 0;
        while(BoolValide == 0){ // Tant que l'emplacement de la piece n'est pas valide faire ...
            Game.Xcoin = rand() % X; // Génére une valeur X
            Game.Ycoin = rand() % Y; // Génére une valeur Y
            for(int i=0;i<Game.Score;i++){ // Vérifie si les coordonnée chevauche la queue 
                BoolValide = 1;
                if(Game.Xcoin == Game.cnake[i][1] && Game.Ycoin == Game.cnake[i][0]){
                    BoolValide = 0;
                    break;
                }
            }
        }
    }else{
        for(int i=1;i<Game.Score;i++){ // Si le seprent rentre en contacte avec ca queu alors GAME OVER 
            if(Game.cnake[0][0] == Game.cnake[i][0] && Game.cnake[0][1] == Game.cnake[i][1]){
                Game.BoolAlive = 0;
                strcpy(Game.ReasonOfDeath,"tu t'es manger la queue ...\n");
                return Game;
            }
        }
    }

    // Nouvelle coordonnée de la pièce
    Game.Tab[Game.Ycoin][Game.Xcoin] = 2;

    return Game;
}

/* FONCTION D'INSERTION DE COORDONNER DANS LE TABLEAU DE COORDONNER DE LA QUEUE DU SERPENT */
struct PARAMETRE InsertNewSize(struct PARAMETRE Game,int X,int Y){
    int* TabBuffer = (int*)calloc(2,sizeof(int)); // Tableau buffer
    
    // Index 0 est égal a la valeur Y mis en entrée 
    TabBuffer[0] = Y; 

    // Index 1 est égalt a la valeur de X mis en entrée
    TabBuffer[1] = X;

    // On crée un buffer pour stocket la premier valeur du tableau pour plus tard
    int* BufferFirstElement = Game.cnake[0];

    // On décale toute les valeur pour faire de la place a la nouvelle valeur
    for(int i = Game.Score;i != 0; i --){
        Game.cnake[i+1] = Game.cnake[i];
    }
    // Le deuxiéme élément du tableau est l'ancien premier élément
    Game.cnake[1] = BufferFirstElement;
    // Le premier élément est le nouvelle élément crée plus tot
    Game.cnake[0] = TabBuffer;

    return Game;
}

/* FONCTION DE RAFRECHISSEMENT DE LA QUEUE POUR TOUJOUR AVOIR X-n et Y-n */
struct PARAMETRE refreshTail(struct PARAMETRE Game){
    for(int i = Game.Score; i > 0; i--){
        Game.cnake[i][0] = Game.cnake[i-1][0];
        Game.cnake[i][1] = Game.cnake[i-1][1];
    }
    Game.cnake[0][0] = Game.Yposition;
    Game.cnake[0][1] = Game.Xposition;

    return Game;
}

// ##############################################################################################################################################################################################

/* FONCTION UI POUR AVOIR LE MENU A BOUTON */
int TerminalUi(int Ystart,int n,...){
    va_list Args;
    va_start(Args,n);
    String* TabString = (String*)calloc(n,sizeof(String));

    for(int i=0;i<n;i++){
        String Buffer = va_arg(Args,String);
        TabString[i] = Buffer;
    }
    va_end(Args);

    char key;
    int choix = 0;

    for (int i = 0; i < n; i++) {
        gotoxy(0, Ystart + i * 2);
        if (i == choix) {
            printf_RED("> ");
            printf_GREEN("[");
            printf_BLUE("%d", i + 1);
            printf_GREEN("] - %s                        ", TabString[i]);
        } else {
            printf_GREEN(" [");
            printf_BLUE("%d", i + 1);
            printf_GREEN("] - %s                        ", TabString[i]);
        }
    }

    while (1) {
        if (kbhit()) {
            key = getch();

            // Efface l'ancienne sélection
            gotoxy(0, Ystart + choix * 2);
            printf_GREEN(" [");
            printf_BLUE("%d", choix + 1);
            printf_GREEN("] - %s                        ", TabString[choix]);

            if (key == HAUT && choix > 0)
                choix--;
            else if (key == BAS && choix < n - 1)
                choix++;
            else if (key == 13)
                return choix + 1;

            // Dessine la nouvelle sélection
            gotoxy(0, Ystart + choix * 2);
            printf_RED("> ");
            printf_GREEN("[");
            printf_BLUE("%d", choix + 1);
            printf_GREEN("] - %s                        ", TabString[choix]);
        }
        Sleep(30);
    }

    return -1;
}

// ##############################################################################################################################################################################################

/* PRINTF VERSION COLORER */
void printf_GREEN(String Text,...){
    va_list Args;
    va_start(Args,Text);

    for(int i=0;i<strlen(Text);i++){
        if(Text[i] == '%'){
            if(Text[i+1] == 'd'){
                int _int = va_arg(Args,int);
                printf("\033[1;32m%d\033[0m",_int);
                i ++;
            }else if(Text[i+1] == 'f'){
                double _double = va_arg(Args,double);
                printf("\033[1;32m%f\033[0m",_double);
                i ++;
            }else if(Text[i+1] == 's'){
                String _String = va_arg(Args,String);
                printf("\033[1;32m%s\033[0m",_String);
                i ++;
            }else if(Text[i+1] == 'c'){
                int _char = va_arg(Args,int);
                printf("\033[1;32m%c\033[0m",_char);
                i++;
            }
        }else{
            printf("\033[1;32m%c\033[0m",Text[i]);
        }
    }

    va_end(Args);
}

void printf_BLUE(String Text,...){
    va_list Args;
    va_start(Args,Text);

    for(int i=0;i<strlen(Text);i++){
        if(Text[i] == '%'){
            if(Text[i+1] == 'd'){
                int _int = va_arg(Args,int);
                printf("\033[1;34m%d\033[0m",_int);
                i ++;
            }else if(Text[i+1] == 'f'){
                double _double = va_arg(Args,double);
                printf("\033[1;34m%f\033[0m",_double);
                i ++;
            }else if(Text[i+1] == 's'){
                String _String = va_arg(Args,String);
                printf("\033[1;34m%s\033[0m",_String);
                i ++;
            }else if(Text[i+1] == 'c'){
                int _char = va_arg(Args,int);
                printf("\033[1;34m%c\033[0m",_char);
                i++;
            }
        }else{
            printf("\033[1;34m%c\033[0m",Text[i]);
        }
    }

    va_end(Args);
}

void printf_RED(String Text,...){
    va_list Args;
    va_start(Args,Text);

    for(int i=0;i<strlen(Text);i++){
        if(Text[i] == '%'){
            if(Text[i+1] == 'd'){
                int _int = va_arg(Args,int);
                printf("\033[1;31m%d\033[0m",_int);
                i ++;
            }else if(Text[i+1] == 'f'){
                double _double = va_arg(Args,double);
                printf("\033[1;31m%f\033[0m",_double);
                i ++;
            }else if(Text[i+1] == 's'){
                String _String = va_arg(Args,String);
                printf("\033[1;31m%s\033[0m",_String);
                i ++;
            }else if(Text[i+1] == 'c'){
                int _char = va_arg(Args,int);
                printf("\033[1;31m%c\033[0m",_char);
                i++;
            }
        }else{
            printf("\033[1;31m%c\033[0m",Text[i]);
        }
    }

    va_end(Args);
}

void printf_MAGENTA(String Text,...){
    va_list Args;
    va_start(Args,Text);

    for(int i=0;i<strlen(Text);i++){
        if(Text[i] == '%'){
            if(Text[i+1] == 'd'){
                int _int = va_arg(Args,int);
                printf("\033[0;35m%d\033[0m",_int);
                i ++;
            }else if(Text[i+1] == 'f'){
                double _double = va_arg(Args,double);
                printf("\033[0;35m%f\033[0m",_double);
                i ++;
            }else if(Text[i+1] == 's'){
                String _String = va_arg(Args,String);
                printf("\033[0;35m%s\033[0m",_String);
                i ++;
            }else if(Text[i+1] == 'c'){
                int _char = va_arg(Args,int);
                printf("\033[0;35m%c\033[0m",_char);
                i++;
            }
        }else{
            printf("\033[0;35m%c\033[0m",Text[i]);
        }
    }

    va_end(Args);
}

// ##############################################################################################################################################################################################



void HideCursor() {
    HANDLE consoleHandle = GetStdHandle(STD_OUTPUT_HANDLE);
    CONSOLE_CURSOR_INFO info;
    info.dwSize = 100;
    info.bVisible = FALSE;  // FALSE = cache le curseur
    SetConsoleCursorInfo(consoleHandle, &info);
}

void gotoxy(int x, int y) {
    COORD coord = {x, y};
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
}