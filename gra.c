#include <gtk/gtk.h>
#include "graficzne.h"
#include "gra.h"
#include "fifo.h"

void wybierzCel(GtkWidget* widget, int* numer){
    extern int Xtarget;
    extern int Ytarget;
    Xtarget = numer[0]/10;
    Ytarget = numer[0]%10;

    extern pole wrog[10][10];
    for(int i = 0; i < 10;  i++){
        for(int j = 0; j < 10; j++){
            if(wrog[i][j].trafienie==0){
                gtk_button_set_image(GTK_BUTTON(wrog[i][j].btn), gtk_image_new_from_file("woda.png"));
            }
        }
    }
    extern GtkWidget *atak;
    gtk_widget_set_sensitive(atak, TRUE);
    gtk_button_set_image(GTK_BUTTON(wrog[Xtarget][Ytarget].btn), gtk_image_new_from_file("yellow.png"));
}

void wybierzCelSalvo(GtkWidget* widget, int* numer){
    extern int salvo[10][10];
    extern pole wrog[10][10];
    extern int liczbaCeli;
    extern GtkWidget *atak;
    if(salvo[*numer/10][*numer%10]==0){
        salvo[*numer/10][*numer%10]=1;
        gtk_button_set_image(GTK_BUTTON(wrog[*numer/10][*numer%10].btn), gtk_image_new_from_file("yellow.png"));
        liczbaCeli++;
        gtk_widget_set_sensitive(atak, TRUE);

    }else{
        salvo[*numer/10][*numer%10]=0;
        gtk_button_set_image(GTK_BUTTON(wrog[*numer/10][*numer%10].btn), gtk_image_new_from_file("woda.png"));
        liczbaCeli--;
        if(liczbaCeli<=0){
            gtk_widget_set_sensitive(atak, FALSE);
        }
    }
}


void potwierdzCelSalvo(){
    extern int gamer;
    extern int tura;
    extern int liczbaCeli;
    int naWodzie = 0;
    extern int moje[];
    for(int  i = 0; i<5 ; i++){
        if(moje[i]>0){
            naWodzie++;
        }
    }
    if(liczbaCeli>naWodzie){
        return;
    }
    if(gamer%2 != tura%2){
        return;
    }
    int ok = 0;

    int x, y;
    extern int salvo[10][10];
    extern pole wrog[10][10];
    char a[1+liczbaCeli*2+2];
    a[0] = '0'+liczbaCeli;

    a[2*liczbaCeli+1] = '\0';
    int id = 1;
    for(int i = 0; i < 10; i++){
        for(int j = 0; j< 10; j++){
            if(salvo[i][j]==1){
                a[id] = '0'+i;
                id++;
                a[id] = '0'+j;
                id++;
            }
        }
    }
    for(int i = 0;  i<10;  i++){
        for(int j = 0;  j<  10; j++){
            if(salvo[i][j]==1){
                salvo[i][j]=0;
                if(wrog[i][j].statek!=0){
                    ok=1;
                    gtk_button_set_image(GTK_BUTTON(wrog[i][j].btn), gtk_image_new_from_file("red.png"));
                    extern int jego[];
                    wrog[i][j].trafienie=1;
                    jego[wrog[i][j].statek-1]--;

                    for(int i = 0; i < 5 ; i++ ){
                        if(jego[i]>0){
                            ok=0;
                        }
                    }
                }else{
                    gtk_button_set_image(GTK_BUTTON(wrog[i][j].btn), gtk_image_new_from_file("white.png"));


                }
                gtk_widget_set_sensitive(wrog[i][j].btn, FALSE);
            }
        }
    }

    tura++;


    extern PipesPtr rura;
    sendStringToPipe(rura, a);
    extern GtkWidget *atak;
    gtk_widget_set_sensitive(atak, FALSE);
    if(ok){

        extern GtkWidget* grid;
        extern GtkWidget* window;
        gtk_widget_destroy(grid);

        grid = gtk_grid_new();

        gtk_orientable_set_orientation (GTK_ORIENTABLE (grid), GTK_ORIENTATION_VERTICAL);
        gtk_container_add(GTK_CONTAINER(window), grid);


        GtkWidget* tekst = gtk_label_new(u8"Wygrana!");


        gtk_grid_attach(GTK_GRID(grid), tekst, 0, 0, 1, 1);

        gtk_widget_show_all(window);
    }else{
        g_timeout_add(100, pobierzStrzalySalvo, NULL);

    }
}

gboolean pobierzStrzalySalvo(){
    char wejscie[13];
    extern PipesPtr rura;
    extern int liczbaCeli;
    liczbaCeli = 0;
    int ok = 0;
    if(getStringFromPipe(rura, wejscie, 12)){
        int id =1;
        int n = wejscie[0]-'0';
        for(int i = 0; i< n; i++){
            int x = wejscie[id] - '0';
            id++;
            int y  = wejscie[id] - '0';
            id++;


            extern pole gracz[10][10];
            if(gracz[x][y].statek!=0){
                ok= 1;
                gtk_button_set_image(GTK_BUTTON(gracz[x][y].btn), gtk_image_new_from_file("red.png"));
                extern int moje[];
                gracz[x][y].trafienie=1;
                moje[gracz[x][y].statek-1]--;



                for(int i = 0; i < 5 ; i++ ){
                    if(moje[i]>0){
                        ok=0;
                    }
                }
            }else{
                gtk_button_set_image(GTK_BUTTON(gracz[x][y].btn), gtk_image_new_from_file("white.png"));

            }
        }

        extern int tura;
        tura++;
        if(ok){
            extern GtkWidget* grid;
            extern GtkWidget* window;
            gtk_widget_destroy(grid);

            grid = gtk_grid_new();

            gtk_orientable_set_orientation (GTK_ORIENTABLE (grid), GTK_ORIENTATION_VERTICAL);
            gtk_container_add(GTK_CONTAINER(window), grid);


            GtkWidget* tekst = gtk_label_new(u8"Przegrana!");


            gtk_grid_attach(GTK_GRID(grid), tekst, 0, 0, 1, 1);

            gtk_widget_show_all(window);
        }
        return FALSE;
    }
    return TRUE;
}


void potwierdzCel(){
    extern int gamer;
    extern int tura;
    if(gamer%2 != tura%2){
        return;
    }
    int ok = 0;
    extern int Xtarget;
    extern int Ytarget;
    extern GtkWidget* lab;
    extern pole wrog[10][10];
    if(wrog[Xtarget][Ytarget].statek!=0){
        ok=1;
        gtk_button_set_image(GTK_BUTTON(wrog[Xtarget][Ytarget].btn), gtk_image_new_from_file("red.png"));
        extern int jego[];
        wrog[Xtarget][Ytarget].trafienie=1;
        jego[wrog[Xtarget][Ytarget].statek-1]--;




        if(jego[wrog[Xtarget][Ytarget].statek-1]==0){

            gtk_label_set_text(GTK_LABEL(lab), "Trafiono zatopiono");
        }else{
            gtk_label_set_text(GTK_LABEL(lab), "Trafiono");
        }

        for(int i = 0; i < 5 ; i++ ){
            if(jego[i]>0){
                ok=0;
            }
        }
    }else{
        gtk_button_set_image(GTK_BUTTON(wrog[Xtarget][Ytarget].btn), gtk_image_new_from_file("white.png"));

        gtk_label_set_text(GTK_LABEL(lab), u8"Pudło");
    }
    gtk_widget_set_sensitive(wrog[Xtarget][Ytarget].btn, FALSE);

    tura++;
    char a[5];
    a[0] = '0'+Xtarget;
    a[1] = '0'+Ytarget;
    a[2] = '\0';

    extern PipesPtr rura;
    sendStringToPipe(rura, a);
    extern GtkWidget *atak;
    gtk_widget_set_sensitive(atak, FALSE);
    if(ok){

        extern GtkWidget* grid;
        extern GtkWidget* window;
        gtk_widget_destroy(grid);

        grid = gtk_grid_new();

        gtk_orientable_set_orientation (GTK_ORIENTABLE (grid), GTK_ORIENTATION_VERTICAL);
        gtk_container_add(GTK_CONTAINER(window), grid);


        GtkWidget* tekst = gtk_label_new(u8"Wygrana!");


        gtk_grid_attach(GTK_GRID(grid), tekst, 0, 0, 1, 1);

        gtk_widget_show_all(window);
    }else{
        g_timeout_add(100, pobierzStrzal, NULL);

    }
}


gboolean pobierzStrzal(){
    char wejscie[7];
    extern PipesPtr rura;

    if(getStringFromPipe(rura, wejscie, 5)){
        int x = wejscie[0] - '0';
        int y  = wejscie[1] - '0';
        int ok = 0;
        extern GtkWidget* lab;
        extern pole gracz[10][10];
        if(gracz[x][y].statek!=0){
            ok= 1;
            gtk_button_set_image(GTK_BUTTON(gracz[x][y].btn), gtk_image_new_from_file("red.png"));
            extern int moje[];
            gracz[x][y].trafienie=1;
            moje[gracz[x][y].statek-1]--;




            if(moje[gracz[x][y].statek-1]==0){

                gtk_label_set_text(GTK_LABEL(lab), u8"Przeciwnik trafił i zatopił");
            }else{
                gtk_label_set_text(GTK_LABEL(lab), u8"Przeciwnik trafił");
            }

            for(int i = 0; i < 5 ; i++ ){
                if(moje[i]>0){
                    ok=0;
                }
            }
        }else{
            gtk_button_set_image(GTK_BUTTON(gracz[x][y].btn), gtk_image_new_from_file("white.png"));

            gtk_label_set_text(GTK_LABEL(lab), u8"Przeciwnik spudłował");
        }
        extern int tura;
        tura++;
        if(ok){
            extern GtkWidget* grid;
            extern GtkWidget* window;
            gtk_widget_destroy(grid);

            grid = gtk_grid_new();

            gtk_orientable_set_orientation (GTK_ORIENTABLE (grid), GTK_ORIENTATION_VERTICAL);
            gtk_container_add(GTK_CONTAINER(window), grid);


            GtkWidget* tekst = gtk_label_new(u8"Przegrana!");


            gtk_grid_attach(GTK_GRID(grid), tekst, 0, 0, 1, 1);

            gtk_widget_show_all(window);
        }
        return FALSE;
    }
    return TRUE;
}
