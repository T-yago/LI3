#include "../includes/interactmode.h"
#include <ncurses.h>
#include <string.h>
#include "../includes/cities.h"
#include "../includes/data.h"
#include "../includes/drivers_services.h"
#include "../includes/interactquery1.h"
#include "../includes/interactquery2.h"
#include "../includes/interactquery3.h"
#include "../includes/interactquery4.h"
#include "../includes/interactquery5.h"
#include "../includes/interactquery6.h"
#include "../includes/interactquery7.h"
#include "../includes/interactquery8.h"
#include "../includes/interactquery9.h"

char qm_title [11][110] = {"  /$$$$$$                                                /$$      /$$                              ",
                           " /$$__  $$                                              | $$$    /$$$                              ",
                           "| $$  | $$ /$$   /$$  /$$$$$$   /$$$$$$  /$$   /$$      | $$$$  /$$$$  /$$$$$$  /$$$$$$$  /$$   /$$",
                           "| $$  | $$| $$  | $$ /$$__  $$ /$$__  $$| $$  | $$      | $$ $$/$$ $$ /$$__  $$| $$__  $$| $$  | $$",
                           "| $$  | $$| $$  | $$| $$$$$$$$| $$  |__/| $$  | $$      | $$  $$$| $$| $$$$$$$$| $$  | $$| $$  | $$",
                           "| $$/$$ $$| $$  | $$| $$_____/| $$      | $$  | $$      | $$   $ | $$| $$_____/| $$  | $$| $$  | $$",
                           "|  $$$$$$/|  $$$$$$/|  $$$$$$$| $$      |  $$$$$$$      | $$/    | $$|  $$$$$$$| $$  | $$|  $$$$$$/",
                           "|_____ $$$|_______/ |________/|__/      |_____  $$      |__/     |__/|________/|__/  |__/|_______/ ",
                           "     |___/                              /$$  | $$/                                                 ",
                           "                                       |  $$$$$$/                                                   ",
                           "                                       |_______/                                                    "};
void exitprogram(Catalog_Users *catalog_users, Catalog_Drivers *catalog_drivers, Catalog_Rides *catalog_rides, Catalog_Cities *catalog_cities) {
    free_users_catalog (catalog_users);
    free_drivers_catalog (catalog_drivers);
    free_rides_catalog (catalog_rides);
    free_cities_catalog (catalog_cities);
    endwin();
    exit(0);
}
void query_selection(int n, int x, int y, Catalog_Users *catalog_users, Catalog_Drivers* catalog_drivers, Catalog_Rides *catalog_rides, Catalog_Cities *catalog_cities) {
    switch(n) {
        case 0:
            clear();
            query1_menu(catalog_users, catalog_drivers, catalog_rides, catalog_cities, x, y);
            break;
        case 1:
            clear();
            query2_menu(catalog_users, catalog_drivers, catalog_rides, catalog_cities, x, y);
            break;
        case 2:
            clear();
            query3_menu(catalog_users, catalog_drivers, catalog_rides, catalog_cities, x, y);
            break;
        case 3:
            clear();
            query4_menu(catalog_users, catalog_drivers, catalog_rides, catalog_cities, x, y);
            break;
        case 4:
            clear();
            query5_menu(catalog_users, catalog_drivers, catalog_rides, catalog_cities, x, y);
            break;
        case 5:
            clear();
            query6_menu(catalog_users, catalog_drivers, catalog_rides, catalog_cities, x, y);
            break;
        case 6:
            clear();
            query7_menu(catalog_users, catalog_drivers, catalog_rides, catalog_cities, x, y);
            break;
        case 7:
            clear();
            query8_menu(catalog_users, catalog_drivers, catalog_rides, catalog_cities, x, y);
            break;
        case 8:
            clear();
            query9_menu(catalog_users, catalog_drivers, catalog_rides, catalog_cities, x, y);
            break;
        case 9:
            exitprogram(catalog_users, catalog_drivers, catalog_rides, catalog_cities);
    }
}

void queries_menu(int x, int y, Catalog_Users *catalog_users, Catalog_Drivers* catalog_drivers, Catalog_Rides *catalog_rides, Catalog_Cities *catalog_cities) {
                     
    char options[10][30] = {"Query 1", "Query 2", "Query 3", "Query 4", "Query 5", "Query 6", "Query 7", "Query 8", "Query 9", "SAIR"};

    int highlight = 0;
    int choice;
    int num_options = 10;

    while(1) {
        for (int j = 0; j < 11; j++) {
            mvprintw(j + 3, x/2 - strlen(qm_title[j])/2, "%s", qm_title[j]);
        }
        for (int i = 0; i < num_options; i++) {
            if (i == highlight) {
                attron(A_REVERSE | A_BOLD);
            }
            mvprintw(y/2 - 10 + 2*i, x/2 - strlen(options[i])/2, "%s", options[i]);
            attroff(A_REVERSE | A_BOLD);
        }

        mvprintw(y/2 + 11, x/2 - strlen("Pressione Enter para selecionar uma das queries")/2, "Pressione Enter para selecionar uma das queries");
        mvprintw(y/2 + 12, x/2 - strlen("Use as setas Cima e Baixo para escolher uma das opções")/2, "Use as setas Cima e Baixo para escolher uma das opções"); 

        choice = getch();

        switch(choice) {
            case KEY_UP:
                if(highlight == 0)
                    highlight = num_options-1;
                else
                    --highlight;
                break;
            case KEY_DOWN:
                if(highlight == num_options-1)
                    highlight = 0;
                else
                    ++highlight;
                break;
            case 10:
                query_selection(highlight, x, y, catalog_users, catalog_drivers, catalog_rides, catalog_cities);
                break;            
        }
    }
}

int interactmode() {
    char pathfiles[100];

    initscr();    /* Start curses mode */
    printw("Enter file path: "); /* Prompt for file path */
    refresh();    /* Print prompt on screen */
    getnstr(pathfiles, 100); /* Get input from user and store in filepath */

    //criação dos catálogos
    Catalog_Users * catalog_users = users_catalog(pathfiles);
    initHash_users(catalog_users);
    
    Catalog_Drivers * catalog_drivers = drivers_catalog(pathfiles);
    init_array_drivers(catalog_drivers);
    
    Catalog_Rides * catalog_rides = rides_catalog(pathfiles);
    //init_array_genders (catalog_rides);
    
    Catalog_Cities * catalog_cities = cities_catalog ();
    fill_data (catalog_users,catalog_drivers,catalog_rides,catalog_cities);
    
    //criação das estruturas auxiliares para as queries
    top_N_drivers (catalog_drivers);  // talvez mudar de sítio
    top_N_users (catalog_users);   

    clear();

    cbreak();
    noecho();
    keypad(stdscr, true);

    int x, y;
    getmaxyx(stdscr, y, x);

    queries_menu(x,y, catalog_users, catalog_drivers, catalog_rides, catalog_cities);
    
    getch();
    endwin();

    return 0;
} 

// ../../../Dataset/DatasetFase1