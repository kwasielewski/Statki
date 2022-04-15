#include <stdio.h>
#include "fifo.h"
#include "operacyjne.h"
#include "graficzne.h"
void init(){
    extern int salvo[10][10];
    extern pole wrog[10][10];
    extern pole gracz[10][10];
    for(int i = 0; i < 10; i ++){
        for(int j = 0;  j < 10; j++){
            salvo[i][j] = 0;
            wrog[i][j].btn = gtk_button_new();
            gtk_button_set_image(GTK_BUTTON(wrog[i][j].btn), gtk_image_new_from_file("woda.png"));
            wrog[i][j].val[0] = 10*i +j;
            extern void wybierzCel();
            g_signal_connect(wrog[i][j].btn, "clicked", G_CALLBACK(wybierzCel), wrog[i][j].val);
            gtk_widget_set_sensitive (wrog[i][j].btn, FALSE);
            wrog[i][j].x = i;
            wrog[i][j].y = j;
            wrog[i][j].statek=0;
            wrog[i][j].trafienie=0;
            gracz[i][j].btn = gtk_button_new();
            gtk_button_set_image(GTK_BUTTON(gracz[i][j].btn), gtk_image_new_from_file("woda.png"));
            gtk_widget_set_sensitive (gracz[i][j].btn, FALSE);
            extern void startShip(int dane);

            g_signal_connect(gracz[i][j].btn, "clicked", G_CALLBACK(startShip), gracz[i][j].val);
            gracz[i][j].val[0] =10*i+j;
            gracz[i][j].x = i;
            gracz[i][j].y = j;
            gracz[i][j].statek=0;
            gracz[i][j].trafienie=0;
        }
    }
    return;
}
void endProg(){
    extern PipesPtr rura;
    closePipes(rura);
    gtk_main_quit();
    return;
}

void przekazSugestie(gint s){
    extern PipesPtr rura;
    if(s==1){
        sendStringToPipe(rura, "1");
    }else if(s==2){
        sendStringToPipe(rura, "2");
    }


    return;
}

gboolean pobierzSugestie(gpointer data){
    extern int gameMode;
    if(gameMode!=-1){
        return FALSE;
    }
    char wejscie[7];
    extern PipesPtr rura;
    extern int sugestia ;
    extern GtkWidget* klasyczneButton;
    extern GtkWidget* salvoButton;
    getStringFromPipe(rura, wejscie, 4);
    if(wejscie[0]=='1'){
        sugestia = 1;
        gtk_button_set_label(GTK_BUTTON(klasyczneButton), "      Klasyczne\n(sugerowane przez drugiego gracza)");
        return FALSE;
    }else if(wejscie[0]=='2'){
        gtk_button_set_label(GTK_BUTTON(salvoButton), "        Salvo\n(sugerowane przez drugiego gracza)");
        sugestia = 2;
        return FALSE;
    }

    return TRUE;
}
void przekazTrybGry(gint s){
    extern PipesPtr rura;
    if(s==1){
        sendStringToPipe(rura, "1");
    }else if(s==2){
        sendStringToPipe(rura, "2");
    }

    return;
}
gboolean pobierzTrybGry(gpointer data){
    char wejscie[7];
    extern PipesPtr rura;
    extern int gameMode ;
    getStringFromPipe(rura, wejscie, 4);
    if(wejscie[0]=='1'){

        gameMode = 1;
        extern GtkWidget* window;
        extern GtkWidget* grid;

        gtk_widget_destroy(grid);
        buildSetup(window);
        return FALSE;
    }else if(wejscie[0]=='2'){

        gameMode = 2;
        extern GtkWidget* window;
        extern GtkWidget* grid;

        gtk_widget_destroy(grid);
        buildSetup(window);
        return FALSE;
    }
    return TRUE;
}
