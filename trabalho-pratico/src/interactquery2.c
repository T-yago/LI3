#include <ncurses.h>
#include <ctype.h>
#include <string.h>
#include "../includes/interactmode.h"
#include "../includes/drivers_services.h"

char q2_title [11][100] = {" $$$$$$$                                                 $$$$$$$  ", 
                           "$$  __$$                                                $$  __$$$ ",
                           "$$ /  $$ |$$   $$$  $$$$$$$   $$$$$$$   $$ |  $$ |      |__/  $$$ |",
                           "$$ |  $$ |$$ |  $$ |$$  __$$$ $$  __$$_ $$ |  $$ |       $$$$$$  |",
                           "$$ |  $$ |$$ |  $$ |$$$$$$$$ |$$ |  |__|$$ |  $$ |      $$  ____/ ",
                           "$$ $$$$$ |$$ |  $$ |$$   ____|$$ |      $$ |  $$ |      $$ |      ",
                           "$$$$$$$ /|$$$$$$$/ |$$$$$$$$$ $$ |      $$$$$$$$ |      $$$$$$$$$ ",
                           " |___$$$||_______/ |________||__|       |_____$$ |      |________|",
                           "     |___|                              $$|   $$ |                ",
                           "                                        |$$$$$$$ |                ",
                           "                                         |______/                 "};

void q2_output (Catalog_Users *catalog_users, Catalog_Drivers *catalog_drivers, Catalog_Rides *catalog_rides, Catalog_Cities *catalog_cities, int n, int x, int y) {
    int pages;
    if (n % 30 == 0) pages = n / 30;
    else pages = n / 30 + 1;
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
        mvprintw(9, 27,"ID                                                           Nome                                                       Avaliacao Media                         ");
        for (int i = start; i < end; i++) {
            if (a % 31 == 0) a *= 0;
            mvprintw(a + 11, 22, "%012d", get_id_driver_top_N(catalog_drivers, i));
            mvprintw(a + 11, 81, "%s", get_name_driver_top_N(catalog_drivers, i));
            mvprintw(a + 11, 152 , "%.3f", get_aval_med_top_N(catalog_drivers, i));
            mvprintw(a+11, 61, "|");
            mvprintw(a+11, 122, "|");
            mvprintw(a+11, 183, "|");
            a++;
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

void query2_menu(Catalog_Users *catalog_users, Catalog_Drivers *catalog_drivers, Catalog_Rides *catalog_rides, Catalog_Cities *catalog_cities, int x, int y) {
    for (int j = 0; j < 11; j++) {
            mvprintw(j + 3, x/2 - strlen(q2_title[j])/2, "%s", q2_title[j]);
    }
    mvprintw(16, x/2 - strlen("Listar os N condutores com maior avaliação média. Em caso de empate, o resultado é ordenado de forma a que os condutores com a viagem mais recente surjam primeiro.")/2, "Listar os N condutores com maior avaliação média. Em caso de empate, o resultado é ordenado de forma a que os condutores com a viagem mais recente surjam primeiro.");
    mvprintw(17, x/2 - strlen("Caso haja novo empate, é usado o id do condutor para desempatar (por ordem crescente)")/2, "Caso haja novo empate, é usado o id do condutor para desempatar (por ordem crescente)");
    mvprintw(19, x/2 - strlen("O output dará o top N com o id do condutor, nome e avaliação média")/2, "O output dará o top N com o id do condutor, nome e avaliação média");
    mvprintw(29, x/2 - strlen("Introduza o top N desejado: ")/2 - 10, "Introduza o top N desejado: ");

    echo();
    char s[40];
    getnstr(s, 40);
    int n = atoi(s);

    noecho();
    cbreak();

    clear();

    q2_output (catalog_users, catalog_drivers, catalog_rides, catalog_cities, n, x, y);
    
    getch();
}