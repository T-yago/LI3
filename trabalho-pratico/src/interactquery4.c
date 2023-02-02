#include <ncurses.h>
#include "../includes/interactmode.h"
#include "../includes/cities.h"

char q4_title [11][100] ={" $$$$$$                                                 $$$   $$_ ",
                          "$$  __$$                                                $$ |  $$ |",
                          "$$ /  $$ |$$ |  $$ | $$$$$$|   $$$$$$$  $$ |  $$ |      $$ |  $$ |",
                          "$$ |  $$ |$$ |  $$ |$$  __$$ |$$  __$$  $$ |  $$ |      $$$$$$$$ |",
                          "$$ |  $$ |$$ |  $$ |$$$$$$$$ |$$ |  |__|$$ |  $$ |      |_____$$ |",
                          "$$ $$|$$ |$$ |  $$ |$$   ____|$$ |      $$ |  $$ |            $$ |",
                          "|$$$$$$  |$$$$$$ $||$$$$$$$$ |$$ |      |$$$$$$$ |            $$ |",
                          " |___$$$ |  |______/ |_______||__|       |____$$ |            |__|",
                          "     |___|                              $$|   $$ |                ",
                          "                                        |$$$$$$  |                ",
                          "                                         |______/                 "};

void printbox2(int x) {
    mvprintw(38, x/2 - 32, "________________________________________________________________");
    mvprintw(39, x/2 - 32, "|                                                              |");
    mvprintw(40, x/2 - 32, "|                                                              |");
    mvprintw(41, x/2 - 32, "|______________________________________________________________|");
}

void query4_menu(Catalog_Users *catalog_users, Catalog_Drivers *catalog_drivers, Catalog_Rides *catalog_rides, Catalog_Cities *catalog_cities, int x, int y) {
    for (int j = 0; j < 11; j++) {
            mvprintw(j + 3, x/2 - strlen(q4_title[j])/2, "%s", q4_title[j]);
    }

    mvprintw(16, x/2 - strlen("Preço médio das viagens (sem considerar gorjetas) numa determinada cidade.")/2, "Preço médio das viagens (sem considerar gorjetas) numa determinada cidade.");
    mvprintw(20, x/2 - strlen("Introduza a cidade que pretende analisar: ")/2, "Introduza a cidade que pretende analisar: ");

    echo();
    char s[40];
    getnstr(s, 40);

    noecho();
    cbreak();

    printbox2(x);
    mvprintw(36, x/2 - (strlen("Preço Médio das viagens em ") + strlen(s))/2, "Preço médio das viagens em %s", s);

    double preco_medio = 0;
    double total_gasto = 0;
    unsigned int num_rides = 0;
    if (!is_in_hash_cities(catalog_cities,s)) mvprintw(40, x/2 - 10, "Cidade não encontrada");
    else {
        total_gasto = get_total_gasto_city (catalog_cities,s);
        num_rides = get_num_rides_city (catalog_cities,s);
        preco_medio = total_gasto / num_rides;
        if (preco_medio != 0) mvprintw(40, x/2 - 3, "%.3f", preco_medio);
    } 

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
            query4_menu(catalog_users, catalog_drivers, catalog_rides, catalog_cities, x, y);
        }
    }

}   