#include <ncurses.h>
#include <ctype.h>
#include <string.h>
#include "../includes/interactmode.h"
#include "../includes/users_services.h"

char q3_title [11][100] = {"   /$$$$$$                                                 /$$$$$$",
                           " /$$__  $$                                               /$$__  $$",
                           "| $$  | $$ /$$   /$$  /$$$$$$   /$$$$$$  /$$   /$$      |__/  | $$",
                           "| $$  | $$| $$  | $$ /$$__  $$ /$$__  $$| $$  | $$         /$$$$$/",
                           "| $$  | $$| $$  | $$| $$$$$$$$| $$  |__/| $$  | $$        |___  $$",
                           "| $$/$$ $$| $$  | $$| $$_____/| $$      | $$  | $$       /$$  | $$",
                           "|  $$$$$$/|  $$$$$$/|  $$$$$$$| $$      |  $$$$$$$      |  $$$$$$/",
                           "|_____ $$$|_______/ |________/|__/      |____  $$       |______/ ",
                           "      |__/                               /$$  | $$                ",
                           "                                        |  $$$$$$/                ",
                           "                                        |______/                  "};

void q3_output (Catalog_Users *catalog_users, Catalog_Drivers *catalog_drivers, Catalog_Rides *catalog_rides, Catalog_Cities *catalog_cities, int n, int x, int y) {
    int pages = (n / 30) + 1;
    int done = 0;
    int page = 0;

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
        mvprintw(9, 27,"Username                                                       Nome                                                       Distância                         ");
        for (int i = start; i < end; i++) {
            if (a % 31 == 0) a *= 0;
            char* id = get_top_N_users_id(catalog_users, i);
            if (getAccountStatusUser(catalog_users, id)) {
                mvprintw(a + 11, 22, "%s", id);
                mvprintw(a + 11, 81, "%s", getNameUser(catalog_users, id));
                mvprintw(a + 11, 152 , "%d", get_top_N_users_distance(catalog_users, i));
                mvprintw(a+11, 61, "|");
                mvprintw(a+11, 122, "|");
                mvprintw(a+11, 183, "|");
                a++;
            }
            else {
                end++;
                free(id);
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

void query3_menu(Catalog_Users *catalog_users, Catalog_Drivers *catalog_drivers, Catalog_Rides *catalog_rides, Catalog_Cities *catalog_cities, int x, int y) {
    for (int j = 0; j < 11; j++) {
            mvprintw(j + 3, x/2 - strlen(q3_title[j])/2, "%s", q3_title[j]);
    }

    mvprintw(16, x/2 - strlen("Listar os N utilizadores com maior distância viajada. Em caso de empate, o resultado é ordenado de forma a que os utilizadores com a viagem mais recente surjam primeiro.")/2, "Listar os N utilizadores com maior distância viajada. Em caso de empate, o resultado é ordenado de forma a que os utilizadores com a viagem mais recente surjam primeiro.");
    mvprintw(17, x/2 - strlen("Caso haja novo empate, é usado o username do utilizador para desempatar (por ordem crescente).")/2, "Caso haja novo empate, é usado o username do utilizador para desempatar (por ordem crescente).");
    mvprintw(29, x/2 - strlen("Introduza o top N desejado: ")/2 - 10, "Introduza o top N desejado: ");

    echo();
    char s[40];
    getnstr(s, 40);
    int n = atoi(s);

    noecho();
    cbreak();

    q3_output (catalog_users, catalog_drivers, catalog_rides, catalog_cities, n, x, y);

}                                                                   
                                                                