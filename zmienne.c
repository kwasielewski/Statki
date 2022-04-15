#include "graficzne.h"
#include "fifo.h"
GtkWidget *window;
PipesPtr rura = NULL;


int salvo[10][10];
int gameMode=-1;
int gamer=-1;
int sugestia=-1;
int shipLen[] = {1, 2, 2, 3, 4};
int activeShip = 0;
int alreadySet=0;
int Xact = -1;
int Yact = -1;
int tura = 1;
int jego[] = {2, 3, 3, 4, 5};
int moje[] = {2, 3, 3, 4, 5};
int Xtarget = -1;
int Ytarget = -1;
int liczbaCeli = 0;
