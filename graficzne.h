#include <stdio.h>
#include <gtk/gtk.h>

typedef struct pole{
    int x, y;
    int val[1];
    int trafienie;
    int statek;
    GtkWidget* btn;
}pole;
pole gracz[10][10];
pole wrog[10][10];


void buildMenu(GtkWidget* window);

void buildSetup(GtkWidget* window);

void buildGame(GtkWidget* window);

void buildGameSalvo(GtkWidget* window);

void buildInstruction();

void buildSettings(GtkWidget* window);

void buildEnd(GtkWidget* window);

void setModeClassic();

void setModeSalvo();
