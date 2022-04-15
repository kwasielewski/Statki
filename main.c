#include <stdio.h>
#include <string.h>
#include <gtk/gtk.h>
#include "graficzne.h"
#include "operacyjne.h"
#include "fifo.h"


int main(int argc, char** argv){

	gtk_init (&argc, &argv);
	extern PipesPtr rura;
    rura = initPipes(argc, argv);
	extern GtkWidget *window;
    extern int gamer;
    if(strcmp(argv[1],"A")==0){
        gamer = 1;
        g_timeout_add(100, pobierzSugestie, NULL);

    }else{
        gamer = 2;
        g_timeout_add(100, pobierzTrybGry, NULL);
    }

    window=gtk_window_new(GTK_WINDOW_TOPLEVEL);

    gtk_window_set_resizable(GTK_WINDOW(window), FALSE);

    gtk_window_set_title(GTK_WINDOW(window),"Okręty");

    gtk_window_set_position(GTK_WINDOW(window),GTK_WIN_POS_MOUSE);
    gtk_container_set_border_width(GTK_CONTAINER(window), 15);

    g_signal_connect(G_OBJECT(window),"destroy",G_CALLBACK(endProg),NULL);


    init();
    extern pole gracz[10][10];
    extern pole wrog[10][10];


    buildMenu(window);
    extern int gameMode;
    gtk_main ();

	return 0;
}
