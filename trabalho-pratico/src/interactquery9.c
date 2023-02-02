#include <ncurses.h>
#include "../includes/interactmode.h"
#include "../includes/dates.h"
#include "../includes/rides_services.h"

char q9_title[11][100] = {"    /$$$$$$                                                 /$$$$$$ ",
                          "   /$$__  $$                                               /$$__  $$",
                          "  | $$  | $$ /$$   /$$  /$$$$$$   /$$$$$$  /$$   /$$      | $$  | $$",
                          "  | $$  | $$| $$  | $$ /$$__  $$ /$$__  $$| $$  | $$      |  $$$$$$$",
                          "  | $$  | $$| $$  | $$| $$$$$$$$| $$  |__/| $$  | $$       |____  $$",
                          "  | $$/$$ $$| $$  | $$| $$_____/| $$      | $$  | $$       /$$  | $$",
                          "  |  $$$$$$/|  $$$$$$/|  $$$$$$$| $$      |  $$$$$$$      |  $$$$$$/",
                          "   |____ $$$ |______/  |_______/|__/       |____  $$       |______/ ",
                          "       |__/                               /$$  | $$                 ",
                          "                                         |  $$$$$$/                 ",
                          "                                          |______/                  "};

void q9_output(Catalog_Users *catalog_users, Catalog_Drivers *catalog_drivers, Catalog_Rides *catalog_rides, Catalog_Cities *catalog_cities, unsigned short int dateinf, unsigned short int datesup, int x, int y) {
    int array_size = get_top_dist_length(catalog_rides);
    int length = 0;
    unsigned short int date;
    for (int i = 0; i < array_size; i++) {
        date = get_ride_dateint_dist (catalog_rides, i);
        if (date >= dateinf && date <= datesup) length++;
    }
    int pages;
    if (length % 30 == 0) pages = length / 30;
    else pages = length / 30 + 1;
    int done = 0;
    int page = 0;

    unsigned short int dateaux;
    char* date_string;
    int array_rides_index;
    char* city;
    int ride_id;
    unsigned short int distance;
    double tip;


    keypad(stdscr, TRUE);

    while (!done) {
        clear();
        
        int start = page * 30;
        int end = start + 30;
        if (end > length) {
            end = length;
        }
        
        mvprintw(45, x/2 - strlen ("Page 1 / 1")/2 , "Page %d / %d", page + 1, pages);
        int a = 0;
        mvprintw(9, 27,"          ID Viagem          |          Data Viagem          |          Distância          |          Cidade          |          Gorjeta          ");
        for (int i = start; i < end; i++) {
            if (a % 31 == 0) a *= 0;
            dateaux = get_ride_dateint_dist (catalog_rides, i);           
            if (dateaux >= dateinf && dateaux <= datesup) {
                ride_id = get_ride_id_dist(catalog_rides, i);
                array_rides_index = get_array_rides_index_dist (catalog_rides, i);
                distance = get_ride_dist_dist(catalog_rides, i);
                city = get_ride_city (catalog_rides, array_rides_index);
                tip = get_ride_tip(catalog_rides, array_rides_index);
                date_string = convert_to_date(date);
                mvprintw(a + 11, 33, "%012d", ride_id + 1);
                mvprintw(a + 11, 63, "%s", date_string);
                mvprintw(a + 11, 100 , "%d", distance);
                mvprintw(a + 11, 127, "%s", city);
                mvprintw(a + 11, 158, "%.3f", tip);
                free (city);
                free (date_string);
                a++;
            }

        }
        
        mvprintw(50, x/2 - strlen("Pressione 'N' para ver a próxima página, 'B' para a página anterior, 'Q' para voltar ao Menu Inicial")/2 , "Pressione 'N' para ver a próxima página, 'B' para a página anterior, 'Q' para voltar ao Menu Inicial");
        int ch = getch();
        switch (ch) {
        case 'n':
        case 'N':
            page++;
            if (page >= pages) {
            page = pages - 1;
            }
            break;
        case 'b':
        case 'B':
            page--;
            if (page < 0) {
            page = 0;
            }
            break;
        case 'q':
        case 'Q':
            done = 1;
            clear();
            queries_menu(x, y, catalog_users, catalog_drivers, catalog_rides, catalog_cities);
        }
    }
}   

void query9_menu(Catalog_Users *catalog_users, Catalog_Drivers *catalog_drivers, Catalog_Rides *catalog_rides, Catalog_Cities *catalog_cities, int x, int y) {
    for (int j = 0; j < 11; j++) {
        mvprintw(j + 3, x/2 - strlen(q9_title[j])/2, "%s", q9_title[j]);
    }
    mvprintw(16, x/2 - strlen("Listar as viagens nas quais o passageiro deu gorjeta, no intervalo de tempo (data A, data B), sendo esse intervalo representado pelos parâmetros <data A> e <data B>, ordenadas por ordem de")/2, "Listar as viagens nas quais o passageiro deu gorjeta, no intervalo de tempo (data A, data B), sendo esse intervalo representado pelos parâmetros <data A> e <data B>, ordenadas por ordem de");
    mvprintw(17, x/2 - strlen("distância percorrida (em ordem decrescente). Em caso de empate, as viagens mais recentes aparecerão primeiro. Se persistirem empates, ordenar pelo id da viagem (em ordem decrescente)")/2, "distância percorrida (em ordem decrescente). Em caso de empate, as viagens mais recentes aparecerão primeiro. Se persistirem empates, ordenar pelo id da viagem (em ordem decrescente)");
    mvprintw(18, x/2 - strlen("Caso a data seja inválida terá de repetir o processo")/2, "Caso a data seja inválida terá de repetir o processo");

    mvprintw(20, x/2 - strlen("Introduza a data A: ")/2 - 12, "Introduza a data A: ");

    echo();
    char da[20];
    getnstr(da, 20);

    noecho();
    cbreak();

    clear();
    for (int j = 0; j < 11; j++) {
        mvprintw(j + 3, x/2 - strlen(q9_title[j])/2, "%s", q9_title[j]);
    }
    mvprintw(16, x/2 - strlen("Listar as viagens nas quais o passageiro deu gorjeta, no intervalo de tempo (data A, data B), sendo esse intervalo representado pelos parâmetros <data A> e <data B>, ordenadas por ordem de")/2, "Listar as viagens nas quais o passageiro deu gorjeta, no intervalo de tempo (data A, data B), sendo esse intervalo representado pelos parâmetros <data A> e <data B>, ordenadas por ordem de");
    mvprintw(17, x/2 - strlen("distância percorrida (em ordem decrescente). Em caso de empate, as viagens mais recentes aparecerão primeiro. Se persistirem empates, ordenar pelo id da viagem (em ordem decrescente)")/2, "distância percorrida (em ordem decrescente). Em caso de empate, as viagens mais recentes aparecerão primeiro. Se persistirem empates, ordenar pelo id da viagem (em ordem decrescente)");
    mvprintw(18, x/2 - strlen("Caso a data seja inválida terá de repetir o processo")/2, "Caso a data seja inválida terá de repetir o processo");

    mvprintw(20, x/2 - strlen("Introduza a data B: ")/2 - 12, "Introduza a data B: ");

    echo();
    char db[20];
    getnstr(db, 20);

    noecho();
    cbreak();

    unsigned short int dateinf = convert_to_day (da);
    unsigned short int datesup = convert_to_day (db);    
    
    if (dateinf == 65535 || datesup == 65535) query9_menu(catalog_users, catalog_drivers, catalog_rides, catalog_cities, x, y);

    q9_output(catalog_users, catalog_drivers, catalog_rides, catalog_cities, dateinf, datesup, x, y);
}