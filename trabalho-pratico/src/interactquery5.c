#include <ncurses.h>
#include "../includes/dates.h"
#include "../includes/query1.h"
#include "../includes/interactmode.h"

char q5_title[11][100] = {" $$$$$$|                                                $$$$$$$$|", 
                          "$$  __$$|                                               $$  ____|", 
                          "$$ /  $$ |$$    $$   $$$$$$|   $$$$$$|  $$    $$        $$ |     ", 
                          "$$ |  $$ |$$ |  $$ |$$  __$$| $$  __$$| $$ |  $$ |      $$$$$$$| ", 
                          "$$ |  $$ |$$ |  $$ |$$$$$$$$ |$$ |  |_| $$ |  $$ |      |_____$$|", 
                          "$$ $$|$$ |$$ |  $$ |$$   ____|$$ |      $$ |  $$ |      $$|   $$|",
                          "|$$$$$$ /|$$$$$$$ ||$$$$$$$| $$ |       |$$$$$$$ |      |$$$$$$$ |",
                          "|___$$$| |_______/  |_______||__|        |____$$ |      |______/ ",
                          "       |___|                            $$|   $$ |                ",
                          "                                        |$$$$$$  |                ",
                          "                                         |______/                 "};

void printbox3(int x) {
    mvprintw(38, x/2 - 32, "________________________________________________________________");
    mvprintw(39, x/2 - 32, "|                                                              |");
    mvprintw(40, x/2 - 32, "|                                                              |");
    mvprintw(41, x/2 - 32, "|______________________________________________________________|");
}

void query5_menu(Catalog_Users *catalog_users, Catalog_Drivers *catalog_drivers, Catalog_Rides *catalog_rides, Catalog_Cities *catalog_cities, int x, int y) {
    for (int j = 0; j < 11; j++) {
            mvprintw(j + 3, x/2 - strlen(q5_title[j])/2, "%s", q5_title[j]);
    }
    mvprintw(16, x/2 - strlen("Preço médio das viagens (sem considerar gorjetas) num dado intervalo de tempo, sendo esse intervalo representado por <data A> e <data B>")/2, "Preço médio das viagens (sem considerar gorjetas) num dado intervalo de tempo, sendo esse intervalo representado por <data A> e <data B>");
    mvprintw(17, x/2 - strlen("As datas devem ser representadas no formato dd/mm/yyyy. Caso pelo menos uma delas não seja inserida corretamente, terá de repetir o processo.")/2, "As datas devem ser representadas no formato dd/mm/yyyy. Caso pelo menos uma delas não seja inserida corretamente, terá de repetir o processo.");
    
    mvprintw(20, x/2 - strlen("Introduza a data A: ")/2, "Introduza a data A: ");

    echo();
    char da[40];
    getnstr(da, 40);

    clear();
    for (int j = 0; j < 11; j++) {
        mvprintw(j + 3, x/2 - strlen(q5_title[j])/2, "%s", q5_title[j]);
    }
    mvprintw(16, x/2 - strlen("Preço médio das viagens (sem considerar gorjetas) num dado intervalo de tempo, sendo esse intervalo representado por <data A> e <data B>")/2, "Preço médio das viagens (sem considerar gorjetas) num dado intervalo de tempo, sendo esse intervalo representado por <data A> e <data B>");
    mvprintw(17, x/2 - strlen("As datas devem ser representadas no formato dd/mm/yyyy. Caso pelo menos uma delas não seja inserida corretamente, terá de repetir o processo.")/2, "As datas devem ser representadas no formato dd/mm/yyyy. Caso pelo menos uma delas não seja inserida corretamente, terá de repetir o processo.");

    mvprintw(20, x/2 - strlen("Introduza a data B: ")/2, "Introduza a data B: ");
    char db[40];
    getnstr(db, 40);
    noecho();
    cbreak();

    unsigned short int dateinf = convert_to_day (da);
    unsigned short int datesup = convert_to_day (db);

    if (dateinf == 65535 || datesup == 65535) {
        clear();
        query5_menu(catalog_users, catalog_drivers, catalog_rides, catalog_cities, x, y);
    }

    unsigned short int date = 0; 
    double total_gasto_sem_tips = 0;
    double preco_medio = 0;
    uint num_rides = 0;

    uint length = get_array_rides_length (catalog_rides);
    for (uint i=0; i < length ; i++) 
    {
    date = get_ride_date (catalog_rides,i);
        if (date >= dateinf && date <= datesup) 
        {
        int driver =  (get_ride_driver (catalog_rides,i));
        char * car_class =  (get_driver_carclass (catalog_drivers,driver - 1));
        unsigned short int distance = get_ride_distance(catalog_rides,i); // talvz trocar para long?
        total_gasto_sem_tips = calcula_total_gasto (car_class, distance, 0);
        preco_medio += total_gasto_sem_tips;
        num_rides++;
        free (car_class);
        }
    }
    if (num_rides != 0) preco_medio = preco_medio / num_rides;

    printbox3(x);
    mvprintw(36, x/2 - strlen("Preço Médio das viagens entre 22/22/2222 e 22/22/2222")/2, "Preço médio das viagens entre %s e %s", da, db);
    mvprintw(40, x/2 - 3, "%.3f", preco_medio);

    mvprintw(44, x/2 - strlen("Se pretender continuar nesta query, prima C")/2, "Se pretender continuar nesta query, prima C");
    mvprintw(45, x/2 - strlen("Se pretender voltar ao Menu das Queries prima Q")/2, "Se pretender voltar ao Menu das Queries prima Q");

    int ch;
    while(1) {
        ch = getch();
        if(ch == 'Q' || ch == 'q') {
            clear();
            queries_menu(x, y, catalog_users, catalog_drivers, catalog_rides, catalog_cities);
        } else if(ch == 'C' || ch == 'c') {
            clear();
            query5_menu(catalog_users, catalog_drivers, catalog_rides, catalog_cities, x, y);
        }
    }
}