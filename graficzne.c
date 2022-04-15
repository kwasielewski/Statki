#include <stdio.h>
#include <gtk/gtk.h>
#include "graficzne.h"
#include "operacyjne.h"
GtkWidget *grid;
GtkWidget *atak;
GtkWidget *lab;
GtkWidget * manual;
GtkWidget* klasyczneButton;
GtkWidget* salvoButton;
int numery[]={5, 4, 3, 2, 1};

GtkWidget* zasobniczek[7];

void buildMenu(GtkWidget* window){

    grid = gtk_grid_new();

    gtk_orientable_set_orientation (GTK_ORIENTABLE (grid), GTK_ORIENTATION_VERTICAL);
    gtk_container_add(GTK_CONTAINER(window), grid);

    GtkLabel* tytul = (GtkLabel*)gtk_label_new("Okręty");
    klasyczneButton = gtk_button_new_with_label("Klasyczne");
    salvoButton = gtk_button_new_with_label("Salvo");
    GtkWidget* instr =  gtk_button_new_with_label("Instrukcja");

    gtk_grid_attach(GTK_GRID(grid), GTK_WIDGET(tytul), 0, 0 ,1, 1);
    gtk_grid_attach(GTK_GRID(grid), GTK_WIDGET(klasyczneButton), 0, 1 ,1, 1);
    gtk_grid_attach(GTK_GRID(grid), GTK_WIDGET(salvoButton), 0, 2 ,1, 1);
    gtk_grid_attach(GTK_GRID(grid), GTK_WIDGET(instr), 0, 4 ,1, 1);



    g_signal_connect(G_OBJECT(instr), "clicked", G_CALLBACK(buildInstruction),NULL);
    g_signal_connect(G_OBJECT(klasyczneButton),"clicked",G_CALLBACK(setModeClassic), NULL);
    g_signal_connect(G_OBJECT(salvoButton), "clicked", G_CALLBACK(setModeSalvo), NULL);

    gtk_widget_show_all(window);
    return;
}

void buildInstruction(){

    manual=gtk_window_new(GTK_WINDOW_TOPLEVEL);

    gtk_window_set_resizable(GTK_WINDOW(manual), FALSE);

    gtk_window_set_title(GTK_WINDOW(manual),"Instrukcja");

    gtk_window_set_position(GTK_WINDOW(manual),GTK_WIN_POS_MOUSE);
    gtk_container_set_border_width(GTK_CONTAINER(manual), 15);
    GtkWidget* siatka = gtk_grid_new();
    gtk_container_add(GTK_CONTAINER(manual),siatka);
    char tekst[] = "Rozstawienie\n\
Podczas rozstawiania należy wybrać rodzaj umieszczanego statku przez kliknięcie odpowiedniego przycisku po prawej stronie. Następnie wybrać pole na siatce,\n\ na którym znajdować ma się prawy lub dolny koniec statku. Wybrane pole zapali się na żółto. Na zielono zaznaczone będą potencjalne końce statku. Wtedy \n\
wybierając zielone pole potwierdza się wybór. Zamiast tego można go anulować klikając ponownie żółte pole lub wybór rodzaju statku. Jedną z możliwości\n\
 jest całkowity reset ustawienia statków, wybierając odpowiednią opcję po prawej stronie. Po umieszczeniu 5 okrętów należy potwierdzić wybór. Statki mogą się stykać.\n\
\n\
Klasyczne\n\
Co turę należy wybrać jedno pole do strzału z siatki. Każdy wybór należy potwierdzić.\n\
\n\
Salvo\n\
Co turę należy wybrać pola (nie więcej niż posiadanych, niezatopionych staków, i nie mniej niż 1) do strzału z siatki. Każdy wybrany zestaw pól należy potwierdzić.\n\
\n\
Koniec gry\n\
Gra kończy się, zwycięstwem tego gracza, który jako pierwszy zatopi wszystkie statki przeciwnika.";
    GtkWidget* tresc = gtk_label_new(tekst);
    gtk_container_add(GTK_CONTAINER(siatka), tresc);
    g_signal_connect(G_OBJECT(manual),"destroy",G_CALLBACK(gtk_widget_destroy),NULL);
    gtk_widget_show_all(manual);

    return;
}

void buildSetup(GtkWidget* window/*, char mode*/){

    extern pole gracz[10][10];
    extern pole wrog[10][10];

    grid = gtk_grid_new();
    GtkWidget* przeciwnik = gtk_grid_new();
    GtkWidget* statki = gtk_grid_new();
    GtkWidget* zasobnik = gtk_grid_new();

    gtk_grid_attach(GTK_GRID(grid), GTK_WIDGET(przeciwnik), 0, 1, 10 ,10);
    gtk_grid_attach(GTK_GRID(grid), GTK_WIDGET(statki), 0, 11, 10 ,10);
    gtk_grid_attach(GTK_GRID(grid), GTK_WIDGET(zasobnik), 11, 11, 5, 5);

    gtk_container_add(GTK_CONTAINER(window), grid);
    gtk_grid_set_row_spacing(GTK_GRID(grid), 30);
    gtk_grid_set_column_spacing(GTK_GRID(grid), 30);


    GtkWidget* ship = gtk_button_new();
    gtk_button_set_label(GTK_BUTTON(ship), "Lotniskowiec");
    gtk_grid_attach(GTK_GRID(zasobnik), ship, 0, 0, 1, 1);
    extern void setActiveShip(gint numer);
    g_signal_connect(ship, "clicked", G_CALLBACK(setActiveShip), numery);
    zasobniczek[4] = ship;

    ship = gtk_button_new();
    gtk_button_set_label(GTK_BUTTON(ship), "Pancernik");
    gtk_grid_attach(GTK_GRID(zasobnik), ship, 0, 1, 1, 1);
    g_signal_connect(ship, "clicked", G_CALLBACK(setActiveShip), numery+1);
    zasobniczek[3] = ship;

    ship = gtk_button_new();
    gtk_button_set_label(GTK_BUTTON(ship), u8"Krążownik");
    gtk_grid_attach(GTK_GRID(zasobnik), ship, 0, 2, 1, 1);
    g_signal_connect(ship, "clicked", G_CALLBACK(setActiveShip), numery+2);
    zasobniczek[2] = ship;

    ship = gtk_button_new();
    gtk_button_set_label(GTK_BUTTON(ship), u8"Łódź podwodna");
    gtk_grid_attach(GTK_GRID(zasobnik), ship, 0, 3, 1, 1);
    g_signal_connect(ship, "clicked", G_CALLBACK(setActiveShip), numery+3);
    zasobniczek[1] = ship;

    ship = gtk_button_new();
    gtk_button_set_label(GTK_BUTTON(ship), "Niszczyciel");
    gtk_grid_attach(GTK_GRID(zasobnik), ship, 0, 4, 1, 1);
    g_signal_connect(ship, "clicked", G_CALLBACK(setActiveShip), numery+4);
    zasobniczek[0] = ship;


    GtkWidget *fin = gtk_button_new_with_label("Resetuj ustawienie");
    gtk_grid_attach(GTK_GRID(zasobnik), fin, 0, 7, 1, 1);
    extern void resetSetup();
    g_signal_connect(fin, "clicked", G_CALLBACK(resetSetup),NULL);
    zasobniczek[5] = fin;


    fin = gtk_button_new_with_label(u8"Potwierdź");
    gtk_grid_attach(GTK_GRID(zasobnik), fin, 0, 9, 1, 1);
    extern void confirm();
    g_signal_connect(fin, "clicked", G_CALLBACK(confirm), NULL);
    gtk_widget_set_sensitive(fin, FALSE);
    zasobniczek[6] = fin;

    for(int i = 0 ; i < 10; i++){
        for(int j = 0; j < 10; j++){
            gtk_grid_attach(GTK_GRID(przeciwnik), GTK_WIDGET(wrog[i][j].btn), i, j, 1, 1);
            gtk_grid_attach(GTK_GRID(statki), GTK_WIDGET(gracz[i][j].btn), i, j, 1, 1);
       }
    }


    gtk_widget_show_all(window);
    return;

}

void buildGame(GtkWidget* window/*, char mode*/){

    extern pole gracz[10][10];
    extern pole wrog[10][10];

    grid = gtk_grid_new();
    GtkWidget* przeciwnik = gtk_grid_new();
    GtkWidget* statki = gtk_grid_new();
    GtkWidget* zasobnik = gtk_grid_new();

    gtk_grid_attach(GTK_GRID(grid), GTK_WIDGET(przeciwnik), 0, 1, 10 ,10);
    gtk_grid_attach(GTK_GRID(grid), GTK_WIDGET(statki), 0, 11, 10 ,10);
    gtk_grid_attach(GTK_GRID(grid), GTK_WIDGET(zasobnik), 11, 11, 5, 5);
    lab = gtk_label_new("KOMUNIKATY");
    gtk_grid_attach(GTK_GRID(grid), lab, 11, 1, 5, 1);


    gtk_container_add(GTK_CONTAINER(window), grid);
    gtk_grid_set_row_spacing(GTK_GRID(grid), 30);
    gtk_grid_set_column_spacing(GTK_GRID(grid), 30);


    GtkWidget *fin = gtk_button_new_with_label(u8"Potwierdź");
    gtk_grid_attach(GTK_GRID(zasobnik), GTK_WIDGET(fin), 0, 10, 1, 1);
    extern void potwierdzCel();
    g_signal_connect(fin, "clicked", G_CALLBACK(potwierdzCel),NULL);
    gtk_widget_set_sensitive(fin, FALSE);
    atak = fin;

    for(int i = 0 ; i < 10; i++){
        for(int j = 0; j < 10; j++){

            wrog[i][j].btn = gtk_button_new();
            gtk_button_set_image(GTK_BUTTON(wrog[i][j].btn), gtk_image_new_from_file("woda.png"));
            gtk_grid_attach(GTK_GRID(przeciwnik), GTK_WIDGET(wrog[i][j].btn), i, j, 1, 1);
            extern void wybierzCel();
            g_signal_connect(wrog[i][j].btn, "clicked", G_CALLBACK(wybierzCel), wrog[i][j].val);
            gtk_widget_set_sensitive(wrog[i][j].btn, FALSE);

            gracz[i][j].btn = gtk_button_new();
            if(gracz[i][j].statek==0){
                gtk_button_set_image(GTK_BUTTON(gracz[i][j].btn), gtk_image_new_from_file("woda.png"));
            }else{
                gtk_button_set_image(GTK_BUTTON(gracz[i][j].btn), gtk_image_new_from_file("gray.png"));
            }
            gtk_widget_set_sensitive(gracz[i][j].btn, FALSE);
            gtk_grid_attach(GTK_GRID(statki), GTK_WIDGET(gracz[i][j].btn), i, j, 1, 1);

       }
    }



    gtk_widget_show_all(window);
    return;

}

void buildGameSalvo(GtkWidget* window/*, char mode*/){

    extern pole gracz[10][10];
    extern pole wrog[10][10];

    grid = gtk_grid_new();
    GtkWidget* przeciwnik = gtk_grid_new();
    GtkWidget* statki = gtk_grid_new();
    GtkWidget* zasobnik = gtk_grid_new();

    gtk_grid_attach(GTK_GRID(grid), GTK_WIDGET(przeciwnik), 0, 1, 10 ,10);
    gtk_grid_attach(GTK_GRID(grid), GTK_WIDGET(statki), 0, 11, 10 ,10);
    gtk_grid_attach(GTK_GRID(grid), GTK_WIDGET(zasobnik), 11, 11, 5, 5);

    gtk_container_add(GTK_CONTAINER(window), grid);
    gtk_grid_set_row_spacing(GTK_GRID(grid), 30);
    gtk_grid_set_column_spacing(GTK_GRID(grid), 30);

    GtkWidget *fin = gtk_button_new_with_label(u8"Potwierdź");
    gtk_grid_attach(GTK_GRID(zasobnik), GTK_WIDGET(fin), 0, 10, 1, 1);


    extern void potwierdzCelSalvo();
    g_signal_connect(fin, "clicked", G_CALLBACK(potwierdzCelSalvo),NULL);
    gtk_widget_set_sensitive(fin, FALSE);
    atak = fin;

    for(int i = 0 ; i < 10; i++){
        for(int j = 0; j < 10; j++){
            wrog[i][j].btn = gtk_button_new();
            gtk_button_set_image(GTK_BUTTON(wrog[i][j].btn), gtk_image_new_from_file("woda.png"));
            gtk_grid_attach(GTK_GRID(przeciwnik), GTK_WIDGET(wrog[i][j].btn), i, j, 1, 1);


            extern void wybierzCelSalvo();
            g_signal_connect(wrog[i][j].btn, "clicked", G_CALLBACK(wybierzCelSalvo), wrog[i][j].val);
            gtk_widget_set_sensitive(wrog[i][j].btn, FALSE);

            gracz[i][j].btn = gtk_button_new();
            if(gracz[i][j].statek==0){
                gtk_button_set_image(GTK_BUTTON(gracz[i][j].btn), gtk_image_new_from_file("woda.png"));
            }else{
                gtk_button_set_image(GTK_BUTTON(gracz[i][j].btn), gtk_image_new_from_file("gray.png"));
            }
            gtk_widget_set_sensitive(gracz[i][j].btn, FALSE);
            gtk_grid_attach(GTK_GRID(statki), GTK_WIDGET(gracz[i][j].btn), i, j, 1, 1);

       }
    }



    gtk_widget_show_all(window);
    return;

}

void setModeClassic(){
    extern int gamer;
    if(gamer==1){
        extern int gameMode;
        gameMode = 1;
        extern GtkWidget* window;

        gtk_widget_destroy(grid);
        buildSetup(window);
        przekazTrybGry(1);

    }else{
        przekazSugestie(1);
    }
    return;
}

void setModeSalvo(){
    extern int gamer;
    if(gamer==1){
        extern int gameMode;
        gameMode = 2;

        extern GtkWidget* window;

        gtk_widget_destroy(grid);
        buildSetup(window);
        przekazTrybGry(2);
    }else{
        przekazSugestie(2);
    }

    return;
}
void buildSettings(GtkWidget* window){
    GtkWidget *grid = gtk_grid_new();

    gtk_orientable_set_orientation (GTK_ORIENTABLE (grid), GTK_ORIENTATION_VERTICAL);
    gtk_container_add(GTK_CONTAINER(window), grid);


    GtkWidget* powrot = gtk_button_new_with_label(u8"Powrót");
    GtkWidget* zapisz = gtk_button_new_with_label("Zapisz");
    GtkWidget* motyw = gtk_button_new_with_label("Motyw: Jasny");

    gtk_grid_attach(GTK_GRID(grid), motyw, 0, 0, 1, 1);
    gtk_grid_attach(GTK_GRID(grid), zapisz, 0, 1, 1, 1);
    gtk_grid_attach(GTK_GRID(grid), powrot, 0, 2, 1, 1);

    gtk_widget_show_all(window);
    return;
}
void buildEnd(GtkWidget* window){
    GtkWidget *grid = gtk_grid_new();

    gtk_orientable_set_orientation (GTK_ORIENTABLE (grid), GTK_ORIENTATION_VERTICAL);
    gtk_container_add(GTK_CONTAINER(window), grid);


    GtkWidget* tekst = gtk_label_new(u8"Czy wygrałeś?");
    GtkWidget* btn = gtk_button_new_with_label("Zagraj ponownie");

    gtk_grid_attach(GTK_GRID(grid), tekst, 0, 0, 1, 1);
    gtk_grid_attach(GTK_GRID(grid), btn, 0,1, 1,1);



    gtk_widget_show_all(window);
}
