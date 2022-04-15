#include <gtk/gtk.h>
#include "rozstaw.h"
#include "fifo.h"


void startShip(GtkWidget* widget, int* dane){

    int x = dane[0]/10;
    int y = dane[0]%10;

    extern pole gracz[10][10];
    extern int Xact, Yact;
    Xact = x;
    Yact = y;
    gtk_button_set_image(GTK_BUTTON(gracz[x][y].btn), gtk_image_new_from_file("yellow.png"));
    for(int i = 0 ; i<10; i++){
        for(int j = 0; j < 10; j++){
            gtk_widget_set_sensitive(gracz[i][j].btn, FALSE);
        }
    }

    extern int shipLen[];
    extern int activeShip;
    int ok = 1;
    if(Xact - shipLen[activeShip-1] >-1){

        for(int i = 0; i <=shipLen[activeShip-1]; i++){
            if(gracz[Xact-i][Yact].statek!=0){
                ok=0;
            }
        }
        if(ok==1){
            gtk_button_set_image(GTK_BUTTON(gracz[Xact-shipLen[activeShip-1]][Yact].btn), gtk_image_new_from_file("green.png"));
            g_signal_handlers_disconnect_by_func(gracz[Xact-shipLen[activeShip-1]][Yact].btn, G_CALLBACK(startShip), gracz[Xact-shipLen[activeShip-1]][Yact].val);
            gtk_widget_set_sensitive(gracz[Xact-shipLen[activeShip-1]][Yact].btn, TRUE);
            g_signal_connect(gracz[Xact-shipLen[activeShip-1]][Yact].btn, "clicked", G_CALLBACK(endShip), gracz[Xact-shipLen[activeShip-1]][Yact].val);

        }
    }
    ok=1;
    if(Yact - shipLen[activeShip-1] >-1){

        for(int i = 0; i <=shipLen[activeShip-1]; i++){
            if(gracz[Xact][Yact-i].statek!=0){
                ok=0;
            }
        }
        if(ok==1){
            gtk_button_set_image(GTK_BUTTON(gracz[Xact][Yact-shipLen[activeShip-1]].btn), gtk_image_new_from_file("green.png"));
            g_signal_handlers_disconnect_by_func(gracz[Xact][Yact-shipLen[activeShip-1]].btn, G_CALLBACK(startShip), gracz[Xact][Yact-shipLen[activeShip-1]].val);
            gtk_widget_set_sensitive(gracz[Xact][Yact-shipLen[activeShip-1]].btn, TRUE);
            g_signal_connect(gracz[Xact][Yact-shipLen[activeShip-1]].btn, "clicked", G_CALLBACK(endShip), gracz[Xact][Yact-shipLen[activeShip-1]].val);

        }
    }


    gtk_widget_set_sensitive(gracz[x][y].btn, TRUE);
    g_signal_handlers_disconnect_by_func(gracz[x][y].btn, G_CALLBACK(startShip), gracz[x][y].val);
    g_signal_connect(gracz[x][y].btn, "clicked", G_CALLBACK(cancelShip), NULL);
}
int min(int a, int b){
    return (a<b) ? a : b;
}
int max(int a, int b){
    return (a>b) ? a : b;
}


void endShip(GtkWidget* widget, int* dane){
    extern pole gracz[10][10];
    extern int activeShip;
    extern int Xact, Yact;
    int x = dane[0]/10;
    int y = dane[0]%10;
    extern int activeShip;

    for(int i = min(Xact, x); i <=max(Xact, x); i++){
        for(int j = min(Yact, y); j <=max(Yact, y); j++){
            gracz[i][j].statek = activeShip;
            gtk_widget_set_sensitive(gracz[i][j].btn, FALSE);
            gtk_button_set_image(GTK_BUTTON(gracz[i][j].btn), gtk_image_new_from_file("gray.png"));
        }
    }

    for(int i = 0; i < 10; i++){
        for(int j = 0; j < 10; j++){
            if(gracz[i][j].statek==0){
                g_signal_handlers_disconnect_by_func(gracz[i][j].btn, G_CALLBACK(startShip), gracz[i][j].val);


                g_signal_handlers_disconnect_by_func(gracz[i][j].btn, G_CALLBACK(endShip), gracz[i][j].val);
                gtk_button_set_image(GTK_BUTTON(gracz[i][j].btn), gtk_image_new_from_file("woda.png"));
                gtk_widget_set_sensitive(gracz[i][j].btn, TRUE);
            }
        }
    }
    Xact=-1;
    Yact=-1;
    extern int alreadySet;
    alreadySet++;
    extern GtkWidget* zasobniczek[];
    gtk_widget_set_sensitive(zasobniczek[activeShip-1], FALSE);



    if(alreadySet==5){
        gtk_widget_set_sensitive(zasobniczek[6], TRUE);
        for(int i = 0 ; i<10; i++){
            for(int j = 0; j < 10; j++){
                gtk_widget_set_sensitive(gracz[i][j].btn, FALSE);

            }
        }
    }


}
void cancelShip(){
    extern pole gracz[10][10];
    extern int activeShip;

    extern int Xact, Yact;
    if(Xact !=-1 && Yact != -1){

            gracz[Xact][Yact].statek = 0;

            g_signal_handlers_disconnect_by_func(gracz[Xact][Yact].btn, G_CALLBACK(cancelShip), NULL);

            g_signal_connect(gracz[Xact][Yact].btn, "clicked", G_CALLBACK(startShip), gracz[Xact][Yact].val);
            gtk_button_set_image(GTK_BUTTON(gracz[Xact][Yact].btn), gtk_image_new_from_file("woda.png"));
    }
    for(int i = 0; i < 10; i++){
        for(int j = 0; j < 10; j++){
            if(gracz[i][j].statek==0){
                gtk_button_set_image(GTK_BUTTON(gracz[i][j].btn), gtk_image_new_from_file("woda.png"));
                g_signal_handlers_disconnect_by_func(gracz[i][j].btn, G_CALLBACK(cancelShip), NULL);
                g_signal_handlers_disconnect_by_func(gracz[i][j].btn, G_CALLBACK(endShip), gracz[i][j].val);
                g_signal_connect(gracz[i][j].btn, "clicked", G_CALLBACK(startShip), gracz[i][j].val);
                gtk_widget_set_sensitive(gracz[i][j].btn, TRUE);
            }
        }
    }

}
void setActiveShip(GtkWidget* widget, int* numer){
    extern pole gracz[10][10];
    extern int activeShip;

    extern int Xact, Yact;

    if(activeShip == -1){
        activeShip = *numer;
    }else{

        if(Xact !=-1 && Yact != -1){

            gracz[Xact][Yact].statek = 0;


            g_signal_connect(gracz[Xact][Yact].btn, "clicked", G_CALLBACK(startShip), gracz[Xact][Yact].val);
            gtk_button_set_image(GTK_BUTTON(gracz[Xact][Yact].btn), gtk_image_new_from_file("woda.png"));
        }
        activeShip = *numer;
    }
    Xact = -1;
    Yact = -1;


    for(int i = 0; i < 10; i++){
        for(int j = 0; j < 10; j++){
            if(gracz[i][j].statek==0){
                g_signal_handlers_disconnect_by_func(gracz[i][j].btn, G_CALLBACK(endShip), gracz[i][j].val);
                g_signal_handlers_disconnect_by_func(gracz[i][j].btn, G_CALLBACK(cancelShip), NULL);
                g_signal_connect(gracz[i][j].btn, "clicked", G_CALLBACK(startShip), gracz[i][j].val);

                gtk_button_set_image(GTK_BUTTON(gracz[i][j].btn), gtk_image_new_from_file("woda.png"));
                gtk_widget_set_sensitive(gracz[i][j].btn, TRUE);
            }
        }
    }
}

void resetSetup(){

    extern int activeShip;
    extern int alreadySet;
    extern int Xact;
    extern int Yact;
    activeShip = 0;
    alreadySet=0;
    Xact = -1;
    Yact = -1;

    extern pole gracz[10][10];
    for(int i = 0; i < 10 ; i++){
        for(int j = 0;  j<10; j++){
            gracz[i][j].statek=0;
            gtk_button_set_image(GTK_BUTTON(gracz[i][j].btn), gtk_image_new_from_file("woda.png"));
            g_signal_handlers_disconnect_by_func(gracz[i][j].btn, G_CALLBACK(endShip), gracz[i][j].val);
            g_signal_handlers_disconnect_by_func(gracz[i][j].btn, G_CALLBACK(cancelShip), NULL);
            g_signal_connect(gracz[i][j].btn, "clicked", G_CALLBACK(startShip), gracz[i][j].val);
            gtk_widget_set_sensitive(gracz[i][j].btn, FALSE);

        }
    }


    extern GtkWidget* zasobniczek[];

    gtk_widget_set_sensitive(zasobniczek[6], FALSE);

    for(int i = 0; i < 5; i++){
        gtk_widget_set_sensitive(zasobniczek[i], TRUE);
    }

}

gboolean pobierzMape(){
    extern PipesPtr rura;
    char wejscie[105];
    extern pole wrog[10][10];

    if(getStringFromPipe(rura, wejscie, 101)){
        for(int  i= 0; i< 10; i++){
            for(int j = 0;  j < 10; j++){
                int x = wejscie[10*i+j] - '0';

                wrog[i][j].statek = x;
                gtk_widget_set_sensitive(wrog[i][j].btn, TRUE);

            }
        }
        return FALSE;
    }

    return TRUE;
}

void confirm(){
    extern int gamer;
    extern GtkWidget* grid;
    extern GtkWidget *window;
    extern pole gracz[10][10];
    extern PipesPtr rura;

    extern int gameMode;
    if(gameMode==1){


        gtk_widget_destroy(grid);
        buildGame(window);

        char a[105];
        for(int i = 0; i < 10; i++){
            for(int  j = 0; j< 10; j++){

                a[10*i+j]='0'+gracz[i][j].statek;
            }
        }
        a[100] = '\0';


        sendStringToPipe(rura, a);

        g_timeout_add(100, pobierzMape, NULL);
        if(gamer==1){

        }else{


            extern gboolean pobierzStrzal();
            g_timeout_add(100, pobierzStrzal, NULL);
        }
    }else{
        gtk_widget_destroy(grid);

        buildGameSalvo(window);

        char a[105];
        for(int i = 0; i < 10; i++){
            for(int  j = 0; j< 10; j++){

                a[10*i+j]='0'+gracz[i][j].statek;
            }
        }
        a[100] = '\0';


        sendStringToPipe(rura, a);

        g_timeout_add(100, pobierzMape, NULL);
        if(gamer==1){


        }else{

            extern gboolean pobierzStrzalySalvo();
            g_timeout_add(100, pobierzStrzalySalvo, NULL);
        }

    }
    return;
}

