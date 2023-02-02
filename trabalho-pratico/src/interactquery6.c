#include <ncurses.h>
#include "../includes/dates.h"
#include "../includes/interactmode.h"

char q6_title[11][100] ={"  /$$$$$$                                                 /$$$$$$ ",
                         " /$$__  $$                                               /$$__  $$",
                         "| $$  | $$ /$$   /$$  /$$$$$$   /$$$$$$  /$$   /$$      | $$  |__/",
                         "| $$  | $$| $$  | $$ /$$__  $$ /$$__  $$| $$  | $$      | $$$$$$$ ",
                         "| $$  | $$| $$  | $$| $$$$$$$$| $$  |__/| $$  | $$      | $$__  $$",
                         "| $$/$$ $$| $$  | $$| $$_____/| $$      | $$  | $$      | $$  | $$",
                         "|  $$$$$$/|  $$$$$$/|  $$$$$$$| $$      |  $$$$$$$      |  $$$$$$/",
                         " |____ $$$ |______/  |_______/|__/       |____  $$       |______/ ",
                         "     |__/                               /$$  | $$                 ",
                         "                                        | $$$$$$/                 ",
                         "                                        |______/                  "};

void printbox6(int x) {
    mvprintw(38, x/2 - 32, "________________________________________________________________");
    mvprintw(39, x/2 - 32, "|                                                              |");
    mvprintw(40, x/2 - 32, "|                                                              |");
    mvprintw(41, x/2 - 32, "|______________________________________________________________|");
}

void query6_menu(Catalog_Users *catalog_users, Catalog_Drivers *catalog_drivers, Catalog_Rides *catalog_rides, Catalog_Cities *catalog_cities, int x, int y) {
    for (int j = 0; j < 11; j++) {
            mvprintw(j + 3, x/2 - strlen(q6_title[j])/2, "%s", q6_title[j]);
    }

    mvprintw(16, x/2 - strlen("Distância média percorrida, numa determinada cidade, representada por <city>, num dado intervalo de tempo, sendo esse intervalo representado por <data A> e <data B>")/2, "Distância média percorrida, numa determinada cidade, representada por <city>, num dado intervalo de tempo, sendo esse intervalo representado por <data A> e <data B>");
    mvprintw(17, x/2 - strlen("As datas devem ser representadas no formato dd/mm/yyyy. Caso pelo menos uma delas não seja inserida corretamente, terá de repetir o processo.")/2, "As datas devem ser representadas no formato dd/mm/yyyy. Caso pelo menos uma delas não seja inserida corretamente, terá de repetir o processo.");

    mvprintw(20, x/2 - strlen("Introduza a cidade pretendida: ")/2, "Introduza a cidade pretendida: ");
    echo();
    char s[40];
    getnstr(s, 40);

    noecho();
    cbreak();

    clear();
    for (int j = 0; j < 11; j++) {
        mvprintw(j + 3, x/2 - strlen(q6_title[j])/2, "%s", q6_title[j]);
    }

    mvprintw(16, x/2 - strlen("Distância média percorrida, numa determinada cidade, representada por <city>, num dado intervalo de tempo, sendo esse intervalo representado por <data A> e <data B>")/2, "Distância média percorrida, numa determinada cidade, representada por <city>, num dado intervalo de tempo, sendo esse intervalo representado por <data A> e <data B>");
    mvprintw(17, x/2 - strlen("As datas devem ser representadas no formato dd/mm/yyyy. Caso pelo menos uma delas não seja inserida corretamente, terá de repetir o processo.")/2, "As datas devem ser representadas no formato dd/mm/yyyy. Caso pelo menos uma delas não seja inserida corretamente, terá de repetir o processo.");

    mvprintw(20, x/2 - strlen("Introduza a data A: ")/2, "Introduza a data A: ");

    echo();
    char da[40];
    getnstr(da, 40);

    noecho();
    cbreak();

    clear();
    for (int j = 0; j < 11; j++) {
        mvprintw(j + 3, x/2 - strlen(q6_title[j])/2, "%s", q6_title[j]);
    }

    mvprintw(16, x/2 - strlen("Distância média percorrida, numa determinada cidade, representada por <city>, num dado intervalo de tempo, sendo esse intervalo representado por <data A> e <data B>")/2, "Distância média percorrida, numa determinada cidade, representada por <city>, num dado intervalo de tempo, sendo esse intervalo representado por <data A> e <data B>");
    mvprintw(17, x/2 - strlen("As datas devem ser representadas no formato dd/mm/yyyy. Caso pelo menos uma delas não seja inserida corretamente, terá de repetir o processo.")/2, "As datas devem ser representadas no formato dd/mm/yyyy. Caso pelo menos uma delas não seja inserida corretamente, terá de repetir o processo.");

    mvprintw(20, x/2 - strlen("Introduza a data B: ")/2, "Introduza a data B: ");

    echo();
    char db[40];
    getnstr(db, 40);

    noecho();
    cbreak();

    char* city = strdup(s);

    printbox6(x);

    if (!is_in_hash_cities (catalog_cities,city)) mvprintw(40, x/2 - 10, "Cidade não encontrada");    
    else {
        char* city_query = strdup (city);
        double distancia_media = 0;
        unsigned short int dateinf = convert_to_day (da);
        unsigned short int datesup = convert_to_day (db);

        if (dateinf == 65535 || datesup == 65535) {
            clear();
            query6_menu(catalog_users, catalog_drivers, catalog_rides, catalog_cities, x, y);
        }

        distancia_media = get_average_distance (catalog_cities,catalog_rides, city_query,dateinf,datesup);
        if (distancia_media !=0) mvprintw(40, x/2 - 3, "%.3f", distancia_media);
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
            query6_menu(catalog_users, catalog_drivers, catalog_rides, catalog_cities, x, y);
        }
    }
}