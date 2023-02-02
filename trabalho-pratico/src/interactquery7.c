#include <ncurses.h>
#include "../includes/interactmode.h"
#include "../includes/cities_services.h"

char q7_title[11][100] = {"      $$$$$$                                                /$$$$$$$$",
                          "    /$$__  $$                                              |_____ $$/",
                          "   | $$  | $$ /$$   /$$  /$$$$$$   /$$$$$$  /$$   /$$           /$$/ ",
                          "   | $$  | $$| $$  | $$ /$$__  $$ /$$__  $$| $$  | $$          /$$/  ",
                          "   | $$  | $$| $$  | $$| $$$$$$$$| $$  |__/| $$  | $$         /$$/   ",
                          "   | $$/$$ $$| $$  | $$| $$_____/| $$      | $$  | $$        /$$/    ",
                          "   |  $$$$$$/|  $$$$$$/|  $$$$$$$| $$      |  $$$$$$$       /$$/     ",
                          "   |_____ $$$|_______/ |________/|__/      |_____  $$      |__/      ",
                          "         |__/                               /$$  | $$                ",
                          "                                           |  $$$$$$/                ",
                          "                                            |______/                 "};

void q7_output (Catalog_Users *catalog_users, Catalog_Drivers *catalog_drivers, Catalog_Rides *catalog_rides, Catalog_Cities *catalog_cities, char* city, int n, int x, int y) {
    int pages;
    if (n % 30 == 0) pages = n / 30;
    else pages = n / 30 + 1;
    int done = 0;
    int page = 0;
    char* city_query = strdup(city);

    keypad(stdscr, TRUE);

    while (!done) {
        clear();
        
        int start = page * 30;
        int end = start + 30;
        if (end > n) {
            end = n;
        }
        
        mvprintw(45, x/2 - strlen ("Page 1 / 1")/2 , "Page %d / %d", page + 1, pages);
        int a = 0;
        mvprintw(9, 27,"ID                                                           Nome                                                       Avaliacao Media                         ");
        for (int i = start; i < end; i++) {
            if (a % 31 == 0) a *= 0;
            uint id_driver = get_id_driver_from_ordered_array (catalog_cities, city_query, i);
      
            if (get_driver_acc_Status (catalog_drivers, id_driver -1) == true) 
            {   
                char* name = get_driver_name(catalog_drivers, id_driver - 1);
                mvprintw(a + 11, 22, "%012d", id_driver);
                mvprintw(a + 11, 81, "%s", name);
                mvprintw(a + 11, 152 , "%.3f", get_aval_med_from_ordered_array(catalog_cities, city_query, i));
                mvprintw(a+11, 61, "|");
                mvprintw(a+11, 122, "|");
                mvprintw(a+11, 183, "|");
                a++;
                free (name);
            }
            else end++;
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
            free(city_query);
            done = 1;
            clear();
            queries_menu(x, y, catalog_users, catalog_drivers, catalog_rides, catalog_cities);
        }
    }
}

void query7_menu(Catalog_Users *catalog_users, Catalog_Drivers *catalog_drivers, Catalog_Rides *catalog_rides, Catalog_Cities *catalog_cities, int x, int y) {
    for (int j = 0; j < 11; j++) {
            mvprintw(j + 3, x/2 - strlen(q7_title[j])/2, "%s", q7_title[j]);
    }

    mvprintw(16, x/2 - strlen("Top N condutores numa determinada cidade, representada por <city> (no ficheiro rides.csv), ordenado pela avaliação média do condutor. Em caso de empate, o resultado será ordenado através do id do condutor, de forma decrescente.")/2, "Top N condutores numa determinada cidade, representada por <city> (no ficheiro rides.csv), ordenado pela avaliação média do condutor. Em caso de empate, o resultado será ordenado através do id do condutor, de forma decrescente.");
    mvprintw(20, x/2 - strlen("Introduza o Top N desejado: ")/2, "Introduza o Top N desejado: ");

    echo();
    char s[40];
    getnstr(s, 40);
    int n = atoi(s);

    noecho();
    cbreak();

    clear();
    for (int j = 0; j < 11; j++) {
        mvprintw(j + 3, x/2 - strlen(q7_title[j])/2, "%s", q7_title[j]);
    }

    mvprintw(16, x/2 - strlen("Top N condutores numa determinada cidade, representada por <city> (no ficheiro rides.csv), ordenado pela avaliação média do condutor. Em caso de empate, o resultado será ordenado através do id do condutor, de forma decrescente.")/2, "Top N condutores numa determinada cidade, representada por <city> (no ficheiro rides.csv), ordenado pela avaliação média do condutor. Em caso de empate, o resultado será ordenado através do id do condutor, de forma decrescente.");
    mvprintw(17, x/2 - strlen("Caso o nome da cidade não conste da base de dados, terá de repetir o processo novamente.")/2, "Caso o nome da cidade não conste da base de dados, terá de repetir o processo novamente.");
    mvprintw(20, x/2 - strlen("Introduza a cidade pretendida: ")/2, "Introduza a cidade pretendida: ");

    echo();
    char c[40];
    getnstr(c, 40);

    if (!is_in_hash_cities (catalog_cities, c)) {
        clear();
        query7_menu(catalog_users, catalog_drivers, catalog_rides, catalog_cities, x, y);
    }

    noecho();
    cbreak();

    q7_output(catalog_users, catalog_drivers, catalog_rides, catalog_cities, c, n, x, y);
}
